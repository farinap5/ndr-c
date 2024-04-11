#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assembler.h"

void help() {
    printf(
        "### Assemblr for Neander ###\n"
        "./assmr [option...] <asm file>\n"
        "-o <file name>.mem File where to write data.\n"
    );
}

int main(int argc, char **argv) {
    FILE *f;
    FILE *out;
    __uint8_t magic[4] = {0x03, 0x4e, 0x44, 0x52};
    char *foutname = "out.mem";
    char *fname = "assembly.as";

    if (argc > 1) {
        for (int i = 0; i < argc; i++) {
            if (strcmp("-h", argv[i]) == 0 || strcmp("--help", argv[i]) == 0) {
                help();
                return 0;
            } else if (strcmp("-o", argv[i]) == 0 || strcmp("--output", argv[i]) == 0) {
                i++;
                foutname = argv[i];
            } else  {
                fname = argv[i];
            }
        }
    }

    f = fopen(fname, "r");
    if (f == NULL) {
        printf("Error: No such file %s\n", fname);
        return 1;
    }
    
    __uint8_t *mem = assembler(f,2);
   
    Dump(mem);
    fclose(f);

    out = fopen(foutname, "w");
    if (out == NULL) {
        printf("Error: while opening %s\n", foutname);
        return 1;
    }

    fwrite(magic, 4, sizeof(__uint8_t), out);
    //fwrite(mem, 256, sizeof(__uint8_t), out);
    for (int i = 0; i < 256; i++) {
        unsigned char *data = &mem[i];
        fwrite(data, 1, sizeof(__uint8_t), out);
        unsigned char null = '\0';
        fwrite(&null, 1, sizeof(__uint8_t), out);
    }
    fclose(out);
    free(mem);

  return 0;
}