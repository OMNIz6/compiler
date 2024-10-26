#include "interpreter.h"
#include "parser.h"
#include "lexer.h"
#include <stdio.h>
#include <string.h>

void interpret(const char *line) {
    const char *cursor = line;
    Token* tokenArr = tokenize(&cursor);
    print_token_string(tokenArr);
    
    Token result = parse_main(tokenArr);
    if (result.type == TOKEN_NEXT) {
        printf("Next\n");
    } else if (result.type == TOKEN_NUMBER) {
        printf("Result: %d\n", result.data.intValue);
    } else if (result.type == TOKEN_STRING) {
        printf("Result: %s\n", result.data.strValue);
    } else if (result.type == TOKEN_BOOLEAN) {
        printf("Result: %s\n", result.data.intValue ? "true" : "false");
    }
    
}
