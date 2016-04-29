%{
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct
{
	int truelist[100];
	int falselist[100];
}list;
void backpatch(int a[100],int num);
int* merge(int a[100],int b[100]);
char* save[30];
int nextinst=100;
int cnt=0;
%}


%union{
char entry[32];
list llist;
}

%type <num> M
%type <llist> B
%token <entry> id
%type <entry> E
%%

S:B '\n'
 ;
B:B '|''|' M B { backpatch($1.falselist,$4);
	      $$.truelist=merge($1.truelist,$5.truelist);
	      $$.falselist=$5.falselist;}
 |B '&''&' M B{ backpatch($1.truelist,$4);
	 $$.truelist=$5.truelist;
	 $$.falselist=merge($1.falselist,$5.falselist);
 }
 |'!' B { $$.truelist=$2.falselist;
	 $$.falselist=$2.truelist;
 }
 |'('B')' { $$.truelist=$2.truelist;
	 $$.falselist=$2.falselist;
 }
 |E '<' E { $$.truelist[0]=nextinst++;
      $$.falselist[0]=nextinst++;
	char buf[100];
	sprintf(buf,"%s%s%s%s%s","if",$1,"<",$3,"goto_");
	save[cnt++]=buf;
	save[cnt++]="goto_";
 }
 ;
E:id
 ;
M:/*empty*/ {$$=nexinst;}
 ;

%%

void backpatch(int a[100],int num)
{
}
void merge(int a[100],int b[100])
{
}
