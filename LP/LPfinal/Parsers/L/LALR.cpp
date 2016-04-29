#include <bits/stdc++.h>
#include "FirstCalculator.cpp"
#include "LALR.h"
using namespace std;

struct node{
	vector<pair<production,vector<string> > > g;
	vector<pair<string,int> > children;
} DFA[1024];



int gindex = 0;
const string dollar = "$";

class LALRParser{
	
	vector<production> g;
	vector<production> ag;
	map<string,vector<int> > mp;
	set<string> allsym;
	vector<bool> visited;
	map<pair<int,string>,pair<string,int> > table;
	FirstCalculator first;

	public:

	void generateItems(){
		//genearting augmented grammar
		production p;
		p.sym = "Y"; //dummy start
		p.arr.push_back(g[0].sym);
		ag.push_back(p);
		for(int j=0;j<g.size();j++){
			ag.push_back(g[j]);
		}
		//cout<<"Displaying augmentd grammar\n";
//		displayGrammar(ag); 
		///Augmented grammar complete////
		
		//creating a mpa from grammar symbol to the indexes where it is present
		for(int i=0;i<g.size();i++){
			mp[g[i].sym].push_back(i);
		}
		
	}
	
	void  generateAutomation(){
		//generate items
		generateItems();
		//creating  a set of all symbols (NT + T)  for goTo construction
		for(int i=0;i<g.size();i++){
			allsym.insert(g[i].sym);
			for(int j=0;j<g[i].arr.size();j++){
				for(int k=0;k<g[i].arr[j].length();k++){
					allsym.insert(g[i].arr[j].substr(k,1));
				}
			}
		}
		set<string>::iterator it;
		//cout<<"All symbols\n";
//		for(it = allsym.begin();it != allsym.end();it++)
			//cout<<*it<<" ";
		//cout<<endl;
		
		
		vector<pair<production,vector<string> > > send;
		vector<string> sendtemp;
		sendtemp.push_back(dollar);
		production p;
		p.sym = ag[0].sym;
		p.arr.push_back("."+ag[0].arr[0]);
		send.push_back(make_pair(p,sendtemp));
		DFA[gindex].g = calculateClosure(send);
		//cout<<"state 0 closure grammr\n";
//		displayGrammarWithLookahead(DFA[gindex].g);

		queue<int> q;
		q.push(gindex++);
		for(int i=0;i<(1<< ag.size());i++)
			visited.push_back(false);

		while(!q.empty()){
			int state = q.front();
			q.pop();
			visited[state] = true;
			for(it = allsym.begin();it != allsym.end();it++){
				int t = goTo(state,*it);
				if(t >= 0){
					DFA[state].children.push_back(make_pair(*it,t));
					if(!visited[t])
						q.push(t);
				}	
			}
		}
	}

	
	string advanceDot(string str){
		//cout<<"advance dot: str "<<str<<endl;
		string ret = "";
		int n = str.length();
		for(int i=0;i<n;i++){
			if(i != n-1 && str[i] == '.')
				ret += str.substr(i+1,1)+".",i++;
			else ret += str.substr(i,1);
		}
		//cout<<"advance dot: ret "<<ret<<endl;
		return ret;
	}

	string sortConcat(vector<string> arg){
		string ret = "";
		for(int i=0;i<arg.size();i++)
			ret += arg[i];
		sort(ret.begin(),ret.end());
		return ret;
	}

	bool isSame(vector<pair<production,vector<string> > >  r,int pos){
		vector<pair<production,vector<string> > >   l = DFA[pos].g;	
		set<string> ls,rs;
		if(l.size() != r.size())return false;
		else{
			for(int i=0;i<l.size();i++){
				ls.insert(l[i].first.sym+l[i].first.arr[0]+sortConcat(l[i].second));
				rs.insert(r[i].first.sym+r[i].first.arr[0]+sortConcat(r[i].second));
			}
		} 
		if(ls == rs)
			return true;
		ls.clear();
		rs.clear();
		for(int i=0;i<l.size();i++){
			ls.insert(l[i].first.sym+l[i].first.arr[0]);
			rs.insert(r[i].first.sym+r[i].first.arr[0]);
		}
		if(ls == rs){
			////cout<<"saha: "<<pos<<endl;
			//assert(1 == 2);
			
			for(int i=0;i<DFA[pos].g.size();i++){
				for(int j=0;j<r[i].second.size();j++)
					DFA[pos].g[i].second.push_back(r[i].second[j]);
				unique(DFA[pos].g[i].second.begin(),DFA[pos].g[i].second.end());
			}
			return true;
		}
		return false;
	}
	
	
	int goTo(int state,string x){
		//cout<<"goTo: "<<state<<" , "<<x<<endl;
		vector<pair<production,vector<string> > >  ret;

		for(int i=0;i<DFA[state].g.size();i++){
			pair<int,string> fd = findDot(DFA[state].g[i].first.arr[0]);
			////cout<<"fd.first: "<<fd.first<<" fd.second: "<<fd.second<<endl;
			if(fd.first >= 0 && fd.second == x){
				production p;
				p.sym = DFA[state].g[i].first.sym;
				p.arr.push_back(advanceDot(DFA[state].g[i].first.arr[0]));
				//cout<<"found: "<<p.arr[0]<<endl;				
				ret.push_back(make_pair(p,DFA[state].g[i].second));
				p.arr.clear();
			}
		}

//		displayGrammarWithLookahead(ret);
		//cout<<"displaying goto grammar: \n";
		ret = calculateClosure(ret);
//		displayGrammarWithLookahead(ret);
		if(ret.size() == 0)return -1;
		
		int same  = -1;
		for(int i=0;i<gindex;i++){
			if(isSame(ret,i)){
				same = i;
				break;
			}
		}
		
		int newstate = gindex;
		if(same >= 0)
			return same;
		else DFA[gindex++].g = ret;
		return newstate;
	}
	
	
	inline bool isTerminal(string str){
		return (str.size() == 1 && !(str[0] >= 'A' && str[0] <= 'Z'));
	}

	pair<int,string> findDot(string str){
		int n = str.length();
		string s = "";
		for(int i=0;i<n;i++){
			if(str[i] == '.'){
				if(i == n-1)return make_pair(-1,s);
				else return make_pair(i,str.substr(i+1,1));
			}
		}
	}


	vector<string> findLookAhead(pair<production,vector<string> > entry){
		vector<string> ret;
		string str = entry.first.arr[0];
		int n = str.length();
		string s = "";
		for(int i=0;i<n;i++){
			if(str[i] == '.'){
				if(i == n-2)return entry.second;
				else{
					string temp = str.substr(i+1,1);
					////cout<<"temp: "<<temp<<endl;
					ret = first.followUtilFirst(temp);
					return ret;
				}
			}
		}
	}

	vector<pair<production,vector<string> > > calculateClosure(vector<pair<production,vector<string> > > tg){
		vector<pair<production,vector<string> > > ret = tg;
		set<string> st;
		do{
			tg = ret;
			ret.clear();
//			displayGrammarWithLookahead(tg);
			for(int i=0;i<tg.size();i++){
				pair<int,string> fd = findDot(tg[i].first.arr[0]);
				////cout<<"fd.first: "<<fd.first<<" fd.second: "<<fd.second<<endl;
				if(fd.first >= 0){
					ret.push_back(tg[i]);
					vector<string> la = findLookAhead(tg[i]);
					if(!isTerminal(fd.second) && st.find(fd.second) == st.end()){
						//cout<<"ret: 1\n";
//						displayGrammarWithLookahead(ret);
						for(int j=0;j<mp[fd.second].size();j++){
							production temp;
							temp.sym = g[mp[fd.second][j]].sym;
							temp.arr.push_back("."+g[mp[fd.second][j]].arr[0]);
							ret.push_back(make_pair(temp,la));
							st.insert(fd.second);
						}
					}
				}
				else ret.push_back(tg[i]);
			}
		}while(ret.size() > tg.size());
		return ret;
	}
	inline bool isLastDot(string str){
		return (str.length() > 0 && str[str.length()-1] == '.');
	}

	int getProductionNo(production p){
		//displayGrammar(g);
		map<string,int> pno;
		for(int i=0;i<g.size();i++){
			pno.insert(make_pair(g[i].sym+g[i].arr[0],i+1));
		}
		string str = p.sym+p.arr[0];
		string temp = "";
		for(int i=0;i<str.length();i++){
			if(str[i] != '.')
				temp += str[i];
		}
		////cout<<temp<<endl;
		//if(temp == "Y"+g[0].sym)return 0;
		assert(pno.find(temp) != pno.end());
		return pno[temp];
	}

	void constructTable(){
		//cout<<"\nThe SLR-table for the graamar is: \n";
		for(int i=0;i<gindex;i++){
			//cout<<i<<" ";
			for(int j=0;j<DFA[i].children.size();j++){
				if(!isTerminal(DFA[i].children[j].first)){
					//cout<<"["<<DFA[i].children[j].first<<","<<DFA[i].children[j].second<<"]  ";
					table.insert(make_pair(make_pair(i,DFA[i].children[j].first),make_pair("",DFA[i].children[j].second)));
				}
				else{
					//cout<<"["<<DFA[i].children[j].first<<","<<"s"<<DFA[i].children[j].second<<"]  ";
					table.insert(make_pair(make_pair(i,DFA[i].children[j].first),make_pair("s",DFA[i].children[j].second)));
				}
			}
			
			 for(int j=0;j<DFA[i].g.size();j++){
               	if(isLastDot(DFA[i].g[j].first.arr[0])){
               		////cout<<DFA[i].g[j].sym<<" \n"; 
               		if(DFA[i].g[j].first.sym == "Y")continue;
               		for(int k=0;k<DFA[i].g[j].second.size();k++){
               			////cout<<it->second[k]<<endl;
               			int pno = getProductionNo(DFA[i].g[j].first);
               			//cout<<"["<<DFA[i].g[j].second[k]<<","<<"r"<<pno<<"]  ";
               			table.insert(make_pair(make_pair(i,DFA[i].g[j].second[k]),make_pair("r",pno)));
               		}
               	}
        	}
        	//cout<<endl;
		}
	}

	void printtable(){

		cout<<"---------\nn val g/a\n---------\n";
		map<pair<int,string>,pair<string,int> > :: iterator it;
		for(it=table.begin();it!=table.end();it++){
				pair<int,string> pp=it->first;
				pair<string,int> pp1=it->second;
				cout<<pp.first<<" "<<pp.second<<" - "<<pp1.first<<pp1.second<<endl; 
		}
		cout<<"---------\n";
	}

	struct stnode{
		int tag;
		int state;
		string sym;
	};

	stnode make_state(int state){
		stnode ret;
		ret.tag = 1;
		ret.state = state;
		return ret;
	}
	stnode make_sym(string sym){
		stnode ret;
		ret.tag = 2;
		ret.sym = sym;
		return ret;
	}

	int getCount(int pos){
		return g[pos-1].arr[0].size();
	}
	
	bool isDerivable(string str){
		//cout<<"string to check: "<<str<<endl;
		map<pair<int,string>,pair<string,int> > :: iterator it;
		stack<stnode> st;
		st.push(make_state(0));
		int n = str.length();
		int i = 0;
		while(i < n ){
			if(st.top().tag == 1){
				it = table.find(make_pair(st.top().state,str.substr(i,1)));
				if(it == table.end())return false; //goto entry not found
				//cout<<it->second.first<<endl;
				if(it->second.first == "s"){
						st.push(make_sym(str.substr(i,1)));
						st.push(make_state(it->second.second));
						i++;
				}
				else if(it->second.first == "r"){
					int cnt = getCount(it->second.second);
					for(int i=0;i<2*cnt;i++)
						st.pop();
					assert(st.top().tag == 1); //must be a state
					int temp = st.top().state;
					st.push(make_sym(g[it->second.second-1].sym));
					it = table.find(make_pair(temp,st.top().sym));
					if(it == table.end())return false; //parser error;
					assert(it->second.first == ""); //Otherwise A programming error
					st.push(make_state(it->second.second));
				}
				else{
					assert(1 == 2); //should not reach here
				}		
			}
/*			for(stack<stnode> dump = st;!dump.empty();dump.pop()){
				if(dump.top().tag == 1)
					//cout<<dump.top().state<<" ";
				else //cout<<dump.top().sym<<" ";
			}
*/			//cout<<" ===> "<<str.substr(i,str.length())<<endl;
		 }
		return true;
	}

	/////////////Utilities///////////////////
	void inputGrammar(){
        int gsize;
        cin>>gsize;
        for(int i=0;i<gsize;i++){
            production p;
            cin>>p.sym; //assum first input of grammar as start symbol
            int x;
            cin>>x;
            for(int j=0;j<x;j++){
                    string str;
                    cin>>str;
                    p.arr.push_back(str);
            }
            g.push_back(p);
        }
//        displayGrammar(g);
        //cout<<"initialising first\n";
        first.initFirstCalculator(g);
        first.compressGrammar(); 
        first.calculateFirst();

    }
    
  /*  void displayGrammar(vector<production> g){
        for(int i=0;i<g.size();i++){
                //cout<<g[i].sym<<" -> ";
                for(int j=0;j<g[i].arr.size();j++)
                        //cout<<g[i].arr[j]<<" | ";
                //cout<<endl;
        }
    }
    void displayGrammarWithLookahead(vector<pair<production,vector<string> > > g){
    	 for(int i=0;i<g.size();i++){
                //cout<<g[i].first.sym<<" -> ";
                for(int j=0;j<g[i].first.arr.size();j++){
                        //cout<<g[i].first.arr[j]<<" | ";
                	for(int k=0;k<g[i].second.size();k++)
                		//cout<<g[i].second[k]<<" / ";
                }
                //cout<<endl;
        }
    }

    void displayAutomation(){
    	//cout<<"Displaying the LR state Automation: \n";
    	for(int i=0;i<gindex;i++){
    		//cout<<"state: "<<i<<endl;
    		displayGrammarWithLookahead(DFA[i].g);
    		for(int j=0;j<DFA[i].children.size();j++){
    			//cout<<"Goto: "<<DFA[i].children[j].first<<" ==> "<<DFA[i].children[j].second<<endl;
    		}
    	}
    }
     void displayProduction(production p){
        ////cout<<"symbol:============================\n";
        ////cout<<"sym: "<<p.sym<<" --> ";
        //cout<<p.sym<<" -> ";
        for(int i=0;i<p.arr.size();i++)
        cout<<p.arr[i]<<" | ";
        cout<<endl;
    }
    */
};

int main(){
	freopen("input.txt","r",stdin);
	LALRParser slp;
	slp.inputGrammar();
	slp.generateAutomation();
//	slp.displayAutomation();
	slp.constructTable();
	slp.printtable();
	string str;
	//while(1){
		////cout<<"input to check: ";
		cin>>str;
		if(slp.isDerivable(str))
			cout<<"ACCEPTED.\n";
		else cout<<"NOT ACCEPTED\n";
	//}
	return 0;
}
