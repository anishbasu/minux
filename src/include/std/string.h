#ifndef STRING_H
#define STRING_H
#include <std/types.h>
int strlen(char* str);
char* strncpy(char* dest, const char* src, uint8_t len);
int strcmp(const char* dest, char* src);
int strcat(void* dest, const void* src);
int strncmp(const char* str1, const char* str2, int n);
char* itoa(uint64_t value, char* str, int base );
#endif