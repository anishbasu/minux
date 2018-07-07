#include <std/os.h>

void* memcpy(uint8_t* dest, uint8_t* src, int n) {
    uint8_t *p = dest;
    while(n--)
        *p++ = *src++;

    return dest;
}

void* memset(uint8_t* dest, uint8_t src, int n) {
    uint8_t *p = dest;
    while(n--)
        *p++ = src;

    return src;
}
