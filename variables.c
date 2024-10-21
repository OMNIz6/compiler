#include "variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VARS 100

typedef struct {
    char name[50];
    int intValue;
    char strValue[50];
    int isString; // 0 for int, 1 for string
} Variable;

Variable variables[MAX_VARS];
int var_count = 0;

int find_variable(const char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void set_variable_int(const char *name, int value) {
    int idx = find_variable(name);
    if (idx == -1) {
        strcpy(variables[var_count].name, name);
        variables[var_count].intValue = value;
        variables[var_count].isString = 0;
        var_count++;
    } else {
        variables[idx].intValue = value;
        variables[idx].isString = 0;
    }
    printf("true\n");
}

void set_variable_str(const char *name, const char *value) {
    int idx = find_variable(name);
    if (idx == -1) {
        strcpy(variables[var_count].name, name);
        strcpy(variables[var_count].strValue, value);
        variables[var_count].isString = 1;
        var_count++;
    } else {
        strcpy(variables[idx].strValue, value);
        variables[idx].isString = 1;
    }
    printf("true\n");
}

int get_variable_int(const char *name) {
    int idx = find_variable(name);
    if (idx == -1) {
        printf("Error: Undefined variable %s\n", name);
        exit(1);
    }
    
    return variables[idx].intValue;
}

char* get_variable_str(const char *name) {
    int idx = find_variable(name);
    if (idx == -1) {
        printf("Error: Undefined variable %s\n", name);
        exit(1);
    }
    
    return variables[idx].strValue;
}

int get_variable_type(const char *name) {
    int idx = find_variable(name);
    if (idx == -1) {
        printf("Error: Undefined variable %s\n", name);
        exit(1);
    }
    return variables[idx].isString;
}