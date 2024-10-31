#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"

Token parse(Token* arr);
Token parse_main(Token* arr);
Token parse_condition(Token* arr);
void set_meta(const char* line, int line_number);
void print_error(Token error_token, char* error_type, char* error_message);
Token op_not(Token token);
#endif // PARSER_H
