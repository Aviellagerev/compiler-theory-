%{
#include <stdio.h>
#include <malloc.h>
#include "symboltab.h"
#include "translator.h"

extern int yylex(void);
int yyerror(const char *s);
extern int line;
command_list *case_jumps = NULL; /* For tracking case jumps */
int number = 0; /* Counter for numeric values */
int error_number = 0; /* Counter for errors */
var_node *current_varible = NULL, *next_varible = NULL; /* Variables for symbol table */
command *current_command = NULL; /* Current command in the command list */
command_list *temp_link = NULL; /* Temporary link for command lists */
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
    free_tree();
    free_list($2);
}
| error { yyerrok; yyclearin; } /* Recover from program-level errors without semicolon */
;

declarations: declarations declaration
| /* epsilon */
;

declaration: idlist ':' type { set_varible_type($3); } ';'
| idlist ':' error { yyerrok; yyclearin; } /* Recover from type errors */
;

type: INT { $$ = $1; }
| FLOAT { $$ = $1; }
;

idlist: idlist ',' ID { set_varible_name($3); }
| ID { set_varible_name($1); }
| idlist ',' error { yyerrok; yyclearin; } /* Recover from idlist errors */
;

stmt: assignment_stmt { $$ = $1; }
| input_stmt { $$ = $1; }
| output_stmt { $$ = $1; }
| if_stmt { $$ = $1; }
| while_stmt { $$ = $1; }
| switch_stmt { $$ = $1; }
| break_stmt { $$ = $1; }
| stmt_block { $$ = $1; }
| error { yyerrok; yyclearin; $$ = NULL; } /* Recover after any statement error */
;

assignment_stmt: ID '=' expression ';'
{
    $$ = add_assign_commadn($1, $3.last, $3.type, $3.head);
}
| ID '=' expression { fprintf(stderr, "ERROR: line %d: missing semicolon after assignment\n", line-1); $$ = NULL; }
;

input_stmt: INPUT '(' ID ')' ';'
{
    $$ = NULL;
    if (!(current_varible = search_varible($3)))
        fprintf(stderr, "ERROR: unknown variable, not defined in the symbol table");
    else
        $$ = translate_comand(NULL, current_varible->type, "INP", current_varible->name, "", "");
}
| INPUT '(' ID ')' { fprintf(stderr, "ERROR: line %d: missing semicolon after input statement\n", line-1); $$ = NULL; }
;

output_stmt: OUTPUT '(' expression ')' ';'
{
    $$ = translate_comand($3.head, $3.type, "PRT", $3.last, "", "");
    free_state($3.last);
}
| OUTPUT '(' expression ')' { fprintf(stderr, "ERROR: line %d: missing semicolon after output statement\n", line-1); $$ = NULL; }
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
| IF '(' error ')' stmt ELSE stmt { yyerrok; yyclearin; $$ = NULL; } /* Recover from condition errors */
| IF '(' boolexpr ')' error ELSE stmt { yyerrok; yyclearin; $$ = NULL; } /* Recover from then-part errors */
| IF '(' boolexpr ')' stmt ELSE error { yyerrok; yyclearin; $$ = NULL; } /* Recover from else-part errors */
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
| WHILE '(' error ')' stmt { yyerrok; yyclearin; $$ = NULL; } /* Recover from condition errors */
| WHILE '(' boolexpr ')' error { yyerrok; yyclearin; $$ = NULL; } /* Recover from body errors */
;

switch_stmt: SWITCH '(' expression ')' '{' caselist DEFAULT ':' stmtlist '}'
{
    next_varible = add_temp_var(current_varible->type);
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
    fprintf(stderr, "ERROR: line %d: missing DEFAULT in switch statement\n", line-1);
    $$ = NULL;
}
| SWITCH '(' error ')' '{' caselist DEFAULT ':' stmtlist '}' { 
    yyerrok; yyclearin;
     $$ = NULL;
     }
| SWITCH '(' expression ')' '{' error DEFAULT ':' stmtlist '}' { 
    yyerrok; 
    yyclearin; 
    $$ = NULL; }
;


caselist: caselist CASE NUM ':' stmtlist
{
    num = $3.value;
    next_varible = add_temp_var(current_varible->type);
    $$ = translate_comand($1, current_varible->type, "EQL", next_varible->name, current_varible->name, num);
    $$ = translate_comand($$, 'J', "MPZ", "", next_varible->name, "");
    temp_link = add_new_command_list(NULL, get_last_command($$));
    $$ = merege_comand($$, $5);
    $$ = translate_comand($$, 'J', "UMP", "", "", "");
    case_jumps = add_new_command_list(case_jumps, get_last_command($$));
    $$ = add_label($$);
    update_list_to_label(temp_link, get_last_command($$));
}
| /* empty */ { $$ = NULL; case_jumps = NULL; }
| caselist CASE error ':' stmtlist { yyerrok; yyclearin; $$ = $1; } /* Recover from case value errors */
;

break_stmt: BREAK ';' { $$ = NULL; }
| BREAK { fprintf(stderr, "ERROR: line %d: missing semicolon after break\n", line-1); $$ = NULL; }
;

stmt_block: '{' stmtlist '}' { $$ = $2; }
| '{' error '}' { yyerrok; yyclearin; $$ = NULL; } /* Recover from block errors */
;

stmtlist: stmtlist stmt { $$ = merege_comand($1, $2); }
| /* empty */ { $$ = NULL; }
| stmtlist error { yyerrok; yyclearin; $$ = $1; } /* Recover after each statement in list */
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
| error { yyerrok; yyclearin; $$.head = NULL; $$.false = NULL; } /* Recover from boolean expression errors */
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
    add_label($$.head);
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
    number = cast($1);
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
    strcpy($$.last, $1.value);
    $$.type = $1.type;
    $$.head = NULL;
}
;

%%

int yyerror(const char *err)
{
    fprintf(stderr, "ERROR: line %d: %s\n", line-1, err);
    error_number = 1;
    return 1;
}