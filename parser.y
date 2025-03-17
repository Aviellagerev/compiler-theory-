%{
#include <stdio.h>
#include <malloc.h>
#include "symboltab.h"
#include "translator.h"

extern int yylex (void);
int yyerror(const char *s);
extern int line;

int number = 0; /* Counter for numeric values */
int error_number = 0; /* Counter for errors */
var_node *current_varible = NULL, *next_varible = NULL; /* Variables for symbol table */
command *current_command = NULL; /* Current command in the command list */
command_list *temp_link = NULL; /* Temporary link for command lists  for jmp*/
char *num = NULL; /* Temporary storage for numeric values */
int p = 0; /* Counter for case values */
char case_val[10]; /* Array to store case values */
%}
%define parse.error verbose

%union
{
    struct number {
        char value[VARLEN]; /* Value of a number */
        char type; /* Type of the number (INT or FLOAT) */
    } num;

    struct exp {
        command *head; /* Head of the command list for expressions */
        command_list *false; /* False branch for boolean expressions */
        char last[VARLEN]; /* Last variable or value in the expression */
        char type; /* Type of the expression */
    } expression;

    struct bool {
        command_list *false; /* False branch for boolean expressions */
        command *head; /* Head of the command list for boolean expressions */
    } boolean;

    char id[VARLEN]; /* Identifier name */
    char type; /* Type of a variable or expression */
    char op; /* Arithmetic or logical operator */
    char cast_op; /* Cast operator */
    command *stmt; /* Statement command */
    int relop; /* Relational operator */
}

%type <type> type

%type <expression> expression /* Expression with a value and type */
%type <expression> term /* Term in an expression */
%type <expression> factor /* Factor in an expression */

%type <boolean> boolfactor /* Boolean factor */
%type <boolean> boolexpr /* Boolean expression */
%type <boolean> boolterm /* Boolean term */

%type <stmt> output_stmt /* Output statement */
%type <stmt> assignment_stmt /* Assignment statement */
%type <stmt> input_stmt /* Input statement */
%type <stmt> stmt /* General statement */
%type <stmt> if_stmt /* If statement */
%type <stmt> break_stmt /* Break statement */
%type <stmt> switch_stmt /* Switch statement */
%type <stmt> stmt_block /* Block of statements */
%type <stmt> while_stmt /* While statement */
%type <stmt> stmtlist /* List of statements */
%type <stmt> caselist /* List of cases in a switch statement */

%token <id> ID /* Identifier token */
%token CASE /* Case keyword */
%token <type> INT /* Integer type */
%token <type> FLOAT /* Float type */
%token OUTPUT /* Output keyword */
%token INPUT /* Input keyword */
%token IF /* If keyword */
%token ELSE /* Else keyword */
%token SWITCH /* Switch keyword */
%token WHILE /* While keyword */
%token DEFAULT /* Default keyword */
%token BREAK /* Break keyword */
%token <op> ADDOP /* Addition operator */
%token <num> NUM /* Numeric value */
%token <op> MULOP /* Multiplication operator */
%token <cast_op> CAST /* Cast operator */
%token OR /* Logical OR */
%token AND /* Logical AND */
%token NOT /* Logical NOT */
%token <relop> RELOP /* Relational operator */

%%
program: declarations stmt_block
{
    /* Translate the entire program into commands and print them */
    $2 = translate_comand($2, 'H', "ALT", "", "", "");
    command_print($2);
    free_tree(); /* Free the syntax tree */
    free_list($2); /* Free the command list */
}
;

declarations: declarations declaration
| /*epsilon*/ /* Empty declaration */
;

declaration: idlist ':' type { set_varible_type($3); } ';' /* Set the type for variables in the idlist */
;

type: INT { $$ = $1; } /* Integer type */
| FLOAT { $$ = $1; } /* Float type */
;

idlist: idlist ',' ID { set_varible_name($3); } /* Add a variable to the idlist */
| ID { set_varible_name($1); } /* Single variable in the idlist */
;

stmt: assignment_stmt { $$ = $1; } /* Assignment statement */
| input_stmt { $$ = $1; } /* Input statement */
| output_stmt { $$ = $1; } /* Output statement */
| if_stmt { $$ = $1; } /* If statement */
| while_stmt { $$ = $1; } /* While statement */
| switch_stmt { $$ = $1; } /* Switch statement */
| break_stmt { $$ = $1; } /* Break statement */
| stmt_block { $$ = $1; } /* Block of statements */
;

assignment_stmt: ID '=' expression ';'
{
    /* Add an assignment command to the command list */
    $$ = add_assign_commadn($1, $3.last, $3.type, $3.head);
}
;

input_stmt: INPUT '(' ID ')' ';'
{
    /* Generate an input command for the specified variable */
    $$ = NULL;
    if (!(current_varible = search_varible($3)))
        fprintf(stderr, "ERROR: unknown variable, not defined in the symbol table");
    else
        $$ = translate_comand(NULL, current_varible->type, "INP", current_varible->name, "", "");
}
;

output_stmt: OUTPUT '(' expression ')' ';'
{
    /* Generate an output command for the expression */
    $$ = translate_comand($3.head, $3.type, "PRT", $3.last, "", "");
    free_state($3.last); /* Free the state after output */
}
;

if_stmt: IF '(' boolexpr ')' stmt ELSE stmt
{
    /* Merge the boolean expression and statements for the if-else construct */
    $$ = merege_comand($3.head, $5);
    $$ = translate_comand($$, 'J', "UMP", "", "", "");
    temp_link = add_new_command_list(NULL, get_last_command($$));
    $$ = add_label($$);
    updateList($3.false, get_last_command($$));
    $$ = merege_comand($$, $7);
    $$ = add_label($$);
    updateList(temp_link, get_last_command($$));
}
;

while_stmt: WHILE '(' boolexpr ')' stmt
{
    /* Generate commands for the while loop */
    $$ = add_label(NULL);
    $$ = merege_comand($$, $3.head);
    $$ = merege_comand($$, $5);
    $$ = translate_comand($$, 'J', "UMP", "", "", "");
    temp_link = add_new_command_list(NULL, get_last_command($$));
    updateList(temp_link, $$);
    $$ = add_label($$);
    updateList($3.false, get_last_command($$));
}
;

switch_stmt: SWITCH '(' expression ')' '{' caselist DEFAULT ':' stmtlist '}'
{
    /* Generate commands for the switch statement */
    next_varible = createTempVar(current_varible->type);
    current_command = translate_comand(current_command, 'J', "MPZ", "", next_varible->name, "");
    $3.head = merege_comand(current_command, $3.head);
    temp_link = add_new_command_list(NULL, get_last_command($3.head));
    $3.head = add_label($3.head);
    updateList(temp_link, get_last_command($3.head));
    current_command = NULL;
    *num = case_val[0];
    current_command = translate_comand(current_command, current_varible->type, "EQL", current_varible->name, next_varible->name, num);
    $3.head = merege_comand(current_command, $3.head);
    $$ = merege_comand($3.head, $6);
    $$ = translate_comand($$, 'J', "UMP", "", "", "");
    temp_link = add_new_command_list(NULL, get_last_command($$));
    $$ = merege_comand($$, $9);
    $$ = add_label($$);
    updateList(temp_link, get_last_command($$));
}
;

caselist: caselist CASE NUM ':' stmtlist
{
    /* Generate commands for each case in the switch statement */
    num = $3.value;
    case_val[p] = *num;
    p++;
    next_varible = createTempVar(current_varible->type);
    $$ = translate_comand($$, current_varible->type, "EQL", current_varible->name, next_varible->name, num);
    $$ = translate_comand($$, 'J', "MPZ", "", next_varible->name, "");
    temp_link = add_new_command_list(NULL, get_last_command($$));
    $$ = add_label($$);
    updateList(temp_link, get_last_command($$));
    $$ = merege_comand($1, $5);
    $$ = translate_comand($$, 'J', "UMP", "", "", "");
    temp_link = add_new_command_list(NULL, get_last_command($$));
    $$ = add_label($$);
    updateList(temp_link, get_last_command($$));
}
| /*empty*/ { $$ = NULL; } /* Empty case list */
;

break_stmt: BREAK ';' { $$ = NULL; } /* Break statement */
;

stmt_block: '{' stmtlist '}' { $$ = $2; } /* Block of statements */
;

stmtlist: stmtlist stmt { $$ = merege_comand($1, $2); } /* List of statements */
| /*empty*/ { $$ = NULL; } /* Empty statement list */
;

boolexpr: boolexpr OR boolterm
{
    /* Generate commands for logical OR */
    $$.head = translate_comand($1.head, 'J', "UMP", "", "", "");
    temp_link = add_new_command_list(NULL, get_last_command($$.head));
    $$.head = add_label($$.head);
    updateList($1.false, get_last_command($$.head));
    $$.head = merege_comand($$.head, $3.head);
    add_label($$.head);
    updateList(temp_link, get_last_command($$.head));
    $$.false = $3.false;
}
| boolterm
{
    /* Boolean term */
    $$.head = $1.head;
    $$.false = $1.false;
}
;

boolterm: boolterm AND boolfactor
{
    /* Generate commands for logical AND */
    $$.head = merege_comand($1.head, $3.head);
    $$.false = mergeLists($1.false, $3.false);
}
| boolfactor
{
    /* Boolean factor */
    $$.false = $1.false;
    $$.head = $1.head;
}
;

boolfactor: NOT '(' boolexpr ')'
{
    /* Generate commands for logical NOT */
    $$.head = translate_comand($3.head, 'J', "UMP", "", "", "");
    $$.false = add_new_command_list(NULL, get_last_command($$.head));
    add_label($$.head);
    updateList($3.false, get_last_command($$.head));
}
| expression RELOP expression
{
    /* Generate commands for relational operators */
    if ($1.type == 'I' && $3.type == 'R')
        $1.head = floatConvert($1.head, $1.last);
    else if ($3.type == 'I' && $1.type == 'R')
        $3.head = floatConvert($3.head, $3.last);
    $$.head = build_relop_command($2, $1.last, $3.last, $1.head, $3.head, typeUpdate($1.type, $3.type));
    $$.false = add_new_command_list(NULL, get_last_command($$.head));
}
;

expression: expression ADDOP term
{
    /* Generate commands for addition/subtraction */
    $$.type = typeUpdate($1.type, $3.type);
    $$.head = build_arithmetic_command($2, $$.type, $$.last, $1.last, $3.last, $1.type, $3.type, $1.head, $3.head);
}
| term
{
    /* Term in an expression */
    $$.type = $1.type;
    $$.head = $1.head;
    strcpy($$.last, $1.last);
}
;

term: term MULOP factor
{
    /* Generate commands for multiplication/division */
    $$.type = typeUpdate($1.type, $3.type);
    $$.head = build_arithmetic_command($2, $$.type, $$.last, $1.last, $3.last, $1.type, $3.type, $1.head, $3.head);
}
| factor
{
    /* Factor in a term */
    $$.type = $1.type;
    $$.head = $1.head;
    strcpy($$.last, $1.last);
}
;

factor: '(' expression ')'
{
    /* Parenthesized expression */
    $$.type = $2.type;
    $$.head = $2.head;
    strcpy($$.last, $2.last);
}
| CAST '(' expression ')'
{
    /* Cast expression */
    number = cast($1);
    if (number == 1 && $3.type == 'R') {
        $$.head = intConvert($3.head, $3.last);
        $$.type = 'I';
    } else if (number == 2 && $3.type == 'I') {
        $$.head = floatConvert($3.head, $3.last);
        $$.type = 'R';
    } else {
        $$.type = $3.type;
        $$.head = $3.head;
    }
    strcpy($$.last, $3.last);
}
| ID
{
    /* Identifier */
    $$.head = NULL;
    if (!(current_varible = search_varible($1))) {
        fprintf(stderr, "ERROR: unknown variable, not defined in the symbol table");
        $$.type = 0;
    } else {
        strcpy($$.last, $1);
        $$.type = current_varible->type;
    }
}
| NUM
{
    /* Numeric value */
    strcpy($$.last, $1.value);
    $$.type = $1.type;
    $$.head = NULL;
}
;

%%

int yyerror(const char *err)
{
    /* Error handling function */
    fprintf(stderr, "ERROR: line %d: %s\n", line, err);
    error_number = 1;
    return 1;
}