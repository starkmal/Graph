#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=405;

int Q,n,m,S,T;
int V[N][N],Lim[N],Dis[N],cnt[N];
int Sap(int x,int flow){
	if(x==T)return flow;
	int d=0,tmp,i;
	for(i=1;i<=T;i++)
	if(V[x][i]&&Dis[i]+1==Dis[x]){
		tmp=Sap(i,min(flow-d,V[x][i]));
		V[x][i]-=tmp,V[i][x]+=tmp;
		d+=tmp;
		if(d==flow||Dis[S]>=T)return d;
	}
	if(Dis[S]>=T)return d;
	if(--cnt[Dis[x]]==0)Dis[S]=T;
	cnt[++Dis[x]]++;
	return d;
}
void Init(){
	memset(V,0,sizeof(V));
	memset(Lim,0,sizeof(Lim));
	memset(cnt,0,sizeof(cnt));
	memset(Dis,0,sizeof(Dis));
}
int main(){
	int i,j,k,x,y,z,d,ans,low;
	scanf("%d",&Q);
	while(Q--){
		Init();
		ans=low=0;
		scanf("%d%d",&n,&m);
		S=n+1,T=S+1;
		for(i=1;i<=m;i++){
			scanf("%d%d%d%d",&x,&y,&z,&d);
			Lim[x]-=z,Lim[y]+=z;
			V[x][y]+=d-z;
		}
		for(i=1;i<=n;i++)
			if(Lim[i]>=0)V[S][i]=Lim[i],low+=Lim[i];
			else V[i][T]=-Lim[i];
		while(Dis[S]<T)ans+=Sap(S,1e9);
		if(ans==low)puts("Yes");
		else puts("No");
	}
}