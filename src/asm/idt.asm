extern handle_interrupt

section .text
bits 64
;IRQ Macros
%macro irq_handle_interrupt 1
    global irq_%1
    irq_%1:
        cli
        mov rdi, dword %1
        jmp _irq_middleware_bounce
%endmacro

_irq_middleware_bounce:
    push rdi
    push rsi
    push rdx
    push rcx
    push rax
    push  r8
    push  r9
    push r10
    push r11
    mov rsi, rsp
    call handle_interrupt
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