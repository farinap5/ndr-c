#include <stdio.h>
#include <string.h>

#include "parser.h"

void help() {
    printf(
        "### Math Parser ###\n"
        "-f <name> Filename to read equation.\n"
        "-o <name> Output file.\n"
    );
}

int main(int argc, char **argv) {
  char *fname = "math.mth";
  char *outfname = "out.as";

  for (int i = 0; i < argc; i++) {
    if (strcmp("-h", argv[i]) == 0 || strcmp("--help", argv[i]) == 0) {
        help();
        return 0;
    } else if (strcmp("-f", argv[i]) == 0 || strcmp("--file", argv[i]) == 0) {
        i++;
        fname = argv[i];
    } else if (strcmp("-o", argv[i]) == 0 || strcmp("--pc", argv[i]) == 0) {
        i++;
        outfname = argv[i];
    }
  }

  char d[256];
  for (int i=0; i < 256; i++)
    d[i] = 0x00;

  FILE *fptr = fopen(fname, "r");
  if (!fptr) {
    printf("Error: Could not open %s\n", fname);
    return 1;
  }
  fgets(d, 100, fptr);

  Lexer l = lexer_create(d);
  parser_expression(l);
  parser_save(outfname);
}