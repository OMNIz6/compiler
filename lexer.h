#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <string.h>

typedef enum {
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_EOF,
    TOKEN_INVALID,
    TOKEN_STRING,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_CONDITION_START,
    TOKEN_CONDITION_END,
    TOKEN_BLOCK_START,
    TOKEN_BLOCK_END,
    TOKEN_BOOLEAN,
    TOKEN_OPERATOR,
    TOKEN_INDENT,
    TOKEN_NEXT
} TokenType;

typedef enum{
    MATH_OP,
    BOOL_OP,
    ASSIGN_OP
} OperatorType;

typedef enum {
    OP_PLUS,
    OP_MINUS,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_EQUAL,
    OP_NOT_EQUAL,
    OP_GREATER,
    OP_LESS,
    OP_GREATER_EQUAL,
    OP_LESS_EQUAL,
    OP_AND,
    OP_OR,
    OP_NOT,
    OP_ASSIGN,
} OperatorValue;
typedef struct{
    OperatorType type;
    OperatorValue value;
} Operator;
typedef union {
    int intValue;
    char* strValue;
    Operator opValue;
} TokenValue;

typedef struct {
    TokenType type;
    TokenValue data;
} Token;

Token get_next_token(const char **input);
Token* tokenize(const char **input);
void print_token_string(Token* arr);
int check_token(Token* arr, TokenType type);
Token assign_string(Token token, char* str);

#endif // TOKEN_H