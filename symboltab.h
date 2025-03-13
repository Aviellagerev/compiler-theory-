#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*length of variable*/
#define VARLEN 20

/*States of variables:
FREE - variable not in use
SAVE - variable not in use but it will be in use
LOCK - variable in use*/
enum { FREE , SAVE , LOCK };

/*Type definition of struct symbol table that have variables.Every varible have a state
that say if we can use this variable or not.Data Structure of symbol table is 
search binary tree that give a simple search of variable what we need*/
typedef struct node{
	char name[VARLEN];
	char type;
	int state;
	int flag ;
	struct node *left;
	struct node *right;
} var_node;

/*Accepts type it can be float or integer and
create temporary variable like t1,t2...,return 
pointer to node in tree with new temporary variable*/
var_node *createTempVar(char);

/*Accepts name and type and add temporary variabele
to binary search tree or in other words to symbol table,
return pointer to node in tree with new temporary variable.*/
var_node *addTempVar(char*, char);

/*Accepts name  and add  variable to binary search tree
without type or in other words to symbol table,
return pointer to node in tree with new variable without type.*/
var_node *addVarName(char*);

/*Accepts type  and tree and add to all variables without
type in binary search tree type which function accept,
return pointer to node in tree to variable with type was added.*/
var_node *addVarType(char, var_node*);

/*Accepts name  and add  variable to binary search tree
without type or in other words to symbol table.*/
void set_varible_name(char*);

/*Accepts type  and tree and add to all variables without
type in binary search tree type which function accept.*/
void set_varible_type(char);

/*Accepts name and search this name in binary search tree
or in other words in symbol table,return pointer to node with
this variable name or if not exist null.*/
var_node *search_varible(char*);

/*Accepts type and pointer to the tree and search variable
with this type and state FREE in the tree pointer to node with
this variable if not found return null */
var_node *search_free_var(char, var_node*);

/*Accepts name and pointer to the tree and search location
for new variable and return pointer to this node where
will be this variable. */
var_node *searchLocation(char*, var_node*);

/*Accepts name of variable and him to state FREE*/
void free_state(char*);

/*Accept pointer to node and free this node*/
void freeVar(var_node*);

/*Free all tree of vaiables*/
void free_tree();

#endif