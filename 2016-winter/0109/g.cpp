#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <vector>
#define fo(i,a,b) for(int i=a;i<=b;i++)

using namespace std;

const int maxn=100010;

bool vis[maxn<<1];
int n,m,a[maxn],b[maxn],c[maxn],d[maxn];
map<int,int> M;
set< pair<int,int> > T[maxn<<1];
vector<int> V;

inline int lowbit(int x)
{
	return x & -x;
}

void Modify(int x,pair<int,int> v)
{
	while(x<=m)
	{
		T[x].insert(v);
		x+=lowbit(x);
	}
}

vector<int> Query(int x,int y)
{
	vector<int> ret;
	while(x)
	{
		set< pair<int,int> >::iterator last=T[x].upper_bound(make_pair(y,maxn));
		for(set< pair<int,int> >::iterator it=T[x].begin();it!=last;it++) ret.push_back(it->second);
		T[x].erase(T[x].begin(),last);
		x-=lowbit(x);
	}
	return ret;
}

int dist[maxn],fa[maxn],path[maxn];
void Bfs()
{
	memset(fa,-1,sizeof fa);
	memset(dist,-1,sizeof dist);
	vector<int> u=Query(M[0],0);
	queue<int> Q;
	for(unsigned i=0;i<u.size();i++) Q.push(u[i]),vis[u[i]]=1,dist[u[i]]=1;
	while(!Q.empty())
	{
		int id=Q.front(); Q.pop();
		vector<int> v=Query(M[c[id]],d[id]);
		for(unsigned i=0;i<v.size();i++)
		{
			if(vis[v[i]])continue;
			vis[v[i]]=1;
			dist[v[i]]=dist[id]+1;
			fa[v[i]]=id;
			Q.push(v[i]);
		}
	}
}

void Initialize()
{
	fo(i,0,n-1) scanf("%d%d%d%d",a+i,b+i,c+i,d+i),V.push_back(a[i]),V.push_back(c[i]);
	sort(V.begin(),V.end());
	m=0;
	M[V[0]]=++m;
	for(unsigned i=1;i<V.size();i++)
		if(V[i]>V[i-1])M[V[i]]=++m;
	fo(i,0,m)T[i].clear();
	fo(i,0,n-1)Modify(M[a[i]],make_pair(b[i],i));
}

void Print()
{
	printf("%d\n",dist[n-1]);
	if(dist[n-1]==-1)return;
	else
	{
		int cnt=0,u=n-1;
		while(u!=-1)
		{
			path[cnt++]=u+1;
			u=fa[u];
		}
		printf("%d",path[cnt-1]);
		for(int i=cnt-2;i>=0;i--)printf(" %d",path[i]);
		printf("\n");
	}
}

int main()
{
	while(~scanf("%d",&n))
	{
		Initialize();
		Bfs();
		Print();
	}
	return 0;
}
