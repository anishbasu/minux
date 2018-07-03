
#include "vga/vga.h"
#include "util/hex.h"
#include "util/multiboot.h"
#include "types.h"
void draw_screen() {
    fb_clear_buffer(VGA_BLACK);
    fb_write_string(VGA_SCREEN_WIDTH / 2 - 4, VGA_SCREEN_HEIGHT / 2, "Minux OS", VGA_CYAN, VGA_BLACK);
    fb_write_string(VGA_SCREEN_WIDTH / 2 - 7, VGA_SCREEN_HEIGHT / 2 + 1, "CS 370 Hobby OS", VGA_WHITE, VGA_BLACK);
    fb_move_cursor(10, 0);
    //fb_disable_cursor();
}

int kmain(unsigned int ptr) {
    char buf[100];
    //multiboot_header_t* header = (multiboot_header_t*) ptr;
    fb_write_string(0,0, itoa(ptr, buf, 16), VGA_CYAN, VGA_BLACK);
    draw_screen();

    while(1);
    return 0;
}