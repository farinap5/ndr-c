#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void Dump(__uint8_t *mem) {
  printf(" #    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");
  for (int i = 0; i < 16; i++) {
    printf("%02x - ", i * 16);
    for (int j = 0; j < 16; j++) {
      printf("%02x ", mem[i * 16 + j]);
    }
    printf("\n");
  }
}

void clean_line(char *line) {
    int len = strlen(line);
    if (len <= 1) {
        return;
    }

    int i = 0;

    // Clean starting white spaces
    while (line[i] == 0x20) {
        i++;
    }
    if (i > 0) {
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < len; k++) {
                if ((k + 1) < len) line[k] = line[k+1];
            }
        }
    }

    // Tim white spaces
    for (int i = 1; i < len; i++) {
        if (line[i] == 0x20 && line[i-1] == 0x20) {
            for (int k = i; k < len; k++) {
                if ((k + 1) < len) {
                    line[k] = line[k+1];
                }
                //i--;
            }
            i--;
        }
    }

    for (int i = 1; i < len; i++) {
        if (line[i] == 0x0a) {
            line[i] = 0x00;
        }
    }

    // Erase comment from the line
    for (int i = 1; i < len; i++) {
        if (line[i] == ';') {
            for (int j = i; j < len; j++) {
                line[j] = 0x00;
            }
        }
    }
}