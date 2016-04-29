#include<bits/stdc++.h>
#include "node.h"
using namespace std;

vector<string> save;
vector<int> patch[100];
int nextinst=0;

void backpatch(int *a,int cnt,int num)
{
	
	int i;
	for(i=0;i<cnt;i++)
	{
	
		patch[num].push_back(a[i]);
	}
	
}
int* mergeList(int *a,int *b,int cnt1,int cnt2)
{

	int *c;
	c=new int[100];
	int cnt=0;
	int i;
	for(i=0;i<cnt1;i++)
	c[cnt++]=a[i];
	for(i=0;i<cnt2;i++)
	c[cnt++]=b[i];
	return c;
}

void calc()
{
	int i,j;
	for(i=0;i<100;i++)
	{
		if(patch[i].size()!=0)
		{
			//cout<<"comehere"<<endl;
			for(j=0;j<patch[i].size();j++)
			{
				int k=patch[i][j];
				//cout<<i<<" "<<j<<" "<<save[k]<<endl;
				string str=save[k];
				char buf[100];
				sprintf(buf,"%d",i);
				//cout<<buf<<endl;
				str+=buf;
				save[k]=str;
				//cout<<save[k]<<endl;
			}
		}
	}
}
void printcode()
{
	int i;
	for(i=0;i<save.size();i++)
	{
		cout<<i<<": "<<save[i]<<endl;
	}
}