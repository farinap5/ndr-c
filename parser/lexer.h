#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    0x09 = Number
*/

#define L_NOP 0x00
#define L_PLUS 0x04
#define L_MINUS 0x05
#define L_ASTERISK 0x06
#define L_SLASH 0x07
#define L_DIGIT 0x09

struct lexer {
    int index;
    int len;
    char *code;
} typedef lexer;

struct token {
    __uint8_t Type;
    char *Symbol;
} typedef token;

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

__uint8_t is_blank(char c);
lexer *lexer_create(char *code);
token *lexi(lexer *l);
void lexer_free(lexer *l);
void lexer_token_free(token *t);