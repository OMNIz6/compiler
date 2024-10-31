#include "variables.h"
#include "functions.h"
#include "executor.h"

Token execute_tokens(Token left_token, Token right_token, Token operator_token){
    Token result_token;
    // printf("left: %s\n", left_token.data.strValue);
    // printf("right: %s\n", right_token.data.strValue);
    // printf("left: %d\n", left_token.data.intValue);
    // printf("right: %d\n", right_token.data.intValue);

    switch (operator_token.data.opValue.value) {
        case OP_PLUS:
            if(left_token.type == TOKEN_NUMBER && right_token.type == TOKEN_NUMBER){
                result_token.type = TOKEN_NUMBER;
                result_token.data.intValue = left_token.data.intValue + right_token.data.intValue;
            }else if(left_token.type == TOKEN_STRING && right_token.type == TOKEN_STRING){
                result_token.type = TOKEN_STRING;
                result_token.data.strValue = malloc(strlen(left_token.data.strValue) + strlen(right_token.data.strValue) + 1);
                strcpy(result_token.data.strValue, left_token.data.strValue);
                strcat(result_token.data.strValue, right_token.data.strValue);
            }else if(left_token.type == TOKEN_STRING && right_token.type == TOKEN_NUMBER){
                result_token = left_token;
                char* str = to_str(right_token.data.intValue);
                result_token = assign_string(result_token, str);
            }else if (left_token.type == TOKEN_STRING && right_token.type == TOKEN_BOOLEAN){
                result_token = left_token;
                char* str = right_token.data.intValue ? "true" : "false";
                result_token = assign_string(result_token, str);
            }else{
                printf("Error: operation not allowed.\n");
                exit(1);
            }
            break;
        case OP_MINUS:
            if(left_token.type == TOKEN_NUMBER && right_token.type == TOKEN_NUMBER){
                result_token.type = TOKEN_NUMBER;
                result_token.data.intValue = left_token.data.intValue - right_token.data.intValue;
            }else{
                printf("Error: operation not allowed.\n");
                exit(1);
            }
            break;
        case OP_MULTIPLY:
            if(left_token.type == TOKEN_NUMBER && right_token.type == TOKEN_NUMBER){
                result_token.type = TOKEN_NUMBER;
                result_token.data.intValue = left_token.data.intValue * right_token.data.intValue;
            }else{
                printf("Error: operation not allowed.\n");
                exit(1);
            }
            break;
        case OP_DIVIDE:
            if(left_token.type == TOKEN_NUMBER && right_token.type == TOKEN_NUMBER){
                result_token.type = TOKEN_NUMBER;
                result_token.data.intValue = left_token.data.intValue / right_token.data.intValue;
            }else{
                printf("Error: operation not allowed.\n");
                exit(1);
            }
            break;
        case OP_EQUAL:
            if(left_token.type == TOKEN_NUMBER && right_token.type == TOKEN_NUMBER){
                result_token.type = TOKEN_BOOLEAN;
                result_token.data.intValue = left_token.data.intValue == right_token.data.intValue;
            }else if(left_token.type == TOKEN_STRING && right_token.type == TOKEN_STRING){
                result_token.type = TOKEN_BOOLEAN;
                result_token.data.intValue = strcmp(left_token.data.strValue, right_token.data.strValue) == 0;
            }else if (left_token.type == TOKEN_BOOLEAN && right_token.type == TOKEN_BOOLEAN){
                result_token.type = TOKEN_BOOLEAN;
                result_token.data.intValue = left_token.data.intValue == right_token.data.intValue;
            }else{
                printf("Error: operation not allowed.\n");
                exit(1);
            }
            break;
        case OP_NOT_EQUAL:
            if(left_token.type == TOKEN_NUMBER && right_token.type == TOKEN_NUMBER){
                result_token.type = TOKEN_BOOLEAN;
                result_token.data.intValue = left_token.data.intValue != right_token.data.intValue;
            }else if(left_token.type == TOKEN_STRING && right_token.type == TOKEN_STRING){
                result_token.type = TOKEN_BOOLEAN;
                result_token.data.intValue = strcmp(left_token.data.strValue, right_token.data.strValue) != 0;
            }else{
                printf("Error: operation not allowed.\n");
                exit(1);
            }
            break;
        case OP_GREATER:
            if(left_token.type == TOKEN_NUMBER && right_token.type == TOKEN_NUMBER){
                result_token.type = TOKEN_BOOLEAN;
                result_token.data.intValue = left_token.data.intValue > right_token.data.intValue;
            }else{
                printf("Error: operation not allowed.\n");
                exit(1);
            }
            break;
        case OP_LESS:
            if(left_token.type == TOKEN_NUMBER && right_token.type == TOKEN_NUMBER){
                result_token.type = TOKEN_BOOLEAN;
                result_token.data.intValue = left_token.data.intValue < right_token.data.intValue;
            }else{
                printf("Error: operation not allowed.\n");
                exit(1);
            }
            break;
        case OP_GREATER_EQUAL:
            if(left_token.type == TOKEN_NUMBER && right_token.type == TOKEN_NUMBER){
                result_token.type = TOKEN_BOOLEAN;
                result_token.data.intValue = left_token.data.intValue >= right_token.data.intValue;
            }else{
                printf("Error: operation not allowed.\n");
                exit(1);
            }
            break;
        case OP_LESS_EQUAL:
            if(left_token.type == TOKEN_NUMBER && right_token.type == TOKEN_NUMBER){
                result_token.type = TOKEN_BOOLEAN;
                result_token.data.intValue = left_token.data.intValue <= right_token.data.intValue;
            }else{
                printf("Error: operation not allowed.\n");
                exit(1);
            }
            break;
        case OP_AND:
            left_token = get_boolean(left_token);
            right_token = get_boolean(right_token);
            if(left_token.type == TOKEN_BOOLEAN && right_token.type == TOKEN_BOOLEAN){
                result_token.type = TOKEN_BOOLEAN;
                result_token.data.intValue = left_token.data.intValue && right_token.data.intValue;
            }else{
                printf("Error: operation not allowed.\n");
                exit(1);
            }
            break;
        case OP_OR:
            left_token = get_boolean(left_token);
            right_token = get_boolean(right_token);
            if(left_token.type == TOKEN_BOOLEAN && right_token.type == TOKEN_BOOLEAN){
                result_token.type = TOKEN_BOOLEAN;
                result_token.data.intValue = left_token.data.intValue || right_token.data.intValue;
            }else{
                printf("Error: operation not allowed.\n");
                exit(1);
            }
            break;
        case OP_ASSIGN:
            if(left_token.type == TOKEN_IDENTIFIER){
                if(right_token.type == TOKEN_NUMBER){
                    set_variable_int(left_token.data.strValue, right_token.data.intValue);
                }else if(right_token.type == TOKEN_STRING){
                    set_variable_str(left_token.data.strValue, right_token.data.strValue);
                }else if(right_token.type == TOKEN_BOOLEAN){
                    set_variable_bool(left_token.data.strValue, right_token.data.intValue);
                }else{
                    printf("Error: operation not allowed.\n");
                    exit(1);
                }
            }else{
                printf("Error: operation not allowed.\n");
                exit(1);
            }
            break;
        default:
            printf("Error: operation not allowed.\n");
            exit(1);
            break;
    }
    return result_token;
}

Token get_boolean(Token token){
    Token result_token;
    if(token.type == TOKEN_BOOLEAN){
        result_token.type = TOKEN_BOOLEAN;
        result_token.data.intValue = token.data.intValue;
    }else if(token.type == TOKEN_IDENTIFIER){
        int type = get_variable_type(token.data.strValue);
        if(type == VARIABLE_BOOL){
            result_token.type = TOKEN_BOOLEAN;
            result_token.data.intValue = get_variable_bool(token.data.strValue);
        }else{
            printf("Error: operation not allowed.\n");
            exit(1);
        }
    }else if(token.type == TOKEN_NUMBER){
        if(token.data.intValue > 0 ){
            result_token.type = TOKEN_BOOLEAN;
            result_token.data.intValue = 1;
        }else{
            result_token.type = TOKEN_BOOLEAN;
            result_token.data.intValue = 0;
        }
    }else if (token.type == TOKEN_STRING){
        if(strlen(token.data.strValue) > 0){
            result_token.type = TOKEN_BOOLEAN;
            result_token.data.intValue = 1;
        }else{
            result_token.type = TOKEN_BOOLEAN;
            result_token.data.intValue = 0;
        }
    }
    else{
        printf("Error: operation not allowed.\n");
        exit(1);
    }
    return result_token;
}