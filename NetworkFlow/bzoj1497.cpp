#include<stdio.h>
#include<ctype.h>
#include<algorithm>
#include<vector>
using namespace std;
const int N=60005,M=350005,Inf=1e9;
inline int _R(){
	int d=0;char t=getchar();
	while(!isdigit(t))t=getchar();
	for(;isdigit(t);t=getchar())d=(d<<3)+(d<<1)+t-'0';
	return d;
}

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

int n,m;
int S,T,Dis[N],Cnt[N];
int Sap(int x,int flow){
	if(x==T)return flow;
	int u,d=0,tmp,i;
	for(i=Last[x];i;i=Next[i])
		if(V[i]>0&&Dis[x]==Dis[u=End[i]]+1){
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
	int i,j,k,x,y,z,ans=0;
	n=_R(),m=_R();
	S=n+m+1,T=S+1;
	for(i=1;i<=n;i++)Ins(i+m,T,_R());
	for(i=1;i<=m;i++){
		x=_R(),y=_R(),z=_R();
		Ins(i,x+m,Inf);
		Ins(i,y+m,Inf);
		Ins(S,i,z);
		ans+=z;
	}
	while(Dis[S]<T)ans-=Sap(S,Inf);
	printf("%d",ans);
}
