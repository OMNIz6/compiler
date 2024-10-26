#ifndef VARIABLES_H
#define VARIABLES_H

#include <stdbool.h>

typedef enum {
    VARIABLE_INT,
    VARIABLE_STR,
    VARIABLE_BOOL,
} DataType;

typedef union  {
    int intValue; 
    char* strValue;
    bool boolValue;
} Value;

typedef struct {
    DataType type;
    char* name;
} VarType;

void set_variable_int(const char *name, int value);
void set_variable_str(const char *name, const char *value);
void set_variable_bool(const char *name, bool value);
int get_variable_int(const char *name);
char* get_variable_str(const char *name);
bool get_variable_bool(const char *name);
int get_variable_type(const char *name);
void freeTable();

#endif // VARIABLES_H