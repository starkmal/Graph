#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stack>
using namespace std;
const int N=205,M=200005;

int Tote,Last[N],Next[M],End[M];
void Ins(int x,int y){
	End[++Tote]=y;
	Next[Tote]=Last[x];
	Last[x]=Tote;
}
int vtt,scc,Dfn[N],Low[N],Id[N],Instack[N];
stack<int>s;
void Tarjan(int x){
	Dfn[x]=Low[x]=++vtt;
	s.push(x),Instack[x]=1;
	for(int i=Last[x],u;i;i=Next[i]){
		u=End[i];
		if(!Dfn[u])Tarjan(u),Low[x]=min(Low[x],Low[u]);
		else if(Instack[u])Low[x]=min(Low[x],Dfn[u]);
	}
	if(Dfn[x]==Low[x]){
		int u;scc++;
		do{
			u=s.top();s.pop();
			Instack[u]=0;
			Id[u]=scc;
		}while(u!=x);
	}
}
int n,m;
typedef pair<int,int> pii;
pii A[N];
int main(){
	int T,i,j,k,x,y,flag;
	scanf("%d",&T);
	while(T--){
		Tote=scc=vtt=0;
		memset(Last,0,sizeof(Last));
		memset(Dfn,0,sizeof(Dfn));
		memset(Id,0,sizeof(Id));
		scanf("%d%d",&n,&m);
		for(i=1;i<=m;i++){
			scanf("%d%d",&A[i].first,&A[i].second);
			if(A[i].first>A[i].second)swap(A[i].first,A[i].second);
		}
		sort(A+1,A+1+m);
		for(i=1;i<=m;i++)
			for(j=i+1;j<=m;j++)
				if(A[j].first<A[i].second&&A[j].second>A[i].second)
					Ins(i,j+m),Ins(i+m,j),Ins(j,i+m),Ins(j+m,i);
		for(i=1;i<=m<<1;i++)if(!Dfn[i])Tarjan(i);
		flag=1;
		for(i=1;i<=m;i++)
			if(Id[i]==Id[i+m]){
				flag=0;
				break;
			}
		puts(flag?"true":"false");
	}
}
