#ifndef REGISTERS_H
#define REGISTERS_H
#include <std/types.h>
static inline uint16_t cs() {
    uint16_t cs;
    asm volatile ("mov %%cs, %0" : "=r"(cs));
    return cs;
}
#endif