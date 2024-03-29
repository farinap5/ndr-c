#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "machine.h"

void help() {
    printf("-- Neader Virtual Machine --\n\n");
    printf(
        "-h, --help     Shows the help menu\n"
        "-f, --file     May be used to set the filename with instructions\n"
        "   Use `-f program.mem` (default: ndr-test.mem)\n"
        "-p, --pc       Configure prog counter register (use decimal)\n"
        "   Use `-p 10` (default: 0)\n"
        "-a, --ac       Configure accumulator register (use decimal)\n"
        "   Use `-a 10` (default: 0)\n"
    );
}

int main(int argc, char **argv) {
  Machine m = {.ac = 0, .pc = 0};
  char head[4];
  char *fname = "ndr-test.mem";

  for (int i = 0; i < argc; i++) {
    if (strcmp("-h", argv[i]) == 0 || strcmp("--help", argv[i]) == 0) {
        help();
        return 0;
    } else if (strcmp("-f", argv[i]) == 0 || strcmp("--file", argv[i]) == 0) {
        i++;
        fname = argv[i];
    } else if (strcmp("-p", argv[i]) == 0 || strcmp("--pc", argv[i]) == 0) {
        i++;
        m.pc = (uint8_t)atoi(argv[i]);
    } else if (strcmp("-a", argv[i]) == 0 || strcmp("--ac", argv[i]) == 0) {
        i++;
        m.ac = (uint8_t)atoi(argv[i]);
    }
  }

  printf("-- Neader Virtual Machine --\n\n");
  printf("AC: %02x   PC: %02x\n\n", m.ac, m.pc);

  FILE *file;
  file = fopen(fname, "rb");
  if (file == NULL) {
    printf("Error: Could not open %s.\n", fname);
    return 1;
  }

  fread(head, sizeof(char), 4, file);
  for(int i = 0; i < 256; i++) {
    uint16_t data;
    fread(&data, sizeof(uint16_t), 1, file);
    m.mem[i] = (uint8_t)data;  
  }
  fclose(file);
  
  // call the machine
  if (run_machine_code(m, 2)) {
    printf("Exit with error.");
  }
  
  return 0;
}