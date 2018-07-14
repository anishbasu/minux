#ifndef KERNEL_ERRORS
#define KERNEL_ERRORS
#include <cpu/irq.h>
void register_errors();
void div_by_zero_error(struct InterruptFrame * frame);
#endif