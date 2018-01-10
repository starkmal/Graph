#include<stdio.h>
#include<string.h>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
const int N=100005,M=N<<3;

int Tote,Last[N],Next[M],End[M];
void Ins(int x,int y){
	End[++Tote]=y;
	Next[Tote]=Last[x];
	Last[x]=Tote;
}
int n,m,Ans,f[N],g[N];
int vtt,Dfn[N],Fa[N],Low[N];
void Cactus(int hd,int tl){
	int i,j,k,u,tot=1;
	deque<int>q;
	for(u=tl;u!=hd;u=Fa[u])tot++;
	for(u=tl,i=tot;i;i--,u=Fa[u])g[i]=f[u];
	for(i=1;i<=tot;i++)g[i+tot]=g[i];
	q.push_back(1);
	for(i=2;i<=tot+tot/2;i++){
		while(!q.empty()&&i-q.front()>tot/2)q.pop_front();
		Ans=max(Ans,g[i]+g[q.front()]+i-q.front());
		while(!q.empty()&&g[i]-i>=g[q.back()]-q.back())q.pop_back();
		q.push_back(i);
	}
	for(i=2;i<=tot;i++)f[hd]=max(f[hd],g[i]+min(i-1,tot-i+1));
}
void Tarjan(int x){
	int i,u;
	Low[x]=Dfn[x]=++vtt;
	for(i=Last[x];i;i=Next[i])
		if((u=End[i])!=Fa[x]){
			if(!Dfn[u]){
				Fa[u]=x;
				Tarjan(u);
				Low[x]=min(Low[x],Low[u]);
			}else Low[x]=min(Low[x],Dfn[u]);
			if(Low[u]>Dfn[x])Ans=max(Ans,f[u]+f[x]+1),f[x]=max(f[x],f[u]+1);
		}
	for(i=Last[x];i;i=Next[i])
		if(Fa[u=End[i]]!=x&&Dfn[u]>Dfn[x])Cactus(x,u);
}
int main(){
	int i,j,k,x,y;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++){
		scanf("%d%d",&k,&x);
		for(j=2;j<=k;j++){
			scanf("%d",&y);
			Ins(x,y),Ins(y,x);
			x=y;
		}
	}
	Tarjan(1);
	printf("%d\n",Ans);
}
