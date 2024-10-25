#include "parser.h"
#include "variables.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tokenIndex = 0;

Token parse_expression_str(Token token, Token* tokenArr) {
    for (int i = 0; tokenArr[tokenIndex].type != TOKEN_EOF || i < 1; tokenIndex++, i++) {
        Token current_token = tokenArr[tokenIndex];
        if (current_token.type == TOKEN_STRING) {
            token = assign_string(token, current_token.value.strValue);
        } else if (current_token.type == TOKEN_PLUS) {
            continue;
        } else if (current_token.type == TOKEN_IDENTIFIER && get_variable_type(current_token.value.strValue) == 1) {
            token = assign_string(token, get_variable_str(current_token.value.strValue));
        } else if (current_token.type == TOKEN_IDENTIFIER && get_variable_type(current_token.value.strValue) == 0) {
            int value = get_variable_int(current_token.value.strValue);
            char* buffer = to_str(value);
            token = assign_string(token, buffer);
            free(buffer);
        } else if (current_token.type == TOKEN_NUMBER) {
            char* buffer = to_str(current_token.value.intValue);
            token = assign_string(token, buffer);
            free(buffer);
        } else {
            printf("Error: Invalid token in expression.\n");
            exit(1);
        }
    }
    tokenIndex--;
    return token;
}

Token parse_expression_int(Token token, Token* tokenArr) {
    int sign = 1;
    int mode = 0;
    for (int i = 0; tokenArr[tokenIndex].type != TOKEN_EOF || i < 1; tokenIndex++, i++) {
        Token current_token = tokenArr[tokenIndex];
        if (current_token.type == TOKEN_STRING) {
            printf("Error Operation: String can't be included in number operations.\n");
            exit(1);
        } else if (current_token.type == TOKEN_NUMBER) {
            if (mode == 1) {
                token.value.intValue *= sign * current_token.value.intValue;
            } else if (mode == 2) {
                token.value.intValue /= sign * current_token.value.intValue;
            } else {
                token.value.intValue += sign * current_token.value.intValue;
            }
            mode = 0;
        } else if (current_token.type == TOKEN_IDENTIFIER) {
            if (mode == 1) {
                token.value.intValue *= sign * get_variable_int(current_token.value.strValue);
            } else if (mode == 2) {
                token.value.intValue /= sign * get_variable_int(current_token.value.strValue);
            } else {
                token.value.intValue += sign * get_variable_int(current_token.value.strValue);
            }
            mode = 0;
        } else if (current_token.type == TOKEN_PLUS) {
            sign = 1;
        } else if (current_token.type == TOKEN_MINUS) {
            sign = -1;
        } else if (current_token.type == TOKEN_MULTIPLY) {
            mode = 1;
        } else if (current_token.type == TOKEN_DIVIDE) {
            mode = 2;
        } else {
            printf("Error: Invalid token in expression.\n");
            exit(1);
        }
    }
    tokenIndex--;
    return token;
}

void parse_expression_omni(Token* tokenArr) {
    Token current_token = tokenArr[0];
    if (current_token.type == TOKEN_STRING || (current_token.type == TOKEN_IDENTIFIER && get_variable_type(current_token.value.strValue) == 1)) {
        Token token = {TOKEN_STRING, .value.strValue = malloc(1)};
        token.value.strValue[0] = '\0';
        for (; tokenArr[tokenIndex].type != TOKEN_EOF; tokenIndex++) {
             token = parse_expression_str(token, tokenArr);
        }
        char* result = token.value.strValue;
        printf("%s\n", result);
    } else if (current_token.type == TOKEN_NUMBER || (current_token.type == TOKEN_IDENTIFIER && get_variable_type(current_token.value.strValue) == 0)) {
        Token token = {TOKEN_NUMBER, .value.intValue = 0};
        for (; tokenArr[tokenIndex].type != TOKEN_EOF; tokenIndex++) {
            token = parse_expression_int(token, tokenArr);
        }
        int result = token.value.intValue;
        printf("%d\n", result);
    } else {
        printf("Error: Invalid expression.\n");
        exit(1);
    }
    tokenIndex = 0;
}

void parse_assignment(Token* tokenArr) {
    Token current_token = tokenArr[tokenIndex];
    if (current_token.type == TOKEN_IDENTIFIER) {
        char var_name[50];
        strcpy(var_name, current_token.value.strValue);
        current_token = tokenArr[++tokenIndex];
        if (current_token.type == TOKEN_ASSIGN) {
            current_token = tokenArr[++tokenIndex];
            Token result_token = current_token;
            tokenIndex++;
            if (current_token.type == TOKEN_NUMBER) {
                for (; tokenArr[tokenIndex].type != TOKEN_EOF; tokenIndex++) {
                    result_token = parse_expression_int(result_token, tokenArr);
                }
                int value = result_token.value.intValue;
                set_variable_int(var_name, value);
            } else if (current_token.type == TOKEN_STRING) {
                for (; tokenArr[tokenIndex].type != TOKEN_EOF; tokenIndex++) {
                    result_token = parse_expression_str(result_token, tokenArr);
                }
                char* str = result_token.value.strValue;
                char* value = malloc(strlen(str) + 1);
                strcpy(value, str);
                set_variable_str(var_name, value);
            } else {
                printf("Error: Invalid value in assignment.\n");
                exit(1);
            }
        } else {
            printf("Error: Expected '=' after variable name.\n");
            exit(1);
        }
    } else {
        printf("Error: Invalid statement.\n");
        exit(1);
    }
    tokenIndex = 0;
}

int parse_condition(Token* tokenArr) {
    int result = 0;
    for (; tokenArr[tokenIndex].type != TOKEN_EOF; tokenIndex++) {
        Token current_token = tokenArr[tokenIndex];
        if (current_token.type == TOKEN_NUMBER) {
            
        } else if (current_token.type == TOKEN_IDENTIFIER) {
            
        } else if (current_token.type == TOKEN_PLUS) {
           
        } else if (current_token.type == TOKEN_MINUS) {
        } else {
            printf("Error: Invalid token in expression.\n");
            exit(1);
        }
    }
    return result;
}
