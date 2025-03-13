
%{
#include <stdio.h>
#include <malloc.h>
#include "symboltab.h"
#include "translator.h"

extern int yylex (void);
int yyerror(const char *s);
extern int line;

int number = 0;
int error_number = 0;
var_node *current_varible = NULL, *next_varible = NULL;
command *current_command = NULL;
command_list *temp_link = NULL;
char *num = NULL;
int p = 0;
char case_val[10] ;
%}
%define parse.error verbose

%union
{
	struct number {
		          char value[VARLEN];
		          char type;
	                        } num;

               struct exp {
		    command *head;
                                     command_list *false;
		    char last[VARLEN];
		    char type;
	                 } expression;
	
	struct bool {
		       command_list *false;
		       command *head;
	                   } boolean;

	char id[VARLEN];	
	char type;
	char op; 
                char cast_op;	
	 command *stmt;	
	int relop; 
}

%type <type> type

%type <expression> expression				
%type <expression> term			
%type <expression> factor

%type <boolean> boolfactor		
%type <boolean> boolexpr
%type <boolean> boolterm

%type <stmt> output_stmt
%type <stmt> assignment_stmt
%type <stmt> input_stmt
%type <stmt> stmt
%type <stmt> if_stmt
%type <stmt> break_stmt
%type <stmt> switch_stmt
%type <stmt> stmt_block
%type <stmt> while_stmt
%type <stmt> stmtlist
%type <stmt> caselist

%token <id> ID
%token CASE
%token <type>INT
%token <type>FLOAT
%token OUTPUT
%token INPUT
%token IF
%token ELSE
%token SWITCH
%token WHILE
%token DEFAULT
%token BREAK
%token <op>ADDOP
%token <num>NUM
%token <op>MULOP
%token <cast_op> CAST
%token OR
%token AND
%token NOT
%token <relop>RELOP


%%
program                                             :      declarations  stmt_block
                                                                                                               {
					                                  $2 = translate_comand($2,'H',"ALT","","","");
					                                   command_print($2);
					                                   free_tree();
					                                   free_list($2);
				                                                }
                                                           ;

declarations                                       :      declarations  declaration 
                                                          |       /*epsilon*/
                                                          ;

declaration                                        :     idlist    ':'  type       { set_varible_type($3);}  ';'   ;
                                                                    

type                                                   :       INT {$$ = $1;}
                                                          |       FLOAT {$$ = $1;}
                                                          ;

idlist                                                  :       idlist  ','  ID { set_varible_name($3);}
                                                          |       ID { set_varible_name($1);}
                                                          ;

stmt                                                   :      assignment_stmt {$$ = $1;}
                                                          |       input_stmt {$$ = $1;}
                                                          |       output_stmt {$$ = $1;}
                                                          |       if_stmt {$$ = $1;}
                                                          |       while_stmt {$$ = $1;}
                                                          |       switch_stmt {$$ = $1;}
                                                          |       break_stmt {$$ = $1;}
                                                          |       stmt_block {$$ = $1;}
                                                          ;

assignment_stmt                                :  ID  '='  expression  ';' { $$ = add_assign_commadn($1, $3.last, $3.type, $3.head);} 
                                                            ;

input_stmt                                          :      INPUT  '('  ID  ')'   ';'  
                                                                                                     {
					                       $$ = NULL;
					                        if(!(current_varible = search_varible($3)))
						                   fprintf(stderr,"ERROR: unknown variable, not defined in the symbol table");
					                        else
						            $$ = translate_comand(NULL,current_varible->type,"INP",current_varible->name,"","");
				                                      }
			          
                                                           ;

output_stmt                                        :     OUTPUT  '('  expression  ')'   ';'
                                                                                                                          {
					                                             $$ = translate_comand($3.head,$3.type,"PRT",$3.last,"","");		
					                                              free_state($3.last);
				                                                           }			          
			             ; 

if_stmt                                                  :    IF  '('  boolexpr  ')'  stmt  ELSE  stmt 
                                                                                           {	
						$$ = merege_comand($3.head, $5);
						$$ = translate_comand($$,'J',"UMP","","","");
						temp_link = add_new_command_list(NULL, get_last_command($$)); 
						$$ = add_label($$);
						updateList($3.false,get_last_command($$));
						$$ = merege_comand($$, $7);
						$$ = add_label($$);
						updateList(temp_link, get_last_command($$));
					           }
                                                           ;

while_stmt                                         :     WHILE  '('  boolexpr  ')'  stmt
                                                                                 {
						$$ = add_label(NULL);
						$$ = merege_comand($$, $3.head);
						$$ = merege_comand($$, $5);
						$$ = translate_comand($$,'J',"UMP","","","");
			                                                temp_link = add_new_command_list(NULL, get_last_command($$));
						updateList(temp_link, $$);
						$$ = add_label($$);
						updateList($3.false, get_last_command($$));
					}
                                                                ;

switch_stmt                                       :    SWITCH  '('  expression  ')'   '{'  caselist  DEFAULT  ':'  stmtlist  '}'
                                                                               {  
                                                                                          
                                                                                     next_varible = createTempVar( current_varible->type );
                                                                                    current_command =  translate_comand(current_command, 'J', "MPZ", "",  next_varible->name, "");                                                                                                   
                                                                                    $3.head = merege_comand(current_command  , $3.head);
                                                                                     temp_link = add_new_command_list(NULL, get_last_command($3.head)); 
				                     $3.head = add_label($3.head);
				                     updateList(temp_link, get_last_command($3.head)); 
                                                                                     current_command = NULL;
                                                                                       *num = case_val[0];
                                                                                     current_command =  translate_comand(current_command, current_varible->type, "EQL", current_varible->name, next_varible->name, num);                                                                                    
                                                                                      $3.head =merege_comand(current_command , $3.head);  
                                                                                      $$ = merege_comand($3.head , $6);  
                                                                                      $$ = translate_comand($$,'J',"UMP","","","");   
                                                                                      temp_link = add_new_command_list(NULL, get_last_command($$));                                                                                                   
				                      $$ = merege_comand($$, $9);
				                                  $$ = add_label($$);
						                updateList(temp_link, get_last_command($$));   
					}  
                                                                              
                                                           ;

caselist                                              :     caselist  CASE  NUM  ':'  stmtlist {                                                                                                                          
					                                          num = $3.value;                                                                                                                        
                                                                                                                         case_val[p] = *num;                                                                                                                     
					                                           p++ ;		                                                                                                      
                                                                                                                        next_varible= createTempVar( current_varible->type ); 
                                                                                                                      $$ = translate_comand($$, current_varible->type, "EQL", current_varible->name, next_varible->name, num);                                                                                                     
                                                                                                                      $$ = translate_comand($$, 'J', "MPZ", "", next_varible->name, "");   
                                                                                                                              temp_link  = add_new_command_list(NULL, get_last_command($$)); 
					                       	$$ = add_label($$);
						                updateList(temp_link, get_last_command($$));                                                 
                                                                                                                       $$ = merege_comand($1, $5);                                                                             
						                       $$ = translate_comand($$,'J',"UMP","","","");
						                       temp_link = add_new_command_list(NULL, get_last_command($$));
                                                                                                                      $$ = add_label($$);
						                updateList(temp_link, get_last_command($$));    
						                      
                          
                                                                                                                                           } 
                                                           |     /*empty*/  {$$ = NULL;}

                                                           ;

break_stmt                                         :     BREAK  ';' {$$ = NULL;} ; 

stmt_block                                         :     '{'  stmtlist  '}'  {$$ = $2;}
                                                           ; 

stmtlist                                               :      stmtlist  stmt    {$$ = merege_comand($1, $2);} 
                                                          |       /*empty*/          {$$ = NULL;}

        
                                                          ;

boolexpr                                            :      boolexpr  OR  boolterm
                                                                                                       {
					                         $$.head = translate_comand($1.head,'J',"UMP","","","");
					                          temp_link = add_new_command_list(NULL, get_last_command($$.head));
					                         $$.head = add_label($$.head);
					                         updateList($1.false, get_last_command($$.head));
					                         $$.head = merege_comand($$.head, $3.head);
					                         add_label($$.head);
					                         updateList(temp_link, get_last_command($$.head));
					                         $$.false = $3.false;
				                                        }
                                                          |      boolterm
                                                                               {
					 $$.head = $1.head;
					 $$.false = $1.false;
				               }
                                                          ;

boolterm                                            :      boolterm  AND  boolfactor
                                                                                                            {
					                              $$.head = merege_comand($1.head,$3.head);
					                              $$.false = mergeLists($1.false, $3.false);
				                                             }
                                                          |       boolfactor
                                                                                   {
					     $$.false = $1.false;
					     $$.head = $1.head;
				                   }
                                                          ;

boolfactor                                          :       NOT  '('  boolexpr  ')'
                                                                                                                 {
					                                    $$.head = translate_comand($3.head,'J',"UMP","","","");
					                                    $$.false = add_new_command_list(NULL,  get_last_command($$.head));
					                                    add_label($$.head);
					                                    updateList($3.false,  get_last_command($$.head));
				                                                 }

                                                          |       expression  RELOP  expression
                                                                                                                                 {
					                                                    if($1.type == 'I' && $3.type == 'R') 
						                                    $1.head = floatConvert($1.head, $1.last);
					                                                    else if($3.type == 'I' && $1.type == 'R')
						                                    $3.head = floatConvert($3.head, $3.last);
					                                                    $$.head = build_relop_command($2, $1.last, $3.last, $1.head, $3.head, typeUpdate($1.type, $3.type));
					                                                    $$.false = add_new_command_list(NULL, get_last_command($$.head));
				                                                                  }
                                                          ;

expression                                         :       expression  ADDOP  term
                                                                                                                 {				
					                                   $$.type = typeUpdate($1.type, $3.type);
					                                   $$.head = build_arithmetic_command ($2, $$.type, $$.last, $1.last, $3.last, $1.type, $3.type, $1.head, $3.head);
				                                                 }
                                                          |       term
                                                                                                                {
					                                  $$.type = $1.type;
					                                  $$.head = $1.head;
					                                  strcpy($$.last, $1.last);
				                                                }
                                                          ;

term                                                   :       term  MULOP  factor
                                                                                                      {
					                         $$.type = typeUpdate($1.type, $3.type);
					                         $$.head = build_arithmetic_command ($2, $$.type, $$.last, $1.last, $3.last, $1.type, $3.type, $1.head, $3.head);
				                                      }

                                                          |       factor
                                                                           {
				              $$.type = $1.type;
				              $$.head = $1.head;
				               strcpy($$.last, $1.last);
				           }
                                                          ;

factor                                                 :       '('  expression  ')'
                                                                                              {

					                  $$.type = $2.type;
					                  $$.head = $2.head;
					                   strcpy($$.last,$2.last);
				                              } 

                                                          |      CAST  '('  expression  ')' {
                                                                                                            number = cast($1);
                                                                                                            if(number == 1 && $3.type == 'R'){
                                                                                                                     $$.head = intConvert($3.head, $3.last);                                                                                                                     
                                                                                                                      $$.type == 'I';
                                                                                                               } else if (number == 2 && $3.type == 'I') {
                                                                                                                     $$.head = floatConvert($3.head, $3.last);                                                                                                                    
                                                                                                                       $$.type == 'R';

                                                                                                               } 
                                                                                                                  else { 
                                                                                                                           $$.type = $3.type;                                                                                                             
					                                           $$.head = $3.head; 
                                                                                                                          }
					                              strcpy($$.last,$3.last);
				                                          } 

                                                          |       ID
                                                                      {
				         $$.head = NULL;
			                         if(!(current_varible = search_varible($1))) 
			                           {
				             fprintf(stderr,"ERROR: unknown variable, not defined in the symbol table");
				             $$.type = 0;
			                            }
				         else
				            {
						strcpy($$.last, $1);
						$$.type = current_varible->type;
				             }
				       }

                                                          |       NUM
                                                                           {
					strcpy($$.last, $1.value);
					$$.type = $1.type;
					$$.head = NULL;
				           }
                                 	
%%

int yyerror(const  char *err)
{
	fprintf(stderr, "ERROR: line %d: %s\n", line,  err);
	error_number = 1;
	return 1;
}