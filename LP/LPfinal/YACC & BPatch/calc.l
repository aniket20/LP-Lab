d [0-9]
entry [a-zA-Z]
%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <math.h>
#include "calc.tab.h"
%}

%%
({d})+|({d})*\.({d})+ {sscanf(yytext,"%lf",&yylval.val); return id;}
({entry})+ {strncpy(yylval.name,yytext,32);return entry;}
[ \t]+ {;}
\n|. {return yytext[0];}
%%
