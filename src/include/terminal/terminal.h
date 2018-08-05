#ifndef TERMINAL_H
#define TERMINAL_H
typedef struct {
    int pos_x, pos_y;
    int width, height;
    int fg_color, bg_color;
} cursor_t;
void print(char* string);
void print_num(int value, int base);
void kprintf(char* format, ...);
#endif