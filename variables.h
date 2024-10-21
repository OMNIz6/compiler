#ifndef VARIABLES_H
#define VARIABLES_H

void set_variable_int(const char *name, int value);
void set_variable_str(const char *name, const char *value);
int get_variable_int(const char *name);
char* get_variable_str(const char *name);
int get_variable_type(const char *name);

#endif // VARIABLES_H