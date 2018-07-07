#include <error/kernel_errors.h>
#include <cpu/irq.h>
void register_errors() {
    set_interrupt_handler(0x0, div_by_zero_error);
}