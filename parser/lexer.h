#ifndef LEXER_H
#define LEXER_H

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

typedef struct lexer *Lexer;
typedef struct token *Token;

Lexer lexer_create(char *code);
Token lexi(Lexer l);
void lexer_free(Lexer l);
void lexer_token_free(Token t);
unsigned char lexer_get_type(Token t);
char *lexer_get_symbol(Token t);

#endif // LEXER_H