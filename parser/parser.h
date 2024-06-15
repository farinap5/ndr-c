#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

int parser_expression(Lexer l);
void parser_save(char *outfname);

#endif // PARSER_H