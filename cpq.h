#ifndef CPQ_H
#define CPQ_H

/* Header file for the CPQ compiler.
   Declares constants, external variables, and function prototypes used in cpq.c.
*/

#include <stdio.h>  /* For FILE, printf, etc. */
#include <string.h> /* For strcmp, strcpy, etc. */
#include <stdlib.h> /* For exit, remove, etc. */
#include <stdarg.h> /* For variable argument handling in report_error */
#include "error.h"  /* For error_messeges and report_error */

/* Constant Definition */
#define LENEXT 3 /* Expected length of the file extension (e.g., ".ou" is 3 characters) */

/* External Declarations for Error Handling */
extern void report_error(const char *format, ...); /* Function to report errors */
extern const char* error_messeges[]; /* Array of predefined error messages */

/* External File Pointers Used by cpq.c and Parser/Lexer */
extern FILE* yyin; /* Input file pointer for the lexer/parser */
extern FILE* quad; /* Output file pointer for quad commands, defined in cpq.c */

/* External Parser-Related Declarations */
extern int yyparse(void); /* Parser function to process input */
extern int error_number;  /* Counter for errors detected during compilation */

/* Function Prototype */
FILE* openFile(char* name, char* type); /* Opens a file with specified name and mode */

#endif /* CPQ_H */