d [0-9]
l [A-Za-z]
punc [;'",.:(){}\[\]]
op [<>=-+*&|^]
com1 [/]
com2 [*]
fir [!<>]
sec [=]

%{
	int numcnt=0,puncnt=0,keycnt=0,opcnt=0,idcnt=0;
%}

%%

({d})({d})* {
	numcnt++;
	printf("%s is a number.\n",yytext);
}
({l})({l}|({d}))* {
	idcnt++;
	printf("%s is a identifier.\n",yytext);
}

%%

int main()
{
	printf("enter the statement:");
	yylex();
	return 0;	
}
