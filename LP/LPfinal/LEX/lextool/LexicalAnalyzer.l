%{
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

%}

letter [a-zA-Z]
digit  [0-9]
%x COMMENT
%x STRING
%%
"include"|"define"|"undef"|"ifdef"|"pragma"|"ifndef"|"error"                                                                                                            printf("\n%s\tPreprocessor Directive",yytext);

"stdlib.h"|"unistd.h"|"stdio.h"|"fstream.h"|"string.h"|"math.h"                                                                                                         printf("\n%s\tStandrad Library",yytext);                             
{digit}+("E"("+"|"-")?{digit}+)?                                                                                                                                        printf("\n%s\tInteger",yytext);

{digit}+"."{digit}+("E"("+"|"-")?{digit}+)?                                                                                                                             printf("\n%s\tFloating pt",yytext);

"if"|"else"|"scanf"|"printf"|"switch"|"return"|"struct"|"do"|"while"|"for"|"case"                                                                                       printf("\n%s\tKeywords",yytext);

"int"|"float"|"double"|"char"|"long long"|"void"|"unsigned char"|"signed char"|"unsigned int"|"short"|"unsigned short"|"long"|"unsigned long"|"long double"             printf("\n%s\tDataType",yytext);

"\"" {BEGIN STRING;printf("\nin quotes\n");}
<STRING>"\"" {BEGIN 0;printf("\nout of quotes\n");}
<STRING>.|\n ECHO;

"/*"    {BEGIN COMMENT; printf("comment started\n");}
<COMMENT>"*/" {BEGIN 0; printf("comment endee\n");}
<COMMENT>.|\n ECHO;

"\a"|"\\n"|"\\b"|"\t"|"\\t"|"\b"|"\\a"                                                                                                                                  printf("\n%s\tEscape sequences",yytext);

{letter}({letter}|{digit})*                                                                                                                                             printf("\n%s\tIdentifier",yytext);

"&&"|"<"|">"|"<="|">="|"="|"+"|"-"|"?"|"*"|"/"|"%"|"&"|"||"                                                                                                             printf("\n%s\tOperator ",yytext);

"{"|"}"|"["|"]"|"("|")"|"#"|"'"|"."|"\""|"\\"|";"|","                                                                                                                   printf("\n%s\tSpecial Character",yytext);

"%d"|"%s"|"%c"|"%f"|"%e"                                                                                                                                                printf("\n%s\t i/p o/p Format Specifier",yytext);


[ \t]+ ;
%%

int yywrap()
{
return 1;
}
int main(int argc,char *argv[])
{
yyin=fopen(argv[1],"r");
yylex();
fclose(yyin);
return 0;
}

