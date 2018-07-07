#ifndef KERNEL_ERRORS
#define KERNEL_ERRORS
void register_errors();
void div_by_zero_error(struct InterruptFrame* frame);
#endif