#include <stdio.h>
#include <stdlib.h>
#include "encoder.h"
#include <string.h>

int print_usage(const char *name)
{
    printf("usage: %s from_file [cp1251|iso-8859-5|koi8] target_file\n", name);
    return EXIT_FAILURE;
} 

utf_8 encode(int symbol, const utf_8 *charmap)
{
    utf_8 result = {1, {symbol}};
    if (!(0x80 & symbol)) {
        return result;
    }

    int offset = symbol-128;
    return charmap[offset];
}

const utf_8* actual_charmap(const char* encode)
{
    if (strcmp(encode, "cp1251") == 0) {
        return cp1251;
    } else if (strcmp(encode, "koi8") == 0) {
        return koi8;
    } else if (strcmp(encode, "iso-8859-5") == 0) {
        return iso8859;
    } else {
        return NULL;
    }
}

int main(int argc, char **argv)
{
    if (argc != 4) {
        return print_usage(argv[0]);
    }

    FILE* file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("can't open from file");
        return EXIT_FAILURE;
    }

    FILE* utf8 = fopen(argv[3], "w");
    if (file == NULL) {
        perror("can't open target file or create");
        return EXIT_FAILURE;
    }

    const utf_8 *charmap = actual_charmap(argv[2]);
    if (charmap == NULL) {
        return print_usage(argv[0]);
    }

    int symbol = 0;
    while ((symbol = fgetc(file)) != EOF)
    {
        utf_8 code = encode(symbol, charmap);
        for (size_t i = 0; i < code.size; i++) 
        {
            int err = fputc(code.bytes[i], utf8);
            if (err == EOF) {
                perror("write error");
                return EXIT_FAILURE;
            }
        }
    }
    
    fclose(file);
    fclose(utf8);
    
    return EXIT_SUCCESS;
}