section .multiboot_header
header_start:
    dd 0xE85250D6 ;magic number
    dd 0          ;arch: Protected mode i386
    dd header_end - header_start
    ;checksum
    dd 0x100000000 - (0xE85250D6 + 0 + (header_end - header_start))

    dw 0 ; type
    dw 0 ; flags
    dw 8 ; size
header_end: