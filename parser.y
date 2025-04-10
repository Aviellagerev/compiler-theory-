%{


#include <stdio.h>
#include <malloc.h>
#include <stdarg.h> 
#include "error.h"
#include "symboltab.h"
#include "translator.h"

/* External Function Declarations */
extern void report_error(const char *format, ...); /* Reports errors with variable arguments */
extern int yylex(void); /* Lexer function to get the next token */
int yyerror(const char *s); /* Error handling function defined below */
extern int line; /* Tracks current line number, defined in lexer */


command_list *case_jumps = NULL; /* List of jumps for case statements in switch */
int number = 0; /* Counter for cast operations  */
int error_number = 0; /* Counter for errors  */
var_node *current_variable = NULL, *next_variable = NULL; /* Pointers to variables in the symbol table */
command *current_command = NULL; /* Current command being processed */
command_list *temp_link = NULL; /* Temporary list for linking commands */
char *num = NULL; /* Temporary storage for numeric values */
int p = 0; /* Counter for case values*/
char case_val[10]; /* Array to store case values ) */
extern const char* error_messeges[]; /* Array of error messages defined elsewhere */
#define YYDEBUG 1 /* For debug */
static int error_count = 0;
const int MAX_ERRORS = 4; /* Limit the number of error messages */
%}

%debug 
/* Parser Configuration */
%define parse.error verbose /* Enable detailed error messages for better debugging */

/* Union Definition: Specifies Types for Semantic Values */
%union
{
    char id[VARLEN]; /* Identifier name */
    char type; /* Type of a variable or expression ('I' or 'R') */
    char op; /* Arithmetic operator (+, -, *, /) */
    char cast_op; /* Cast operator (e.g., to int or float) */
    command *stmt; /* Command representing a statement */
    int relop; /* Relational operator code (e.g., <, >, ==) */

    struct exp {
        command *head; /* Head of the command list for an expression */
        command_list *false; /* False branch for boolean expressions */
        char last[VARLEN]; /* Last variable or value in the expression */
        char type; /* Type of the expression ('I' or 'R') */
    } expression;

    struct number {
        char value[VARLEN]; /* String representation of a numeric value */
        char type; /* 'I' for int, 'R' for float */
    } num;

    struct bool {
        command_list *false; /* False branch for boolean expressions */
        command *head; /* Head of the command list for boolean expressions */
    } boolean;
}

/* Token Declarations */
%token <id> ID                  /* Identifier */
%token CASE                     /* Keyword: case */
%token <type> INT FLOAT         /* Types: INT ('I'), FLOAT ('R') */
%token OUTPUT INPUT IF ELSE SWITCH WHILE DEFAULT BREAK /* Keywords */
%token <op> ADDOP MULOP         /* Arithmetic operators: +, -, *, / */
%token <num> NUM                /* Numeric literal */
%token <cast_op> CAST           /* Cast operator */
%token OR AND NOT               /* Logical operators */
%token <relop> RELOP            /* Relational operators: <, >, ==, etc. */

/* Type Declarations for Non-Terminals */
%type <type> type
%type <expression> expression term factor
%type <boolean> boolfactor boolexpr boolterm
%type <stmt> output_stmt assignment_stmt input_stmt stmt if_stmt break_stmt switch_stmt stmt_block while_stmt stmtlist caselist

/* To solve the conflict of IF without ELSE and the ambiguity that it can create */
%nonassoc IFX  /* Lower precedence for IF without ELSE */
%nonassoc ELSE /* Higher precedence for IF with ELSE */

%%

/* Grammar Rules and Actions */

/* Program: Top-Level Rule Representing the Entire Program */
program: declarations stmt_block
{
    $2 = translate_comand($2, 'H', "ALT", "", "", ""); /* Add a halt command */
    command_print($2); /* Print the generated commands */
    free_symbol_table(); /* Free the symbol table */
    free_list($2); /* Free the command list */
    fprintf(quad, "compiled successfully! ^-^ made by Aviel lagerev\n");
}
| error { yyerrok; yyclearin; } /* Recover from syntax errors at the top level */
;

/* Declarations: A List of Declarations or Empty */
declarations: declarations declaration
| /* epsilon */ /* Allows for no declarations */
;

/* Declaration: Declares a List of Identifiers with a Type */
declaration: idlist ':' type { set_variable_type($3); } ';'
| idlist ':' error { report_error(error_messeges[5]); yyerrok; yyclearin; } /* Missing type */
;

/* Type: Specifies the Type of Variables (Integer or Float) */
type: INT { $$ = $1; } /* 'I' from lexer */
| FLOAT { $$ = $1; } /* 'R' from lexer */
;

/* Idlist: A Comma-Separated List of Identifiers for Declarations */
idlist: idlist ',' ID { set_variable_name($3); } /* Add ID to symbol table */
| ID { set_variable_name($1); } /* Single ID */
| idlist ',' error { report_error(error_messeges[6]); yyerrok; yyclearin; } /* Missing ID */
;

/* Stmt: Represents Various Statement Types in the Language */
stmt: assignment_stmt { $$ = $1; }
| input_stmt { $$ = $1; }
| output_stmt { $$ = $1; }
| if_stmt { $$ = $1; }
| while_stmt { $$ = $1; }
| switch_stmt { $$ = $1; }
| break_stmt { $$ = $1; }
| stmt_block { $$ = $1; }
| ID { report_error(error_messeges[7], $1); $$ = NULL; } /* Lone ID is invalid */
| NUM { report_error(error_messeges[8], $1.value); $$ = NULL; } /* Lone number is invalid */
| error ';' { report_error(error_messeges[16]); yyerrok; $$ = NULL; } /* Error recovery for statements */
;

/* Assignment_stmt: Assigns an Expression's Value to a Variable */
assignment_stmt: ID '=' expression ';'
{
    $$ = add_assign_commadn($1, $3.last, $3.type, $3.head);
}
| ID '=' expression { report_error(error_messeges[9]); $$ = NULL; } /* Missing semicolon */
;

/* Input_stmt: Reads Input into a Variable */
input_stmt: INPUT '(' ID ')' ';'
{
    $$ = NULL;
    if (!(current_variable = search_variable($3)))
        report_error(error_messeges[4], $3); /* Variable not found */
    else
        $$ = translate_comand(NULL, current_variable->type, "INP", current_variable->name, "", "");
}
| INPUT '(' ID ')' { report_error(error_messeges[10]); $$ = NULL; } /* Missing semicolon */
;

/* Output_stmt: Outputs the Result of an Expression */
output_stmt: OUTPUT '(' expression ')' ';'
{
    $$ = translate_comand($3.head, $3.type, "PRT", $3.last, "", "");
    free_variable_state($3.last); /* Free temporary variable if applicable */
}
| OUTPUT '(' expression ')' { report_error(error_messeges[10]); $$ = NULL; } /* Missing semicolon */
;

/* If_stmt: Implements If-Else Logic with Jumps and Labels */
if_stmt: IF '(' boolexpr ')' stmt ELSE stmt
{
    $$ = merege_comand($3.head, $5); /* Merge condition and then-branch */
    $$ = translate_comand($$, 'J', "UMP", "", "", ""); /* Jump to end after then */
    temp_link = add_new_command_list(NULL, get_last_command($$)); /* Link to end */
    $$ = add_label($$); /* Label after then (start of else) */
    update_list_to_label($3.false, get_last_command($$)); /* False jumps to else */
    $$ = merege_comand($$, $7); /* Merge else-branch */
    $$ = add_label($$); /* Label at end */
    update_list_to_label(temp_link, get_last_command($$)); /* Jump from end of 'then' to end */
}
| IF '(' boolexpr ')' stmt %prec IFX
{
    report_error(error_messeges[23]);
    $$ = NULL;
}
| IF '(' error ')' stmt ELSE stmt { report_error(error_messeges[12]); yyerrok; yyclearin; $$ = NULL; }
;

/* While_stmt: Implements a While Loop with Jumps and Labels */
while_stmt: WHILE '(' boolexpr ')' stmt
{
    $$ = add_label(NULL); /* Start label */
    $$ = merege_comand($$, $3.head); /* Condition commands */
    $$ = merege_comand($$, $5); /* Body commands */
    $$ = translate_comand($$, 'J', "UMP", "", "", ""); /* Jump back to start */
    temp_link = add_new_command_list(NULL, get_last_command($$));
    update_list_to_label(temp_link, $$); /* Link jump to start */
    $$ = add_label($$); /* End label */
    update_list_to_label($3.false, get_last_command($$)); /* False exits loop */
}
| WHILE '(' error ')' stmt { report_error(error_messeges[13]); yyerrok; yyclearin; $$ = NULL; }
;

/* Switch_stmt: Implements a Switch Statement with Cases and Default */
switch_stmt: SWITCH '(' expression ')' '{' caselist DEFAULT ':' stmtlist '}'
{
    next_variable = add_temp_var(current_variable ? current_variable->type : 'I'); /* Temp var for comparison */
    $3.head = merege_comand($3.head, $6); /* Merge expression and cases */
    temp_link = add_new_command_list(NULL, get_last_command($3.head)); /* Link to end */
    $3.head = add_label($3.head); /* Label before default */
    $3.head = merege_comand($3.head, $9); /* Merge default statements */
    $3.head = add_label($3.head); /* End label */
    update_list_to_label(temp_link, get_last_command($3.head)); /* Non-matching jumps */
    update_list_to_label(case_jumps, get_last_command($3.head)); /* Case exits */
    case_jumps = NULL; /* Reset case jumps */
    $$ = $3.head;
}
| SWITCH '(' expression ')' '{' caselist '}' /* Missing default */
{
    report_error(error_messeges[14]);
    $$ = NULL;
}
;

/* Caselist: A List of Case Statements in a Switch */
caselist: caselist CASE NUM ':' stmtlist
{
    num = $1 ? $3.value : $3.value; /* Store case value */
    next_variable = add_temp_var(current_variable ? current_variable->type : 'I');
    $$ = translate_comand($1, current_variable ? current_variable->type : 'I', "EQL", next_variable->name, current_variable ? current_variable->name : "", num); /* Equality check */
    $$ = translate_comand($$, 'J', "MPZ", "", next_variable->name, ""); /* Jump if zero (false) */
    temp_link = add_new_command_list(NULL, get_last_command($$)); /* Link to next case */
    $$ = merege_comand($$, $5); /* Case statements */
    $$ = translate_comand($$, 'J', "UMP", "", "", ""); /* Jump to end */
    case_jumps = add_new_command_list(case_jumps, get_last_command($$)); /* Add to case exits */
    $$ = add_label($$); /* Label after case */
    update_list_to_label(temp_link, get_last_command($$)); /* False jumps to next */
}
| /* empty */ { $$ = NULL; case_jumps = NULL; } /* No cases */
;

/* Break_stmt: Handles Break Statements */
break_stmt: BREAK ';' { $$ = NULL; }
| BREAK { report_error(error_messeges[15]); $$ = NULL; } /* Missing semicolon */
;

/* Stmt_block: A Block of Statements Enclosed in Braces */
stmt_block: '{' stmtlist '}' { $$ = $2; }
          | '{' stmtlist error { report_error(error_messeges[16]); $$ = NULL; }
;
/* Stmtlist: A List of Statements */
stmtlist: stmtlist stmt { $$ = merege_comand($1, $2); }
| /* empty */ { $$ = NULL; }

;

/* Boolexpr: Handles Boolean Expressions with OR Operations */
boolexpr: boolexpr OR boolterm
{
    $$.head = translate_comand($1.head, 'J', "UMP", "", "", ""); /* Jump if true */
    temp_link = add_new_command_list(NULL, get_last_command($$.head));
    $$.head = add_label($$.head); /* Label after first term */
    update_list_to_label($1.false, get_last_command($$.head)); /* False continues */
    $$.head = merege_comand($$.head, $3.head); /* Merge second term */
    add_label($$.head); /* Label at end */
    update_list_to_label(temp_link, get_last_command($$.head)); /* True jumps to end */
    $$.false = $3.false; /* False from second term */
}
| boolterm { $$.head = $1.head; $$.false = $1.false; }
;

/* Boolterm: Handles Boolean Terms with AND Operations */
boolterm: boolterm AND boolfactor
{
    $$.head = merege_comand($1.head, $3.head); /* Merge commands */
    $$.false = merge_comnd_list($1.false, $3.false); /* Merge false branches */
}
| boolfactor { $$.false = $1.false; $$.head = $1.head; }
;

/* Boolfactor: Handles Boolean Factors (NOT or Relational Ops) */
boolfactor: NOT '(' boolexpr ')'
{
    $$.head = translate_comand($3.head, 'J', "UMP", "", "", ""); /* Jump if true */
    $$.false = add_new_command_list(NULL, get_last_command($$.head)); /* False branch */
    $$.head = add_label($$.head);
    update_list_to_label($3.false, get_last_command($$.head)); /* True becomes false */
}
| expression RELOP expression /* Relational comparison */
{
    if ($1.type == 'I' && $3.type == 'R')
        $1.head = convert_to_float($1.head, $1.last); /* Convert int to float */
    else if ($3.type == 'I' && $1.type == 'R')
        $3.head = convert_to_float($3.head, $3.last); /* Convert int to float */
    $$.head = build_relop_command($2, $1.last, $3.last, $1.head, $3.head, type_decider($1.type, $3.type));
    $$.false = add_new_command_list(NULL, get_last_command($$.head)); /* False branch */
}
;

/* Expression: Handles Arithmetic Expressions with Addition/Subtraction */
expression: expression ADDOP term
{
    $$.type = type_decider($1.type, $3.type); /* Determine result type */
    $$.head = build_arithmetic_command($2, $$.type, $$.last, $1.last, $3.last, $1.type, $3.type, $1.head, $3.head);
}
| term { $$.type = $1.type; $$.head = $1.head; strcpy($$.last, $1.last); }
;

/* Term: Handles Arithmetic Terms with Multiplication/Division */
term: term MULOP factor
{
    $$.type = type_decider($1.type, $3.type); /* Determine result type */
    $$.head = build_arithmetic_command($2, $$.type, $$.last, $1.last, $3.last, $1.type, $3.type, $1.head, $3.head);
}
| factor { $$.type = $1.type; $$.head = $1.head; strcpy($$.last, $1.last); }
;

/* Factor: Handles Basic Expression Elements (Parentheses, Casts, IDs, Numbers) */
factor: '(' expression ')'
{
    $$.type = $2.type;
    $$.head = $2.head;
    strcpy($$.last, $2.last);
}
| CAST '(' expression ')' /* Type casting */
{
    number = cast($1); /* 1 for int, 2 for float */
    if (number == 1 && $3.type == 'R') {
        $$.head = convert_to_int($3.head, $3.last); /* Float to int */
        $$.type = 'I';
    } else if (number == 2 && $3.type == 'I') {
        $$.head = convert_to_float($3.head, $3.last); /* Int to float */
        $$.type = 'R';
    } else {
        $$.type = $3.type; /* No conversion needed */
        $$.head = $3.head;
    }
    strcpy($$.last, $3.last);
}
| ID
{
    $$.head = NULL;
    if (!(current_variable = search_variable($1))) {
        report_error(error_messeges[4], $1); /* Undefined variable */
        $$.type = 0;
    } else {
        strcpy($$.last, $1);
        $$.type = current_variable->type;
    }
}
| NUM
{
    strcpy($$.last, $1.value);
    $$.type = $1.type;
    $$.head = NULL;
}
;

%%

/* Error Handling Function: Reports Parsing Errors with Line Number */
int yyerror(const char *err)
{
    /*critical error*/
    if (error_count >= MAX_ERRORS) {
        report_error(error_messeges[24]);
        exit(1); /* Terminate after too many errors */
    }

    error_count++;
    report_error("%s\n", err);
    return 1;
}