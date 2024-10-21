#include "parser.h"
#include "lexer.h"
#include "variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* parse_expression_str(const char **input, Token current_token){
    char* result = malloc(1);
    result[0] = '\0'; 
    while (current_token.type != TOKEN_EOF && current_token.type != TOKEN_INVALID) {
        int end_flag = 0;
        if (current_token.type == TOKEN_STRING_LITERAL && end_flag == 0) {
            end_flag = 1;
            current_token = get_next_token(input);
            while (current_token.type != TOKEN_STRING_LITERAL)
            {
                size_t new_length = strlen(result) + strlen(current_token.value.strValue) + 1;
                result = realloc(result, new_length);

                strcat(result, current_token.value.strValue);
                current_token = get_next_token(input);
            }
            current_token = get_next_token(input);
        }else if (current_token.type == TOKEN_PLUS) {
            current_token = get_next_token(input);
        } else if (current_token.type == TOKEN_IDENTIFIER && get_variable_type(current_token.value.strValue) == 1) {
            size_t new_length = strlen(result) + strlen(get_variable_str(current_token.value.strValue)) + 1;
            result = realloc(result, new_length);
            strcat(result, get_variable_str(current_token.value.strValue));
            current_token = get_next_token(input);
        } else {
            printf("Error: Invalid token in expression.\n");
            exit(1);
        }
    }
    return result;
}

int parse_expression_int(const char **input, Token current_token) {
    printf("parse_expression_omni\n");
    int result = 0;
    int sign = 1;

    while (current_token.type != TOKEN_EOF && current_token.type != TOKEN_INVALID) {
        if (current_token.type == TOKEN_NUMBER) {
            result += sign * current_token.value.intValue;
            current_token = get_next_token(input);
        } else if (current_token.type == TOKEN_IDENTIFIER) {
            result += sign * get_variable_int(current_token.value.strValue);
            current_token = get_next_token(input);
        } else if (current_token.type == TOKEN_PLUS) {
            sign = 1;
            current_token = get_next_token(input);
        } else if (current_token.type == TOKEN_MINUS) {
            sign = -1;
            current_token = get_next_token(input);
        } else {
            printf("Error: Invalid token in expression.\n");
            exit(1);
        }
    }
    return result;
}


void parse_expression_omni(const char **input, Token current_token){
    if ((strcmp(current_token.value.strValue, "\"") == 0) || (current_token.type == TOKEN_IDENTIFIER && get_variable_type(current_token.value.strValue) == 1)) {
        char* result = parse_expression_str(input, current_token);
        printf("%s\n", result);
    }else if (current_token.type == TOKEN_NUMBER || (current_token.type == TOKEN_IDENTIFIER && get_variable_type(current_token.value.strValue) == 0)) {
        int result = parse_expression_int(input, current_token);
        printf("%d\n", result);
    } else {
        printf("Error: Invalid expression.\n");
        exit(1);
    }
}

void parse_assignment(const char *input) {
    const char *cursor = input;
    Token current_token = get_next_token(&cursor);
    if (current_token.type == TOKEN_IDENTIFIER) {
        char var_name[50];
        strcpy(var_name, current_token.value.strValue);
        current_token = get_next_token(&cursor);
        if (current_token.type == TOKEN_ASSIGN) {
            current_token = get_next_token(&cursor);
            if (current_token.type == TOKEN_NUMBER) {
                int value = parse_expression_int(&cursor, current_token);
                set_variable_int(var_name, value);
            } else if (current_token.type == TOKEN_STRING_LITERAL) {
                char* value = parse_expression_str(&cursor, current_token);
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
}