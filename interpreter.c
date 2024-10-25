#include "interpreter.h"
#include "parser.h"
#include "lexer.h"
#include <stdio.h>
#include <string.h>

void interpret(const char *line) {
    const char *cursor = line;
    Token* tokenArr = tokenize(&cursor);
    print_token_string(tokenArr);
    if (check_token(tokenArr, TOKEN_ASSIGN)) {
        parse_assignment(tokenArr);
    } else {
        parse_expression_omni(tokenArr);
    }
}
