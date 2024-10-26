#include "interpreter.h"
#include <stdio.h>
#include <string.h>

int main ( int argc, char *argv[] )
{
    //scanf
    if (argc == 1 && strcmp(argv[0], "omni") == 0)
    {
        char line[256];

        printf("Enter your code (type 'exit' to quit):\n");

        while (1) {
            printf("> ");
            fgets(line, sizeof(line), stdin);
            line[strcspn(line, "\n")] = 0;
            if (strcmp(line, "exit") == 0) break;
            interpret(line);
        }
    }
    else if ( argc == 2 ) /* argc should be 2 for correct execution */
    {   
        char *file_name = argv[1];
        // We assume argv[1] is a filename to open
        if (strlen(argv[1]) <= 5 || strcmp(argv[1] + strlen(argv[1]) - 5, ".omni") != 0) {
            file_name = strcat(argv[1], ".omni");
        }
        FILE *file = fopen( file_name, "r" );
        if ( file == 0 )
        {
            printf( "Could not open file\n" );
        }
        else
        {
            char line[1000];
            while ( fgets( line, sizeof line, file ) != NULL )
            {   
                interpret(line);
            }
            fclose( file );
        }
    }
}
