#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"

Token parse_expression_str(Token token, Token* tokenArr);
Token parse_expression_int(Token token, Token* tokenArr);
void parse_expression_omni(Token* tokenArr);
void parse_assignment(Token* tokenArr);


#endif // PARSER_H
