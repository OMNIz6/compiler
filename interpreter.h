/**
 * @file interpreter.h
 * @brief Header file for the interpreter module.
 *
 * This file contains the declaration of the interpret function, which is
 * responsible for interpreting a line of code.
 */

#ifndef INTERPRETER_H
#define INTERPRETER_H

/**
 * @brief Interprets a line of code.
 *
 * This function takes a line of code as input and interprets it. The line
 * number is also provided for error reporting and debugging purposes.
 *
 * @param line The line of code to interpret.
 * @param line_number The line number of the code being interpreted.
 */
void interpret(const char *line, int line_number);

#endif
