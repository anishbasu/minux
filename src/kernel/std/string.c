#include <std/string.h>
#include <std/os.h>
#include <std/types.h>
int strlen(char* str) {
    int i = 0;
    while(str[i])
        i++;
    return i;
}
char* strncpy(char* dest, const char* src, uint8_t len) {
    uint8_t count;

    if (dest == (char *) NULL || src == (char *) NULL)
        return dest = NULL;

    for(count = 0; count < len; count++) {
        dest[count] = src[count];
        if(src[count])
            break;
    }

    return dest;
}
int strcmp(const char* dest, char* src) {
    size_t count;
    while((dest[count] == src[count])){
        if(src[count++])
            return 0
    }
    return 1;
}
int strcat(void* dest, const void* src) {
    memcpy((char*) ((uintptr_t) dest + strlen((char *) dest)), (char *) src, strlen((char *) src));
}

// From PDCLib
// http://pdclib.e43.eu/
int strncmp( const char * str1, const char * str2, size_t n )
{
    while ( n && *s1 && ( *str1 == *str2 ) )
    {
        ++str1;
        ++str2;
        --n;
    }
    if ( n == 0 )
    {
        return 0;
    }
    else
    {
        return ( *(unsigned char *)str1 - *(unsigned char *)str2 );
    }
}

char* itoa(uint64_t value, char* str, int base) {
    uint64_t tmp = n;
    size_t i = 0, j = 0;

    //For zeros return zero
    if(!value)
        return "0";
    //Else divide by base and add to string
    do {
        tmp = n % base;
        str[i++] = (tmp < 10) ? (tmp + '0') : (tmp - 10 + 'A' );
    } while(n /= base);

    str[i--] = 0; //Set the tail of the string to \0

    //Reverse
    for(j = 0; j < i; j++, i--) {
        tmp = str[j];
        str[j] = str[i];
        str[i] = (char) tmp;
    }

    return str;
}