#include "interpreter.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_error_main(const char *message) {
    fprintf(stderr, "\033[1;31mError:\033[0m %s\n", message); // Red color for errors
}

int main(int argc, char *argv[]) {
    if (argc == 1 && (strcmp(argv[0], "omni") == 0 || strcmp(argv[0], "./omni") == 0) ) {
        char line[256];
        printf("Enter your code (type 'exit' to quit):\n");
        int line_number = 0;
        while (1) {
            printf("> ");
            if (fgets(line, sizeof(line), stdin) == NULL) {
                print_error_main("Failed to read input");
                continue;
            }
            line[strcspn(line, "\n")] = 0;
            if (strcmp(line, "exit") == 0) break;
            line_number++;
            interpret(line, line_number);
        }
    } else if (argc == 2) { // argc should be 2 for correct execution
        char *file_name = argv[1];
        if (strlen(argv[1]) <= 5 || strcmp(argv[1] + strlen(argv[1]) - 5, ".omni") != 0) {
            file_name = strcat(argv[1], ".omni");
        }
        FILE *file = fopen(file_name, "r");
        if (file == NULL) {
            print_error_main("Could not open file");
            return 1;
        } else {
            char line[1000];
            int line_number = 0;
            while (fgets(line, sizeof(line), file) != NULL) {
                line_number++;
                interpret(line, line_number);
            }
            if (fclose(file) != 0) {
                print_error_main("Failed to close file");
                return 1;
            }
        }
    } else {
        print_error_main("Invalid number of arguments");
        return 1;
    }
    return 0;
}