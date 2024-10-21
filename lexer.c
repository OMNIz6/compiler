#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Token get_next_token(const char **input) {
    while (isspace(**input)) (*input)++;
    if (isdigit(**input)) {
        Token token = {TOKEN_NUMBER, .value.intValue = 0};
        int i = 0;
        while (isdigit(**input)) {
            token.value.intValue = token.value.intValue * 10 + (*(*input)++ - '0');
        }
        return token;
    }
    if (isalpha(**input)) {
        Token token = {TOKEN_IDENTIFIER, .value.strValue = ""};
        int i = 0;
        while (isalnum(**input)) {
            token.value.strValue[i++] = *(*input)++;
        }
        token.value.strValue[i] = '\0';
        return token;
    }
    switch (**input) {
        case '+':
            (*input)++;
            return (Token){TOKEN_PLUS, .value.strValue = "+"};
        case '-':
            (*input)++;
            return (Token){TOKEN_MINUS, .value.strValue = "-"};
        case '=':
            (*input)++;
            return (Token){TOKEN_ASSIGN, .value.strValue = "="};
        case '\0':
            return (Token){TOKEN_EOF, .value.strValue = ""};
        case '"':
            (*input)++;
            return (Token){TOKEN_STRING_LITERAL, .value.strValue = "\""};
        default:
            (*input)++;
            return (Token){TOKEN_INVALID, .value.strValue = ""};
    }
}