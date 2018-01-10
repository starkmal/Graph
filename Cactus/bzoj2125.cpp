#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int N=10005,M=N<<3;

int n,m;

int Now,Tote=1,Last[N],Next[M],End[M],Len[M];
void Ins(int x,int y,int z){
	End[++Tote]=y;
	Len[Tote]=z;
	Next[Tote]=Last[x];
	Last[x]=Tote;
}

//Dijstra
typedef pair<int,int>pii;
priority_queue<pii,vector<pii>,greater<pii> >q;
int Dis[N],Vis[N];
void Dijstra(){
	memset(Dis,0x3f,sizeof(Dis));
	Dis[1]=0,Vis[1]=1;
	q.push(pii(0,1));
	int x,u;
	while(!q.empty()){
		x=q.top().second,q.pop(),Vis[x]=0;
		for(int i=Last[x],u;i;i=Next[i])
			if(Dis[u=End[i]]>Dis[x]+Len[i]){
				Dis[u]=Dis[x]+Len[i];
				if(!Vis[u])Vis[u]=1,q.push(pii(Dis[u],u));
			}
	}
}

//Cactus
int vtt,Dfn[N],Fae[N],Del[M],dist[N];
int bcc,W[N],Id[N];
void Cactus(int tl,int e){
	int i,u,hd=End[e];
	Del[e]=Del[e^1]=1;
	W[++bcc]=Len[e];
	for(i=Fae[tl],u=tl;u!=hd;u=End[i^1],i=Fae[u]){
		Del[i]=Del[i^1]=1;
		W[bcc]+=Len[i];
		Id[u]=bcc;
		Ins(u,hd,0),Ins(hd,u,0);
	}
}
void Tarjan(int x){
	Dfn[x]=++vtt;
	for(int i=Last[x],u;i;i=Next[i])
		if(i<=Now&&(i^1)!=Fae[x]){
			u=End[i];
			if(!Dfn[u]){
				Fae[u]=i;
				dist[u]=dist[x]+Len[i];
				Tarjan(u);
			}
			else if(Dfn[u]<Dfn[x])Cactus(x,i);
		}
}

//LCA
int Fa[N][22],Dep[N];
void Bfs(){
	queue<int>Q;
	memset(Vis,0,sizeof(Vis));
	Q.push(1),Vis[1]=1;
	int x,u,i,j;
	while(!Q.empty()){
		x=Q.front(),Q.pop();
		for(i=Last[x];i;i=Next[i])
			if(!Del[i]&&!Vis[u=End[i]]){
				Dep[u]=Dep[x]+1;
				Fa[u][0]=x;
				for(j=1;j<=20;j++)Fa[u][j]=Fa[Fa[u][j-1]][j-1];
				Vis[u]=1;
				Q.push(u);
			}
	}
}
int LCA(int x,int y){
	if(Dep[x]>Dep[y])swap(x,y);
	int s,i,u=x,v=y,t=Dep[y]-Dep[x];
	for(i=0;i<=20;i++)
		if((1<<i)&t)y=Fa[y][i];
	if(x==y)return Dis[v]-Dis[u];
	for(i=20;i>=0;i--)
		if(Fa[x][i]!=Fa[y][i])x=Fa[x][i],y=Fa[y][i];
	if(Id[x]&&Id[x]==Id[y]){
		s=abs(dist[x]-dist[y]);
		s=min(s,W[Id[x]]-s);
		return Dis[u]-Dis[x]+Dis[v]-Dis[y]+s;
	}
	return Dis[u]+Dis[v]-2*Dis[Fa[x][0]];
}

int main(){
	int T,i,j,k,x,y,z;
	scanf("%d%d%d",&n,&m,&T);
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		Ins(x,y,z),Ins(y,x,z);
	}
	Dijstra();
	memset(Vis,0,sizeof(Vis));
	Now=Tote;
	Tarjan(1);
	Bfs();
	while(T--){
		scanf("%d%d",&x,&y);
		printf("%d\n",LCA(x,y));
	}
}
