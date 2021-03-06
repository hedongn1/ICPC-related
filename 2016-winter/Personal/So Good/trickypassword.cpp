#include <map>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for (int i = a;i <= b;i ++)

using namespace std;

const int maxn = 100005;
int N,M,a[maxn],tot,size,num;
int rep[maxn<<1],f[75][maxn<<1],g[75][maxn];
map<int,int> H;

int Get(int v)
{
	if (!H.count(v)) H[v] = ++num, rep[num] = v;
	return H[v];
}

void Construct()
{
	tot = (int)(sqrt(N)*0.16)+1;
	size = N/tot;
	int st,en = 0;
	fo(i,1,tot)
	{
		st = en + 1;
		if (i == tot) en = N; else en = st + size - 1;
		fo(j,1,num) f[i][j] = f[i-1][j];
		fo(j,1,N) g[i][j] = g[i-1][j];
		fo(j,st,en) g[i][++f[i][a[j]]] ++;
	}
}

int main()
{
	scanf("%d",&N);
	fo(i,1,N) scanf("%d",&a[i]), a[i] = Get(a[i]);
	Construct();
	for (scanf("%d",&M);M;M --)
	{
		int op,x,y;
		scanf("%d%d%d",&op,&x,&y);
		int i = min((y-1)/size+1,tot);
		if (op == 1)
		{
			int ori = a[y];
			a[y] = Get(x);
			fo(j,i,tot) g[j][f[j][ori]--] --, g[j][++f[j][a[y]]] ++;
		} else
		{
			int cnt = f[i-1][a[y]],ans;
			fo(j,(i-1)*size+1,y) cnt += (a[j] == a[y]);
			if (x == 1) ans = rep[a[y]];
			else if ((x-1) & 1) ans = cnt;
			else
			{
				ans = g[i-1][cnt];
				fo(j,(i-1)*size+1,y) if (++f[i-1][a[j]] == cnt) ans ++;
				fo(j,(i-1)*size+1,y) f[i-1][a[j]] --;
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
