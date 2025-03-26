// #include "symboltab.h"

// int var_count = 1; // Tracks the number of temporary variables created
// var_node *head = NULL; // Root of the binary search tree (BST) for the symbol table
// char* symboltab_err = "ERROR: This ame of variable exist in symbol table\n"; // Error message for duplicate variables

// /* Generates a new temporary variable of the specified type.
//    Reuses a free variable of the same type if available.
//    Returns a pointer to the node representing the variable. */
// var_node* add_temp_var(char type)
// {
// 	char name[VARLEN]; // Buffer to store the generated variable name
// 	var_node* new_temp; // Pointer to the new or reused variable node

// 	// Search for a free variable of the specified type
// 	new_temp = search_free_var(type, head);
// 	if (!new_temp || new_temp->state == FREE) // If no free variable is found
// 	{
// 		sprintf(name, "var%d", var_count); // Generate a unique name (e.g., "var1")
// 		new_temp = set_temp_var(name, type); // set the new variable to the symbol table
// 		++var_count; // Increment the temporary variable counter
// 	}
// 	new_temp->state = SAVE; // Mark the variable as in use
// 	return new_temp; // Return the node for the variable
// }

// /* Adds a new temporary variable with the given name and type to the symbol table.
//    Returns a pointer to the newly created node. */
// var_node* set_temp_var(char* name, char type)
// {
// 	var_node* new_temp, *prev; // Pointers for the new node and its parent

// 	if (!head) // If the symbol table is empty
// 	{
// 		head = (var_node*)malloc(sizeof(var_node)); // Create the root node
// 		new_temp = head; // Set the new node as the root
// 	}
// 	else // If the symbol table is not empty
// 	{
// 		new_temp = (var_node*)malloc(sizeof(var_node)); // Allocate memory for the new node
// 		prev = searchLocation(name, head); // Find the correct location to insert the new node
// 		if (strcmp(prev->name, name) < 0) // Insert to the right if the new name is greater
// 			prev->right = new_temp;
// 		else // Insert to the left otherwise
// 			prev->left = new_temp;
// 	}
// 	sprintf(new_temp->name, "%s", name); // Set the variable name
// 	new_temp->type = type; // Set the variable type
// 	new_temp->state = LOCK; // Mark the variable as in use
// 	new_temp->flag = 1; // Indicate that the variable has a type
// 	new_temp->left = NULL; // Initialize left child pointer
// 	new_temp->right = NULL; // Initialize right child pointer
// 	return new_temp; // Return the new node
// }

// /* Adds a new variable with the given name to the symbol table.
//    Returns a pointer to the newly created node. */
// var_node *add_var_name(char* name)
// {
// 	var_node *new_var_name, *prev; // Pointers for the new node and its parent

// 	if (!head) // If the symbol table is empty
// 	{
// 		head = (var_node*)malloc(sizeof(var_node)); // Create the root node
// 		new_var_name = head; // Set the new node as the root
// 	}
// 	else // If the symbol table is not empty
// 	{
// 		new_var_name = (var_node*)malloc(sizeof(var_node)); // Allocate memory for the new node
// 		prev = searchLocation(name, head); // Find the correct location to insert the new node
// 		if (strcmp(prev->name, name) < 0) // Insert to the right if the new name is greater
// 			prev->right = new_var_name;
// 		else // Insert to the left otherwise
// 			prev->left = new_var_name;
// 	}
// 	sprintf(new_var_name->name, "%s", name); // Set the variable name
// 	new_var_name->state = LOCK; // Mark the variable as in use
// 	new_var_name->flag = 0; // Indicate that the variable does not have a type yet
// 	new_var_name->left = NULL; // Initialize left child pointer
// 	new_var_name->right = NULL; // Initialize right child pointer
	
// 	return new_var_name; // Return the new node
// }

// /* Recursively assigns the specified type to all untyped variables in the symbol table.
//    Returns a pointer to the current node. */
// var_node* addVarType(char type, var_node* curr)
// {
// 	if (curr) // If the current node exists
// 	{
// 		addVarType(type, curr->left); // Traverse the left subtree
// 		if (curr->flag == 0) // If the variable does not have a type
// 		{
// 			curr->type = type; // Assign the type
// 			curr->flag = 1; // Mark the variable as typed
// 		}
// 		addVarType(type, curr->right); // Traverse the right subtree
// 	}
// 	return curr; // Return the current node
// }

// /* Adds a variable with the given name to the symbol table if it does not already exist.
//    Prints an error message if the variable name is a duplicate. */
// void set_varible_name(char *name)
// {
// 	if(!search_varible(name)) // If the variable does not exist
// 		add_var_name(name); // Add it to the symbol table
// 	else // If the variable already exists
// 		printf("%s\n",symboltab_err); // Print an error message
// }

// /* Assigns the specified type to all untyped variables in the symbol table. */
// void set_varible_type(char type)
// {
// 	var_node* curr = head; // Start from the root of the symbol table
//     addVarType(type, curr); // Assign the type to all untyped variables		
// }

// /* Searches for a variable by name in the symbol table.
//    Returns a pointer to the node if found, otherwise returns NULL. */
// var_node *search_varible(char *name)
// {
// 	var_node *curr = head; // Start from the root of the symbol table
	
// 	while(curr) // Traverse the symbol table
// 	{
// 		if(!strcmp(curr->name, name)) // If the variable is found
// 			return curr;
// 		else if(strcmp(curr->name, name) < 0) // If the search name is greater, go right
// 			curr=curr->right;
// 		else // If the search name is smaller, go left
// 			curr=curr->left;
// 	}
// 	return NULL; // Return NULL if the variable is not found
// }

// /* Recursively searches for a free variable of the specified type.
//    Returns a pointer to the node if found, otherwise returns NULL. */
// var_node *search_free_var(char type, var_node *curr)
// {
// 	var_node *free_var; // Pointer to a free variable node
	
// 	if(!curr) // If the current node is NULL
// 		return NULL;
// 	if(curr->state == FREE && curr->type == type) // If a free variable of the correct type is found
// 		return curr;
// 	if((free_var = search_free_var(type,curr->left))) // Search the left subtree
// 		return free_var;
// 	return search_free_var(type,curr->right); // Search the right subtree
// }

// /* Finds the correct location in the symbol table to insert a new variable.
//    Returns a pointer to the parent node where the new variable should be inserted. */
// var_node *searchLocation(char *name, var_node *curr)
// {	
// 	if(!curr) // If the current node is NULL
// 		return NULL;
// 	if(strcmp(curr->name, name) < 0) // If the new name is greater, go right
// 	{
// 		if(curr->right) // If the right child exists, continue searching
// 			return searchLocation(name,curr->right);
// 		return curr; // Return the current node as the insertion point
// 	}
// 	if(curr->left) // If the new name is smaller, go left
// 		return searchLocation(name,curr->left);
// 	return curr; // Return the current node as the insertion point
// }

// /* Marks a variable as free if it exists and is currently in use. */
// void free_state( char *name )
// {
// 	var_node *curr = NULL; // Pointer to the variable node
		
// 	if( (curr = search_varible(name)) && curr->state == SAVE ) // If the variable exists and is in use
// 			curr->state = FREE; // Mark it as free
// }

// /* Recursively frees all nodes in the symbol table starting from the given node. */
// void free_var(var_node* curr)
// {
// 	if (curr) // If the current node exists
// 	{
// 		free_var(curr->right); // Free the right subtree
// 		free_var(curr->left); // Free the left subtree
// 		free(curr); // Free the current node
// 	}
// }

// /* Frees the entire symbol table by deallocating all nodes. */
// void free_tree()
// {	
// 	free_var(head); // Start freeing from the root of the symbol table
// }
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
        printf("ERROR: Variable name exists in symbol table\n");
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
