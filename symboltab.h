#ifndef SYMBOLTAB_H
#define SYMBOLTAB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"

#define VARLEN 32          // Maximum length for variable names
#define TABLE_SIZE 211     // Prime number for better hash distribution

// Variable states
#define FREE 0             // Variable is available for reuse
#define SAVE 1             // Variable is currently in use
#define LOCK 2             // Variable cannot be modified/reused

// Symbol table node structure
typedef struct var_node {
    char name[VARLEN];     // Variable name
    char type;             // Data type (e.g., 'i' for integer)
    int state;             // Current state (FREE/SAVE/LOCK)
    int flag;              // Type assignment flag (1 = type set)
    struct var_node *next; // Next node in collision chain
} var_node;

// Global symbol table and temporary counter
extern var_node* symbol_table[TABLE_SIZE];
extern int var_count;

// Function prototypes
void set_variable_name(char* name);
var_node* search_variable(char* name);
var_node* add_variable_name(char* name);
var_node* add_temp_var(char type);
void set_variable_type(char type);
void free_variable_state(char* name);
void free_symbol_table();

// External error handling references
extern void report_error(const char *format, ...);
extern const char* error_messeges[];
extern FILE* quad;
#endif // SYMBOLTAB_H