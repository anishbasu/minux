#ifndef TERMINAL_H
#define TERMINAL_H
void print(char* string);
void init_term();
typedef struct cursor {
    int pos_x, pos_y;
    int width, height;
} cursor_t;
#endif