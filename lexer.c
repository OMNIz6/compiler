#include "lexer.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Token assign_string(Token token, char* str) {
    size_t new_length = strlen(token.data.strValue) + strlen(str) + 1;
    token.data.strValue = realloc(token.data.strValue, new_length);
    if (token.data.strValue[0] == '\0') {
        strcpy(token.data.strValue, str);
    } else {
        strcat(token.data.strValue, str);
    }
    return token;
}

Token get_next_token(const char **input) {
    if (**input == '\t' ) {
        (*input)++;
        Token token = {TOKEN_INDENT, .data.strValue = malloc(1)};
        token.data.strValue[0] = '\0';
        return token;
    }
    while (isspace(**input)) (*input)++;
    if (isdigit(**input)) {
        Token token = {TOKEN_NUMBER, .data.intValue = 0};
        while (isdigit(**input)) {
            token.data.intValue = token.data.intValue * 10 + (*(*input)++ - '0');
        }
        return token;
    }
    if (isalpha(**input)) {
        const char *start = *input;
        char name[50];
        int i = 0;
        while (isalnum(**input)) {
            name[i++] = *(*input)++;
        }
        name[i] = '\0';
        if (strcmp(name, "if") == 0) {
            Token token = {TOKEN_IF, .data.strValue = malloc(1)};
            token.data.strValue[0] = '\0';
            strcpy(token.data.strValue, name);
            return token;
        } else if (strcmp(name, "else") == 0) {
            Token token = {TOKEN_ELSE, .data.strValue = malloc(1)};
            token.data.strValue[0] = '\0';
            strcpy(token.data.strValue, name);
            return token;
        } else if (strcmp(name, "true") == 0) {
            Token token = {TOKEN_BOOLEAN, .data.intValue = 1};
            return token;
        } else if (strcmp(name, "false") == 0) {
            Token token = {TOKEN_BOOLEAN, .data.intValue = 0};
            return token;
        } else if (strcmp(name, "and") == 0) {
            Token token = {TOKEN_OPERATOR, .data.opValue = {BOOL_OP, OP_AND}};
            return token;
        } else if (strcmp(name, "or") == 0) {
            Token token = {TOKEN_OPERATOR, .data.opValue = {BOOL_OP, OP_OR}};
            return token;
        }else {
            Token token = {TOKEN_IDENTIFIER, .data.strValue = malloc(1)};
            token.data.strValue[0] = '\0';
            strcpy(token.data.strValue, name);
            return token;
        }
        free(name);
    }
    switch (**input) {
        case '+': {
            (*input)++;
            Token token = {TOKEN_OPERATOR, .data.opValue = {MATH_OP, OP_PLUS}};
            return token;
        }
        case '-': {
            (*input)++;
            Token token = {TOKEN_OPERATOR, .data.opValue = {MATH_OP, OP_MINUS}};
            return token;
        }
        case '*': {
            (*input)++;
            Token token = {TOKEN_OPERATOR, .data.opValue = {MATH_OP, OP_MULTIPLY}};
            return token;
        }
        case '/': {
            (*input)++;
            Token token = {TOKEN_OPERATOR, .data.opValue = {MATH_OP, OP_DIVIDE}};
            return token;
        }
        case '=': {
            (*input)++;
            if (**input == '=') {
                (*input)++;
                Token token = {TOKEN_OPERATOR, .data.opValue = {BOOL_OP, OP_EQUAL}};
                return token;
            } else {
                Token token = {TOKEN_OPERATOR, .data.opValue = {ASSIGN_OP, OP_ASSIGN}};
                return token;
            }
        }
        case '>': {
            (*input)++;
            if (**input == '=') {
                (*input)++;
                Token token = {TOKEN_OPERATOR, .data.opValue = {BOOL_OP, OP_GREATER_EQUAL}};
                return token;
            } else {
                Token token = {TOKEN_OPERATOR, .data.opValue = {BOOL_OP, OP_GREATER}};
                return token;
            }
        }
        case '<': {
            (*input)++;
            if (**input == '=') {
                (*input)++;
                Token token = {TOKEN_OPERATOR, .data.opValue = {BOOL_OP, OP_LESS_EQUAL}};
                return token;
            } else {
                Token token = {TOKEN_OPERATOR, .data.opValue = {BOOL_OP, OP_LESS}};
                return token;
            }
        }
        case '!': {
            (*input)++;
            if (**input == '=') {
                (*input)++;
                Token token = {TOKEN_OPERATOR, .data.opValue = {BOOL_OP, OP_NOT_EQUAL}};
                return token;
            } else {
                Token token = {TOKEN_OPERATOR, .data.opValue = {BOOL_OP, OP_NOT}};
                return token;
            }
        }
        case '&': {
            (*input)++;
            if (**input == '&') {
                (*input)++;
                Token token = {TOKEN_OPERATOR, .data.opValue = {BOOL_OP, OP_AND}};
                return token;
            } else {
                Token token = {TOKEN_INVALID, .data.strValue = malloc(1)};
                token.data.strValue[0] = '\0';
                return token;
            }
        }
        case '|': {
            (*input)++;
            if (**input == '|') {
                (*input)++;
                Token token = {TOKEN_OPERATOR, .data.opValue = {BOOL_OP, OP_OR}};
                return token;
            } else {
                Token token = {TOKEN_INVALID, .data.strValue = malloc(1)};
                token.data.strValue[0] = '\0';
                return token;
            }
        }
        case '\0': {
            Token token = {TOKEN_EOF, .data.strValue = malloc(1)};
            token.data.strValue[0] = 'e';
            return token;
        }
        case '"': {
            Token token = {TOKEN_STRING, .data.strValue = malloc(1)};
            token.data.strValue[0] = '\0';
            if (token.data.strValue == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
            }
            (*input)++;
            int i = 0;
            char* str = malloc(1);
            while (**input != '"') {
                str = realloc(str, i + 1);
                str[i++] = *(*input)++;
            }
            token = assign_string(token, str);
            (*input)++;
            token.data.strValue[i] = '\0';
            return token;
        }
        case '\'': {
            Token token = {TOKEN_STRING, .data.strValue = malloc(1)};
            token.data.strValue[0] = '\0';
            if (token.data.strValue == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
            }
            (*input)++;
            int i = 0;
            char* str = malloc(1);
            while (**input != '\'') {
                str = realloc(str, i + 1);
                str[i++] = *(*input)++;
            }
            token = assign_string(token, str);
            (*input)++;
            token.data.strValue[i] = '\0';
            return token;
        }
        case '(': {
            (*input)++;
            Token token = {TOKEN_CONDITION_START, .data.strValue = malloc(1)};
            token.data.strValue[0] = '\0';
            return token;
        }
        case ')': {
            (*input)++;
            Token token = {TOKEN_CONDITION_END, .data.strValue = malloc(1)};
            token.data.strValue[0] = '\0';
            return token;
        }
        case '{': {
            (*input)++;
            Token token = {TOKEN_BLOCK_START, .data.strValue = malloc(1)};
            token.data.strValue[0] = '\0';
            return token;
        }
        case '}': {
            (*input)++;
            Token token = {TOKEN_BLOCK_END, .data.strValue = malloc(1)};
            token.data.strValue[0] = '\0';
            return token;
        }
        default: {
            (*input)++;
            Token token = {TOKEN_INVALID, .data.strValue = malloc(1)};
            token.data.strValue[0] = '\0';
            return token;
        }
    }
}

Token* tokenize(const char **input) {
    Token* tokenArr = malloc(1);
    int len = 0;
    while (isspace(**input)) {
        (*input)++;
        Token token = {TOKEN_INDENT, .data.strValue = malloc(1)};
        token.data.strValue[0] = '\0';
        tokenArr = realloc(tokenArr, (len + 1) * sizeof(Token));
        tokenArr[len++] = token;
    };
    
    Token token = get_next_token(input);
    
    while (1) {
        tokenArr = realloc(tokenArr, (len + 1) * sizeof(Token));
        tokenArr[len++] = token;
        if (token.type == TOKEN_EOF) {
            break;
        } else {
            token = get_next_token(input);
        }
    }
    return tokenArr;
}

void print_token_string(Token* arr) {
    printf("Token string: ");
    int i = 0;
    while (1) {
        switch (arr[i].type) {
            case TOKEN_NUMBER:
                printf("NUMBER ");
                break;
            case TOKEN_IDENTIFIER:
                printf("IDENTIFIER ");
                break;
            case TOKEN_STRING:
                printf("STRING ");
                break;
            case TOKEN_EOF:
                printf("EOF ");
                break;
            case TOKEN_INVALID:
                printf("INVALID ");
                break;
            case TOKEN_IF:
                printf("IF ");
                break;
            case TOKEN_ELSE:
                printf("ELSE ");
                break;
            case TOKEN_CONDITION_START:
                printf("CONDITION_START ");
                break;
            case TOKEN_CONDITION_END:
                printf("CONDITION_END ");
                break;
            case TOKEN_BLOCK_START:
                printf("BLOCK_START ");
                break;
            case TOKEN_BLOCK_END:
                printf("BLOCK_END ");
                break;
            case TOKEN_BOOLEAN:
                printf("BOOLEAN ");
                break;
            case TOKEN_INDENT:
                printf("INDENT ");
                break;
            case TOKEN_OPERATOR:
                switch (arr[i].data.opValue.value) {
                    case OP_PLUS:
                        printf("PLUS ");
                        break;
                    case OP_MINUS:
                        printf("MINUS ");
                        break;
                    case OP_MULTIPLY:
                        printf("MULTIPLY ");
                        break;
                    case OP_DIVIDE:
                        printf("DIVIDE ");
                        break;
                    case OP_EQUAL:
                        printf("EQUAL ");
                        break;
                    case OP_NOT_EQUAL:
                        printf("NOT_EQUAL ");
                        break;
                    case OP_GREATER:
                        printf("GREATER ");
                        break;
                    case OP_LESS:
                        printf("LESS ");
                        break;
                    case OP_GREATER_EQUAL:
                        printf("GREATER_EQUAL ");
                        break;
                    case OP_LESS_EQUAL:
                        printf("LESS_EQUAL ");
                        break;
                    case OP_AND:
                        printf("AND ");
                        break;
                    case OP_OR:
                        printf("OR ");
                        break;
                    case OP_NOT:
                        printf("NOT ");
                        break;
                    case OP_ASSIGN:
                        printf("ASSIGN ");
                        break;
                    default:
                        printf("OPERATOR ");
                        break;
                }
                break;
            default:
                printf("TOKEN ");
                break;
        }
        if (arr[i].type == TOKEN_EOF) {
            break;
        }
        i++;
    }
    printf("\n");
}

int check_token(Token* arr, TokenType type) {
    int i = 0;
    while (1) {
        if (arr[i].type == type) {
            return 1;
        }
        if (arr[i].type == TOKEN_EOF) {
            break;
        }
        i++;
    }
    return 0;
}
