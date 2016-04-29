#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

struct production{
        char parent;
        vector <string> children;
};

map <char, set <char> > FIRST;
map <char, set <char> > FOLLOW;
map <char, int>mark;
map <char, int>mrk;

vector <production> V;
char start_sym;

void input(){
        int n;
        cin>>n;
        for(int i=0; i<n; i++){
                production P;
                cin>>P.parent;
                if(i==0)start_sym=P.parent;
                int x;
                cin>>x;
                string s;
                for(int j=0; j<x; j++){
                        cin>>s;
                        P.children.pb(s);
                }
                V.pb(P);
        }
}

int getIndx(char c){
        for(int i=0; i<V.size(); i++){
                if(V[i].parent==c)return i;
        }
        return -1;
}

set <char>::iterator it;
void merge(set <char>& s1, set<char>& s2){
        for(it=s2.begin(); it!=s2.end(); it++)s1.insert(*it);
}

set<char> calfirst(char c){
        if(mark[c])return FIRST[c];
        if(!(c>='A' && c<='Z')){
                set <char> ret;
                ret.insert(c);
                return ret;
        }
        mark[c]=1;
        int ind=getIndx(c);
        set <char> ret;
        for(int i=0; i<V[ind].children.size(); i++){
                for(int j=0; j<V[ind].children[i].size(); j++){
                        set <char> C=calfirst(V[ind].children[i][j]);
                        merge(ret, C);
                        merge(FIRST[V[ind].children[i][j]], C);
                        if(C.find('~')==C.end())break;

                }
        }
        return ret;
}

set<char> calfollow(char c){
        if(mrk[c])return FOLLOW[c];
        mrk[c]=1;
        set <char> ret;
        if(c==start_sym){
                ret.insert('$');
        }
        for(int i=0; i<V.size(); i++){
                vector <string> v=V[i].children;
                for(int j=0; j<v.size(); j++){
                        string s=v[j];
                        for(int k=0; k<s.size(); k++){
                                if(s[k]!=c)continue;
                                for(int _k=k+1; ; _k++){
                                        if(_k==s.size()){
                                                set <char> C=calfollow(V[i].parent);
                                                merge(FOLLOW[V[i].parent], C);
                                                merge(FOLLOW[s[_k-1]], C);
                                                merge(ret, C);
                                                break;
                                        }
                                        if(!(s[_k]>='A' && s[_k]<='Z')){
                                                ret.insert(s[_k]);
                                                break;
                                        }
                                        else{
                                                set <char> C=calfirst(s[_k]);
                                                int fl=0;
                                                set <char>::iterator IT;
                                                if((IT=C.find('~'))!=C.end()){
                                                        fl=1;
                                                        C.erase(IT);
                                                }
                                                merge(ret, C);
                                                if(!fl)break;
                                        }
                                }
                        }
                }
        }
        return ret;
}


map <char, set <char> >::iterator mit;
map <pair <char, char>, production>PT;
map <pair <char, char>, production>::iterator pit;

int flag;
void construct_parse_table(){
        for(int i=0; i<V.size(); i++){
                vector <string>v=V[i].children;
                for(int j=0; j<v.size(); j++){
                        set <char> alpha;
                        string s=v[j];
                        if(s=="~")alpha=FOLLOW[V[i].parent];
                        else{
                                for(int k=0; k<s.size(); k++){
                                        if(s[k]>='A' && s[k]<='Z'){
                                                set<char> C=FIRST[s[k]];
                                                int fl=0;
                                                if(C.find('~')!=C.end())fl=1;
                                                merge(alpha, C);
                                                if(!fl)break;
                                        }
                                        else{
                                                alpha.insert(s[k]);
                                                break;
                                        }
                                }
                        }
                        for(it=alpha.begin(); it!=alpha.end(); it++){
                                char x=*it;
                                production P;
                                P.parent=V[i].parent;
                                P.children.pb(v[j]);
                                if(PT.find(mp(V[i].parent, x))!=PT.end())flag=-1;
                                PT[mp(V[i].parent, x)]=P;
                        }
                }
        }
}

vector <production> ans;
int A;

void parse(string s){

        s+="$";
        stack <char> S;
        S.push('$');
        S.push(start_sym);
        int p=0;

        while(true){
                if(S.empty()|| p>=s.size())break;
                char X=S.top();
                if(X=='~'){
                        S.pop();
                        continue;
                }
                if(X>='A' && X<='Z'){
                        if(PT.find(mp(X,s[p]))==PT.end())break;
                        production P=PT[mp(X,s[p])];
                        string _s=P.children[0];
                        ans.pb(P);
                        S.pop();
                        for(int i=_s.size()-1; i>=0; i--)S.push(_s[i]);
                }
                else{
                        if(X==s[p] && X=='$'){
                                A=1;
                                S.pop();
                                p++;
                                break;
                        }
                        else if(X==s[p]){
                                S.pop();
                                p++;
                        }
                        else break;
                }
        }
}

int main(){
        input();
        for(int i=0; i<V.size(); i++){
                if(!mark[V[i].parent]){
                        FIRST[V[i].parent]=calfirst(V[i].parent);
                }
        }

        for(mit=FIRST.begin(); mit!=FIRST.end(); mit++){
                if(!(mit->first>='A' && mit->first<='Z'))continue;
                cout<<mit->first<<endl;
                set <char> F=mit->second;
                for(it=F.begin(); it!=F.end(); it++)cout<<*it<<" ";
                cout<<endl;
        }

        for(int i=0; i<V.size(); i++){
                for(int j=0; j<V[i].children.size(); j++){
                        string s=V[i].children[j];
                        for(int k=0; k<s.size(); k++){
                                if((s[k]>='A' && s[k]<='Z') && !mrk[s[k]]){
                                        FOLLOW[s[k]]=calfollow(s[k]);
                                }
                        }
                }
        }



        for(mit=FOLLOW.begin(); mit!=FOLLOW.end(); mit++){
                cout<<mit->first<<endl;
                set <char> F=mit->second;
                for(it=F.begin(); it!=F.end(); it++)cout<<*it<<" ";
                cout<<endl;
        }

        flag=0;
        construct_parse_table();
        if(flag==-1){
                cout<<"Not LL(1) grammar"<<endl;
        }
        for(pit=PT.begin(); pit!=PT.end(); pit++){
                pair<char, char>p=pit->first;
                production q=pit->second;
                cout<<p.first<<" "<<p.second<<" "<<q.parent<<"-->"<<q.children[0]<<endl;
        }

        string prse;
        cin>>prse;
        A=0;
        parse(prse);
        if(A==-1)cout<<"Not Accepted"<<endl;
        else{
                printf("Accepted\n");
                for(int i=0; i<ans.size(); i++)cout<<ans[i].parent<<" "<<ans[i].children[0]<<endl;
        }
        return 0;
}