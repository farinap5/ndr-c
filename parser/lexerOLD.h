#ifndef LEXOLD_H
#define LEXOLD_H

typedef struct token *Token;

/**
 * @brief Lexical analyzer function to parse tokens from input data.
 *
 * This function processes the input string and returns the next token each time
 * it is called. On the first call, the input string should be provided. For subsequent
 * calls, NULL should be passed to continue lexing from the previous position.
 *
 * @param[in] data The input string to lex on the first call, or NULL for subsequent calls.
 *
 * @return A Token struct representing the next token in the input string.
 * If no more tokens are available, the function should return a token (of code 0x00) indicating end of input.
 *
 * @note The caller is responsible for ensuring that the input string remains valid for
 * the duration of the lexing process.
 * @warning The function assumes the input string is null-terminated and valid.
 */
Token lex(char *data);

#endif // LEXOLD_H