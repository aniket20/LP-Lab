%%

\/\*([^*]*|\".*\")*\*\/	{
	printf("%s is the valid input \n",yytext);
}
%%

int main()
{
	yylex();
	return 0;
}
