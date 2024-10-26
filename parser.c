#include "parser.h"
#include "variables.h"
#include "functions.h"
#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef struct {
    int indent;
    int condition;
    int if_indent;
    int else_flag;
} Condition;

typedef struct {
    Condition data[MAX_STACK_SIZE];
    int top;
} Stack;

void push(Stack* stack, Condition value) {
    if (stack->top < MAX_STACK_SIZE - 1) {
        stack->data[++stack->top] = value;
    } else {
        fprintf(stderr, "Stack overflow\n");
        exit(1);
    }
}

Condition pop(Stack* stack) {
    if (stack->top >= 0) {
        return stack->data[stack->top--];
    } else {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
}

Condition peek(const Stack* stack) {
    if (stack->top >= 0) {
        return stack->data[stack->top];
    } else {
        fprintf(stderr, "Stack is empty\n");
        exit(1);
    }
}

int cursor = 0;
int bool_flag = 0;
int current_indent = 0;

Stack if_stack = {.top = -1};

Token assign_token(Token token){
    Token result_token;
    if(token.type == TOKEN_IDENTIFIER){
        int type = get_variable_type(token.data.strValue);
        if(type == VARIABLE_INT){
            result_token.type = TOKEN_NUMBER;
            result_token.data.intValue = get_variable_int(token.data.strValue);
        }else if(type == VARIABLE_STR){
            result_token.type = TOKEN_STRING;
            result_token.data.strValue = get_variable_str(token.data.strValue);
        }else if(type == VARIABLE_BOOL){
            result_token.type = TOKEN_BOOLEAN;
            result_token.data.intValue = get_variable_bool(token.data.strValue);
        }else{
            printf("Error: Invalid operation.\n");
            exit(1);
        }
    }else{
        return token;
    }
    return result_token;
}

Token parse(Token* arr){
    // Event* eventArr = malloc(sizeof(Event));
    Token left;
    Token right;
    Token operator;
    Token result = {TOKEN_STRING, .data.strValue = "null"};
    if (arr[cursor].type == TOKEN_IF){
        cursor++;
        left = parse(arr);
        if (left.type == TOKEN_BOOLEAN){
            Condition con = {.condition = left.data.intValue, .indent = 0, .if_indent = current_indent, .else_flag = 0};
            push(&if_stack, con);
        }
    }
    while(arr[cursor].type != TOKEN_EOF){
        if(arr[cursor].type == TOKEN_IDENTIFIER){
            if(arr[cursor+1].type == TOKEN_OPERATOR){
                left = arr[cursor];
                cursor++;
                operator = assign_token(arr[cursor]);
                if (arr[cursor + 1].type == TOKEN_CONDITION_START){
                    cursor++;
                    right = parse_condition(arr);
                    result = execute_tokens(left, right, operator);
                } else if (operator.data.opValue.value == OP_ASSIGN){
                    if(arr[cursor + 2].type == TOKEN_EOF){
                        cursor++;
                        right = assign_token(arr[cursor]);
                        execute_tokens(left, right, operator);
                    }else if (operator.data.opValue.type == BOOL_OP){
                        if (bool_flag == 1){
                            break;
                        }
                        bool_flag = 1;
                        if (arr[cursor+2].data.opValue.type != BOOL_OP){
                            cursor++;
                            right = parse(arr);
                        }else{
                            cursor++;
                            right = assign_token(arr[cursor]);
                        }
                        result = execute_tokens(left, right, operator);
                        bool_flag = 0;
                    }else{
                        cursor++;
                        right = parse(arr);
                        execute_tokens(left, right, operator);
                    }
                    result = (Token){TOKEN_NEXT};
                }else{
                    left = assign_token(left);
                    cursor++;
                    right = assign_token(arr[cursor]);
                    result = execute_tokens(left, right, operator);
                }
            } else if(arr[cursor+1].type == TOKEN_EOF){
                result = assign_token(arr[cursor]);
            }
        }else if(arr[cursor].type == TOKEN_NUMBER || arr[cursor].type == TOKEN_STRING || arr[cursor].type == TOKEN_BOOLEAN){
            if (arr[cursor+1].type == TOKEN_EOF){
                result = assign_token(arr[cursor]);
            }else if (arr[cursor+1].type == TOKEN_OPERATOR){
                left = assign_token(arr[cursor]);
                cursor++;
                operator = assign_token(arr[cursor]);
                if (arr[cursor + 1].type == TOKEN_CONDITION_START){
                    cursor++;
                    right = parse_condition(arr);
                    result = execute_tokens(left, right, operator);
                }else if (operator.data.opValue.value == OP_ASSIGN){
                    printf("Error: Can't assign to a value.\n");
                }else if (operator.data.opValue.type == BOOL_OP){
                    if (bool_flag == 1){
                        break;
                    }
                    bool_flag = 1;
                    if (arr[cursor+2].data.opValue.type != BOOL_OP)
                    {
                        cursor++;
                        right = parse(arr);
                    }else{
                        cursor++;
                        right = assign_token(arr[cursor]);
                    }
                    result = execute_tokens(left, right, operator);
                    bool_flag = 0;
                }else{
                    cursor++;
                    right = assign_token(arr[cursor]);
                    result = execute_tokens(left, right, operator);
                }
                
            }else{
                
            }
            
        }else if (arr[cursor].type == TOKEN_OPERATOR){
            left = result;
            operator = assign_token(arr[cursor]);
            if (arr[cursor + 1].type == TOKEN_CONDITION_START){
                cursor++;
                right = parse_condition(arr);
                result = execute_tokens(left, right, operator);
            } else if (operator.data.opValue.type == BOOL_OP){
                if (bool_flag == 1){
                    break;
                }
                bool_flag = 1;
                if (arr[cursor+2].data.opValue.type != BOOL_OP)
                {
                    cursor++;
                    right = parse(arr);
                }else{
                    cursor++;
                    right = assign_token(arr[cursor]);
                }
                result = execute_tokens(left, right, operator);
                bool_flag = 0;
            }else{
                cursor++;
                right = assign_token(arr[cursor]);
                result = execute_tokens(left, right, operator);
            }
        }else if (arr[cursor].type == TOKEN_CONDITION_START){
            cursor++;
            right = parse_condition(arr);
            result = execute_tokens(left, right, operator);
        }
        if (arr[cursor].type == TOKEN_EOF){
            break;
        }
        
        cursor++;
    }

    
    return result;
}

Token parse_condition(Token* arr){
    printf("Parsing condition\n");
    Token left;
    Token right;
    Token operator;
    Token result = {TOKEN_STRING, .data.strValue = "null"};
    cursor++;
    while(arr[cursor].type != TOKEN_CONDITION_END){
        printf("start cursor: %d\n", cursor);
        if(arr[cursor].type == TOKEN_IDENTIFIER){
            if(arr[cursor+1].type == TOKEN_OPERATOR){
                left = arr[cursor];
                cursor++;
                operator = assign_token(arr[cursor]);
                if (arr[cursor + 1].type == TOKEN_CONDITION_START){
                    cursor++;
                    right = parse_condition(arr);
                    result = execute_tokens(left, right, operator);
                } else if (operator.data.opValue.value == OP_ASSIGN){
                    if(arr[cursor + 2].type == TOKEN_EOF){
                        cursor++;
                        right = assign_token(arr[cursor]);
                        execute_tokens(left, right, operator);
                    }else if (operator.data.opValue.type == BOOL_OP){
                        if (bool_flag == 1){
                            break;
                        }
                        bool_flag = 1;
                        if (arr[cursor+2].data.opValue.type != BOOL_OP){
                            cursor++;
                            right = parse(arr);
                        }else{
                            cursor++;
                            right = assign_token(arr[cursor]);
                        }
                        result = execute_tokens(left, right, operator);
                        bool_flag = 0;
                    }else{
                        cursor++;
                        right = parse(arr);
                        execute_tokens(left, right, operator);
                    }
                    result = (Token){TOKEN_NEXT};
                }else{
                    left = assign_token(left);
                    cursor++;
                    right = assign_token(arr[cursor]);
                    result = execute_tokens(left, right, operator);
                }
            } else if(arr[cursor+1].type == TOKEN_EOF){
                result = assign_token(arr[cursor]);
            }
        }else if(arr[cursor].type == TOKEN_NUMBER || arr[cursor].type == TOKEN_STRING || arr[cursor].type == TOKEN_BOOLEAN){
            if (arr[cursor+1].type == TOKEN_EOF){
                result = assign_token(arr[cursor]);
            }else if (arr[cursor+1].type == TOKEN_OPERATOR){
                left = assign_token(arr[cursor]);
                cursor++;
                operator = assign_token(arr[cursor]);
                if (arr[cursor + 1].type == TOKEN_CONDITION_START){
                    cursor++;
                    right = parse_condition(arr);
                    result = execute_tokens(left, right, operator);
                }else if (operator.data.opValue.value == OP_ASSIGN){
                    printf("Error: Can't assign to a value.\n");
                }else if (operator.data.opValue.type == BOOL_OP){
                    if (bool_flag == 1){
                        break;
                    }
                    bool_flag = 1;
                    if (arr[cursor+2].data.opValue.type != BOOL_OP)
                    {
                        cursor++;
                        right = parse(arr);
                    }else{
                        cursor++;
                        right = assign_token(arr[cursor]);
                    }
                    result = execute_tokens(left, right, operator);
                    bool_flag = 0;
                }else{
                    cursor++;
                    right = assign_token(arr[cursor]);
                    result = execute_tokens(left, right, operator);
                }
                
            }else{
                
            }
            
        }else if (arr[cursor].type == TOKEN_OPERATOR){
            left = result;
            operator = assign_token(arr[cursor]);
            if (arr[cursor + 1].type == TOKEN_CONDITION_START){
                cursor++;
                right = parse_condition(arr);
                result = execute_tokens(left, right, operator);
            } else if (operator.data.opValue.type == BOOL_OP){
                if (bool_flag == 1){
                    break;
                }
                bool_flag = 1;
                if (arr[cursor+2].data.opValue.type != BOOL_OP)
                {
                    cursor++;
                    right = parse(arr);
                }else{
                    cursor++;
                    right = assign_token(arr[cursor]);
                }
                result = execute_tokens(left, right, operator);
                bool_flag = 0;
            }else{
                cursor++;
                right = assign_token(arr[cursor]);
                result = execute_tokens(left, right, operator);
            }
        }else if (arr[cursor].type == TOKEN_CONDITION_START){
            cursor++;
            right = parse_condition(arr);
            result = execute_tokens(left, right, operator);
        }
        if (arr[cursor].type == TOKEN_EOF){
            break;
        }
        printf("end cursor: %d\n", cursor);
        cursor++;
    }
    return result;
}
Token parse_main(Token* arr){
    cursor = 0;
    current_indent = 0;
    if (if_stack.top != -1){
        while (arr[cursor].type == TOKEN_INDENT){
            current_indent++;
            cursor++;
        }
        if(peek(&if_stack).indent == 0){
            Condition con = pop(&if_stack);
            con.indent = current_indent;
            push(&if_stack, con);
        }
        if (current_indent == peek(&if_stack).if_indent && arr[cursor].type == TOKEN_ELSE){
            Condition con = pop(&if_stack);
            con.else_flag = 1;
            push(&if_stack, con);
        }
        if (current_indent < peek(&if_stack).indent){
            pop(&if_stack);
            return parse_main(arr);
        }else if (current_indent == peek(&if_stack).indent){
            if (peek(&if_stack).condition == 1){
                if (peek(&if_stack).else_flag == 1){
                    return (Token){TOKEN_NEXT};
                }
                
                return parse(arr);
            } else if (peek(&if_stack).condition == 0 && peek(&if_stack).else_flag == 1){
                return parse(arr);
            }else{
                return (Token){TOKEN_NEXT};
            }
        }
        
    }else{
        return parse(arr);
    }
}