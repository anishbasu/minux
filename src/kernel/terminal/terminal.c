#include <vga/vga.h>
#include <std/string.h>
#include <terminal/terminal.h>
#include <std/stdarg.h>
volatile cursor_t cursor = {
    .pos_x = 0,
    .pos_y = 0,
    .width = VGA_SCREEN_WIDTH,
    .height = VGA_SCREEN_HEIGHT,
    .fg_color = VGA_LIGHT_GRAY,
    .bg_color = VGA_BLACK
};

void print_num(int value, int base) {
    char buf[32];
    switch(base) {
        case 2:
            print("b");
            break;
        case 8:
            print("0");
            break;
        case 16:
            print("0x");
            break;
    }
    print(itoa(value,buf,base));
}

void set_foreground(uint8_t fg) {
    cursor.fg_color = fg;
}

void set_background(uint8_t bg) {
    cursor.bg_color = bg;
}

void clr() {
    fb_clear_buffer(cursor.fg_color, cursor.bg_color);
    cursor.pos_x = 0;
    cursor.pos_y = 0;
}
void print(char* string) {
    int i = 0;
    while(string[i] != 0){
        if(string[i] == '\n'){
            cursor.pos_x = 0;
            cursor.pos_y += 1;
        } else {
            if(cursor.pos_x == cursor.width){
                cursor.pos_x = 0;
                cursor.pos_y++;
            }
            fb_write_cell(fb_get_pos(cursor.pos_x, cursor.pos_y), string[i], cursor.fg_color, cursor.bg_color);
            cursor.pos_x++;
        }
        i++;
    }
    fb_move_cursor(cursor.pos_x, cursor.pos_y);
}

void print_pos() {
    kprintf("pos: %d, x:%d y:%d\n", fb_get_pos(cursor.pos_x, cursor.pos_y), cursor.pos_x, cursor.pos_y);
}
void kprintf(char* format, ...) {
    __gnuc_va_list data;
    va_start(data, format);
    for(;*format; format++) {
        char c = *format;
        switch(c) {
            case '\n':
                cursor.pos_x = 0;
                cursor.pos_y += 1;
                break;
            case '\r':
                cursor.pos_x = 0;
                break;
            case '%':
                format++;
                c = *format;
                switch(c) {
                    case 'c':
                        fb_write_cell(fb_get_pos(cursor.pos_x, cursor.pos_y), (char) va_arg(data, int), cursor.fg_color, cursor.bg_color);
                        cursor.pos_x+=1;
                        break;
                    case 's':
                        kprintf(va_arg(data, char*));
                        break;
                    case 'd':
                        print_num(va_arg(data, int), 10);
                        break;
                    case 'x':
                        print_num(va_arg(data, int), 16);
                        break;
                }
                break;
            default:
                fb_write_cell(fb_get_pos(cursor.pos_x, cursor.pos_y), c, cursor.fg_color, cursor.bg_color);
                cursor.pos_x++;
        }

        if(cursor.pos_y >= VGA_SCREEN_HEIGHT) {
            cursor.pos_y = VGA_SCREEN_HEIGHT - 1;
            fb_scroll(cursor.fg_color, cursor.bg_color);
        }
    }
    fb_move_cursor(cursor.pos_x, cursor.pos_y);
}