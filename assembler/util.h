#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#endif //UTIL_H