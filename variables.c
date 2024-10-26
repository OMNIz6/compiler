#include "variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100 // Define the size of the hash table

typedef struct Variable {
    char name[50];
    Value value;
    VarType type; // 0 for int, 1 for string
    struct Variable* next;
} Variable;

Variable* hashTable[TABLE_SIZE];

VarType intType = {VARIABLE_INT, "integer"};
VarType strType = {VARIABLE_STR, "string"};
VarType boolType = {VARIABLE_BOOL, "boolean"};


// Hash function to map a string key to an index
unsigned int hash(const char* key) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    // Convert the string key into an integer
    for (i = 0; i < key_len; i++) {
        value = value * 37 + key[i];
    }

    // Return an index based on the table size
    return value % TABLE_SIZE;
}

// Function to find a variable by name
Variable* find_variable(const char* name) {
    unsigned int index = hash(name);
    Variable* current = hashTable[index];

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current; // Found the variable
        }
        current = current->next; // Traverse the linked list
    }

    return NULL; // Variable not found
}

// Function to set an integer variable
void set_variable_int(const char* name, int value) {
    // printf("Setting variable %s to %d\n", name, value);
    unsigned int index = hash(name);
    Variable* var = find_variable(name);

    if (var == NULL) {
        var = (Variable*) malloc(sizeof(Variable));
        strcpy(var->name, name);
        var->next = hashTable[index];
        hashTable[index] = var;
    }

    var->value.intValue = value;
    var->type = intType;
}

// Function to set a string variable
void set_variable_str(const char* name, const char* value) {
    // printf("Setting variable %s to %s\n", name, value);
    unsigned int index = hash(name);
    Variable* var = find_variable(name);

    if (var == NULL) {
        var = (Variable*) malloc(sizeof(Variable));
        strcpy(var->name, name);
        var->next = hashTable[index];
        hashTable[index] = var;
    }
    var->value.strValue = (char*) malloc(strlen(value) + 1);

    strcpy(var->value.strValue, value);
    var->type = strType;
}

void set_variable_bool(const char* name, bool value) {
    unsigned int index = hash(name);
    Variable* var = find_variable(name);

    if (var == NULL) {
        var = (Variable*) malloc(sizeof(Variable));
        strcpy(var->name, name);
        var->next = hashTable[index];
        hashTable[index] = var;
    }

    var->value.boolValue = value;
    var->type = boolType;
}

// Function to get an integer variable
int get_variable_int(const char* name) {
    Variable* var = find_variable(name);
    if (var == NULL) {
        printf("Error: Undefined variable %s\n", name);
        exit(1);
    }

    return var->value.intValue;
}

// Function to get a string variable
char* get_variable_str(const char* name) {
    Variable* var = find_variable(name);
    if (var == NULL) {
        printf("Error: Undefined variable %s\n", name);
        exit(1);
    }

    return var->value.strValue;
}

bool get_variable_bool(const char* name) {
    Variable* var = find_variable(name);
    if (var == NULL) {
        printf("Error: Undefined variable %s\n", name);
        exit(1);
    }

    return var->value.boolValue;
}

// Function to get the type of a variable
int get_variable_type(const char* name) {
    Variable* var = find_variable(name);
    if (var == NULL) {
        printf("Error: Undefined variable %s\n", name);
        exit(1);
    }

    return var->type.type;
}

char* get_variable_type_name(const char* name) {
    Variable* var = find_variable(name);
    if (var == NULL) {
        printf("Error: Undefined variable %s\n", name);
        exit(1);
    }

    return var->type.name;
}

// Free all allocated memory for the hash table
void freeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Variable* current = hashTable[i];
        while (current != NULL) {
            Variable* temp = current;
            current = current->next;
            free(temp);
        }
    }
}