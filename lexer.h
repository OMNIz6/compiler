#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <string.h>

typedef enum {
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_ASSIGN,
    TOKEN_EOF,
    TOKEN_INVALID,
    TOKEN_STRING,
    TOKEN_EQUAL,
    TOKEN_NOT_EQUAL,
    TOKEN_GREATER,
    TOKEN_LESS,
    TOKEN_GREATER_EQUAL,
    TOKEN_LESS_EQUAL,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_NOT,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_INDENT,
    TOKEN_BOOLEAN,
} TokenType;

typedef union {
    int intValue;
    char* strValue;
} TokenValue;

typedef struct {
    TokenType type;
    TokenValue value;
} Token;

Token get_next_token(const char **input);
Token* tokenize(const char **input);
void print_token_string(Token* arr);
int check_token(Token* arr, TokenType type);
Token assign_string(Token token, char* str);

#define DEFAULT_TOKEN_STRING (Token){ \
    .value.strValue = malloc(1), \
}

#endif // TOKEN_H