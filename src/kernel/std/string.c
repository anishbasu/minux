#include <std/string.h>
#include <std/types.h>
char* itoa(uint64_t value, char* str, int base) {
    uint64_t tmp = value;
    size_t i = 0, j = 0;

    //Else divide by base and add to string
    do {
        tmp = value % base;
        str[i++] = (tmp < 10) ? (tmp + '0') : (tmp - 10 + 'A' );
    } while(value /= base);

    str[i--] = 0; //Set the tail of the string to \0

    //Reverse
    for(j = 0; j < i; j++, i--) {
        tmp = str[j];
        str[j] = str[i];
        str[i] = (char) tmp;
    }

    return str;
}