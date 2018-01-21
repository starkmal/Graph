#include<stdio.h>
#include<ctype.h>
#include<algorithm>
#include<stack>
using namespace std;
const int N=1005,M=800005,Inf=1e9;
inline int _R(){
	int d=0;bool b=1;char t=getchar();
	while(!isdigit(t))b=t=='-'?0:1,t=getchar();
	for(;isdigit(t);t=getchar())d=(d<<3)+(d<<1)+t-'0';
	return b?d:-d;
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

stack<int>s;
int scc,vtt,sz[N],Id[N],Instack[N],Dfn[N],Low[N];
void Tarjan(int x){
	Dfn[x]=Low[x]=++vtt;
	s.push(x),Instack[x]=1;
	int i,u;
	for(i=Last[x];i;i=Next[i])
		if(i%2==0){
			u=End[i];
			if(!Dfn[u])Tarjan(u),Low[x]=min(Low[x],Low[u]);
			else if(Instack[u])Low[x]=min(Low[x],Dfn[u]);
		}
	if(Low[x]==Dfn[x]){
		scc++;
		do{
			u=s.top(),s.pop();
			Instack[u]=0;
			Id[u]=scc;sz[scc]++;
		}while(u!=x);
	}
}

int n,m;
int a[N];
int S,T,Dis[N],Cnt[N];
int Sap(int x,int flow){
	if(x==T)return flow;
	int u,i,tmp,d=0;
	for(i=Last[x];i;i=Next[i])
		if(V[i]&&Dis[x]==Dis[u=End[i]]+1){
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
	int i,j,k,x,y,ans=0;
	n=_R(),m=_R();
	S=n*m+1,T=S+1;
	for(i=1;i<=n*m;i++){
		a[i]=_R();
		if(i%m)Ins(i,i+1,Inf);
		k=_R();
		while(k--){
			x=_R(),y=_R();
			Ins(x*m+y+1,i,Inf);
		}
	}
	for(i=1;i<=n*m;i++)
		if(!Dfn[i])Tarjan(i);
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			if(sz[Id[k=i*m+j+1]]<2){
				if(a[k]>0)ans+=a[k],Ins(S,k,a[k]);
				else Ins(k,T,-a[k]);
			}
//	for(i=1;i<=T;i++)
//		for(j=Last[i];j;j=Next[j])
//			if(j%2==0)printf("%d %d %d\n",i,End[j],V[j]);
	while(Dis[S]<T)ans-=Sap(S,Inf);
	printf("%d",ans);
}
