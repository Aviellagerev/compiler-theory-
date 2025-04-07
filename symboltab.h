#ifndef SYMBOLTAB_H
#define SYMBOLTAB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#define VARLEN 32  // Max length of a variable name
#define TABLE_SIZE 211  // Hash table size (prime number for better distribution)

// States for a variable
#define FREE 0  // Variable can be reused
#define SAVE 1  // Variable is in use
#define LOCK 2  // Variable is locked

// Node structure for the hash table (linked list for collisions)
typedef struct var_node {
    char name[VARLEN];  // Variable name
    char type;          // Variable type (e.g., 'i' for integer)
    int state;          // State of the variable (FREE, SAVE, LOCK)
    int flag;           // 1 = has type, 0 = no type
    struct var_node *next;  // Linked list for handling collisions
} var_node;
extern FILE* quad;
void set_varible_name(char* name);
var_node* search_varible(char* name);
var_node* add_var_name(char* name);
var_node* add_temp_var(char type);
void set_varible_type(char type);
void free_state(char* name);
void free_tree();

extern void report_error(const char *format, ...);
#endif // SYMBOLTAB_H
