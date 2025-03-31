#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <stdio.h>
#include "symboltab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Assumed macros for argument length and label count.
   Adjust these values as needed for your project. */
#define ARGLEN 100
#define LABELS 100

/*--------------------------------------------------------------
 * Forward declarations for types used in translator.c
 *--------------------------------------------------------------*/

/* Command structure: represents a quad or assembly command.
   (Field sizes are assumed and can be adjusted.) */
typedef struct command {
    char com[50];         // command name (e.g. "IADD", "JMP")
    char firstArg[50];
    char secondArg[50];
    char thirdArg[50];
    struct command *next;
} command;
enum {equal,notEqual,bigger,smaller,biggerOrEqual,smallerOrEqual,castToInt,castToFloat};

/* Linked list of commands */
typedef struct command_list {
    command *com;
    struct command_list *next;
} command_list;


/*--------------------------------------------------------------
 * Function prototypes from translator.c
 *--------------------------------------------------------------*/

/* Merges two command lists into one */
command_list* merge_comnd_list(command_list* head, command_list* tail);

/* Prepend a new command to a command list */
command_list* add_new_command_list(command_list* list, command* com);

/* Merges two command sequences */
command* merege_comand(command* head, command* tail);

/* Retrieves the last command in the command list */
command* get_last_command(command* head);

/* Creates a new quad command and appends it to the command list */
command* translate_comand(command* head, char type, char* com, char* firstArg, char* secondArg, char* thirdArg);

/* Creates an assignment command (with error reporting if variable not found or type mismatch) */
command* add_assign_commadn(char* var, char* exp, char expType, command* expHead);

/* Builds an arithmetic command from two command sequences */
command* build_arithmetic_command(char op, char type, char* last, char* firstArgLast, char* secondArgLast, char firstType, char secondType, command* firstHead, command* secondHead);

/* Builds a math operator command for add/sub/mul/div operations */
command* build_math_operator_command(char op, command* head, char type, char* firstArg, char* secondArg, char* thirdArg);

/* Builds a relational operator command */
command* build_relop_command(int relopType, char* firstVar, char* secondVar, command* firstHead, command* secondHead, char compareType);

/* Flips a relational operator command (for resolving >= and <=) */
command* flip_command(command* head, char* lastVar);

/* Generates a label command */
command* add_label(command* head);

/* Converts a command’s last argument to a float operation */
command* convert_to_float(command* head, char* last);

/* Converts a command’s last argument to an integer operation */
command* convert_to_int(command* head, char* last);

/* Determines the resulting type from two type characters */
char type_decider(char type1, char type2);

/* Returns a cast code for a given cast operator */
int cast(int castOp);

/* Updates a command list so that each command’s first argument is renamed to a label */
void update_list_to_label(command_list* head, command* label);

/* Renames a command’s first argument */
void rename_argument(command* com, char* newArg);

/* Prints all commands in the command list to the output file (quad) */
void command_print(command* head);

/* Frees the entire command linked list */
void free_list(command* head);

#endif /* TRANSLATOR_H */
