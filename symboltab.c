#include "symboltab.h"

var_node* symbol_table[TABLE_SIZE] = {NULL};  // Hash table
int var_count = 1;  // Temporary variable counter

/* Hash function to map variable names to an index */
unsigned int hash_function(char *name) {
    unsigned int hash = 0;
    while (*name)
        hash = (hash * 31) + *name++;
    return hash % TABLE_SIZE;
}

/* Search for a variable by name in the hash table */
var_node* search_varible(char* name) {
    unsigned int index = hash_function(name);
    var_node *curr = symbol_table[index];

    while (curr) {
        if (strcmp(curr->name, name) == 0)
            return curr;  // Found variable
        curr = curr->next;
    }
    return NULL;  // Not found
}

/* Add a new variable to the symbol table */
var_node* add_var_name(char* name) {
    unsigned int index = hash_function(name);
    var_node *new_var = (var_node*)malloc(sizeof(var_node));
    
    if (!new_var) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    strcpy(new_var->name, name);
    new_var->state = LOCK;
    new_var->flag = 0;
    new_var->next = symbol_table[index];  // Insert at the head of the list
    symbol_table[index] = new_var;
    
    return new_var;
}

/* Check if a variable exists, if not, add it */
void set_varible_name(char *name) {
    if (!search_varible(name))
        add_var_name(name);
    else
        report_error("ERROR: Variable name exists in symbol table\n");
}

/* Assign a type to all untyped variables */
void set_varible_type(char type) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        var_node *curr = symbol_table[i];
        while (curr) {
            if (curr->flag == 0) {
                curr->type = type;
                curr->flag = 1;
            }
            curr = curr->next;
        }
    }
}

/* Search for a free temporary variable of a specific type */
var_node* search_free_var(char type) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        var_node *curr = symbol_table[i];
        while (curr) {
            if (curr->state == FREE && curr->type == type)
                return curr;
            curr = curr->next;
        }
    }
    return NULL;
}

/* Add a temporary variable */
var_node* add_temp_var(char type) {
    char name[VARLEN];
    var_node *new_temp = search_free_var(type);
    
    if (!new_temp) {
        sprintf(name, "var%d", var_count++);
        new_temp = add_var_name(name);
        new_temp->type = type;
        new_temp->flag = 1;
    }
    
    new_temp->state = SAVE;
    return new_temp;
}

/* Mark a variable as free */
void free_state(char* name) {
    var_node *curr = search_varible(name);
    if (curr && curr->state == SAVE)
        curr->state = FREE;
}

/* Free the entire symbol table */
void free_tree() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        var_node *curr = symbol_table[i];
        while (curr) {
            var_node *temp = curr;
            curr = curr->next;
            free(temp);
        }
        symbol_table[i] = NULL;
    }
}
