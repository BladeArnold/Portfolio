/********************************************************************* 
  Name: Blade Arnold            NetID: baa215 
  Course: CSE 4714              Assignment: Part 1 
  Programming Environment:  Visual studio code
  Purpose of File: Contains the rules for the lexer for project 1.
*********************************************************************/ 

%option yylineno
%option noyywrap
%{
#include "lexer.h"
int line_number = 1;
int length;
%}

/* Rules for the more complex  */
/* Grabs all the the stuff in between the '' */
String ['][^'\n]*[']
/* Finds all the identifier in the program */
Identify [A-Z][A-Z0-9]*
/* Removes all the comments  */
Comm [{][^\n{}]*[}]

%%
 /* Gets all the integers */
[0-9]+ {return TOK_INTLIT;}
 /* Gets all the floats and looks for the . too make sure it is a float */
[0-9]+[.][0-9]+ {return TOK_FLOATLIT;}


 /* All the rules for the keywords found in the part 1 description */
BEGIN {return TOK_BEGIN;}
BREAK {return TOK_BREAK;}
CONTINUE {return TOK_CONTINUE;}
DOWNTO {return TOK_DOWNTO;}
ELSE {return TOK_ELSE;}
END {return TOK_END;}
FOR {return TOK_FOR;}
IF {return TOK_IF;}
LET {return TOK_LET;}
PROGRAM {return TOK_PROGRAM;}
READ {return TOK_READ;}
THEN {return TOK_THEN;}
TO {return TOK_TO;}
VAR {return TOK_VAR;}
WHILE {return TOK_WHILE;}
WRITE {return TOK_WRITE;}

INTEGER {return TOK_INTEGER;}
REAL {return TOK_REAL;}

 /* All symbols found in the part 1 description */
; {return TOK_SEMICOLON;}
: {return TOK_COLON;}
"(" {return TOK_OPENPAREN;}
")" {return TOK_CLOSEPAREN;}

"+" {return TOK_PLUS;}
- {return TOK_MINUS;}
"*" {return TOK_MULTIPLY;}
"/" {return TOK_DIVIDE;}
:= {return TOK_ASSIGN;}
= {return TOK_EQUALTO;}
"<" {return TOK_LESSTHAN;}
">" {return TOK_GREATERTHAN;}
"<>" {return TOK_NOTEQUALTO;}
 
 /* More keywords from part 1*/
MOD {return TOK_MOD;}
NOT {return TOK_NOT;}
OR {return TOK_OR;}
AND {return TOK_AND;}



 /* Rules for the last few  that also compares the length of the yytext*/
{Identify} { if (strlen(yytext) <= 8) 
              {
                return TOK_IDENT; 
              }
            else
              {
                return TOK_UNKNOWN;
              }
           }


{String} {if (strlen(yytext) <= 80) 
              {
                return TOK_STRINGLIT; 
              }
            else
              {
                return TOK_UNKNOWN;
              }
          }
 /* eats the comments */
{Comm} 


 /* Counts the line number */
\n     { ++line_number;}


 /* Eat any whitespace, will need to be modified to count lines */

[ \t\r]+             /* nop */

 /* Found an unknown character */

.         { return TOK_UNKNOWN; }

 /* Recognize end of file */





<<EOF>>   { return TOK_EOF; }

