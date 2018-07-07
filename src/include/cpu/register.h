#ifndef REGISTERS_H
#define REGISTERS_H
#include <std/types.h>
inline uint16_t cs() {
    uint16_t cs;
    asm volatile ("mov %0, %%cs" : "=r"(cs));
    return cs;
}
#endif