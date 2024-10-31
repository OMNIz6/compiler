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

Token get_next_token(const char **input, int *index, int *char_count) {
    while (isspace(**input)) {(*input)++; (*index)++;};

    Token token;
    token.index = *index;

    if (isdigit(**input)) {
        token.type = TOKEN_NUMBER;
        token.data.intValue = 0;
        while (isdigit(**input)) {
            token.data.intValue = token.data.intValue * 10 + (*(*input)++ - '0');
            (*char_count)++;
        }
        return token;
    }

    if (isalpha(**input)) {
        const char *start = *input;
        char name[50];
        int i = 0;
        while (isalnum(**input)) {
            name[i++] = *(*input)++;
            (*char_count)++;
        }
        name[i] = '\0';
        if (strcmp(name, "if") == 0) {
            token.type = TOKEN_IF;
            token.data.strValue = malloc(1);
            token.data.strValue[0] = '\0';
            strcpy(token.data.strValue, name);
        } else if (strcmp(name, "else") == 0) {
            token.type = TOKEN_ELSE;
            token.data.strValue = malloc(1);
            token.data.strValue[0] = '\0';
            strcpy(token.data.strValue, name);
        } else if (strcmp(name, "true") == 0) {
            token.type = TOKEN_BOOLEAN;
            token.data.intValue = 1;
        } else if (strcmp(name, "false") == 0) {
            token.type = TOKEN_BOOLEAN;
            token.data.intValue = 0;
        } else if (strcmp(name, "and") == 0) {
            token.type = TOKEN_OPERATOR;
            token.data.opValue = (Operator){BOOL_OP, OP_AND};
        } else if (strcmp(name, "or") == 0) {
            token.type = TOKEN_OPERATOR;
            token.data.opValue = (Operator){BOOL_OP, OP_OR};
        } else {
            token.type = TOKEN_IDENTIFIER;
            token.data.strValue = malloc(1);
            token.data.strValue[0] = '\0';
            strcpy(token.data.strValue, name);
        }
        return token;
    }

    switch (**input) {
        case '+':
            (*input)++;
            (*char_count)++;
            token.type = TOKEN_OPERATOR;
            token.data.opValue = (Operator){MATH_OP, OP_PLUS};
            return token;
        case '-':
            (*input)++;
            (*char_count)++;
            token.type = TOKEN_OPERATOR;
            token.data.opValue = (Operator){MATH_OP, OP_MINUS};
            return token;
        case '*':
            (*input)++;
            (*char_count)++;
            token.type = TOKEN_OPERATOR;
            token.data.opValue = (Operator){MATH_OP, OP_MULTIPLY};
            return token;
        case '/':
            (*input)++;
            (*char_count)++;
            token.type = TOKEN_OPERATOR;
            token.data.opValue = (Operator){MATH_OP, OP_DIVIDE};
            return token;
        case '=':
            (*input)++;
            (*char_count)++;
            if (**input == '=') {
                (*input)++;
                (*char_count)++;
                token.type = TOKEN_OPERATOR;
                token.data.opValue = (Operator){BOOL_OP, OP_EQUAL};
            } else {
                token.type = TOKEN_OPERATOR;
                token.data.opValue = (Operator){ASSIGN_OP, OP_ASSIGN};
            }
            return token;
        case '>':
            (*input)++;
            (*char_count)++;
            if (**input == '=') {
                (*input)++;
                (*char_count)++;
                token.type = TOKEN_OPERATOR;
                token.data.opValue = (Operator){BOOL_OP, OP_GREATER_EQUAL};
            } else {
                token.type = TOKEN_OPERATOR;
                token.data.opValue = (Operator){BOOL_OP, OP_GREATER};
            }
            return token;
        case '<':
            (*input)++;
            (*char_count)++;
            if (**input == '=') {
                (*input)++;
                (*char_count)++;
                token.type = TOKEN_OPERATOR;
                token.data.opValue = (Operator){BOOL_OP, OP_LESS_EQUAL};
            } else {
                token.type = TOKEN_OPERATOR;
                token.data.opValue = (Operator){BOOL_OP, OP_LESS};
            }
            return token;
        case '!':
            (*input)++;
            (*char_count)++;
            if (**input == '=') {
                (*input)++;
                (*char_count)++;
                token.type = TOKEN_OPERATOR;
                token.data.opValue = (Operator){BOOL_OP, OP_NOT_EQUAL};
            } else {
                token.type = TOKEN_OPERATOR;
                token.data.opValue = (Operator){BOOL_OP, OP_NOT};
            }
            return token;
        case '&':
            (*input)++;
            (*char_count)++;
            if (**input == '&') {
                (*input)++;
                (*char_count)++;
                token.type = TOKEN_OPERATOR;
                token.data.opValue = (Operator){BOOL_OP, OP_AND};
            } else {
                token.type = TOKEN_INVALID;
                token.data.strValue = malloc(1);
                token.data.strValue[0] = '\0';
            }
            return token;
        case '|':
            (*input)++;
            (*char_count)++;
            if (**input == '|') {
                (*input)++;
                (*char_count)++;
                token.type = TOKEN_OPERATOR;
                token.data.opValue = (Operator){BOOL_OP, OP_OR};
            } else {
                token.type = TOKEN_INVALID;
                token.data.strValue = malloc(1);
                token.data.strValue[0] = '\0';
            }
            return token;
        case '\0':
            token.type = TOKEN_EOF;
            token.data.strValue = malloc(1);
            token.data.strValue[0] = 'e';
            return token;
        case '"': {
            token.type = TOKEN_STRING;
            token.data.strValue = malloc(1);
            token.data.strValue[0] = '\0';
            if (token.data.strValue == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
            }
            (*input)++;
            (*char_count)++;
            int i = 0;
            char* str = malloc(1);
            while (**input != '"') {
                str = realloc(str, i + 1);
                str[i++] = *(*input)++;
                (*char_count)++;
            }
            token = assign_string(token, str);
            (*input)++;
            (*char_count)++;
            token.data.strValue[i] = '\0';
            return token;
        }
        case '\'': {
            token.type = TOKEN_STRING;
            token.data.strValue = malloc(1);
            token.data.strValue[0] = '\0';
            if (token.data.strValue == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
            }
            (*input)++;
            (*char_count)++;
            int i = 0;
            char* str = malloc(1);
            while (**input != '\'') {
                str = realloc(str, i + 1);
                str[i++] = *(*input)++;
                (*char_count)++;
            }
            token = assign_string(token, str);
            (*input)++;
            (*char_count)++;
            token.data.strValue[i] = '\0';
            return token;
        }
        case '(':
            (*input)++;
            (*char_count)++;
            token.type = TOKEN_CONDITION_START;
            token.data.strValue = malloc(1);
            token.data.strValue[0] = '\0';
            return token;
        case ')':
            (*input)++;
            (*char_count)++;
            token.type = TOKEN_CONDITION_END;
            token.data.strValue = malloc(1);
            token.data.strValue[0] = '\0';
            return token;
        case '{':
            (*input)++;
            (*char_count)++;
            token.type = TOKEN_BLOCK_START;
            token.data.strValue = malloc(1);
            token.data.strValue[0] = '\0';
            return token;
        case '}':
            (*input)++;
            (*char_count)++;
            token.type = TOKEN_BLOCK_END;
            token.data.strValue = malloc(1);
            token.data.strValue[0] = '\0';
            return token;
        default:
            (*input)++;
            (*char_count)++;
            token.type = TOKEN_INVALID;
            token.data.strValue = malloc(1);
            token.data.strValue[0] = '\0';
            return token;
    }
}

Token* tokenize(const char **input) {
    Token* tokenArr = malloc(1);
    int len = 0;
    int index = 0;
    int char_count = 0;

    while (isspace(**input)) {
        if (**input == '\n') {
            index++;
            char_count = 0;
        }
        (*input)++;
        char_count++;
        Token token = {TOKEN_INDENT, .data.strValue = malloc(1), index, char_count};
        token.data.strValue[0] = '\0';
        tokenArr = realloc(tokenArr, (len + 1) * sizeof(Token));
        tokenArr[len++] = token;
        index = index + char_count-1;
        char_count = 0;
    }

    Token token = get_next_token(input, &index, &char_count);
    token.count = char_count;
    index = index + char_count;
    char_count = 0;
    

    while (1) {
        tokenArr = realloc(tokenArr, (len + 1) * sizeof(Token));
        tokenArr[len++] = token;
        if (token.type == TOKEN_EOF) {
            break;
        } else {
            token = get_next_token(input, &index, &char_count);
        }
        token.count = char_count;
        index = index + char_count;
        char_count = 0;
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
