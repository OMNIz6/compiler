#include "functions.h"
#include <stdlib.h>
#include <stdio.h>

char* to_str(int num){
    char* str = malloc(50);
    sprintf(str, "%d", num);
    return str;
}

int to_int(char* str){
    return atoi(str);
}