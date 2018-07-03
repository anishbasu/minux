#ifndef UTIL_IO_H
#define UTIL_IO_H
/* outb - send a byte to an I/O port. Defined in io.asm
 * @param port I/O port
 * @param data the data to send
 */
void outb(unsigned short port, unsigned char data);
/* inb - receive a byte from an I/O port. Defined in io.asm
 * @param port I/O port
 * @param data the data to send
 */
unsigned char inb(unsigned short port);
#endif