#ifndef OS_H
#define OS_H
#include <std/types.h>
/**
 * memcpy - Copy n octets from src to dest.
 * dest* - Destination pointer to copy to
 * src* - Source pointer to copy from
 * int n - Number of octets to copy
 */
void* memcpy(uint8_t* dest, uint8_t* src, int n);
/**
 * memset - Set n octets in dest to src
 * dest* - Destination pointer to copy to
 * src - Octet to set to
 * int n - Number of octets to copy
 */
void* memset(uint8_t* dest, uint8_t src, int n);
#endif