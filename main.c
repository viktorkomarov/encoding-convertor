#include <stdio.h>
#include <stdlib.h>
#include "encoder.h"

int print_usage(const char *name)
{
    printf("usage: %s path_to_file [cp1251|iso-8859-5|koi8] path_to_result_file\n", name);
    return EXIT_FAILURE;
} 


int main(int argc, char **argv)
{
    if (argc != 4) {
        return print_usage(argv[0]);
    }

    FILE* file = fopen(argv[1], "rb");
    if (file == NULL) return print_usage(argv[0]);

    FILE* utf8 = fopen(argv[3], "w");
    if (file == NULL) return print_usage(argv[0]);

    int symbol = 0;
    while ((symbol = fgetc(file)) != EOF)
    {
        utf_8 code = encode_cp1251(symbol);
        for (size_t i = 0; i < code.size; i++) 
        {
            int err = fputc(code.bytes[i], utf8);
            if (err == -1) {
                perror("write");
                return EXIT_FAILURE;
            }
        }
    }
    
    fclose(file);
    fclose(utf8);
    
    return EXIT_SUCCESS;
}