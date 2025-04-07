#ifndef ERROR_H
#define ERROR_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h> /* Added for variable argument handling */
extern int line;
extern int error_number;
void report_error(const char *format, ...);

#endif