#include "cpq.h"
extern int yydebug;
/* Global Output File Pointer */
FILE* quad = NULL; /* Output file pointer for quad commands, initialized to NULL */

/* Main entry point for the CPQ compiler.
   Processes command-line arguments, opens input/output files, and invokes the parser.
   Returns:
   - 1 on successful compilation
   - 0 on failure (e.g., invalid arguments, file errors, or parsing errors)
*/
int main(int argc, char* argv[]) {
    char* input_filename;  /* Name of the input file */
    char* extension;       /* Pointer to the file extension */
    FILE* input_file;      /* Temporary pointer for input file */
    FILE* output_file;     /* Temporary pointer for output file */

    /* Check for correct number of command-line arguments */
    if (argc != 2) {
        report_error(error_messeges[1]); /* "Invalid number of arguments" */
        return 0;
    }

    input_filename = argv[1];
    extension = input_filename + strlen(input_filename) - LENEXT;

    /* Validate input file extension (must be ".ou" or ".OU") */
    if (strcmp(extension, ".ou") != 0 && strcmp(extension, ".OU") != 0) {
        report_error(error_messeges[3]); /* "Invalid file extension" */
        return 0;
    }

    /* Open input file for reading */
    input_file = openFile(input_filename, "r");
    if (!input_file) {
        return 0; /* Error already reported by openFile */
    }
    yyin = input_file; /* Assign to global lexer/parser input */

    /* Change extension to ".qud" for output file */
    strcpy(extension, ".qud");

    /* Open output file for writing */
    output_file = openFile(input_filename, "w");
    if (!output_file) {
        fclose(yyin); /* Clean up input file on failure */
        return 0;     /* Error already reported by openFile */
    }
    quad = output_file; /* Assign to global output file pointer */

    /* Parse the input file and check for errors */
   // yydebug = 1;
    if (yyparse() != 0 || error_number > 0) {
        fclose(quad);
        remove(input_filename); /* Remove incomplete output file */
        fclose(yyin);
        report_error(error_messeges[2]); /* "Compilation failed" */
    } else {
        printf("Success ^-^\n"); /* Indicate successful compilation */
        fclose(yyin);
        fclose(quad);
    }

    return 1; /* Successful execution */
}

/* Opens a file with the specified name and mode.
   Parameters:
   - name: The filename to open
   - type: The mode ("r" for read, "w" for write, etc.)
   Returns:
   - Pointer to the opened FILE object, or NULL on failure
*/
FILE* openFile(char* name, char* type) {
    FILE* file = fopen(name, type);
    if (file == NULL) {
        report_error(error_messeges[0]); /* "Cannot open file" */
    }
    return file;
}