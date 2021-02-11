#ifndef ENCODER_HEADER
#define ENCODER_HEADER

#include <stdlib.h>


typedef struct utf_8
{
    size_t size;
    unsigned char bytes[4];
}utf_8;

extern const utf_8 cp1251[128];
extern const utf_8 koi8[128];
extern const utf_8 iso8859[128];

#endif