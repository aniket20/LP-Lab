%{
#include<stdio.h>
#include<math.h>
#include <stdlib.h>
static char* check(char* s1,char* s2,char* s3);
%}

%union{
int num;
bool val;
char typ[32];
}
%token <num> integer
%token <val> boolean
%type <typ> E
%%
S:S
 |SE
 |/*empty*/
 ;
E:E'+'E   {$$=check($1,,$2,$3);}
 |E'=''='E  {$$=check($1,$2,$4);}
 |'('E')' {$$=$2;}
 |integer {$$="int";}
 |boolean {$$="bool";}
 ;
%%

int main()
{
	yyparse();
}
yyerror()
{
	printf("error\n");
}
staitc char* check(char* left,char* op,char* right)
{
	int fl=0,i,j;
	for(i=0;i<strlen(left);i++)
	{
		for(j=0;j<strlen(right);j++)
		{
			if(left[i]!=right[j])
			{
				fl=1;
				break;
			}
		}
		if(fl==1)
		break;
	}
	if(strlen(op)==1)
	{
		if(fl==0 && left[0]=='i')
		{
			return left;
		}
		else
			printf("error");
	}
	else
	{
		if(fl==0)
		{
			return left;
		}
		else
			printf("error");
	}
	return NULL;
}
