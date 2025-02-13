/**
 * @file lexer.h
 * @brief Header file for the lexer component of the compiler.
 *
 * This file contains the definitions and function declarations for tokenizing
 * the input source code.
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <string.h>

/**
 * @enum TokenType
 * @brief Enum representing different types of tokens.
 */
typedef enum {
    TOKEN_NUMBER,          /**< Numeric token */
    TOKEN_IDENTIFIER,      /**< Identifier token */
    TOKEN_EOF,             /**< End of file token */
    TOKEN_INVALID,         /**< Invalid token */
    TOKEN_STRING,          /**< String token */
    TOKEN_IF,              /**< 'if' keyword token */
    TOKEN_ELSE,            /**< 'else' keyword token */
    TOKEN_CONDITION_START, /**< Condition start token */
    TOKEN_CONDITION_END,   /**< Condition end token */
    TOKEN_BLOCK_START,     /**< Block start token */
    TOKEN_BLOCK_END,       /**< Block end token */
    TOKEN_BOOLEAN,         /**< Boolean token */
    TOKEN_OPERATOR,        /**< Operator token */
    TOKEN_INDENT,          /**< Indentation token */
    TOKEN_NEXT             /**< Next token */
} TokenType;

/**
 * @enum OperatorType
 * @brief Enum representing different types of operators.
 */
typedef enum {
    MATH_OP,   /**< Mathematical operator */
    BOOL_OP,   /**< Boolean operator */
    ASSIGN_OP  /**< Assignment operator */
} OperatorType;

/**
 * @enum OperatorValue
 * @brief Enum representing different operator values.
 */
typedef enum {
    OP_PLUS,          /**< '+' operator */
    OP_MINUS,         /**< '-' operator */
    OP_MULTIPLY,      /**< '*' operator */
    OP_DIVIDE,        /**< '/' operator */
    OP_EQUAL,         /**< '==' operator */
    OP_NOT_EQUAL,     /**< '!=' operator */
    OP_GREATER,       /**< '>' operator */
    OP_LESS,          /**< '<' operator */
    OP_GREATER_EQUAL, /**< '>=' operator */
    OP_LESS_EQUAL,    /**< '<=' operator */
    OP_AND,           /**< '&&' operator */
    OP_OR,            /**< '||' operator */
    OP_NOT,           /**< '!' operator */
    OP_ASSIGN         /**< '=' operator */
} OperatorValue;

/**
 * @struct Operator
 * @brief Struct representing an operator with its type and value.
 */
typedef struct {
    OperatorType type;  /**< Type of the operator */
    OperatorValue value; /**< Value of the operator */
} Operator;

/**
 * @union TokenValue
 * @brief Union representing the value of a token.
 */
typedef union {
    int intValue;      /**< Integer value */
    char* strValue;    /**< String value */
    Operator opValue;  /**< Operator value */
} TokenValue;

/**
 * @struct Token
 * @brief Struct representing a token with its type, value, and position.
 */
typedef struct {
    TokenType type;    /**< Type of the token */
    TokenValue data;   /**< Value of the token */
    int index;         /**< Index of the token in the input */
    int count;         /**< Count of the token */
} Token;

/**
 * @brief Get the next token from the input.
 *
 * @param input Pointer to the input string.
 * @param line Pointer to the current line number.
 * @param char_count Pointer to the current character count.
 * @return The next token.
 */
Token get_next_token(const char **input, int *line, int *char_count);

/**
 * @brief Tokenize the input string.
 *
 * @param input Pointer to the input string.
 * @return Array of tokens.
 */
Token* tokenize(const char **input);

/**
 * @brief Print the string representation of tokens.
 *
 * @param arr Array of tokens.
 */
void print_token_string(Token* arr);

/**
 * @brief Check if a token matches a specific type.
 *
 * @param arr Array of tokens.
 * @param type Type to check against.
 * @return 1 if the token matches the type, 0 otherwise.
 */
int check_token(Token* arr, TokenType type);

/**
 * @brief Assign a string value to a token.
 *
 * @param token The token to assign the string to.
 * @param str The string to assign.
 * @return The token with the assigned string.
 */
Token assign_string(Token token, char* str);

#endif // TOKEN_H