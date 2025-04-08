#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <stdio.h>
#include "symboltab.h"
#include <stdlib.h>
#include <string.h>
#include "error.h"

/* Constants for argument length and label count. Adjust as needed based on project requirements. */
#define ARGLEN 100  /* Maximum length for command arguments */
#define LABELS 100  /* Maximum number of labels allowed in the program */

/* Memory allocation constants. These define sizes for various data types. Adjust as needed. */
#define ERRLEN 100  /* Memory size reserved for error message strings */
#define CHAR 1      /* Memory size reserved for single characters */
#define STR 4       /* Memory size reserved for short strings */

/*--------------------------------------------------------------
 * Forward declarations for types used in translator.c
 *--------------------------------------------------------------*/
extern const char* error_messeges[];  /* Array of predefined error messages used for reporting */
typedef char strings[STR];            /* Custom type for fixed-size string arrays of length STR */
typedef char chars[CHAR];             /* Custom type for fixed-size character arrays of length CHAR */

/* Command structure: represents a quad or assembly command.
   Fields:
   - com: stores the command name (e.g., "IADD", "JMP")
   - firstArg, secondArg, thirdArg: hold the command’s arguments
   - next: links to the next command in a sequence
   (Field sizes are assumed and can be adjusted based on requirements.)
*/
typedef struct command {
    char com[50];         // Command name
    char first_argument[50];    // First argument of the command
    char second_argument[50];   // Second argument of the command
    char third_argument[50];    // Third argument of the command
    struct command *next; // Pointer to the next command in the linked list
} command;

/* Enumeration for relational operations and type casts.
   Defines symbolic constants for comparison operators and type conversions.
*/
enum {
    equal,          // Represents "=="
    notEqual,       // Represents "!="
    bigger,         // Represents ">"
    smaller,        // Represents "<"
    biggerOrEqual,  // Represents ">="
    smallerOrEqual, // Represents "<="
    castToInt,      // Represents a cast to integer
    castToFloat     // Represents a cast to float
};

/* Linked list of commands.
   Fields:
   - com: pointer to a command structure
   - next: pointer to the next node in the list
*/
typedef struct command_list {
    command *com;               // Pointer to a command
    struct command_list *next;  // Pointer to the next command list node
} command_list;

/* Structure to hold character-based commands and their memory addresses.
   Fields:
   - charCmd: single character representing the command
   - charAddress: pointer to a character array
*/
typedef struct {
    char char_command;       // Character representing the command
    chars* char_addres; // Pointer to the character array for storage
} char_command_struct;

/* Structure to hold string-based commands and their memory addresses.
   Fields:
   - stringCmd: pointer to a string representing the command
   - strAddress: pointer to a string array
*/
typedef struct {
    char* string_command;     // Pointer to the string representing the command
    strings* string_addres; // Pointer to the string array for storage
} string_command_struct;

/* External function to report errors with formatted output */
extern void report_error(const char *format, ...);

/*--------------------------------------------------------------
 * Function prototypes from translator.c
 *--------------------------------------------------------------*/

/* Merges two command lists into a single list.
   Parameters: head (first list), tail (second list)
   Returns: pointer to the merged list
*/
command_list* merge_comnd_list(command_list* head, command_list* tail);

/* Prepends a new command to an existing command list.
   Parameters: list (current list), com (command to add)
   Returns: pointer to the updated list
*/
command_list* add_new_command_list(command_list* list, command* com);

/* Merges two command sequences into a single sequence.
   Parameters: head (first sequence), tail (second sequence)
   Returns: pointer to the merged sequence
*/
command* merege_comand(command* head, command* tail);

/* Retrieves the last command in a command sequence.
   Parameters: head (start of the sequence)
   Returns: pointer to the last command
*/
command* get_last_command(command* head);

/* Creates a new quad command and appends it to the command sequence.
   Parameters: head (current sequence), type (data type), com (command name),
               firstArg, secondArg, thirdArg (command arguments)
   Returns: pointer to the updated sequence
*/
command* translate_comand(command* head, char type, char* com, char* firstArg, char* secondArg, char* thirdArg);

/* Creates an assignment command, with error reporting for variable issues.
   Parameters: var (variable name), exp (expression), expType (expression type),
               expHead (expression command sequence)
   Returns: pointer to the new command sequence
*/
command* add_assign_commadn(char* var, char* exp, char expType, command* expHead);

/* Builds an arithmetic command from two command sequences.
   Parameters: op (operator), type (result type), last (result variable),
               firstArgLast, secondArgLast (last arguments of operands),
               firstType, secondType (operand types), firstHead, secondHead (operand sequences)
   Returns: pointer to the new command sequence
*/
command* build_arithmetic_command(char op, char type, char* last, char* firstArgLast, char* secondArgLast, char firstType, char secondType, command* firstHead, command* secondHead);

/* Builds a math operator command for addition, subtraction, multiplication, or division.
   Parameters: op (operator), head (current sequence), type (data type),
               firstArg, secondArg, thirdArg (command arguments)
   Returns: pointer to the updated sequence
*/
command* build_math_operator_command(char op, command* head, char type, char* firstArg, char* secondArg, char* thirdArg);

/* Builds a relational operator command for comparisons.
   Parameters: relopType (type of relational operator), firstVar, secondVar (variables to compare),
               firstHead, secondHead (operand sequences), compareType (comparison type)
   Returns: pointer to the new command sequence
*/
command* build_relop_command(int relopType, char* firstVar, char* secondVar, command* firstHead, command* secondHead, char compareType);

/* Flips a relational operator command (e.g., converts >= to <=).
   Parameters: head (current sequence), lastVar (variable to adjust)
   Returns: pointer to the updated sequence
*/
command* flip_command(command* head, char* lastVar);

/* Generates a label command and appends it to the sequence.
   Parameters: head (current sequence)
   Returns: pointer to the updated sequence
*/
command* add_label(command* head);

/* Converts the last argument of a command to a float operation.
   Parameters: head (current sequence), last (variable to convert)
   Returns: pointer to the updated sequence
*/
command* convert_to_float(command* head, char* last);

/* Converts the last argument of a command to an integer operation.
   Parameters: head (current sequence), last (variable to convert)
   Returns: pointer to the updated sequence
*/
command* convert_to_int(command* head, char* last);

/* Determines the resulting type from two operand types.
   Parameters: type1, type2 (types of the operands)
   Returns: resulting type character
*/
char type_decider(char type1, char type2);

/* Returns a cast code for a given cast operator.
   Parameters: castOp (cast operator from the enum)
   Returns: integer code for the cast
*/
int cast(int castOp);

/* Updates a command list by renaming each command’s first argument to a label.
   Parameters: head (command list), label (label command to use)
*/
void update_list_to_label(command_list* head, command* label);

/* Renames the first argument of a command.
   Parameters: com (command to modify), newArg (new argument name)
*/
void rename_argument(command* com, char* newArg);

/* Prints all commands in the sequence to the output file (quad format).
   Parameters: head (start of the sequence)
*/
void command_print(command* head);

/* Frees the entire command linked list to prevent memory leaks.
   Parameters: head (start of the sequence)
*/
void free_list(command* head);

#endif /* TRANSLATOR_H */