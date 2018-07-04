global long_mode_start
extern kmain
section .text
bits 64
long_mode_start:
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    xor rbp, rbp
    push rbp
    call kmain
    pop rdi
    hlt