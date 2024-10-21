#include "interpreter.h"
#include "parser.h"
#include "lexer.h"
#include <stdio.h>
#include <string.h>

void parse_expression_omni(const char **input, Token current_token);

void interpret(const char *line) {
    if (strchr(line, '=')) {
        parse_assignment(line);
    } else {
        const char *cursor = line;
        Token token = get_next_token(&cursor);
        parse_expression_omni(&cursor, token);
    }
}
