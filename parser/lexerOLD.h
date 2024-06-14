#ifndef LEXOLD_H
#define LEXOLD_H

#include <stdlib.h>

typedef struct token *Token;
__uint8_t is_struct(char c);
__uint8_t is_op(char c);
__uint8_t is_digit(char c);
__uint8_t is_blank(char c);
Token lex(char *data);

#endif // LEXOLD_H