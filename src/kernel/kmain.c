
#include <vga/vga.h>
#include <util/multiboot.h>
#include <std/types.h>
#include <terminal/terminal.h>
#include <cpu/irq.h>
#include <error/kernel_errors.h>

int kmain() {
    init_term();
    print("Testing");
    print("Testing\nTesting");
    print("Should be on a new line\n");
    load_IDT();
    register_errors();
    int i = 1/0;
    while(1);
    return 0;
}