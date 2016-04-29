%{
#include <bits/stdc++.h>
#include "node.h"
using namespace std;
int temp;
double temp1;
int yylex(void);
void yyerror(const char*);

%}

%union{
	node val;
	double num;
}

%type <val> L
%type <val> S
%type <num> B
%token <num> NUM
%%

S: L '.' L '\n'{
	$$.value = $1.value + $3.value/(1<<$3.len);
	printf("%lf\n", $$.value);
}
| L {
	$$.value = $1.value;
}
;
L: L B {
	$$.len = $1.len +1;
	$$.value = $1.value*2 + $2;
}
| B {
	$$.value=$1;
	$$.len=1;
}
;
B: NUM {
	$$ = $1;
}
;
%%

int main()
{
	yyparse();
}

void yyerror(const char* str)
{
	printf("%s\n",str);
}

