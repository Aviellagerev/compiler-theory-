#include "error.h"
#include <stdarg.h> /* For va_list and variadic arguments */
#include <stdio.h>  /* For fprintf and vfprintf */
#include <string.h> /* For strcmp */

void report_error(const char *format, ...) {
    va_list args;
    va_start(args, format);

    /* Check if the format matches specific error messages (indices 0-3) */
    if (strcmp(format, error_messeges[0]) == 0 ||
        strcmp(format, error_messeges[1]) == 0 ||
        strcmp(format, error_messeges[2]) == 0 ||
        strcmp(format, error_messeges[3]) == 0) {
        /* Special case: Print without line number for these errors */
        fprintf(stderr, "ERROR: ");
        vfprintf(stderr, format, args);
    } else {
        /* Default case: Print with line number for all other errors */
        fprintf(stderr, "ERROR: line %d: ", line - 1);
        vfprintf(stderr, format, args);
    }

    va_end(args);
    error_number++; /* Increment error counter */
}