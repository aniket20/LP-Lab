#include <bits/stdc++.h>
#include "SLR.h"
using namespace std;
////////////Input://///////
/*
5
E 1 TA
A 2 +TA Z
T 1 FB
B 2 *FB Z
F 2 (E) i
2
i+*i
i+i*i
*/
class FollowCalculator{
    vector<production> g;
    string epsilon;
    string start;
    int gsize;
    map<string,vector<string> > first;
    map<string,vector<string> > follow;
    map<string,int > ind;
public:
    
    FollowCalculator(vector<production> pg)
            :epsilon("Z"),g(pg)
    {}
    map<string,vector<string> > getFirst(){
        return first;
    }
    map<string,vector<string> > getFollow(){
        return follow;
    }

    bool isFirstNT(string str){
        return (str[0] <= 'Y' && str[0] >= 'A'); //Z is reserved
    }
    bool isTerminal(string str){
        return (str.size() == 1 && !isFirstNT(str));
    }
    bool containsEpsilon(string str){
        assert(first.find(str) != first.end());
        for(int i=0;i<first[str].size();i++)
            return (first[str][i] == epsilon);
        return false;
    }

    //assume compressed grammar is available
    void firstUtil(string sym){
        cout<<"calculating first of: "<<sym<<endl;
        if(first.find(sym) != first.end()) //already calculated
            return;
        if(isTerminal(sym)){
            first[sym].push_back(sym);
            return;
        }
        set<string> st;
        set<string> :: iterator sit;
        int indx = ind[sym]; //index of production with this as left symbol
        for(int i=0;i<g[indx].arr.size();i++){
            if(g[indx].arr[i] == epsilon) // S->epsilon form
                first[sym].push_back(epsilon);
            else if(!isFirstNT(g[indx].arr[i])) //S->aB form
                first[sym].push_back(g[indx].arr[i].substr(0,1));
            else if(isFirstNT(g[indx].arr[i])){ //if not of form S->aB i.e S-> ABCD form
                for(int j=0;j<g[indx].arr[i].size();j++){
                    cout<<"case 3\n";
                    vector<string> ::iterator it;
                    string temp = g[indx].arr[i].substr(j,1);
                    firstUtil(temp);  //calculate FIRST(A) 
                    if(containsEpsilon(temp)){
                        for(it = first[temp].begin();it != first[temp].end();it++)
                            if(*it != epsilon)
                                st.insert(*it); //move forward  
                    }
                    else{//end moving forward
                        for(it = first[temp].begin();it != first[temp].end();it++)
                            if(*it != epsilon)
                                st.insert(*it);
                        for(sit = st.begin();sit != st.end();sit++)
                            first[sym].push_back(*sit);
                        break;
                    }
                }
            }
        }
        return;
    }
    
    
    void calculateFirst(){
        for(int i=0;i<g.size();i++){
            ind[g[i].sym] = i;
        }
        cout<<"The Fiest is as follows: \n";
        for(int i=0;i<g.size();i++){
            if(first.find(g[i].sym) == first.end())
                firstUtil(g[i].sym);
                
            cout<<g[i].sym<<" --> ";
            for(int j=0;j<first[g[i].sym].size();j++){
                cout<<first[g[i].sym][j]<<" ";
            }
            cout<<endl;
        }
    }
    
    
    /////////////////////////////Follow////////////////////////////////////
    vector<string> followUtilFirst(string beta){
        vector<string> ret;
        map<string,vector<string> > :: iterator it;
        int efl = 0;
        int fl = 0;
        for(int i=0;i<beta.length();i++){
            string temp = beta.substr(i,1);
            cout<<endl;
            if(!isFirstNT(temp)){ //if terminal return
                ret.push_back(temp);
                return ret;
            }
            else{
                efl = 0;
                for(int j=0;j<first[temp].size();j++){
                    //cout<<first[temp][j]<<" ";
                    if(first[temp][j] == epsilon)
                        efl = 1;
                    else ret.push_back(first[temp][j]);
                }
                if(efl == 0)
                    return ret; 
            }
        }
        if(efl == 1)
            ret.push_back(epsilon);
        return ret;
    }
    void followUtil(int index,map<string,vector<string> > &mp){
            
        for(int i=0;i<g[index].arr.size();i++){
            for(int j=0;j<g[index].arr[i].length();j++){
                string alpha = g[index].arr[i].substr(0,j);
                string B =  g[index].arr[i].substr(j,1);
                string beta =  g[index].arr[i].substr(j+1,g[index].arr[i].length());
                cout<<"alpha : "<<alpha<<" B: "<<B<<" beata: "<<beta<<endl;
                
                if(!isFirstNT(B)) //if B is not a a non-terminal do nothing
                    continue;
                cout<<"Calculating follow of NT: "<<B<<endl;
                int efl = 0;    
                if(beta.length() >= 1)
                {
                    vector<string>  followbeta = followUtilFirst(beta);
                    cout<<"fOLLOW BETA: "<<beta<<" size: "<<followbeta.size()<<endl;
                    for(int k=0;k<followbeta.size();k++)
                        cout<<followbeta[k]<<"  ";
                    cout<<endl;
                    
                    for(int k=0;k<followbeta.size();k++){ //rule 2
                        if(followbeta[k] == epsilon)
                            efl = 1;
                        else follow[B].push_back(followbeta[k]);
                    }
                }
                if(efl || beta.length() == 0){ //Rule 3 
                    cout<<" Rule 3 adding folow of "<<g[index].sym<<" in follow of "<<B<<endl;
                    mp[B].push_back(g[index].sym);
                }
            }
        }
    }
    //Calculating first is prerequisite for calculating follow
    void calculateFollow(){
        calculateFirst();

        follow[start].push_back("$");
        map<string,vector<string> > mp;
        map<string,vector<string> > :: iterator it;
        for(int i=0;i<g.size();i++){
            followUtil(i,mp);
            cout<<g[i].sym<<" --> ";
            for(int j=0;j<follow[g[i].sym].size();j++){
                cout<<follow[g[i].sym][j]<<" ";
            }
            cout<<endl;
        }
        
        cout<<"contains of map  \n";
        for(int i=0;i<g.size();i++){
            cout<<g[i].sym<<" --> ";
            for(int j=0;j<mp[g[i].sym].size();j++){
                cout<<mp[g[i].sym][j]<<" ";
            }
            cout<<endl;
        }
        cout<<"\n\nThe Follow is as follows: \n";
        set<string> st;
        for(int i=0;i<g.size();i++){
            for(int j=0;j<follow[g[i].sym].size();j++){
                st.insert(follow[g[i].sym][j]);
            }
            for(int j=0;j<mp[g[i].sym].size();j++){
                if(mp[g[i].sym][j] != g[i].sym){
                    string x = mp[g[i].sym][j];
                    for(int k=0;k<follow[x].size();k++)
                        st.insert(follow[x][k]);
                }
            }
            follow[g[i].sym].clear();
            cout<<g[i].sym<<" --> ";
            for(set<string>:: iterator sit=st.begin();sit!=st.end();sit++){
                follow[g[i].sym].push_back(*sit);
                cout<<*sit<<" ";
            }
            cout<<endl;
            st.clear();
        }
    }
    
    ////////////////////////////Utilities////////////////////////////////////
    void displayGrammar(){
        for(int i=0;i<g.size();i++){
            cout<<g[i].sym<<" -> ";
            for(int j=0;j<g[i].arr.size();j++)
                cout<<g[i].arr[j]<<" | ";
            cout<<endl;
        }
    }
        
    void displayProduction(production p){
        //cout<<"symbol:============================\n";
        //cout<<"sym: "<<p.sym<<" --> ";
        cout<<p.sym<<" -> ";
        for(int i=0;i<p.arr.size();i++)
        cout<<p.arr[i]<<" | ";
        cout<<endl;
    }
    
    void compressGrammar(){
        vector<production> ret;
        //comparison operator for production comaprison defined by operator overloading
        sort(g.begin(),g.end());//,compareProduction);
        int i = 0;
        while(i < g.size()){
                int j=i+1;
                while(j < g.size() && g[i].sym == g[j].sym){
                        g[i].arr.insert(g[i].arr.begin(),g[j].arr.begin(),g[j].arr.end());
                        j++;
                }
                ret.push_back(g[i]);
                i = j;
        }
        g = ret;
       }
        
    void purge(){
        first.clear();
        follow.clear();
        ind.clear();
        g.clear();
        epsilon = "";
    }
            
};

//}