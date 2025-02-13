/**
 * @file executor.h
 * @brief Header file for token execution functions.
 *
 * This file contains the declarations for functions that execute tokens
 * and handle boolean token operations.
 */

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "lexer.h"
#include <stdio.h>

/**
 * @brief Executes the given tokens based on the operator token.
 *
 * This function takes two operand tokens and an operator token, and
 * performs the operation specified by the operator token on the operand tokens.
 *
 * @param left_token The left operand token.
 * @param right_token The right operand token.
 * @param operator_token The operator token specifying the operation.
 * @return The result of the operation as a Token.
 */
Token execute_tokens(Token left_token, Token right_token, Token operator_token);

/**
 * @brief Converts a token to its boolean representation.
 *
 * This function takes a token and converts it to a boolean token.
 *
 * @param token The token to be converted.
 * @return The boolean representation of the token.
 */
Token get_boolean(Token token);

#endif // EXECUTOR_H