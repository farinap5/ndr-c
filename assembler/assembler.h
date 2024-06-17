#ifndef ASSEMB_H
#define ASSEMB_H

/*
    The assembler must receive a file descriptor of a file.
    It retunts the memory.
*/
__uint8_t *assembler(FILE *f, int v);

#endif // ASSEMB_H