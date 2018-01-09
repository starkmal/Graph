#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
using namespace std;
const int N=10005,M=80005;

//-----------Edge Data----------- 
int Tote=1,Last[N],Next[M],End[M],Len[M]; 
int Now,Del[M];
void Ins(int x,int y,int z){
	End[++Tote]=y;
	Len[Tote]=z;
	Next[Tote]=Last[x];
	Last[x]=Tote;
}

//------------Global Data-----------

int n,m,T;

//----------Dijstra-----------

typedef pair<int,int> pii;
priority_queue<pii,vector<pii>,greater<pii> >Q;
int Dis[N];
bool Vis[N];

void Dijstra(){
	memset(Dis,0x3f,sizeof(Dis));
	Dis[1]=0,Vis[1]=1;
	Q.push(pii(0,1));
	int x,u;
	while(!Q.empty()){
		x=Q.top().second,Q.pop(),Vis[x]=0;
		for(int i=Last[x];i;i=Next[i]){
			u=End[i];
			if(Dis[u]>Dis[x]+Len[i]){
				Dis[u]=Dis[x]+Len[i];
				if(!Vis[u])Vis[u]=1,Q.push(pii(Dis[u],u));
			}
		}
	}
}

//-----------cactus-----------

int bcc,W[N],dist[N],Id[N]; 
int vtt,FaE[N],Dfn[N];

void Cactus(int x,int e){
	int rt=End[e];
	W[++bcc]=Len[e];
	Del[e]=Del[e^1]=1;
	/*Id[rt]=bcc;*/			//环顶不能赋编号
	for(;x!=rt;x=End[FaE[x]^1]){
		Del[FaE[x]]=Del[FaE[x]^1]=1;
		W[bcc]+=Len[FaE[x]];
		Id[x]=bcc;
		Ins(x,rt,0),Ins(rt,x,0);
	}
}
void Tarjan(int x){
	Dfn[x]=++vtt;
	for(int i=Last[x],u;i;i=Next[i])
		if(i<=Now&&(i^1)!=FaE[x]){
			u=End[i];
			if(!Dfn[u]){
				FaE[u]=i;
				dist[u]=dist[x]+Len[i];
				Tarjan(u);
			}
			else if(Dfn[x]>Dfn[u])Cactus(x,i);
		}
}

//-----------LCA-----------

int Fa[N][22],Dep[N];

queue<int>q;
void Bfs(){
	memset(Vis,0,sizeof(Vis));
	q.push(1),Vis[1]=1;
	int x,u,i,j;
	while(!q.empty()){
		x=q.front(),q.pop();
		for(i=Last[x];i;i=Next[i])
			if(!Del[i]&&!Vis[u=End[i]]){
				Dep[u]=Dep[x]+1;
				Fa[u][0]=x;
				for(j=1;j<=20;j++)Fa[u][j]=Fa[Fa[u][j-1]][j-1];
				Vis[u]=1,q.push(u);
			}
	}
}
int LCA(int x,int y){
	if(Dep[x]>Dep[y])swap(x,y);
	int i,u=x,v=y,t=Dep[v]-Dep[u],s;
	for(i=0;i<=20;i++)
	if((1<<i)&t)v=Fa[v][i];
	if(u==v)return Dis[y]-Dis[x];
	for(i=20;i>=0;i--)
		if(Fa[u][i]!=Fa[v][i])
			u=Fa[u][i],v=Fa[v][i];
	if(Id[u]&&Id[u]==Id[v]){
		s=abs(dist[u]-dist[v]);
		s=min(s,W[Id[u]]-s);
		return Dis[y]-Dis[v]+Dis[x]-Dis[u]+s;
	}
	return Dis[y]+Dis[x]-2*Dis[Fa[u][0]];
}

//-----------Main-----------
int main(){
	int i,j,k,x,y,z;
	scanf("%d%d%d",&n,&m,&T);
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		Ins(x,y,z),Ins(y,x,z);
	}
	Now=Tote;
	Dijstra();
	Tarjan(1);
	Bfs();
	while(T--){
		scanf("%d%d",&x,&y);
		printf("%d\n",LCA(x,y));
	}
}
