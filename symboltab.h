// #ifndef SYMBOLTAB_H
// #define SYMBOLTAB_H

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define VARLEN 32 // Maximum length of a variable name

// // States for a variable
// #define FREE 0 // Variable is free and can be reused
// #define SAVE 1 // Variable is in use
// #define LOCK 2 // Variable is locked (in use)


// /*@brief Node structure for the binary search tree*/
// typedef struct var_node {
//     char name[VARLEN]; // Name of the variable
//     char type;         // Type of the variable (e.g., 'i' for integer, 'f' for float)
//     int state;         // State of the variable (FREE, SAVE, or LOCK)
//     int flag;          // Flag to indicate if the variable has a type (1 = has type, 0 = no type)
//     struct var_node *left;  // Pointer to the left child
//     struct var_node *right; // Pointer to the right child
// } var_node;

// /* @brief Creates a temporary variable of the specified type.
//    @param type The type of the variable to create.
//    @return A pointer to the node representing the temporary variable. */
// var_node* add_temp_var(char type);

// /* @brief Adds a temporary variable with the given name and type to the symbol table.
//    @param name The name of the variable.
//    @param type The type of the variable.
//    @return A pointer to the newly created node. */
// var_node* set_temp_var(char* name, char type);

// /* @brief Adds a variable with the given name to the symbol table.
//    @param name The name of the variable.
//    @return A pointer to the newly created node. */
// var_node* add_var_name(char* name);

// /* @brief Recursively assigns the specified type to all untyped variables in the symbol table.
//    @param type The type to assign.
//    @param curr The current node in the BST.
//    @return A pointer to the current node. */
// var_node* addVarType(char type, var_node* curr);

// /* @brief Adds a variable with the given name to the symbol table if it does not already exist.
//    @param name The name of the variable.
//    @note Prints an error message if the variable name is a duplicate. */
// void set_varible_name(char* name);

// /* @brief Assigns the specified type to all untyped variables in the symbol table.
//    @param type The type to assign. */
// void set_varible_type(char type);

// /* @brief Searches for a variable by name in the symbol table.
//    @param name The name of the variable to search for.
//    @return A pointer to the node if found, otherwise NULL. */
// var_node* search_varible(char* name);

// /* @brief Recursively searches for a free variable of the specified type.
//    @param type The type of the variable to search for.
//    @param curr The current node in the BST.
//    @return A pointer to the node if found, otherwise NULL. */
// var_node* search_free_var(char type, var_node* curr);

// /* @brief Finds the correct location in the symbol table to insert a new variable.
//    @param name The name of the variable to insert.
//    @param curr The current node in the BST.
//    @return A pointer to the parent node where the new variable should be inserted. */
// var_node* searchLocation(char* name, var_node* curr);

// /* @brief Marks a variable as free if it exists and is currently in use.
//    @param name The name of the variable to free. */
// void free_state(char* name);

// /* @brief Recursively frees all nodes in the symbol table starting from the given node.
//    @param curr The current node to free. */
// void free_var(var_node* curr);

// /* @brief Frees the entire symbol table by deallocating all nodes. */
// void free_tree();

// #endif // SYMBOLTAB_H
#ifndef SYMBOLTAB_H
#define SYMBOLTAB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void set_varible_name(char* name);
var_node* search_varible(char* name);
var_node* add_var_name(char* name);
var_node* add_temp_var(char type);
void set_varible_type(char type);
void free_state(char* name);
void free_tree();

#endif // SYMBOLTAB_H
