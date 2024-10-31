/**
 * @file parser.h
 * @brief Header file for the parser module.
 *
 * This file contains function declarations for parsing tokens.
 */

#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

/**
 * @brief Parses an array of tokens.
 *
 * @param arr Array of tokens to be parsed.
 * @return Parsed token.
 */
Token parse(Token* arr);

/**
 * @brief Parses the main function tokens.
 *
 * @param arr Array of tokens to be parsed.
 * @return Parsed token.
 */
Token parse_main(Token* arr);

/**
 * @brief Parses condition tokens.
 *
 * @param arr Array of tokens to be parsed.
 * @return Parsed token.
 */
Token parse_condition(Token* arr);

/**
 * @brief Sets metadata for the parser.
 *
 * @param line The line of code.
 * @param line_number The line number in the source code.
 */
void set_meta(const char* line, int line_number);

/**
 * @brief Prints an error message.
 *
 * @param error_token The token where the error occurred.
 * @param error_type The type of error.
 * @param error_message The error message.
 */
void print_error(Token error_token, char* error_type, char* error_message);

/**
 * @brief Performs a logical NOT operation on a token.
 *
 * @param token The token to be negated.
 * @return The negated token.
 */
Token op_not(Token token);

#endif // PARSER_H