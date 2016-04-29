#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define max 10
vector< vector<string> > production;
vector<string> v;
string prefix="";
vector<string>oldpro;
vector<string>newpro;
vector<string>newpro2;
int main(){
	int prelength=1;
	int n,i,j,k,l,ucount=1;
		string pro="",val="S";
		cout<<"Enter number of productions\n";
		cin>>n;
		string c="~";
		cout<<"Enter productions S->AB|c as S AB c ~\n";
		for(i=0;i<n;i++){
			int flag=1;
			while(1){
				pro="";
				cin>>pro;
				if(pro==c)
					break;
				v.push_back(pro);
			}
			production.pb(v);
			v.clear();
		}
	while(prelength!=0){
		for(i=0;i<n;i++){
			v.clear();
			v=production[i];
			for(int ind=1;ind<v.size();ind++){
			//	cout<<ind<<"im the index...\n";
				prefix="";
				int flag=1;
				//int ind=1;
				int cnt=0;
				int cnt1=0;
				int ne=0;
				while(flag){
					ne=0;
					prefix+=v[ind][cnt];
					for(int x=1;x<v.size();x++){
						if(v[x][cnt]!=prefix[cnt]){
							ne++;	
						}
					}
					cnt++;
					if(ne==v.size()-2){
						flag=0;
						prefix[cnt-1]='\0';
					}
				}
	//			if(ind<v.size()-1){
	//				ind++;
	//			}
				cout<<prefix<<endl;
				oldpro=v;
				vector<string>temp1;
				int length=prefix.length();
				newpro.pb(v[0]);
				val+='\'';
				temp1.pb(val);
				string temp=prefix.substr(0,length-1)+val;
				newpro.pb(temp);
				for(int z=1;z<oldpro.size();z++){
					int flag1=1;
					string value=oldpro[z];
					//cout<<"value "<<value<<" "<<prefix<<endl;
					for(int y=0;y<length-1;y++){
						if(value[y]!=prefix[y]){
							//cout<<value[y]<<" "<<prefix[y]<<" "<<y<<"  vi"<<endl;
							flag1=0;
							break;
						}
					}
					//cout<<flag1<<endl;
					if(flag1==1){
						string pnew=value.substr(length-1,value.length()-length-1);
						//cout<<"pnew - "<<pnew<<endl;
						temp1.pb(pnew);
					}
					else{
						newpro.pb(value);
					}
					
				}
		
				cout<<endl;
				production[i]=newpro;
				newpro.clear();
				production.pb(temp1);
				temp1.clear();
			
		//		newpro.pb(val);
		//		newpro.pb(prefix);
		//		production.pb(newpro);
		//		cout<<"added-\n";
		//		for(int in=0;in<newpro.size();in++){
		//			cout<<newpro[in]<<" ";
		//		}
		//		cout<<endl;
				
				newpro.clear();
				oldpro.clear();
				v.clear();
				prelength=length-1;
				cout<<prelength<<" prelength\n";
					if(prelength>0){
			
						cout<<"Left factored grammer is\n";
						for(int ic=0;ic<production.size();ic++){
							cout<<production[ic][0]<<"->";
							for(int jc=1;jc<production[ic].size();jc++){
								cout<<production[ic][jc]<<" ";
							}
							cout<<endl;
						}
					}
			}
		}
		
	}
	
	return 0;
}
