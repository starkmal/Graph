#include <stdio.h>
#include <stack>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;
const int N=2005,M=2000005;

int Tote,Last[N],Next[M],End[M];
void Ins(int x,int y){
	End[++Tote]=y;
	Next[Tote]=Last[x];
	Last[x]=Tote;
}
int n,m;

int scc,vtt,Dfn[N],Low[N],Id[N],Instack[N];
stack<int>s;
void Tarjan(int x) {
	Dfn[x]=Low[x]=++vtt;
	s.push(x),Instack[x]=1;
	for(int i=Last[x];i;i=Next[i]){
		int u=End[i];
		if(!Dfn[u])Tarjan(u),Low[x]=min(Low[x],Low[u]);
		else if(Instack[u])Low[x]=min(Low[x],Dfn[u]);
	}
	if(Low[x]==Dfn[x]){
		int u;scc++;
		do {
			u=s.top(),s.pop();
			Instack[u]=0;
			Id[u]=scc;
		} while(u!=x);
	}
}
int main() {
	int i,j,k,x,y,flag;
	while (scanf("%d%d",&n,&m)!=EOF) {
		memset(Dfn,0,sizeof(Dfn));
		memset(Instack,0,sizeof(Instack));
		memset(Last,0,sizeof(Last));
		vtt=scc=Tote=0;
		for(i=1;i<=m;i++){
			scanf("%d%d",&x,&y);
			if(x>0&&y>0)Ins(x+n,y),Ins(y+n,x);
			else if(x<0&&y<0)Ins(-x,-y+n),Ins(-y,-x+n);
			else if(x<0&&y>0)Ins(y+n,-x+n),Ins(-x,y);
			else if(x>0&&y<0)Ins(x+n,-y+n),Ins(-y,x);
		}
		for(i=1;i<=n<<1;i++)if(!Dfn[i])Tarjan(i);
		flag=1;
		for(i=1;i<=n;i++)
			if(Id[i]==Id[i+n]){
				flag=0;
				break;
			}
		printf("%d\n",flag);
	}
}
