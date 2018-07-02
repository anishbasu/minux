#include "vga.h"
/* fb_get_pos:
 * Get the framebuffer memory positions
 * @param x The x coordinate.
 * @param y The y coordinate
*/
int fb_get_pos(int x, int y) {
    return (x + VGA_SCREEN_WIDTH * y) * 2; //Need * 2 for color info and character
}


/* fb_write_string:
 * Writes a string with a given foreground and background.
 *  @param char* string The string to write
 *  @param fg The foreground color
 *  @param bg The background color
*/  
void fb_write_string(int x, int y, char* string, unsigned char fg, unsigned char bg){
    int i = 0;
    int start_pos = fb_get_pos(x, y);
    while(string[i] != 0) {
       fb_write_cell(start_pos + i * 2, string[i], fg, bg);
       i++;
   }
}

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
    char* fb = (char *)VGA_FB_ADDR;
    fb[i] = c;
    fb[i + 1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}

/* fb_clear_buffer
 * Clears buffer one character at a time
 * @param bg The background color to use
*/
void fb_clear_buffer(unsigned char bg) {
    for(int y = 0; y < VGA_SCREEN_HEIGHT; y++) {
        for(int x = 0; x < VGA_SCREEN_WIDTH; x++) {
            fb_write_cell(fb_get_pos(x,y), ' ', VGA_BLACK, bg);
        }
    }
}