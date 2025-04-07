#include "error.h"
void report_error(const char *format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "ERROR: line %d: ", line - 1);
    vfprintf(stderr, format, args);
    va_end(args);
    error_number++;
}