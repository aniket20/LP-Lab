#include<bits/stdc++.h>
using namespace std;
stack <pair <char,int> > st;
pair <char,int>mp;
map<char,int> ops;
vector< vector <string> > grammar;
vector< string> pro;
vector<string> news;

string findPro(int ipt){
        ipt++;
        pro.clear();
        int sz=grammar.size();
        int pt;
//      cout<<"input pt"<<ipt<<endl;
        for( pt=ipt;pt>=0;pt--){
                if(news[pt][0]=='_'){
                        pt--;
//                      cout<<"Breaking with pt= "<<pt<<endl;
                        break;
                }
        }
//      cout<<"pt "<<pt<<endl;
        int flag=0,ptt;
        string production="";
        for(int i=pt;i<news.size()-1;i++){
                if(news[i][0]=='_') break;
                else{
                        if(news[i][0]!='~'){
                                production+=news[i];
//                              cout<<"added "<<news[i]<<endl;
                                flag++;
                                if(flag!=1){
                                        news[i]="~";
                                }
                                else if(flag==1){
                                        ptt=i;
                                }
                        }
                }
        
        }
        //cout<<production<<" <- "<<ptt<<endl;
        news[ptt]=production;
        int fl=0;
        for(int i=0;i<sz;i++){
                pro.clear();
                pro=grammar[i];
                int sz1=pro.size();
                for(int j=1;j<sz1;j++){
                        if(pro[j]==production){
                                news[ptt]=pro[0];
        //                      cout<<"Found "<<production<<" is derived from "<<pro[0]<<"->"<<pro[j]<<endl;
                                fl=1;
                                break;
                        }
                }
                if(fl) break;
        }
if(production=="") cout<<"E";
        for(int i=0;i<news.size()-1;i++){
                cout<<news[i]<<" ";
        }
        cout<<endl;
}

int main(){
       
        int p;
        char ch;
        cin>>ch;
        p=ch-'0';
        
        for(int i=0;i<p;i++){
                pro.clear();
                string g="";
                cin>>g;
                while(g[0]!='~'){
                        pro.push_back(g);
                        cin>>g;

                }
                grammar.push_back(pro);
        }
        int it=grammar.size();
        for(int i=0;i<it;i++){
                pro.clear();
                pro=grammar[i];
                int it1=pro.size();
                cout<<pro[0]<<"->";
                for(int j=1;j<it1;j++){
                        cout<<pro[j]<<"|";
                }
                cout<<endl;
        }
        int n=6;
        string op[6]={"i","*","/","+","-","$"};
        
        ops['i']=0;
        ops['*']=1;
        ops['/']=2;
        ops['+']=3;
        ops['-']=4;
        ops['$']=5;


        int prec[6][6];
        string s;
        
        int matched;
        cout<<"Enter the input string \n";
        cin>>s;
        cout<<s<<endl;
        //return 0;
        
        int  len=s.length();
        string sss="_";
        cout<<len<<endl;

        for(int i=0;i<len;i++){
        //cout<<"in loop";
        news.push_back(sss);
        }

        cout<<s<<endl;
        int ipt,pt=0;
        int max=s.length();

        for(int i=0;i<n;i++){
                char val;
                for(int j=0;j<n;j++){
                        cin>>val;
                        prec[i][j]=val-'0';
                }
        }
        cout<<"  ";
        for(int i=0;i<n;i++){
                cout<<op[i]<<" ";
        }
        cout<<endl;
        for(int i=0;i<n;i++){
                cout<<op[i]<<" ";
                for(int j=0;j<n;j++){

                        int x=prec[i][j];
                        if(x==0) cout<<"E ";
                        else if(x==1) cout<<"L ";
                        else if(x==2) cout<<"G ";
                        else if(x==3) cout<<"W ";
                        else cout<<"A ";
                }
                cout<<endl;
        }

cout<<"parse tree is printed as a string where '_' means blank and otherwise the productions used till now\n";

                mp=make_pair('$',1000);
                pt=0,ipt=-1;
                st.push(mp);
        while(!(st.top().first=='$' && s[pt]=='$')){
                        //cout<<st.top().first<<" "<<char(s[pt])<<endl;
                        int preval=prec[ops[st.top().first]][ops[char(s[pt])]];
                //      cout<<"value"<<preval<<"\n ";
                        if(preval==1 || preval==0){
                //      cout<<"Pushed ";
                                mp=make_pair(char(s[pt]),pt);

                                pt++;
                                st.push(mp);
                        //      cout<<mp.first<<endl;                           
                        }
                        else if(preval==2){
                                mp=st.top();
                                st.pop();
                                //string temp1=string(mp.first);

                                news[mp.second]="";
                                news[mp.second]+=mp.first;
                //              cout<<"mp.second "<<mp.second<<" "<<news[mp.second]<<" "<<endl;
                                string ret=findPro(mp.second);
                //              cout<<"production found is "<<ret<<endl;
                        }
                        else if(preval==3){
                                cout<<"Error while parsing breaking bad...!\n";
                                break;
                        }
                        else if(preval==4){
                                cout<<"Congrats string is Accepted...!\n";
                        }
        }
        return 0;


}