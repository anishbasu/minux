
#include <vga/vga.h>
#include <util/hex.h>
#include <util/multiboot.h>
#include <std/types.h>
#include <terminal/terminal.h>
/*void draw_screen() {
    fb_clear_buffer(VGA_BLACK);
    fb_write_string(VGA_SCREEN_WIDTH / 2 - 4, VGA_SCREEN_HEIGHT / 2, "Minux OS", VGA_CYAN, VGA_BLACK);
    fb_write_string(VGA_SCREEN_WIDTH / 2 - 7, VGA_SCREEN_HEIGHT / 2 + 1, "CS 370 Hobby OS", VGA_WHITE, VGA_BLACK);
    fb_move_cursor(10, 0);
    //fb_disable_cursor();
}*/

int kmain() {
    init_term();
    print("Testing");
    print("Testing\nTesting");
    print("Should be on a new line\n");
    while(1);
    return 0;
}