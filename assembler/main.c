#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "table/table.h"

int main(void) {
    FILE *f;
    f = fopen("assembly.as", "r");
    struct KVDB defDB = DBInit();

    char *line;
    size_t lineSize = 0;
    
    int test = 1;
    char cLine = 0;

    /// Address definitions
    while (getline(&line, &lineSize, f) != -1) {
        cLine++;
        clean_line(line);
        char *token = strtok(line, " ");
        if (strcmp(token, "ADDR") == 0) {
            printf("ADDR section started\n");
            while (getline(&line, &lineSize, f) != -1) {
                cLine++;
                clean_line(line);
                
                char *end = strtok(line, " ");
                if (strcmp(end, "END") == 0) {
                    printf("ADDR section end\n");
                    break;
                }
                char *val = strtok(NULL, " ");
                if (val[0] != '$') {
                    printf("Error line %d: start label with $\n", cLine);
                    return 1;
                } else {
                    printf("    DEF %02x %s\n", (__uint8_t)strtol(end, NULL, 16), val);
                    DBAdd(defDB, val, (__uint8_t)strtol(end, NULL, 16));
                }
            }
            break;
        }
    }

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