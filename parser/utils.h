#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

void help() {
    printf(
        "### Math Parser ###"
        "-f <name> Filename to read equation.\n"
        "-o <name> Output file.\n"
    );
}

#endif //UTIL_H