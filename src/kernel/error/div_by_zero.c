#include <terminal/terminal.h>
#include <cpu/irq.h>
#include <error/kernel_errors.h>
void div_by_zero_error(struct InterruptFrame* frame) {
    print("DIVIDE BY ZERO CAUGHT!");
    asm("hlt");
}