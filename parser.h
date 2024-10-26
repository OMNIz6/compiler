#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"

Token parse(Token* arr);
Token parse_main(Token* arr);
Token parse_condition(Token* arr);

#endif // PARSER_H
