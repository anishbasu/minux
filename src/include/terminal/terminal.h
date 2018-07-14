#ifndef TERMINAL_H
#define TERMINAL_H
void print(char* string);
typedef struct cursor {
    int pos_x, pos_y;
    int width, height;
} cursor_t;
void init_term();
#endif