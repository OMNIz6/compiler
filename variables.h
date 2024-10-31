/**
 * @file variables.h
 * @brief Header file for variable management in the compiler.
 *
 * This file contains the definitions and function declarations for managing
 * variables of different data types (int, string, bool) in the compiler.
 */

#ifndef VARIABLES_H
#define VARIABLES_H

#include <stdbool.h>

/**
 * @enum DataType
 * @brief Enum to represent the type of a variable.
 */
typedef enum {
    VARIABLE_INT,  /**< Integer variable */
    VARIABLE_STR,  /**< String variable */
    VARIABLE_BOOL  /**< Boolean variable */
} DataType;

/**
 * @union Value
 * @brief Union to store the value of a variable.
 */
typedef union {
    int intValue;     /**< Integer value */
    char* strValue;   /**< String value */
    bool boolValue;   /**< Boolean value */
} Value;

/**
 * @struct VarType
 * @brief Struct to represent a variable with its type and name.
 */
typedef struct {
    DataType type;  /**< Type of the variable */
    char* name;     /**< Name of the variable */
} VarType;

/**
 * @brief Set the value of an integer variable.
 * 
 * @param name The name of the variable.
 * @param value The integer value to set.
 */
void set_variable_int(const char *name, int value);

/**
 * @brief Set the value of a string variable.
 * 
 * @param name The name of the variable.
 * @param value The string value to set.
 */
void set_variable_str(const char *name, const char *value);

/**
 * @brief Set the value of a boolean variable.
 * 
 * @param name The name of the variable.
 * @param value The boolean value to set.
 */
void set_variable_bool(const char *name, bool value);

/**
 * @brief Get the value of an integer variable.
 * 
 * @param name The name of the variable.
 * @return The integer value of the variable.
 */
int get_variable_int(const char *name);

/**
 * @brief Get the value of a string variable.
 * 
 * @param name The name of the variable.
 * @return The string value of the variable.
 */
char* get_variable_str(const char *name);

/**
 * @brief Get the value of a boolean variable.
 * 
 * @param name The name of the variable.
 * @return The boolean value of the variable.
 */
bool get_variable_bool(const char *name);

/**
 * @brief Get the type of a variable.
 * 
 * @param name The name of the variable.
 * @return The type of the variable as an integer.
 */
int get_variable_type(const char *name);

/**
 * @brief Free the memory allocated for the variable table.
 */
void freeTable();

#endif // VARIABLES_H