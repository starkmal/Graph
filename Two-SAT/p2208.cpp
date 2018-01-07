#include<stdio.h>
#include <string.h>
#include<stack>
#include<vector>
#include<algorithm>
using namespace std;
const int N=2005;

int n,m;
typedef vector<int> vt;
typedef vt::iterator vi;
vt G[N];
int vtt,scc,Id[N],Dfn[N],Low[N],Instack[N];
stack<int>s;
void Tarjan(int x){
	Dfn[x]=Low[x]=++vtt;
	s.push(x),Instack[x]=1;
	for(vi now=G[x].begin();now!=G[x].end();now++){
		if(!Dfn[*now])Tarjan(*now),Low[x]=min(Low[x],Low[*now]);
		else if(Instack[*now])Low[x]=min(Low[x],Dfn[*now]);
	}
	if(Low[x]==Dfn[x]){
		scc++;
		int u;
		do{
			u=s.top(),s.pop();
			Instack[u]=0;
			Id[u]=scc;
		}while(u!=x);
	}
}
int main(){
	int i,j,k,A1,A2,C1,C2,flag;
	while(scanf("%d%d",&n,&m)!=EOF){
		memset(Dfn,0,sizeof(Dfn));
		vtt=0;
		for(i=1;i<=m;i++){
			scanf("%d%d%d%d",&A1,&A2,&C1,&C2);
			G[A1+C1*n+1].push_back(A2+(1-C2)*n+1);
			G[A1+(1-C1)*n+1].push_back(A2+C2*n+1);
		}
		for(i=1;i<=n<<1;i++)if(!Dfn[i])Tarjan(i);
		flag=0;
		for(i=1;i<=n;i++)
			if(Id[i]==Id[i+n]){
				flag=1;
				break;
			}
		puts(flag?"NO":"YES");
		for(i=1;i<=n;i++)vector<int>().swap(G[i]);
	}
}
