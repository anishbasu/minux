
#include "vga/vga.h"

void draw_screen() {
    fb_clear_buffer(VGA_BLACK);
    fb_write_string(VGA_SCREEN_WIDTH / 2 - 4, VGA_SCREEN_HEIGHT / 2, "Minux OS", VGA_CYAN, VGA_BLACK);
    fb_write_string(VGA_SCREEN_WIDTH / 2 - 7, VGA_SCREEN_HEIGHT / 2 + 1, "CS 370 Hobby OS", VGA_WHITE, VGA_BLACK);
}

int main() {
    draw_screen();
    while(1);
    return 0;
}