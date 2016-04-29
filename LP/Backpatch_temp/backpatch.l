ent [a-zA-Z]
%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <math.h>
#include<bits/stdc++.h>
#include "node.h"
#include "y.tab.h"
%}

%%
"else" {strncpy(yylval.entry, yytext, 32); return ELSE;}
"if" {strncpy(yylval.entry, yytext, 32); return IF;}
"while" {strncpy(yylval.entry, yytext, 32); return WHILE;}
"||" {strncpy(yylval.entry,yytext,32); return orr;}
"&&" {strncpy(yylval.entry,yytext,32); return andd;}
"!" {strncpy(yylval.entry,yytext,32); return nott;}
"<"|">"|"<="|">"|"==" {strncpy(yylval.entry,yytext,32); return rel;}
({ent})+ {strncpy(yylval.entry,yytext,32);return id;}
[ \t]+ {;}
\n|. {return yytext[0];}

%%
