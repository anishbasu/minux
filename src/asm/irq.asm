extern interrupt_router
extern gdt64
section .text
bits 64
;IRQ Macros
%macro irq_handle_interrupt 1
    global irq_%1 ;global so that we can access it from C
    irq_%1: ;Create a function for each IRQ line
        cli
        mov rdi, dword %1 ;Send ID
        jmp _irq_middleware_bounce
%endmacro

_irq_middleware_bounce:
    cli
    push rdi
    push rsi
    push rdx
    push rcx
    push rax
    push  r8
    push  r9
    push r10
    push r11
    ; Interrupt ID has already been sent
    mov rsi, rsp ;Send interrupt frame
    call interrupt_router
    pop  r11
    pop  r10
    pop   r9
    pop   r8
    pop  rax
    pop  rcx
    pop  rdx
    pop  rsi
    pop  rdi
    sti
    iretq

irq_handle_interrupt 0
irq_handle_interrupt 1
irq_handle_interrupt 2
irq_handle_interrupt 3
irq_handle_interrupt 4
irq_handle_interrupt 5
irq_handle_interrupt 6
irq_handle_interrupt 7
irq_handle_interrupt 8
irq_handle_interrupt 9
irq_handle_interrupt 10
irq_handle_interrupt 11
irq_handle_interrupt 12
irq_handle_interrupt 13
irq_handle_interrupt 14
irq_handle_interrupt 15
irq_handle_interrupt 16
irq_handle_interrupt 17
irq_handle_interrupt 18
irq_handle_interrupt 19
irq_handle_interrupt 20
irq_handle_interrupt 21
irq_handle_interrupt 22
irq_handle_interrupt 23
irq_handle_interrupt 24
irq_handle_interrupt 25
irq_handle_interrupt 26
irq_handle_interrupt 27
irq_handle_interrupt 28
irq_handle_interrupt 29
irq_handle_interrupt 30
irq_handle_interrupt 31
irq_handle_interrupt 32
irq_handle_interrupt 33
irq_handle_interrupt 34
irq_handle_interrupt 35
irq_handle_interrupt 36
irq_handle_interrupt 37
irq_handle_interrupt 38
irq_handle_interrupt 39
irq_handle_interrupt 40
irq_handle_interrupt 41
irq_handle_interrupt 42
irq_handle_interrupt 43
irq_handle_interrupt 44
irq_handle_interrupt 45
irq_handle_interrupt 46
irq_handle_interrupt 47
irq_handle_interrupt 48
irq_handle_interrupt 49
irq_handle_interrupt 50
irq_handle_interrupt 51
irq_handle_interrupt 52
irq_handle_interrupt 53
irq_handle_interrupt 54
irq_handle_interrupt 55
irq_handle_interrupt 56
irq_handle_interrupt 57
irq_handle_interrupt 58
irq_handle_interrupt 59
irq_handle_interrupt 60
irq_handle_interrupt 61
irq_handle_interrupt 62
irq_handle_interrupt 63
irq_handle_interrupt 64