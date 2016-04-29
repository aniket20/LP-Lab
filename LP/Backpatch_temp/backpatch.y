%{
#include<bits/stdc++.h>
#include "node.h"
using namespace std;

int yylex(void);
void yyerror(const char*);
extern vector<string> save;
extern vector<int> patch[100];
extern int nextinst;
%}


%union{
int num;
char entry[32];
struct node* patchlist;
}

%type <num> M
%token orr
%token andd
%token nott
%token IF
%token WHILE
%token ELSE
%token <entry> rel
%type <patchlist> B
%type <patchlist> S
%type <patchlist> L 
%token <entry> id
%type <entry> E A 



%left orr
%left andd
%right nott
%nonassoc ')'
%nonassoc ELSE



%%

Start: S '\n' {
 					printf("Three address code of given expression:\n");
					calc();printcode();
}
;

	

S: IF '(' B ')' M S {
					cout<<"CUMMING INTO IF\n";
					$$ = new node();
					backpatch($3->truelist,$3->cnt1,$5);
					backpatch($3->falselist,$3->cnt2,$6->nextlist[0]+1);
					$$->nextlist=mergeList($3->falselist,$6->nextlist,$3->cnt2,$6->cnt3);
	}
 | '{' L '}' {
 					cout<<"CUMMING INTO L\n";
 					$$ = new node();					
 					$$->nextlist = $2->nextlist;
 					$$->cnt3 = $2->cnt3;
 }
 | A  {
 					$$ = new node();
 					$$->nextlist[$$->cnt3++] = nextinst;
 					nextinst++;
 }
 | WHILE M '(' B ')' M S M{
 					cout<<"CUMMING INTO WHILE\n";
 					backpatch($7->nextlist, $7->cnt3 , $2);
 					backpatch($4->truelist , $4->cnt1 , $6);
 					backpatch($4->falselist , $4->cnt2 , $8+1);
 					$$ = new node();

 					$$->nextlist = $4->falselist;
 					$$->cnt3 = $4->cnt2;
 					string buf="";
 					buf+="goto_";
 					char temp[32];
 					sprintf(temp , "%d" , $2);
 					buf+=temp;
 					save.push_back(buf);
 					cout<<"GOING OUT oF WHILE\n";

 }

 | IF '(' B ')' M S ELSE M S M {

 					backpatch($3->truelist, $3->cnt1 , $5);
 					backpatch($3->falselist , $3->cnt2 , $8);
 					node * temp;
 					$$ = new node();
 					$$->nextlist = mergeList($6->nextlist, $9->nextlist , $6->cnt3, $9->cnt3);
 					$$->cnt3 = $6->cnt3 + $9->cnt3;


 }
;
L:L M S {
					$$=new node();
					backpatch($1->nextlist,$1->cnt3,$2);
					$$->nextlist = $3->nextlist;

 }
 |S {
 					$$=new node();
					$$->nextlist = $1->nextlist;
 }
;

A:E '=' {
					cout<<"STATEMENT IS PRINTING\n";
					string buf="";
					buf += $1;
					buf += "=";
					save.push_back(buf);

	}
;

B:B orr  M B { 
		cout<<"BAHAAR\n";
		$$=new node();
		//cout<<"or"<<endl;
		//cout<<$3<<endl;
		backpatch($1->falselist,$1->cnt2,$3);
	    $$->truelist=mergeList($1->truelist,$4->truelist,$1->cnt1,$4->cnt1);
	    $$->cnt1=$1->cnt1+$4->cnt1;
	    $$->falselist=$4->falselist;
	    $$->cnt2=$4->cnt2;
	}
 |B andd M B{ 
 		cout<<"ANDAR\n";
 		$$=new node();
 		//cout<<"and"<<endl;
		//cout<<$3<<endl;
 		backpatch($1->truelist,$1->cnt1,$3);
	 	$$->truelist=$4->truelist;
	 	$$->cnt1=$4->cnt1;
	 	$$->falselist=mergeList($1->falselist,$4->falselist,$1->cnt2,$4->cnt2);
	 	$$->cnt2=$1->cnt2+$4->cnt2;
 }
 |nott B { 
 		$$=new node();
 		$$->truelist=$2->falselist;
 		$$->cnt1=$2->cnt2;
	 	$$->falselist=$2->truelist;
	 	$$->cnt2=$2->cnt1;
 }
 |'('B')' {
 		$$=new node();
 		$$->truelist=$2->truelist;
 		$$->cnt1=$2->cnt1;
 		$$->cnt2=$2->cnt2;
		$$->falselist=$2->falselist;
 }
 |E rel E { 

 		$$=new node();
 		$$->truelist[$$->cnt1++]=nextinst++;
 		//cout<<$1<<$2<<$3<<endl;
 		//cout<<nextinst<<endl;
      	$$->falselist[$$->cnt2++]=nextinst++;
      	//cout<<nextinst<<endl;
		string buf="";
		string e1,e2,e3;
		e1=$1;
		e2=$2;
		e3=$3;
		buf+="if"+e1+e2+e3+"goto_";
		save.push_back(buf);
		save.push_back("goto_");
 }
 ;
E:id
 ;
M:/*empty*/ {
		//cout<<nextinst<<endl;
		$$=nextinst;}
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
