#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lexer.h"
#include "parser.h"

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

    #define L_NOP 0x00
    #define L_PLUS 0x04
    #define L_MINUS 0x05
    #define L_ASTERISK 0x06
    #define L_SLASH 0x07
    #define L_DIGIT 0x09
*/

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

Lexer lexer_create(char *code) {
    Lexer l = (Lexer) malloc(sizeof(l));
    l->index = 0;
    l->len = strlen(code);
    l->code = (char *) malloc(sizeof(char) * strlen(code));
    strncpy(l->code, code, l->len);
    return l;
}

Token lexi(Lexer l) {
    Token t = (Token)malloc(sizeof(t));
    
    l->len = strlen(l->code);
    if (l->len <= l->index) {
        t->Type;
        return t;
    }
    int i = 0;

    while (is_blank(l->code[l->index])) {
        memmove(l->code + l->index, l->code + l->index + 1, l->len - l->index);
        i++;
    }

    if (is_digit(l->code[l->index])) {
        i = 0;
        
        while (is_digit(l->code[i + l->index])) i++;

        t->Symbol = (char *)malloc(sizeof(char)*i);
        strncpy(t->Symbol, l->code + l->index, (size_t)i);

        l->index += i;
        t->Type = 0x09;
        return t;
    }

    if (is_op(l->code[l->index])) {
        t->Type = is_op(l->code[l->index]);
        t->Symbol = (char *)malloc(sizeof(char));
        strncpy(t->Symbol, l->code + l->index, 1);
        l->index++;
        return t;
    }

    if (is_struct(l->code[l->index])) {
        t->Type = is_struct(l->code[l->index]);
        t->Symbol = (char *)malloc(sizeof(char));
        strncpy(t->Symbol, l->code + l->index, 1);
        l->index++;
        return t;
    }

    t->Type = 0x00;
    return t;
}

void lexer_free(Lexer l) {
    free(l->code);
    free(l);
}

void lexer_token_free(Token t) {
    free(t->Symbol);
    free(t);
}

char *lexer_get_symbol(Token t) {
    return t->Symbol;
}

unsigned char lexer_get_type(Token t) {
    return t->Type;
}