#ifndef TERMINAL_H
#define TERMINAL_H
#include <std/types.h>
typedef struct {
    uint8_t pos_x, pos_y;
    uint8_t width, height;
    uint8_t fg_color, bg_color;
} cursor_t;
void print(char* string);
void print_num(int value, int base);
void kprintf(char* format, ...);
void print_pos();
void set_foreground(uint8_t fg);
void set_background(uint8_t bg);
void clr();
#endif