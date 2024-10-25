#include "lexer.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Token assign_string(Token token, char* str) {
    size_t new_length = strlen(token.value.strValue) + strlen(str) + 1;
    token.value.strValue = realloc(token.value.strValue, new_length);
    if (token.value.strValue[0] == '\0') {
        strcpy(token.value.strValue, str);
    } else {
        strcat(token.value.strValue, str);
    }
    return token;
}

Token get_next_token(const char **input) {
    while (isspace(**input)) (*input)++;
    if (isdigit(**input)) {
        Token token = {TOKEN_NUMBER, .value.intValue = 0};
        while (isdigit(**input)) {
            token.value.intValue = token.value.intValue * 10 + (*(*input)++ - '0');
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
            Token token = {TOKEN_IF, .value.strValue = malloc(1)};
            token.value.strValue[0] = '\0';
            strcpy(token.value.strValue, name);
            return token;
        } else if (strcmp(name, "true") == 0) {
            Token token = {TOKEN_BOOLEAN, .value.strValue = "true", .value.intValue = 1};
            strcpy(token.value.strValue, name);
            return token;
        } else if (strcmp(name, "false") == 0) {
            Token token = {TOKEN_BOOLEAN, .value.strValue = "false", .value.intValue = 0};
            strcpy(token.value.strValue, name);
            return token;
        } else {
            Token token = {TOKEN_IDENTIFIER, .value.strValue = malloc(1)};
            token.value.strValue[0] = '\0';
            strcpy(token.value.strValue, name);
            return token;
        }
        free(name);
    }
    switch (**input) {
        case '+': {
            (*input)++;
            Token token = {TOKEN_PLUS, .value.strValue = malloc(1)};
            token.value.strValue[0] = '\0';
            token = assign_string(token, "+");
            return token;
        }
        case '-': {
            (*input)++;
            Token token = {TOKEN_MINUS, .value.strValue = malloc(1)};
            token.value.strValue[0] = '\0';
            token = assign_string(token, "-");
            return token;
        }
        case '*': {
            (*input)++;
            Token token = {TOKEN_MULTIPLY, .value.strValue = malloc(1)};
            token.value.strValue[0] = '\0';
            token = assign_string(token, "*");
            return token;
        }
        case '/': {
            (*input)++;
            Token token = {TOKEN_DIVIDE, .value.strValue = malloc(1)};
            token.value.strValue[0] = '\0';
            token = assign_string(token, "/");
            return token;
        }
        case '=': {
            (*input)++;
            if (**input == '=') {
                (*input)++;
                Token token = {TOKEN_EQUAL, .value.strValue = malloc(1)};
                token.value.strValue[0] = '\0';
                token = assign_string(token, "==");
                return token;
            } else {
                Token token = {TOKEN_ASSIGN, .value.strValue = malloc(1)};
                token.value.strValue[0] = '\0';
                token = assign_string(token, "=");
                return token;
            }
        }
        case '>': {
            (*input)++;
            if (**input == '=') {
                (*input)++;
                Token token = {TOKEN_GREATER_EQUAL, .value.strValue = malloc(1)};
                token.value.strValue[0] = '\0';
                token = assign_string(token, ">=");
                return token;
            } else {
                Token token = {TOKEN_GREATER, .value.strValue = malloc(1)};
                token.value.strValue[0] = '\0';
                token = assign_string(token, ">");
                return token;
            }
        }
        case '<': {
            (*input)++;
            if (**input == '=') {
                (*input)++;
                Token token = {TOKEN_LESS_EQUAL, .value.strValue = malloc(1)};
                token.value.strValue[0] = '\0';
                token = assign_string(token, "<=");
                return token;
            } else {
                Token token = {TOKEN_LESS, .value.strValue = malloc(1)};
                token.value.strValue[0] = '\0';
                token = assign_string(token, "<");
                return token;
            }
        }
        case '!': {
            (*input)++;
            if (**input == '=') {
                (*input)++;
                Token token = {TOKEN_NOT_EQUAL, .value.strValue = malloc(1)};
                token.value.strValue[0] = '\0';
                token = assign_string(token, "!=");
                return token;
            } else {
                Token token = {TOKEN_NOT, .value.strValue = malloc(1)};
                token.value.strValue[0] = '\0';
                token = assign_string(token, "!");
                return token;
            }
        }
        case '&': {
            (*input)++;
            if (**input == '&') {
                (*input)++;
                Token token = {TOKEN_AND, .value.strValue = malloc(1)};
                token.value.strValue[0] = '\0';
                token = assign_string(token, "&&");
                return token;
            } else {
                Token token = {TOKEN_INVALID, .value.strValue = malloc(1)};
                token.value.strValue[0] = '\0';
                return token;
            }
        }
        case '|': {
            (*input)++;
            if (**input == '|') {
                (*input)++;
                Token token = {TOKEN_OR, .value.strValue = malloc(1)};
                token.value.strValue[0] = '\0';
                token = assign_string(token, "||");
                return token;
            } else {
                Token token = {TOKEN_INVALID, .value.strValue = malloc(1)};
                token.value.strValue[0] = '\0';
                return token;
            }
        }
        case '\0': {
            Token token = {TOKEN_EOF, .value.strValue = malloc(1)};
            token.value.strValue[0] = 'e';
            return token;
        }
        case '"': {
            Token token = {TOKEN_STRING, .value.strValue = malloc(1)};
            token.value.strValue[0] = '\0';
            if (token.value.strValue == NULL) {
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
            token.value.strValue[i] = '\0';
            return token;
        }
        case '\'': {
            Token token = {TOKEN_STRING, .value.strValue = malloc(1)};
            token.value.strValue[0] = '\0';
            if (token.value.strValue == NULL) {
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
            token.value.strValue[i] = '\0';
            return token;
        }
        default: {
            (*input)++;
            Token token = {TOKEN_INVALID, .value.strValue = malloc(1)};
            token.value.strValue[0] = '\0';
            return token;
        }
    }
}

Token* tokenize(const char **input) {
    printf("Tokenizing...\n");
    Token* tokenArr = malloc(1);
    int len = 0;
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
            case TOKEN_PLUS:
                printf("PLUS ");
                break;
            case TOKEN_MINUS:
                printf("MINUS ");
                break;
            case TOKEN_ASSIGN:
                printf("ASSIGN ");
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
            case TOKEN_MULTIPLY:
                printf("MULTIPLY ");
                break;
            case TOKEN_DIVIDE:
                printf("DIVIDE ");
                break;
            case TOKEN_EQUAL:
                printf("EQUAL ");
                break;
            case TOKEN_NOT_EQUAL:
                printf("NOT_EQUAL ");
                break;
            case TOKEN_GREATER:
                printf("GREATER ");
                break;
            case TOKEN_LESS:
                printf("LESS ");
                break;
            case TOKEN_GREATER_EQUAL:
                printf("GREATER_EQUAL ");
                break;
            case TOKEN_LESS_EQUAL:
                printf("LESS_EQUAL ");
                break;
            case TOKEN_AND:
                printf("AND ");
                break;
            case TOKEN_OR:
                printf("OR ");
                break;
            case TOKEN_NOT:
                printf("NOT ");
                break;
            case TOKEN_IF:
                printf("IF ");
                break;
            case TOKEN_ELSE:
                printf("ELSE ");
                break;
            case TOKEN_INDENT:
                printf("INDENT ");
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
