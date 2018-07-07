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