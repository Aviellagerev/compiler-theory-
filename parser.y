%{
    
#include <stdio.h>
#include <malloc.h>
#include <stdarg.h> /* Added for variable argument handling */
#include "error.h"
#include "symboltab.h"
#include "translator.h"


extern void report_error(const char *format, ...);
extern int yylex(void);
int yyerror(const char *s);
extern int line; /* Defined in lexer, tracks current line number */
command_list *case_jumps = NULL; /* For tracking case jumps in switch statements */
int number = 0; /* Counter for cast operations */
int error_number = 0; /* Counter for errors */
var_node *current_variable = NULL, *next_variable = NULL; /* Symbol table variables */
command *current_command = NULL; /* Current command in the command list */
command_list *temp_link = NULL; /* Temporary link for command lists */
char *num = NULL; /* Temporary storage for numeric values */
int p = 0; /* Counter for case values */
char case_val[10]; /* Array to store case values */
extern const char* error_messeges[];


%}

%define parse.error verbose /* Enable detailed error messages */

%union
{
    struct number {
        char value[VARLEN]; /* Value of a number */
        char type; /* Type of the number (I for int, R for float) */
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
    char type; /* Type of a variable or expression (I or R) */
    char op; /* Arithmetic operator */
    char cast_op; /* Cast operator */
    command *stmt; /* Statement command */
    int relop; /* Relational operator code */
}

%type <type> type
%type <expression> expression term factor
%type <boolean> boolfactor boolexpr boolterm
%type <stmt> output_stmt assignment_stmt input_stmt stmt if_stmt break_stmt switch_stmt stmt_block while_stmt stmtlist caselist

%token <id> ID
%token CASE
%token <type> INT FLOAT
%token OUTPUT INPUT IF ELSE SWITCH WHILE DEFAULT BREAK
%token <op> ADDOP MULOP
%token <num> NUM
%token <cast_op> CAST
%token OR AND NOT
%token <relop> RELOP

%%

program: declarations stmt_block
{
    $2 = translate_comand($2, 'H', "ALT", "", "", "");
    command_print($2);
    free_tree(); /* Free symbol table */
    free_list($2); /* Free command list */
}
| error { yyerrok; yyclearin; } /* Recover from top-level errors */
;

declarations: declarations declaration
| /* epsilon */
;

declaration: idlist ':' type { set_varible_type($3); } ';'
| idlist ':' error { report_error(error_messeges[5]); yyerrok; yyclearin; }
;

type: INT { $$ = $1; } /* 'I' from lexer */
| FLOAT { $$ = $1; } /* 'R' from lexer */
;

idlist: idlist ',' ID { set_varible_name($3); }
| ID { set_varible_name($1); }
| idlist ',' error { report_error(error_messeges[6]); yyerrok; yyclearin; }
;

stmt: assignment_stmt { $$ = $1; }
| input_stmt { $$ = $1; }
| output_stmt { $$ = $1; }
| if_stmt { $$ = $1; }
| while_stmt { $$ = $1; }
| switch_stmt { $$ = $1; }
| break_stmt { $$ = $1; }
| stmt_block { $$ = $1; }
| ID { report_error(error_messeges[7], $1); $$ = NULL; }
| NUM { report_error(error_messeges[8], $1.value); $$ = NULL; }
| error { yyerrok; yyclearin; $$ = NULL; } /* yyerror is called automatically */
;

assignment_stmt: ID '=' expression ';'
{
    $$ = add_assign_commadn($1, $3.last, $3.type, $3.head);
}
| ID '=' expression { report_error(error_messeges[9]); $$ = NULL; }
;

input_stmt: INPUT '(' ID ')' ';'
{
    $$ = NULL;
    if (!(current_variable = search_varible($3)))
        report_error(error_messeges[4], $3);
    else
        $$ = translate_comand(NULL, current_variable->type, "INP", current_variable->name, "", "");
}
| INPUT '(' ID ')' { report_error(error_messeges[10]); $$ = NULL; }
;

output_stmt: OUTPUT '(' expression ')' ';'
{
    $$ = translate_comand($3.head, $3.type, "PRT", $3.last, "", "");
    free_state($3.last); /* Mark variable as free if temporary */
}
| OUTPUT '(' expression ')' { report_error(error_messeges[10]); $$ = NULL; }
;

if_stmt: IF '(' boolexpr ')' stmt ELSE stmt
{
    $$ = merege_comand($3.head, $5);
    $$ = translate_comand($$, 'J', "UMP", "", "", "");
    temp_link = add_new_command_list(NULL, get_last_command($$));
    $$ = add_label($$);
    update_list_to_label($3.false, get_last_command($$));
    $$ = merege_comand($$, $7);
    $$ = add_label($$);
    update_list_to_label(temp_link, get_last_command($$));
}
| IF '(' error ')' stmt ELSE stmt { report_error(error_messeges[12]); yyerrok; yyclearin; $$ = NULL; }
;

while_stmt: WHILE '(' boolexpr ')' stmt
{
    $$ = add_label(NULL);
    $$ = merege_comand($$, $3.head);
    $$ = merege_comand($$, $5);
    $$ = translate_comand($$, 'J', "UMP", "", "", "");
    temp_link = add_new_command_list(NULL, get_last_command($$));
    update_list_to_label(temp_link, $$);
    $$ = add_label($$);
    update_list_to_label($3.false, get_last_command($$));
}
| WHILE '(' error ')' stmt { report_error(error_messeges[13]); yyerrok; yyclearin; $$ = NULL; }
;

switch_stmt: SWITCH '(' expression ')' '{' caselist DEFAULT ':' stmtlist '}'
{
    next_variable = add_temp_var(current_variable ? current_variable->type : 'I'); /* Default to int if no current var */
    $3.head = merege_comand($3.head, $6);
    temp_link = add_new_command_list(NULL, get_last_command($3.head));
    $3.head = add_label($3.head);
    $3.head = merege_comand($3.head, $9);
    $3.head = add_label($3.head);
    update_list_to_label(temp_link, get_last_command($3.head));
    update_list_to_label(case_jumps, get_last_command($3.head));
    case_jumps = NULL;
    $$ = $3.head;
}
| SWITCH '(' expression ')' '{' caselist '}'
{
    report_error(error_messeges[14]);
    $$ = NULL;
}
;

caselist: caselist CASE NUM ':' stmtlist
{
    num = $1 ? $3.value : $3.value; /* Use NUM value directly */
    next_variable = add_temp_var(current_variable ? current_variable->type : 'I');
    $$ = translate_comand($1, current_variable ? current_variable->type : 'I', "EQL", next_variable->name, current_variable ? current_variable->name : "", num);
    $$ = translate_comand($$, 'J', "MPZ", "", next_variable->name, "");
    temp_link = add_new_command_list(NULL, get_last_command($$));
    $$ = merege_comand($$, $5);
    $$ = translate_comand($$, 'J', "UMP", "", "", "");
    case_jumps = add_new_command_list(case_jumps, get_last_command($$));
    $$ = add_label($$);
    update_list_to_label(temp_link, get_last_command($$));
}
| /* empty */ { $$ = NULL; case_jumps = NULL; }
;

break_stmt: BREAK ';' { $$ = NULL; }
| BREAK { report_error(error_messeges[15]); $$ = NULL; }
;

stmt_block: '{' stmtlist '}' { $$ = $2; }
| '{' error '}' { report_error(error_messeges[16]); yyerrok; yyclearin; $$ = NULL; }
;

stmtlist: stmtlist stmt { $$ = merege_comand($1, $2); }
| stmtlist error { report_error(error_messeges[16]); yyerrok; yyclearin; $$ = $1; }
| /* empty */ { $$ = NULL; }
;

boolexpr: boolexpr OR boolterm
{
    $$.head = translate_comand($1.head, 'J', "UMP", "", "", "");
    temp_link = add_new_command_list(NULL, get_last_command($$.head));
    $$.head = add_label($$.head);
    update_list_to_label($1.false, get_last_command($$.head));
    $$.head = merege_comand($$.head, $3.head);
    add_label($$.head);
    update_list_to_label(temp_link, get_last_command($$.head));
    $$.false = $3.false;
}
| boolterm { $$.head = $1.head; $$.false = $1.false; }
;

boolterm: boolterm AND boolfactor
{
    $$.head = merege_comand($1.head, $3.head);
    $$.false = merge_comnd_list($1.false, $3.false);
}
| boolfactor { $$.false = $1.false; $$.head = $1.head; }
;

boolfactor: NOT '(' boolexpr ')'
{
    $$.head = translate_comand($3.head, 'J', "UMP", "", "", "");
    $$.false = add_new_command_list(NULL, get_last_command($$.head));
    $$.head = add_label($$.head);
    update_list_to_label($3.false, get_last_command($$.head));
}
| expression RELOP expression
{
    if ($1.type == 'I' && $3.type == 'R')
        $1.head = convert_to_float($1.head, $1.last);
    else if ($3.type == 'I' && $1.type == 'R')
        $3.head = convert_to_float($3.head, $3.last);
    $$.head = build_relop_command($2, $1.last, $3.last, $1.head, $3.head, type_decider($1.type, $3.type));
    $$.false = add_new_command_list(NULL, get_last_command($$.head));
}
;

expression: expression ADDOP term
{
    $$.type = type_decider($1.type, $3.type);
    $$.head = build_arithmetic_command($2, $$.type, $$.last, $1.last, $3.last, $1.type, $3.type, $1.head, $3.head);
}
| term { $$.type = $1.type; $$.head = $1.head; strcpy($$.last, $1.last); }
;

term: term MULOP factor
{
    $$.type = type_decider($1.type, $3.type);
    $$.head = build_arithmetic_command($2, $$.type, $$.last, $1.last, $3.last, $1.type, $3.type, $1.head, $3.head);
}
| factor { $$.type = $1.type; $$.head = $1.head; strcpy($$.last, $1.last); }
;

factor: '(' expression ')'
{
    $$.type = $2.type;
    $$.head = $2.head;
    strcpy($$.last, $2.last);
}
| CAST '(' expression ')'
{
    number = cast($1); /* cast() returns 1 for int, 2 for float */
    if (number == 1 && $3.type == 'R') {
        $$.head = convert_to_int($3.head, $3.last);
        $$.type = 'I';
    } else if (number == 2 && $3.type == 'I') {
        $$.head = convert_to_float($3.head, $3.last);
        $$.type = 'R';
    } else {
        $$.type = $3.type;
        $$.head = $3.head;
    }
    strcpy($$.last, $3.last);
}
| ID
{
    $$.head = NULL;
    if (!(current_variable = search_varible($1))) {
        report_error(error_messeges[4], $1);
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

int yyerror(const char *err)
{
    report_error("%s\n", err);
    return 1;
}