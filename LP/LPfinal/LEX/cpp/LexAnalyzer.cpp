//roll no 137115
//aniket chavan
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define f first
#define s second

map<string,set<string> >dictionary;
map<string,set<string> >:: iterator it;
set<string> dict;
set<string>::iterator it1;

void function(){
        string key,val;
        dict.insert("stdio.h");
        dict.insert("unistd.h");
        dict.insert("stdlib.h");
        key="Standard library ";
        dictionary[key]=dict;
        dict.clear();
        dict.insert("include");
        dict.insert("define");
        key="Directives ";
        dictionary[key]=dict;
        dict.clear();
        dict.insert("int");
        dict.insert("float");
        dict.insert("double");
        dict.insert("bool");
        dict.insert("string");
        dict.insert("char");
        dict.insert("long");
        dict.insert("short");
        key="DataType";
        dictionary[key]=dict;
        dict.clear();
        dict.insert("do");
        dict.insert("while");
        dict.insert("for");
        dict.insert("main");
        dict.insert("cin");
        dict.insert("cout");
        dict.insert("endl");
        dict.insert("return");
        key="Keywords";
        dictionary[key]=dict;
        dict.clear();
        dict.insert("+");
        dict.insert("-");
        dict.insert("*");
        dict.insert("/");
        dict.insert("=");
        dict.insert("<");
        dict.insert(">");
        dict.insert("!");
        dict.insert("&");
        dict.insert("<<");
        dict.insert(">>");
        dict.insert("%");
        dict.insert("^");
        dict.insert("++");
        dict.insert("--");
        dict.insert("==");
        dict.insert("<=");
        dict.insert(">=");
        dict.insert("!=");
        dict.insert("|");
        dict.insert("&&");
        dict.insert("||");
        dict.insert("#");
         key="Operators";
        dictionary[key]=dict;
        dict.clear();
        dict.insert("(");
        dict.insert(")");
        dict.insert("{");
        dict.insert("}");
        dict.insert("[");
        dict.insert("]");
        key="SpecialSymbols";
        dictionary[key]=dict;
        dict.clear();

}

int parse(string token){
        for(it=dictionary.begin();it!=dictionary.end();it++){
                for(it1=it->s.begin();it1!=it->s.end();it1++){
                        if(*it1==token){
                                cout<<it->f<<" \t\t"<<token<<endl;
                                return 1;
                        }
                }
        }
}

int ifid(string token){
                int flag=1;
                if((token[0]>='a' && token[0]<='z' )||(token[0]>='A' && token[0]<='Z') || token[0]=='_'){
                int len=token.length();
                for(int i=1;i<len;i++){
                        if((token[i]>='a' && token[i]<='z' )||(token[i]>='A' && token[i]<='Z') || (token[i]>='0' && token[i]<='9') || token[i]=='_'){

                        }
                        else
                                return 0;
                }
                cout<<"Identifier \t\t"<<token<<endl;
                return 1;
        }
        else if((token[0]>='0' && token[0]<='9') || token[0]=='.'){
                        int len=token.length();
                        for(int i=1;i<len;i++){
                                if((token[i]>='0' && token[i]<='9' )|| token[i]=='.'){
                                }
                                else
                                        return 0;
                        }
                        cout<<"Number \t\t\t"<<token<<endl;
                        return 1;
        }
}

int main(){
        function();
        string s;
        string token="";
        getline(cin,s);
        while(s!=""){

                int len=s.length();
                for(int i=0;i<len;i++){
                        char ch=s[i];
                        int result=0;
                        if(ch==' ' || ch==',' || ch==';' || ch=='\n' || ch=='\t'){
                                if(parse(token)!=1){
                                        int val=ifid(token);
                                        if(val==1){
                                                token="";
										 }
                                        else if(val==0 && token!=""){
                                                cout<<"error! unidentified token \n"<<token<<endl;;
                                        }
                                }
                                else
                                        token="";
                        }
                        else{
                                token+=s[i];
                        }
                }
        getline(cin,s);
        }
        return 0;
}
