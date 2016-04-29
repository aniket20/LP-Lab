#include<bits/stdc++.h>
#define pb push_back
using namespace std;
vector<string> production;
vector<string> beta;
vector<string> alpha;
int main(){
        string s;
        cout<<"enter number of productions\n";
        int n;
        cin>>n;
        cout<<"enter productions in standard format ( S->A|B|c ) \n";
        for(int i=0;i<n;i++){
                cin>>s;
                if(s[0]<'A' || s[0] > 'Z' || s[1] != '-' || s[2] != '>'){
                        cout<<"Invalid production\n";
                }
                else
                        production.push_back(s);
        }
        for(int i=0;i<n;i++){
                cout<<endl;
                int flag=0;
                string pro=production[i];
                cout<<"production is : "<<pro<<endl;
                int l=pro.length();
                int ind=3;
                //cout<<"just outside main while index "<<ind<<endl;
                while(ind<=l){
                        //cout<<"main while index and pro[ind]"<<ind<<" "<<pro[ind]<<endl;
                        string al="";
                        string bt="";
                        if(pro[ind]==pro[0] && (pro[ind-1]=='>'||pro[ind-1]=='|')){
                                flag=1;
                                ind++;
                                //cout<<"match found index "<<ind-1<<endl;
                                while( pro[ind]!='|' && ind<=l ){
                                        //cout<<"alpha while index "<<ind<<endl;
                                        al+=pro[ind];
                                        ind++;
                                }
                                alpha.push_back(al);
                                cout<<"Alpha "<<al<<endl;
                                al="";
                                ind++;
                        }
                        else{
                                while( pro[ind]!='|' && ind<=l ){
                                        bt+=pro[ind];
                                        //cout<<"main while index "<<ind<<endl;
                                        ind++;
                                }
                                beta.push_back(bt);
                                ind++;
                                cout<<"BETA "<<bt<<endl;
                                bt="";
                        }

                }
                if(flag==1){
                	cout<<endl<<endl;
                        cout<<"grammar is left recursive \nAfter elimination of left recursion grammer is \n\n";
                        if(beta.size()==0){
                                cout<<"Can not eliminate the Left Recursion "<<endl;
                        }
                        else{
                                string s="";
                                cout<<pro[0]<<"->";
                                for(int it=0;it<beta.size();it++){
                                        if(it!=beta.size()-1)
                                                cout<<beta[it]<<pro[0]<<"'|";
                                                 else
                                                cout<<beta[it]<<pro[0]<<"'";

                                }

                                cout<<endl;
                                cout<<pro[0]<<"->";
                                for(int it=0;it<alpha.size();it++){
                                        cout<<alpha[it]<<pro[0]<<"'|";
                                }
                                cout<<"epsilon "<<endl;
                        }
                }
                else{
                        cout<<"Grammar is not left recursive !";
                }

                // for(int x=0;x<alpha.size();x++){
                //      cout<<alpha[x]<<" ";
                // }
                // cout<<endl;
                // for(int x=0;x<beta.size();x++){
                //      cout<<beta[x]<<" ";
                // }
                // cout<<endl;
                alpha.clear();
                beta.clear();
                flag=0;
        }
        return 0;
}

