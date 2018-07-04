#include <vga/vga.h>
#include <terminal/terminal.h>

struct cursor_t cursor;
void init_term() {
    cursor.pos_x = 0;
    cursor.pos_y = 0;
    cursor.width = 0;
    cursor.height = 0;
}
void print(char* string) {
    int i = 0;
    while(string[i] != 0){
        if(string[i] == '\n'){
            cursor.pos_x = 0;
            cursor.pos_y++;
            i++;
            continue;
        }
        if(cursor.pos_x == 81){
            cursor.pos_x = 0;
            cursor.pos_y++;
        }
        fb_write_cell(fb_get_pos(cursor.pos_x, cursor.pos_y), string[i], VGA_LIGHT_GRAY, VGA_BLACK);
        cursor.pos_x++;
        i++;
    }
    fb_move_cursor(cursor.pos_x, cursor.pos_y);
}