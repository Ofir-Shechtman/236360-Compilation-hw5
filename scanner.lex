%{
#include "semantics.hpp"
#include "hw3_output.hpp"
#include "parser.tab.hpp"
%}
%option yylineno
%option noyywrap
SPACE [ ]
TAB \t
CR \r
DQ \"
LF (\n)
WS ({SPACE}|{TAB}|{CR}|{LF})
LETTER [a-zA-Z]
DIGIT [0-9]
ID {LETTER}({LETTER}|{DIGIT})*
relop (==|!=|<=|>=|<|>)
%%
void {return VOID;}
int {return INT;}
byte {return BYTE;}
bool {return BOOL;}
and {return AND;}
or {return OR;}
not {return NOT;}
true {return TRUE;}
false {return FALSE;}
return {return RETURN;}
if {return IF;}
else {return ELSE;}
while {return WHILE;}
break {return BREAK;}
continue {return CONTINUE;}
switch {return SWITCH;}
case {return CASE;}
default {return DEFAULT;}
>=|<=|<|> {return RELOP;}
!=|== {return EQUALITY;}
: {return COLON;}
; {return SC;}
, {return COMMA;}
\( {return LPAREN;}
\) {return RPAREN;}
\{ {return LBRACE;}
\} {return RBRACE;}
= {return ASSIGN;}
b {return B;}
[\*\/] {return MULT_DIV_OP;}
[\+\-] {return ADD_SUB_OP;}
0|[1-9]{DIGIT}* {yylval=new Num(yytext); return NUM;}
{ID} {yylval=new Id(yytext); return ID;}
(\/\/)[^\n\r\r\n]* {;}
({DQ})([^\"\\\n\r\0]|(\\.))*({DQ}) {yylval=new String(yytext); return STRING;}
{WS} {;}
. {output::errorLex(yylineno);}
%%