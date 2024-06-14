#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lexerOLD.h"

/*
    0x00 = nop
    0x01 = Open Parentesis
    0x02 = Close Parentesis
    0x03 = Equal
    0x04 = Plus
    0x05 = Minus
    0x06 = Asterisk
    0x07 = Slash
    0x08 = Expoent
*/

struct token {
    __uint8_t Type;
    char *Symbol;
};

__uint8_t is_struct(char c) {
    switch (c) {
        case '(':
            return 0x01;
        case ')':
            return 0x02;
        default:
            return 0;
    }
}

__uint8_t is_op(char c) {
    switch (c) {
        case '+':
            return 0x04;
        case '-':
            return 0x05;
        case '*':
            return 0x06;
        case '/':
            return 0x07;
        case '=':
            return 0x03;
        case '^':
            return 0x08;
        default:
            return 0;
    }
}

__uint8_t is_digit(char c) {
    switch (c) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return 1;
        default:
            return 0;
    }
}

__uint8_t is_blank(char c) {
    switch (c) {
        case ' ':
        case '\t':
        case '\r':
        case '\n':
            return 1;
        default:
            return 0;
    }
}



Token lex(char *data) {
    Token t = (Token)malloc(sizeof(t));
    static char *buff;
    if (data != NULL) buff = strdup(data);
    if (buff == NULL) return NULL;

    int slen = strlen(buff);

    int i = 0;
    while (is_blank(buff[0])) {
        memmove(buff, buff + i, slen - i + 1);
        i++;
    }

    i = 0;
    if (is_digit(buff[0])) {
        while (is_digit(buff[i])) {
            i++;
        }
        t->Symbol = (char *)malloc(sizeof(char)*i);
        strncpy(t->Symbol, buff, (size_t)i);

        for (int j = 0; j < i; j++) {
            memmove(buff, buff + 1, slen - j);
        }

        t->Type = 0x01;
        return t;
    }

    if (is_op(buff[0])) {
        t->Type = is_op(buff[0]);
        t->Symbol = (char *)malloc(sizeof(char));
        strncpy(t->Symbol, buff, 1);
        memmove(buff, buff + 1, slen - 1);
        return t;
    }

    if (is_struct(buff[0])) {
        t->Type = is_struct(buff[0]);
        t->Symbol = (char *)malloc(sizeof(char));
        strncpy(t->Symbol, buff, 1);
        memmove(buff, buff + 1, slen - 1);
        return t;
    }
    
    t->Type = 0x00;
    return t;
}

int main() {
    char *data = "(11111 + 5) ";
    Token t = lex(data);
    printf("Simble: %s Code: %d\n", t->Symbol, t->Type);
    t = lex(NULL);
    printf("Simble: %s Code: %d\n", t->Symbol, t->Type);
    t = lex(NULL);
    printf("Simble: %s Code: %d\n", t->Symbol, t->Type);
    t = lex(NULL);
    printf("Simble: %s Code: %d\n", t->Symbol, t->Type);
    t = lex(NULL);
    printf("Simble: %s Code: %d\n", t->Symbol, t->Type);
    t = lex(NULL);
    printf("Simble: %s Code: %d\n", t->Symbol, t->Type);
    return 0;
}