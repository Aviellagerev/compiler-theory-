#include "symboltab.h"

var_node* symbol_table[TABLE_SIZE] = {NULL};  // Hash table initialization
int var_count = 1;                            // Temporary variable counter

/**
 * @brief Generates hash index for a variable name
 * @param name Variable name to hash
 * @return Hash index between 0 and TABLE_SIZE-1
 */
unsigned int hash_function(const char *name) {
    unsigned int hash = 0;
    while (*name) {
        hash = (hash * 31) + *name++;
    }
    return hash % TABLE_SIZE;
}

/**
 * @brief Searches for a variable in the symbol table
 * @param name Variable name to search for
 * @return Pointer to variable node if found, NULL otherwise
 */
var_node* search_variable(char *name) {
    unsigned int index = hash_function(name);
    var_node *current = symbol_table[index];

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * @brief Adds a new variable to the symbol table
 * @param name Variable name to add
 * @return Pointer to new node if successful, NULL otherwise
 */
var_node* add_variable_name(char *name) {
    // Check for existing variable
    if (search_variable(name) != NULL) {
        report_error(error_messeges[19], name);
        return NULL;
    }

    // Allocate new node
    unsigned int index = hash_function(name);
    var_node *new_node = (var_node*)malloc(sizeof(var_node));
    
    if (new_node == NULL) {
        report_error(error_messeges[0], "Memory allocation failed");
        return NULL;
    }

    // Initialize node fields
    strncpy(new_node->name, name, VARLEN);
    new_node->state = LOCK;
    new_node->flag = 0;
    new_node->type = '\0';
    
    // Insert at head of chain
    new_node->next = symbol_table[index];
    symbol_table[index] = new_node;

    return new_node;
}

/**
 * @brief Public interface to declare a new variable
 * @param name Variable name to declare
 */
void set_variable_name(char *name) {
    if (add_variable_name(name) == NULL) {
        // Error already reported by add_variable_name
        return;
    }
}

/**
 * @brief Assigns type to all untyped variables
 * @param type Data type to assign (e.g., 'i', 'f')
 */
void set_variable_type(char type) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        var_node *current = symbol_table[i];
        while (current != NULL) {
            if (current->flag == 0) {
                current->type = type;
                current->flag = 1;
            }
            current = current->next;
        }
    }
}

/**
 * @brief Finds a reusable temporary variable of specified type
 * @param type Data type to search for
 * @return Pointer to available variable or NULL if none found
 */
var_node* search_free_var(char type) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        var_node *current = symbol_table[i];
        while (current != NULL) {
            if (current->state == FREE && current->type == type) {
                return current;
            }
            current = current->next;
        }
    }
    return NULL;
}

/**
 * @brief Creates or reuses a temporary variable
 * @param type Data type for the temporary variable
 * @return Pointer to temporary variable node
 */
var_node* add_temp_var(char type) {
    char temp_name[VARLEN];
    var_node *temp = search_free_var(type);
    
    if (temp == NULL) {
        // Generate unique temporary name
        do {
            snprintf(temp_name, VARLEN, "var%d", var_count++);
        } while (search_variable(temp_name) != NULL);
        
        temp = add_variable_name(temp_name);
        if (temp == NULL) {
            return NULL;  // Error already reported
        }
        
        temp->type = type;
        temp->flag = 1;
    }
    
    temp->state = SAVE;
    return temp;
}

/**
 * @brief Releases a variable for potential reuse
 * @param name Name of variable to mark as FREE
 */
void free_variable_state(char *name) {
    var_node *target = search_variable(name);
    if (target != NULL && target->state == SAVE) {
        target->state = FREE;
    }
}

/**
 * @brief Completely cleans up the symbol table
 */
void free_symbol_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        var_node *current = symbol_table[i];
        while (current != NULL) {
            var_node *next = current->next;
            free(current);
            current = next;
        }
        symbol_table[i] = NULL;
    }
    var_count = 1;  // Reset temporary counter
}