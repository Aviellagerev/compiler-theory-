#ifndef ERROR_H
#define ERROR_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h> /* Added for variable argument handling */
extern int line;
extern int error_number;
void report_error(const char *format, ...);
static const char* error_messeges[] = {
    "Error: Could not open file\n",                                   /* error_messeges[0] */
    "Usage: <program> <filename>\n",                                  /* error_messeges[1] */
    "Parse error encountered\n",                                      /* error_messeges[2] */
    "Invalid file extension\n"   ,                                    /* error_messeges[3] */
    "unknown variable '%s', not defined in symbol table\n",           /* error_messeges[4] */
    "invalid type\n",                                                 /*error_messeges[5] */ 
    "invalid identifier in list\n",                                   /*error_messeges[6] */ 
    "incomplete statement starting with ID '%s'\n",                   /*error_messeges[7] */ 
    "unexpected number '%s'\n",                                       /*error_messeges[8] */ 
    "missing semicolon after assignment\n",                           /*error_messeges[9]*/
    "missing semicolon after input statement\n",                      /*error_messeges[10]*/
    "missing semicolon after output statement\n",                     /*error_nesseges[11]*/
    "invalid condition in if\n",                                      /*error_nesseges[12]*/
    "invalid condition in while\n",                                   /*error_nesseges[13]*/
    "missing DEFAULT in switch statement\n",                          /*error_nesseges[14]*/
    "missing semicolon after break\n",                                /*error_nesseges[15]*/
    "invalid statement block\n",                                      /*error_nesseges[16]*/
    "error in statement list\n",                                      /*error_nesseges[17]*/
    "cast from float to int ERROR!\n",                                /*error_nesseges[18]*/
    "the varible %s exsists in table \n",                             /*error_nesseges[19]*/                        
    "Identifier '%.*s...' exceeds maximum length of %d characters\n", /*error_messeges[20] */
    "Unknown token '%s'\n"                                            /*error_messeges[21] */ 
};
#endif