%option noyywrap
%{
#include <stdio.h>
#include "symboltab.h"
#include "translator.h"
#include "parser.tab.h"
#include "error.h"
int line = 1;
extern  void report_error(const char *format, ...);
extern const char* error_messeges[];
%}
%option noinput
%option nounput
%x COMMENT

%%

"{"       { return '{'; }
"}"       { return '}'; }
"("       { return '('; }
")"       { return ')'; }
","       { return ','; }
":"       { return ':'; }
"="       { return '='; }
";"       { return ';'; }

"float"   { yylval.type = 'R'; return FLOAT; }
"int"     { yylval.type = 'I'; return INT; }
"break"   { return BREAK; }
"if"      { return IF; }
"case"    { return CASE; }
"else"    { return ELSE; }
"default" { return DEFAULT; }
"output"  { return OUTPUT; }
"input"   { return INPUT; }
"switch"  { return SWITCH; }
"while"   { return WHILE; }

"=="      { yylval.relop = equal; return RELOP; }
"!="      { yylval.relop = notEqual; return RELOP; }
"<"       { yylval.relop = smaller; return RELOP; }
">"       { yylval.relop = bigger; return RELOP; }
">="      { yylval.relop = biggerOrEqual; return RELOP; }
"<="      { yylval.relop = smallerOrEqual; return RELOP; }

"+"       { yylval.op = '+'; return ADDOP; }
"-"       { yylval.op = '-'; return ADDOP; }
"*"       { yylval.op = '*'; return MULOP; }
"/"       { yylval.op = '/'; return MULOP; }

"cast<int>"   { yylval.cast_op = castToInt; return CAST; }
"cast<float>" { yylval.cast_op = castToFloat; return CAST; }

"!"       { return NOT; }
"||"      { return OR; }
"&&"      { return AND; }

[0-9]+"."[0-9]*    { 
                     strncpy(yylval.num.value, yytext, VARLEN);
                     yylval.num.type = 'R';/*assigned as float (real number ) */
                     return NUM;
                   }
[0-9]+             { 
                     strncpy(yylval.num.value, yytext, VARLEN);
                     yylval.num.type = 'I'; /*assignet as int*/
                     return NUM;
                   }

[a-zA-Z][0-9a-zA-Z]* { 
                       if (yyleng < VARLEN) {
                         strcpy(yylval.id, yytext);
                       } else {
                         report_error(error_messeges[20], VARLEN - 1, yytext, VARLEN - 1);
                       }
                       return ID;
                     }

"/*"              { BEGIN(COMMENT); }
<COMMENT>[^*\n]*  
<COMMENT>"*"+[^*/\n]* 
<COMMENT>\n       { ++line; }
<COMMENT>"*"+"/"  { BEGIN(0); }

[ \t]             ;
"\n"              { ++line; }

.                 { report_error(error_messeges[21], yytext); }

%%