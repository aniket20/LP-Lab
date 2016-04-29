//refer end of file for input
//roll no 137115
#include<bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define pb push_back
map<string,set<string> >product;
map<string,set<string> >:: iterator it;
set<string>::iterator it1;
vector<string> v,v1;
vector<vector<string> >store[100];
string make(string s1,string s2){
	if(s1==s2){
		return s1;
	}
	string temp=s1+s2;
	return temp;
}
int main(){
	int length,p1,p2,post;
	string succ,prec,str;
	char ch;
	cout<<"Enter the number of productions\n";
	int n;
	cin>>n;
	cout<<"Enter the productions(Productions must be in cnf and use S as a start symbol)\n";
	for(int i=0;i<n;i++){
		cin>>prec;//Left side of  the production
		cin>>succ;//right side of the production int cnf i.e. non terminals in group of 2 no restrictions on terminal see input file cyk.txt
		product[prec].insert(succ);
	}
	
	
	while(1){
		cout<<"Enter the string to be verified\n";
		char tre=getchar();
		getline(cin,str);
		string temp="";
		for(int i=0;i<str.size();i++){
			while(i<str.size() && str[i]!=' '){
				temp+=str[i];
				i++;
			}
			v.pb(temp);
			temp="";
		}
		length=v.size();
		for(int i=0;i<length;i++){
			for(it=product.begin();it!=product.end();it++){
				it1=(it->S).find(v[i]);
				if(it1!=it->S.end()){
					v1.pb(it->F);
				}
			}
			store[0].pb(v1);
			v1.clear();
		}
		
		for(int i=1;i<length;i++){
			for(int j=0;j<length;j++){
				post=i+j;
				if(post>=length){
					break;
				}
				p1=j;
				p2=post;
				for(int k=j;k<post;k++){
					for(int l=0;l<store[k-j][j].size();l++){
						for(int m=0;m<store[post-(k+1)][k+1].size();m++){
							string pre=make(store[k-j][j][l],store[post-(k+1)][k+1][m]);
							for(it=product.begin();it!=product.end();it++){
								it1=(it->S).find(pre);
								if(it1!=(it->S).end()){
									v1.pb(it->F);
								//	v.pb(it->S);
								}
								
							}
						}
					}
				}
				store[i].pb(v1);
				v1.clear();
			}
		}
		
		for(int i=0;i<length;i++){
			for(int j=0;j<store[i].size();j++){
				for(int k=0;k<store[i][j].size();k++){
					cout<<store[i][j][k]<<" ";
					if(k!=store[i][j].size()-1){
						cout<<",";
					}
				}
				if(store[i][j].size()==0){
					cout<<"#";
				}			
				cout<<"|";
			}
			cout<<endl;
			store[i].clear();
		}
	}
	return 0;
}
/*
S AB
B BC
B DA
B eats
C EA
A FG
A she
D eats
E with
G fish
G fork
F a
*/

