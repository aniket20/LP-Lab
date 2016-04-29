%{
#include "node.h"
#include "y.tab.h"
%}

%%
[01] {yylval.num=(double)atoi(yytext);return NUM;}
[ \t]+ {;}
\n|. {return yytext[0];}

%%