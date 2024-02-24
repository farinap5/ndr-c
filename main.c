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

  /*
  m.mem[0] = 0x20;
  m.mem[1] = 0x00;
  m.mem[2] = 0x10;
  m.mem[3] = 0x01;
  m.mem[4] = 0xf0;
  */

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
  
  int r = 1;
  int c = 0;
  while (r) {
    c++;
    if (c > 100)
      break;
    
    printf("PC: %02x  AC: %02x |", m.pc, m.ac);
    switch (m.mem[m.pc]) {
      //printf("-> pc %02x\n",m.pc);
      case 00:
        m.pc++;
        break;
      case 16: // 0x10
        STA(&m);
        break;
      case 32: // 0x20
        LDA(&m);
        break;
      case 48: // 0x30
        ADD(&m);
        break;
      case 64: // 0x40
        OR(&m);
        break;
      case 80: // 0x50
        AND(&m);
        break;
      case 96: // 0x60
        NOT(&m);
        break;
      case 128: // 0x80
        JMP(&m);
        break;
      case 144: // 0x90
        JN(&m);
        break;
      case 160: // 0xa0
        JZ(&m);
        break;
      case 240: // HLT 0xf0
        printf(" HLT\n");
        r = 0;
        break;
      default:
        printf(" Not A Instruction\n");
        break;
    }
  }
  printf("\n");
  Dump(&m);
  
  return 0;
}