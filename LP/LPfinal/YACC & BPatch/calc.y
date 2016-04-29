%{	
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include <math.h>

double powr(double x,double y);
static double lookup(char* str);
static void store(char *str,double n);
%}

%union{
double val;
char name[32];
}

%token <val> id;
%token <name> entry;
%type <val> E
%left '+''-'
%left '*''/'
%right '^'
%right UMINUS

%%
S:A
 |S A
 ;
A:entry '=' E '\n' {store($1,$3);printf("The value of %s is:%lf\n",$1,$3);}
 |E '\n' {printf("The ans is:%lf\n",$1);}
 |error '\n' { printf("Discarding malforward error.\n");}
 ;
E:E '+' E{$$=$1+$3;}
 |E '-' E{$$=$1-$3;}
 |E '*' E{$$=$1*$3;}
 |E '/' E{$$=$1/$3;}
 |E '^' E{$$=powr($1,$3);}
 |'('E')'{$$=$2;}
 |'-' E %prec UMINUS {$$=-$2;}
 |id
 |entry{$$=lookup($1);}
 ;
%%
int main()
{
	yyparse();
}
yyerror(char* str)
{
	printf("error\n");
	printf("%s\n",str);
}
typedef struct
{
	double ans;
	char s[32];
}arr;
static arr ar[50];
static int cnt=0;
static void store(char* str,double n)
{
	printf("%s %lf\n",str,n);
	int i;
	for(i=0; i<strlen(str); i++)ar[cnt].s[i]=str[i];
	ar[cnt].s[i]='\0';
	ar[cnt].ans=n;
	printf("%s %lf\n",ar[cnt].s,ar[cnt].ans);
	cnt++;
	printf("%d\n",cnt);
	//printf("%s %s\n", ar[0].s, ar[1].s);
}
static double lookup(char* str)
{
	int i,fl,j;
	printf("lookup %s\n",str);
	printf("%d\n",cnt);
	for(i=0; i<cnt; i++){
		printf("%s\n", ar[i].s);
	}
	for(i=0;i<cnt;i++)
	{
		printf("entry\n");
		char* st=ar[i].s;
		printf("%s %lf\n",st,ar[i].ans);
		fl=0;
		for(j=0;j<strlen(st);j++)
		{
			if(st[j]!=str[j])
			{
				fl=1;
				break;
			}
		}
		if(fl==0)
		{
			printf("ans\n");
			printf("%s %lf\n",ar[i].s,ar[i].ans);
			return ar[i].ans;
		}
	}
	return 0;
}
double powr(double x,double y)
{
	double ans=1.0;
	int y1=(int)y;
	printf("%lf %d\n",x,y1);
	while(y1>0)
	{
		if(y1&1)
		{
			ans=ans*x;
		}
		ans=ans*ans;
		y1=y1/2;
	}
	printf("%lf\n",ans);
	return ans;
}
