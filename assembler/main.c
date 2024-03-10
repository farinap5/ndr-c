#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "table/table.h"

int main(void) {
    FILE *f;
    f = fopen("assembly.as", "r");
    /*
        Database to hold the defs where 
        $var (a variable with arbitrary name) = 0x10 (a arbitrary address)
    */
    struct KVDB defDB = DBInit();

    /*
        Database to hold the labels where
        :label (a label with arbitrary name) = 0x10 (automatically defined address)
    */
    struct KVDB labelDB = DBInit();
    
    __uint8_t mem[256];
    for (int i = 0; i < 256; i++) {
        mem[i] = 0x00;
    }

    char *line;
    size_t lineSize = 0;
    
    int test = 1;
    char cLine = 0;

    /* Address definitions
    ADDR ; start addressing section
        8 $end1
        89 $end2
    END
    */
    while (getline(&line, &lineSize, f) != -1) {
        cLine++;
        clean_line(line);
        char *token = strtok(line, " ");
        if (strcmp(token, "ADDR") == 0) { // read the header of the section (ADDR)
            printf("ADDR section started\n");
            while (getline(&line, &lineSize, f) != -1) {
                cLine++;
                clean_line(line);
                
                char *end = strtok(line, " ");
                if (strcmp(end, "END") == 0) { // end the section
                    printf("ADDR section end\n");
                    break;
                }
                char *val = strtok(NULL, " ");
                if (val[0] != '$') {
                    printf("Error line %d: start definition with $\n", cLine);
                    return 1;
                } else {
                    printf("    DEF %02x %s\n", (__uint8_t)strtol(end, NULL, 16), val);
                    DBAdd(defDB, val, (__uint8_t)strtol(end, NULL, 16));
                }
            }
            break;
        }
    }


    // Data definition
    while (getline(&line, &lineSize, f) != -1) {
        clean_line(line);
        char *token = strtok(line, " ");
        if (strcmp(token, "DATA") == 0) {
            printf("DATA section started\n");
            while (getline(&line, &lineSize, f) != -1) {
                clean_line(line);
                
                char *end = strtok(line, " ");
                if (strcmp(end, "END") == 0) {
                    printf("DATA section end\n");
                    break;
                }
                __uint8_t addr;
                char *val = strtok(NULL, " ");
                if (val[0] == '$') {
                    addr = DBGet(defDB, val);
                    printf("    DB %02x %s=%02x\n", (__uint8_t)strtol(end, NULL, 16), val, addr);
                } else {
                    addr = (__uint8_t)strtol(val, NULL, 16);
                    printf("    DB %02x %02x\n", (__uint8_t)strtol(end, NULL, 16), addr);
                }
                mem[addr] = (__uint8_t)strtol(end, NULL, 16);
            }
            break;
        }
    }

    int insCount = 0;
    // this iterate is to measure the bytes to place labels
    while (getline(&line, &lineSize, f) != -1) {
        clean_line(line);
        char *token = strtok(line, " ");
        if (strcmp(token, "TEXT") == 0) {
            printf("TEXT section started\n");

            while (getline(&line, &lineSize, f) != -1) {
                clean_line(line);
                
                char *token = strtok(line, " ");
                if (strcmp(token, "END") == 0) {
                    printf("DATA section end\n");
                    break;
                } else if (strcmp(token, "STA") == 0) {
                    insCount += 2;
                } else if (strcmp(token, "LDA") == 0) {
                    insCount += 2;
                } else if (strcmp(token, "NOT") == 0) {
                    insCount += 1;
                } else if (strcmp(token, "JMP") == 0) {
                    insCount += 2;
                } else if (strcmp(token, "JN") == 0) {
                    insCount += 2;
                } else if (strcmp(token, "JZ") == 0) {
                    insCount += 2;
                } else if (strcmp(token, "OR") == 0) {
                    insCount += 2;
                } else if (strcmp(token, "AND") == 0) {
                    insCount += 2;
                } else if (strcmp(token, "HLT") == 0) {
                    insCount += 2;
                } else if (strcmp(token, "ADD") == 0) {
                    insCount += 2;
                } else if (strcmp(token, "NOP") == 0) {
                    insCount += 1;
                } else if (token[0] == ':') {
                    int real_addrs = (insCount == 0) ? insCount : insCount + 1;
                    printf("label %s to %d byte\n", token, real_addrs);
                    DBAdd(labelDB, token, real_addrs); // add the labels address to the database
                } else if (strcmp(token, "HLT") == 0) {
                    insCount += 1;
                } 
            }
            break;
        }
    }

    printf("final size: %d\n\n\n\n\n", insCount);
    


    int address_index = 0;
    // Assembler
    fseek(f, 0, SEEK_SET);
    while (getline(&line, &lineSize, f) != -1) {
        clean_line(line);
        char *token = strtok(line, " ");
        if (strcmp(token, "TEXT") == 0) {
            printf("TEXT section started\n");

            int insCount = 0;
            while (getline(&line, &lineSize, f) != -1) {
                clean_line(line);
                
                char *token = strtok(line, " ");
                if (strcmp(token, "END") == 0) {
                    printf("Text section end\n");
                    break;
                } else if (strcmp(token, "STA") == 0) {
                    __uint8_t addr;
                    token = strtok(NULL, " "); // get the next token after " "
                    if (token[0] == '$') {
                        addr = DBGet(defDB, token);
                        printf("    STA %s=%02x\n", token, addr);
                    } else {
                        addr = (__uint8_t)strtol(token, NULL, 16);
                        printf("    STA %02x\n", addr);
                    }
                    mem[address_index] = 0x10;
                    address_index++;
                    mem[address_index] = addr;
                    address_index++;
                } else if (strcmp(token, "LDA") == 0) {
                    __uint8_t addr;
                    token = strtok(NULL, " ");
                    if (token[0] == '$') {
                        addr = DBGet(defDB, token);
                        printf("    LDA %s=%02x\n", token, addr);
                    } else {
                        addr = (__uint8_t)strtol(token, NULL, 16);
                        printf("    LDA %02x\n", addr);
                    }
                    mem[address_index] = 0x20;
                    address_index++;
                    mem[address_index] = addr;
                    address_index++;
                } else if (strcmp(token, "ADD") == 0) {
                    __uint8_t addr;
                    token = strtok(NULL, " ");
                    if (token[0] == '$') {
                        addr = DBGet(defDB, token);
                        printf("    ADD %s=%02x\n", token, addr);
                    } else {
                        addr = (__uint8_t)strtol(token, NULL, 16);
                        printf("    ADD %02x\n", addr);
                    }
                    mem[address_index] = 0x30;
                    address_index++;
                    mem[address_index] = addr;
                    address_index++;
                } else if (strcmp(token, "OR") == 0) {
                    __uint8_t addr;
                    token = strtok(NULL, " ");
                    if (token[0] == '$') {
                        addr = DBGet(defDB, token);
                        printf("    OR %s=%02x\n", token, addr);
                    } else {
                        addr = (__uint8_t)strtol(token, NULL, 16);
                        printf("    OR %02x\n", addr);
                    }
                    mem[address_index] = 0x40;
                    address_index++;
                    mem[address_index] = addr;
                    address_index++;
                } else if (strcmp(token, "AND") == 0) {
                    __uint8_t addr;
                    token = strtok(NULL, " ");
                    if (token[0] == '$') {
                        addr = DBGet(defDB, token);
                        printf("    AND %s=%02x\n", token, addr);
                    } else {
                        addr = (__uint8_t)strtol(token, NULL, 16);
                        printf("    AND %02x\n", addr);
                    }
                    mem[address_index] = 0x50;
                    address_index++;
                    mem[address_index] = addr;
                    address_index++;
                } else if (strcmp(token, "NOT") == 0) {
                    printf("    NOT\n");
                    mem[address_index] = 0x60;
                    address_index++;
                } else if (strcmp(token, "JMP") == 0) {
                    __uint8_t addr;
                    token = strtok(NULL, " ");
                    if (token[0] == ':') {
                        addr = DBGet(labelDB, token);
                        printf("    JMP %s=%02x\n", token, addr);
                    } else {
                        addr = (__uint8_t)strtol(token, NULL, 16);
                        printf("    JMP %02x\n", addr);
                    }
                    mem[address_index] = 0x80;
                    address_index++;
                    mem[address_index] = addr;
                    address_index++;
                }else if (strcmp(token, "JN") == 0) {
                    __uint8_t addr;
                    token = strtok(NULL, " ");
                    if (token[0] == ':') {
                        addr = DBGet(labelDB, token);
                        printf("    JN %s=%02x\n", token, addr);
                    } else {
                        addr = (__uint8_t)strtol(token, NULL, 16);
                        printf("    JN %02x\n", addr);
                    }
                    mem[address_index] = 0x90;
                    address_index++;
                    mem[address_index] = addr;
                    address_index++;
                } else if (strcmp(token, "JZ") == 0) {
                    __uint8_t addr;
                    token = strtok(NULL, " ");
                    if (token[0] == '$') {
                        addr = DBGet(defDB, token);
                        printf("    JZ %s=%02x\n", token, addr);
                    } else {
                        addr = (__uint8_t)strtol(token, NULL, 16);
                        printf("    JZ %02x\n", addr);
                    }
                    mem[address_index] = 0xa0;
                    address_index++;
                    mem[address_index] = addr;
                    address_index++;
                } else if (strcmp(token, "HLT") == 0) {
                    printf("    HLT\n");
                    mem[address_index] = 0xf0;
                    address_index++;
                } else if (strcmp(token, "NOP") == 0) {
                    printf("    NOP\n");
                    mem[address_index] = 0xf0;
                    address_index++;
                }
            }
            break;
        }
    }
   
    Dump(mem);
    fclose(f);
  return 0;
}