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
                char *val = strtok(NULL, " ");
                if (val[0] == '$') {
                    printf("    DB %02x %s=%02x\n", (__uint8_t)strtol(end, NULL, 16), val, DBGet(defDB, val));
                } else {
                    printf("    DB %02x %02x\n", (__uint8_t)strtol(end, NULL, 16), (__uint8_t)strtol(val, NULL, 16));
                }
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
                }  else if (strcmp(token, "ADD") == 0) {
                    insCount += 2;
                } else if (token[0] == ':') {
                    printf("label %s to %d byte\n", token, insCount+1);
                    DBAdd(labelDB, token, insCount+1); // add the labels address to the database
                } 
            }
            break;
        }
    }

    printf("final size: %d\n\n\n\n\n", insCount);
    


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
                    printf("DATA section end\n");
                    break;
                } else if (strcmp(token, "STA") == 0) {
                    token = strtok(NULL, " ");
                    if (token[0] == '$') {
                        printf("    STA %s=%02x\n", token, DBGet(defDB, token));
                    } else {
                        printf("    STA %02x\n", (__uint8_t)strtol(token, NULL, 16));
                    }
                    insCount += 2;

                } else if (strcmp(token, "LDA") == 0) {
                    token = strtok(NULL, " ");
                    if (token[0] == '$') {
                        printf("    LDA %s=%02x\n", token, DBGet(defDB, token));
                    } else {
                        printf("    LDA %02x\n", (__uint8_t)strtol(token, NULL, 16));
                    }
                    insCount += 2;
                }


            }
            break;
        }
    }
    //printf("%02x\n", DBGet(defDB, "end1"));

    /*while (getline(&line, &lineSize, f) != -1) {
        clean_line(line);
        
        
        char *token = strtok(line, " ");
        if (strcmp(token, "DB") == 0) {
            char *end = strtok(NULL, " ");
            char *val = strtok(NULL, " ");
            printf("DB %02x %02x\n", (__uint8_t)strtol(end, NULL, 16), (__uint8_t)strtol(val, NULL, 16));
        }
    }

    int insCount = 0;
    while (getline(&line, &lineSize, f) != -1) {
        clean_line(line);
        
        
        char *token = strtok(line, " ");
        if (strcmp(token, "LDA") == 0) {
            token = strtok(NULL, " ");
            printf("LDA %02x\n", (__uint8_t)strtol(token, NULL, 16));
            insCount += 2;


        } else if (strcmp(token, "STA") == 0) {
            token = strtok(NULL, " ");
            printf("STA %02x\n", (__uint8_t)strtol(token, NULL, 16));
            insCount += 2;


        } else if (strcmp(token, "DB") == 0) {
            char *end = strtok(NULL, " ");
            char *val = strtok(NULL, " ");
            printf("DB %02x %02x\n", (__uint8_t)strtol(end, NULL, 16), (__uint8_t)strtol(val, NULL, 16));
            insCount += 2;
        }
        
    }*/
    
    fclose(f);
  return 0;
}