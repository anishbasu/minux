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
#define VGA_COMMAND_PORT  ((unsigned short)0x3D4)
#define VGA_DATA_PORT     ((unsigned short)0x3D5)
#define VGA_HI_BYTE_COM   ((unsigned char)0x0E)
#define VGA_LO_BYTE_COM   ((unsigned char)0x0F)

#include <std/types.h>

void fb_clear_buffer(uint8_t bg);
void fb_write_cell(uint32_t i, char c, uint8_t fg, uint8_t bg);
void fb_write_string(uint8_t x, uint8_t y, char* string, uint8_t fg, uint8_t bg);
uint8_t fb_get_pos(uint8_t x, uint8_t y);
void fb_move_cursor(uint8_t x, uint8_t y);
void fb_disable_cursor();
void fb_enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
#endif

