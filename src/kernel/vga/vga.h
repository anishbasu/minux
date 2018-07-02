#ifndef VGA_H
#define VGA_H
#define VGA_FB_ADDR  0xB8000
#define VGA_BLACK          0
#define VGA_BLUE           1
#define VGA_GREEN          2
#define VGA_CYAN           3
#define VGA_RED            4
#define VGA_MAGENTA        5
#define VGA_BROWN          6
#define VGA_LIGHT_GRAY     7
#define VGA_DARK_GRAY      8
#define VGA_LIGHT_BLUE     9
#define VGA_LIGHT_GREEN   10
#define VGA_LIGHT_CYAN    11
#define VGA_LIGHT_RED     12
#define VGA_LIGHT_MAGENTA 13
#define VGA_YELLOW        14
#define VGA_WHITE         15
#define VGA_SCREEN_WIDTH  80
#define VGA_SCREEN_HEIGHT 25
void fb_clear_buffer(unsigned char bg);
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
void fb_write_string(int x, int y, char* string, unsigned char fg, unsigned char bg);
int  fb_get_pos(int x, int y);
#endif

