# Printing to Screen
## Motivation

While we can get to C, the very best way to see our operating work is by literally seeing it work. Hence, we will be writing the print function for our hobby operating system.

## VGA Basics

The hardware provides us with a VGA (Video Graphics Array) in the form of; you guessed it - an array starting at the memory address **0xB8000**. The basic VGA text mode that the BIOS boots us into consists of a resolution of 80 x 25 (w x h), and alternating bytes in the array are for color and text.

## Finding the position of the text

The position is calculated with the following formula:

```c
uintptr_t fb_get_pos(uint8_t x, uint8_t y)
{
    return (x + VGA_SCREEN_WIDTH * y) * 2; //Need * 2 for color info and character
}
```

The cursor on the screen wraps around at the 160th byte (one for color and one for ASCII with 80 being the screen width).

## VGA Colors

The colors in VGA text mode are defined as follows:

```c
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
```

The color palette only supports 8 primary colors with 8 more colors supported by setting the light bit which at **0x8**.

## Writing to screen

We can write each character directly to the screen using the following code:
```c
void fb_write_cell(uint32_t i, char c, uint8_t fg, uint8_t bg)
{
    char* fb = (char *)VGA_FB_ADDR;
    fb[i] = c;
    fb[i + 1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}
```

First we write the character in the i-th position, and the color information on the i+1-th position. Background color makes up the high byte, while the foreground color makes the low byte.

## Setting up Variadic Arguments

Variadic arguments are the arguments that enable `printf(chat* fmt, ...)` to work with a number of arguments. This feature is actually built into _gcc_ as a builtin macro inside **stdarg.h**.

## Writing `printf`

We make use of a cursor struct to keep track of the position of where we are supposed to be printing characters, and make us of  `__gnuc_va_list`  to iterate over the arguments and print them.

`\r` and `\n` have special meanings for the cursor. `\r` puts the cursor position to 0 on the same line while `\n` sends the cursor to the next line.

```c
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
```
