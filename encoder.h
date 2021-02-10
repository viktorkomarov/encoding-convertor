#include <stdlib.h>

typedef struct utf_8
{
    size_t size;
    unsigned char bytes[4];
}utf_8;

utf_8 encode_cp1251(int symbol);