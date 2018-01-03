#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=805,M=800005,Inf=1e9;

int n,m,S,T,EX;
int Lim[N],Dis[N],Cnt[N];
int Tote=1,Last[N],Next[M],End[M],V[M];
void Ins(int x,int y,int z){
	End[++Tote]=y;
	V[Tote]=z;
	Next[Tote]=Last[x];
	Last[x]=Tote;

	End[++Tote]=x;
	Next[Tote]=Last[y];
	Last[y]=Tote;
}
int Sap(int x,int flow){
	if(x==T)return flow;
	int u,i,d=0,tmp;
	for(i=Last[x];i;i=Next[i])
		if(V[i]&&Dis[u=End[i]]+1==Dis[x]){
			tmp=Sap(u,min(flow-d,V[i]));
			V[i]-=tmp,V[i^1]+=tmp,d+=tmp;
			if(d==flow||Dis[S]>=T)return d;
		}
	if(Dis[S]>=T)return d;
	if(--Cnt[Dis[x]]==0)Dis[S]=T;
	Cnt[++Dis[x]]++;
	return d;
}
int main(){
	int i,j,k,x,y,u,d,ans=0,low=0;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++){
		scanf("%d%d%d%d",&x,&y,&d,&u);
		Lim[x]-=d,Lim[y]+=d;
		Ins(x,y,u-d);
	}
	S=n+1,T=S+1,EX=Tote+1;
	for(i=1;i<=n;i++)
		if(Lim[i]>=0)Ins(S,i,Lim[i]),low+=Lim[i];
		else Ins(i,T,-Lim[i]);
	Ins(n,1,Inf);

	while(Dis[S]<T)Sap(S,Inf);
	ans=V[Tote];
	
	memset(Dis,0,sizeof(Dis));
	memset(Cnt,0,sizeof(Cnt));
	for(i=EX;i<=Tote;i++)V[i]=0;
	S=1,T=n;
	while(Dis[S]<T)ans+=Sap(S,Inf);
	printf("%d",ans);
}