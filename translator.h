#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "symboltab.h"

/* Constants */
/* Maximum lengths for command arguments and labels. Adjust as needed. */
#define ARGLEN 100  /* Max length of command arguments */
#define LABELS 100  /* Max number of labels in the program */

/* Memory allocation sizes for data types. Adjust as needed. */
#define ERRLEN 100  /* Size for error message strings */
#define CHAR 1      /* Size for single characters */
#define STR 4       /* Size for short strings */

/* Type Definitions */

/* Fixed-size string and character array types */
typedef char strings[STR];    /* Array of STR characters */
typedef char chars[CHAR];     /* Array of CHAR characters */

/* Command structure: Represents a quad or assembly instruction.
 * Fields:
 * - com: Command name (e.g., "IADD", "JMP")
 * - first_argument, second_argument, third_argument: Command arguments
 * - next: Pointer to the next command in the sequence
 */
typedef struct command {
    char com[50];             /* Command identifier */
    char first_argument[50];  /* First argument */
    char second_argument[50]; /* Second argument */
    char third_argument[50];  /* Third argument */
    struct command *next;     /* Link to next command */
} command;

/* Command list structure: A linked list node for commands.
 * Fields:
 * - com: Pointer to a command
 * - next: Pointer to the next node in the list
 */
typedef struct command_list {
    command *com;              /* Command pointer */
    struct command_list *next; /* Next list node */
} command_list;

/* Enumeration for relational operators and type casts */
enum {
    equal = 0,         /* "==" */
    notEqual,          /* "!=" */
    bigger,            /* ">" */
    smaller,           /* "<" */
    biggerOrEqual,     /* ">=" */
    smallerOrEqual,    /* "<=" */
    castToInt,         /* Cast to integer */
    castToFloat        /* Cast to float */
};

/* Character command structure: Holds single-character commands.
 * Fields:
 * - char_command: Single character for the command
 * - char_addres: Pointer to a character array
 */
typedef struct {
    char char_command;     /* Command character */
    chars *char_addres;    /* Character array pointer */
} char_command_struct;

/* String command structure: Holds string-based commands.
 * Fields:
 * - string_command: Pointer to the command string
 * - string_addres: Pointer to a string array
 */
typedef struct {
    char *string_command;  /* Command string */
    strings *string_addres; /* String array pointer */
} string_command_struct;

/* External Declarations */
extern const char *error_messeges[]; /* Predefined error messages */
extern void report_error(const char *format, ...); /* Error reporting function */

/* Function Prototypes */

/**
 * Merges two command lists into a single list.
 * @param head First command list
 * @param tail Second command list
 * @return Pointer to the merged command list
 */
command_list* merge_comnd_list(command_list* head, command_list* tail);

/**
 * Adds a command to the start of a command list.
 * @param list Existing command list
 * @param com Command to prepend
 * @return Pointer to the updated command list
 */
command_list* add_new_command_list(command_list* list, command* com);

/**
 * Combines two command sequences into one.
 * @param head First command sequence
 * @param tail Second command sequence
 * @return Pointer to the merged command sequence
 */
command* merege_comand(command* head, command* tail);

/**
 * Retrieves the last command in a sequence.
 * @param head Start of the command sequence
 * @return Pointer to the last command, or NULL if empty
 */
command* get_last_command(command* head);

/**
 * Appends a new quad command to a sequence.
 * @param head Current command sequence
 * @param type Data type of the command ('I' or 'R')
 * @param com Command name (e.g., "ADD", "JMP")
 * @param first_argument First argument
 * @param second_argument Second argument
 * @param third_argument Third argument
 * @return Pointer to the updated command sequence
 */
command* translate_comand(command* head, char type, char* com, char* first_argument, char* second_argument, char* third_argument);

/**
 * Creates an assignment command with type checking.
 * Reports errors for undefined variables or type mismatches.
 * @param var Variable name to assign to
 * @param exp Expression result
 * @param expression_type Type of the expression ('I' or 'R')
 * @param expression_head Command sequence of the expression
 * @return Pointer to the new command sequence
 */
command* add_assign_commadn(char* var, char* exp, char expression_type, command* expression_head);

/**
 * Constructs an arithmetic operation command.
 * @param op Arithmetic operator ('+', '-', '*', '/')
 * @param type Result type ('I' or 'R')
 * @param last Result variable name
 * @param first_argumentLast Last argument of first operand
 * @param second_argumentLast Last argument of second operand
 * @param first_type Type of first operand ('I' or 'R')
 * @param second_type Type of second operand ('I' or 'R')
 * @param first_head First operand’s command sequence
 * @param second_head Second operand’s command sequence
 * @return Pointer to the new command sequence
 */
command* build_arithmetic_command(char op, char type, char* last, char* first_argumentLast, char* second_argumentLast, char first_type, char second_type, command* first_head, command* second_head);

/**
 * Builds a command for basic arithmetic operations.
 * @param op Operator ('+', '-', '*', '/')
 * @param head Current command sequence
 * @param type Data type ('I' or 'R')
 * @param first_argument First argument
 * @param second_argument Second argument
 * @param third_argument Third argument
 * @return Pointer to the updated command sequence
 */
command* build_math_operator_command(char op, command* head, char type, char* first_argument, char* second_argument, char* third_argument);

/**
 * Creates a command for relational comparisons.
 * @param relation_op_type Relational operator type (from enum)
 * @param first_varible First variable to compare
 * @param second_varible Second variable to compare
 * @param first_head First operand’s command sequence
 * @param second_head Second operand’s command sequence
 * @param cmp_types Comparison type ('I' or 'R')
 * @return Pointer to the new command sequence
 */
command* build_relop_command(int relation_op_type, char* first_varible, char* second_varible, command* first_head, command* second_head, char cmp_types);

/**
 * Inverts a relational operator command (e.g., > to <).
 * @param head Current command sequence
 * @param last_varible Variable to adjust
 * @return Pointer to the updated command sequence
 */
command* flip_command(command* head, char* last_varible);

/**
 * Adds a label command to the sequence.
 * @param head Current command sequence
 * @return Pointer to the updated command sequence
 */
command* add_label(command* head);

/**
 * Converts a command’s last argument to a float.
 * @param head Current command sequence
 * @param last Variable to convert
 * @return Pointer to the updated command sequence
 */
command* convert_to_float(command* head, char* last);

/**
 * Converts a command’s last argument to an integer.
 * @param head Current command sequence
 * @param last Variable to convert
 * @return Pointer to the updated command sequence
 */
command* convert_to_int(command* head, char* last);

/**
 * Determines the resulting type of an operation.
 * @param type1 First operand type ('I' or 'R')
 * @param type2 Second operand type ('I' or 'R')
 * @return Resulting type ('I' or 'R')
 */
char type_decider(char type1, char type2);

/**
 * Maps a cast operator to its corresponding code.
 * @param cast_operation Cast operator (from enum)
 * @return Integer code for the cast (castToInt or castToFloat)
 */
int cast(int cast_operation);

/**
 * Updates all commands in a list to reference a label.
 * @param head Command list to update
 * @param label Label command to reference
 */
void update_list_to_label(command_list* head, command* label);

/**
 * Renames a command’s first argument.
 * @param com Command to modify
 * @param newArg New argument name
 */
void rename_argument(command* com, char* newArg);

/**
 * Outputs all commands in the sequence to a quad file.
 * @param head Start of the command sequence
 */
void command_print(command* head);

/**
 * Frees the memory used by a command sequence.
 * @param head Start of the command sequence
 */
void free_list(command* head);

#endif /* TRANSLATOR_H */