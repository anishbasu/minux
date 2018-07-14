# Kicking and Screaming into 32-bit Assembly

We intend to load our simple Operating System using the GRUB2 bootloader. We could make our own bootloader but this being an OS class we will skip that part.

## Setting up GRUB2
We set up the GRUB configuration file as follows:

**isofiles/boot/grub/grub.cfg**

```assembly
set timeout=0
set default=0

menuentry "minux" {
    multiboot2 /boot/kernel.bin
    boot
}
```

This configuration shows the GRUB menu with one menuentry, Minux.
The description of the variables are as follows:

- **timeout** - How long to wait for keyboard in the menu (in seconds)
- **default** - The default entry to boot into (in this case)
- **menuentry** - This defines our OS entry in the GRUB menu. We're usinng Multiboot 2 to load our OS. We point to the file in the file system which contains the OS binary.

## Setting up the Multiboot header
The GRUB bootloader finds our kernel and checks for the header to verify whether it is a valid multiboot header. We define this in pure Assembly as follows:

**asm/multiboot_header.asm**

```assembly
section .multiboot_header

MAGIC equ 0xE85250D6
ARCH equ 0x0

header_start:
    dd MAGIC ;magic number
    dd ARCH         ;arch: Protected mode i386
    dd header_end - header_start
    ;checksum
    dd (1 << 32) - (MAGIC + ARCH + (header_end - header_start))

    dw 0 ; type
    dw 0 ; flags
    dw 8 ; size
header_end:
```

The header consists of the following:

A section label named **multiboot_header**. This is required later in the linking stage to create the binary correctly so that the bootloader can locate and read the file properly.

We define the **header_start** and **header_end** labels to compute the checksums. Inside the header we have 4 things:
- **Magic Number** (0xE85250D6) - Tells the GRUB Bootloader that this is a valid kernel and to start reading the kernel.
- **Architecture** (0x0) - Tells the Bootloader to start in 32-bit protected mode.
- **Length of Header** (header_end - header_start) - Tells the lenngth of the header (for computing flags)
- **Checksum** - Verifies the integrity of the binary.

The rest of the words are flags to set up the CPU. We won't be discussing them here.

## Checking Long Mode using CPUID

In order to load 64 bit instructions, we need to move from 32-bit to 64-bit, but first we need to check whether the CPU itself supports 64-bits. If you are in 2018, and using a relatively recent computer, your CPU is already 64-bit.

**CPUID** is an instruction that is supported by all IA32 compatible CPUs, which tells us a whole lot about the CPU that we are running on. It pushes the CPU flags to the stack. This command takes arguments via the **eax** and supplementary arguments via the **ecx** register.

We use the 0x80000000H argument in the EAX register to initially check the extended CPU flag compatibility. We then compare the CPUID against a known value (0x80000001) for extended CPU Flags.

We then send the 0x80000001 argument in the EAX for extended CPU flags which allow us to test for long mode. This returns the CPU flags in the EAX register. The descriptions for the flags are given [here](https://en.wikipedia.org/wiki/CPUID#EAX=80000001h:_Extended_Processor_Info_and_Feature_Bits). We check whether the 29th bit (lm bit) is set to ascertain presence of long-mode (ie. supports 64 bit instructions).

## Enabling Paging

For the CPU to switch to long mode, we need to map the Page Tables to switch to long mode. We set up the page table entries in the **bss** section as follows:

**asm/boot.asm**

```assembly
align 4096
p4_table:
    resb 4096
p3_table:
    resb 4096
p2_table:
    resb 4096
stack_bottom:
    resb 4096 * 4
stack_top:
```

We set each level of page tables up by first setting the flags in the head of each table to `0b11` which means present and writeable along with the address to the next segment of the page table. The p2 page table is mapped to a bigger address space using the flag `0b10000011` for each segment in 512 segments.

**asm/boot.asm**

```assembly
set_up_page_tables:
    ; map first P4 entry to P3 table
    mov eax, p3_table
    or eax, 0b11 ; present + writable
    mov [p4_table], eax

    ; map first P3 entry to P2 table
    mov eax, p2_table
    or eax, 0b11 ; present + writable
    mov [p3_table], eax
    mov ecx, 0 ; Setup counter
.map_p2_table:
    ; map ecx-th P2 entry to a huge page that starts at address 2MiB*ecx
    mov eax, 0x200000  ; 2MiB
    mul ecx            ; start address of ecx-th page
    or eax, 0b10000011 ; present + writable + huge
    mov [p2_table + ecx * 8], eax ; map ecx-th entry

    inc ecx            ; increase counter
    cmp ecx, 512       ; if counter == 512, the whole P2 table is mapped
    jne .map_p2_table  ; else map the next entry
    ret
```

The paging is enabled first by mappinng the p4 table to the cr3 register (it then discovers the rest using the flags we set up before on the tables), and then setting up the PAE (Physical Address Extension) flags in the cr4 register.

We then read the MSR using the arguments from ECX, and then set the long-mode flag (8th bit) to the Model Specific Register using WRMSR.

Finally, we set the paging flag in the CR0 register to enable paging.

**asm/boot.asm**

```assembly
enable_paging:
    ; load P4 to cr3 register (cpu uses this to access the P4 table)
    mov eax, p4_table
    mov cr3, eax

    ; enable PAE-flag in cr4 (Physical Address Extension)
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ; set the long mode bit in the EFER MSR (model specific register)
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    ; enable paging in the cr0 register
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    ret
```

## Setting up the Global Descriptor Table

Now that we have Paging set up, we can load the Global Descriptor Table and jump into long mode. The global descriptor table defines the code and data sections of the kernel in the memory. We then can load the table using the **lgdt** command using the pointer. We set up the GDT using the following flags:

**asm/boot.asm**

```assembly
.code: equ $ - gdt64
    dq (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53) ; Executable, Code, Present and 64 bit flags set
.data: equ $ - gdt64
    dq (1<<44) | (1<<47) ; Data and Present Flags Set
```

### Possible Flags:

(https://os.phil-opp.com/entering-longmode/)

|Bit |Name      |Description      |
|----|----------|-----------------|
|  42|conforming|The current privilege level can be higher than the specified level for code segments.|
|  43|executable|The segment is executable|
|  44|descriptor type|Should be set for both code and data segments|
|45-46|privilege|Ring level: Can be values from 0 (highest) to 3 (lowest)|
|  47|present   | If the segment is to be counted|
|  53|64-bit    | If the code segment has 64-bit instructions|
|  54|32-bit    | If the code segment has 32-bit instructions|
 

The **code** section is stored in the **cs** register and the data section is stored in the **ds** register.

Now we load the GDT by using the following instruction:

```assembly
lgdt [gdt64.pointer]
```

Then we switch to long mode by calling long-mode code through the code section as follows:

```assembly
jmp gdt64.code:long_mode_start
```