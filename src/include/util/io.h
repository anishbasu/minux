#ifndef UTIL_IO_H
#define UTIL_IO_H
#include <std/types.h>
/* outb - send a byte to an I/O port. Defined in io.asm
 * @param port I/O port
 * @param data the data to send
 */
static inline void outb(uint16_t port, uint8_t val){
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}
/* inb - receive a byte from an I/O port. Defined in io.asm
 * @param port I/O port
 * @param data the data to send
 */
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}
#endif