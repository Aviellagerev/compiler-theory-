#include "symboltab.h"

int var_count = 1;
var_node *head = NULL;
char* symboltab_err = "ERROR: This ame of variable exist in symbol table\n";

/*Accepts type it can be float or integer and
create temporary variable like t1,t2...,return
pointer to node in tree with new temporary variable*/
var_node* createTempVar(char type)
{
	char name[VARLEN];
	var_node* new_temp;

	new_temp = search_free_var(type, head);
	if (!new_temp || new_temp->state == FREE)
	{
		sprintf(name, "t%d", var_count);
		new_temp = addTempVar(name, type);
		++var_count;
	}
	new_temp->state = SAVE;
	return new_temp;
}

/*Accepts name and type and add temporary variabele
to binary search tree or in other words to symbol table,
return pointer to node in tree with new temporary variable.*/
var_node* addTempVar(char* name, char type)
{
	var_node* new_temp, *prev;

	if (!head)
	{
		head = (var_node*)malloc(sizeof(var_node));
		new_temp = head;
	}
	else
	{
		new_temp = (var_node*)malloc(sizeof(var_node));
		prev = searchLocation(name, head);
		if (strcmp(prev->name, name) < 0)
			prev->right = new_temp;
		else
			prev->left = new_temp;
	}
	sprintf(new_temp->name, "%s", name);
	new_temp->left = NULL;
	new_temp->right = NULL;
	new_temp->type = type;
	new_temp->state = LOCK;
	new_temp->flag = 1;
	return new_temp;
}

/*Accepts name  and add  variable to binary search tree
without type or in other words to symbol table,
return pointer to node in tree with new variable without type.*/
var_node *addVarName(char* name)
{
	var_node *new_var_name, *prev;

	if (!head)
	{
		head = (var_node*)malloc(sizeof(var_node));
		new_var_name = head;
	}
	else
	{
		new_var_name = (var_node*)malloc(sizeof(var_node));
		prev = searchLocation(name, head);
		if (strcmp(prev->name, name) < 0)
			prev->right = new_var_name;
		else
			prev->left = new_var_name;
	}
	sprintf(new_var_name->name, "%s", name);
	new_var_name->left = NULL;
	new_var_name->right = NULL;
	new_var_name->state = LOCK;
	new_var_name->flag = 0;
	return new_var_name;
}

/*Accepts type  and pointer to node in tree and add to all variables without
type in binary search tree type which function accept,
return pointer to node in tree to variable with type was added.*/
var_node* addVarType(char type, var_node* curr)
{

	if (curr)
	{
		addVarType(type, curr->left);
		if (curr->flag == 0) {
			curr->type = type;
			curr->flag = 1;
		}
		addVarType(type, curr->right);
	}
	return curr;
}

/*Accepts name  and add  variable to binary search tree
without type or in other words to symbol table.*/
void set_varible_name(char *name)
{
	if(!search_varible(name))
		addVarName(name); 
	else
		printf("%s\n",symboltab_err);
}

/*Accepts type  and tree and add to all variables without
type in binary search tree type which function accept.*/
void set_varible_type(char type)
{
	var_node* curr = head;
    addVarType(type, curr);		
}

/*Accepts name and search this name in binary search tree
or in other words in symbol table,return pointer to node with
this variable name or if not exist null.*/
var_node *search_varible(char *name)
{
	var_node *curr = head;
	
	while(curr)
	{
		if(!strcmp(curr->name, name))
			return curr;
		else if(strcmp(curr->name, name) < 0)
			curr=curr->right;
		else
			curr=curr->left;
	}
	return NULL;
}

/*Accepts type and pointer to the tree and search variable
with this type and state FREE and return tree pointer to node with
FREE state variable if not found return null */
var_node *search_free_var(char type, var_node *curr)
{
	var_node *free_var;
	
	if(!curr)
		return NULL;
	if(curr->state == FREE && curr->type == type)
		return curr;
	if((free_var = search_free_var(type,curr->left)))
		return free_var;
	return search_free_var(type,curr->right);
}

/*Accepts name and pointer to the tree and search location
for new variable and return pointer to this node where
will be this variable. */
var_node *searchLocation(char *name, var_node *curr)
{	
	if(!curr)
		return NULL;
	if(strcmp(curr->name, name) < 0)
	{
		if(curr->right)
			return searchLocation(name,curr->right);
		return curr;
	}
	if(curr->left)
		return searchLocation(name,curr->left);
	return curr;
}

/*Accepts name of variable and him to state FREE*/
void free_state( char *name )
{
	var_node *curr = NULL;
		
	if( (curr = search_varible(name)) && curr->state == SAVE )
			curr->state = FREE;
}

/*Accept pointer to node and free this node*/
void free_var(var_node* curr)
{
	if (curr)
	{
		free_var(curr->right);
		free_var(curr->left);
		free(curr);
	}
}

/*Free all tree of vaiables*/
void free_tree()
{	
	free_var(head);
}

