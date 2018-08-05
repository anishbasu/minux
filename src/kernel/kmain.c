
#include <vga/vga.h>
#include <util/multiboot.h>
#include <std/types.h>
#include <terminal/terminal.h>
#include <cpu/irq.h>
#include <error/kernel_errors.h>
#include <irq_handlers/timer.h>

int kmain() {
    load_IDT();
    register_errors();
    init_pit();
    while(1);
    return 0;
}