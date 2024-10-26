#ifndef EXECUTER_H
#define EXECUTER_H
#include "lexer.h"
#include <stdio.h>

Token execute_tokens(Token left_token, Token right_token, Token operator_token);
Token get_boolean(Token token);
#endif // EXECUTER_H