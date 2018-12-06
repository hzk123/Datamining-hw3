#include <bits/stdc++.h>
#define eps 1e-6
#define pid pair<int,double>

using namespace std;

const double df = 0.15;
struct Edge
{
	int to;
	int next;
}edge[200020];
int n;
int head[200020],cnt;

double a[200020] , next_a[200020];
double h[200020] , next_h[200020];

void init()
{
	cnt = 0;
	n = 0;
	memset(head,-1,sizeof head);
}

void add(int u , int v)
{
	edge[cnt].next = head[u];
	edge[cnt].to = v;
	head[u] = cnt++;
}

void get_graph(char* path)
{
	freopen(path,"r",stdin);
	init();
	int u , v;
	while(scanf("%d,%d",&u,&v)!=EOF) 
		add(u,v),
		n = max(n , max(u,v));
}


void solve() // use iteration to calculate hits
{
	double maxdiff = 233333;
	for (int u = 1 ; u <= n ; u++)
		a[u] = 1,
		h[u] = 1;

	while ( maxdiff > eps)
	{
		for (int u = 1 ; u <= n ; u++)
			next_a[u] = next_h[u] = 0;
		for (int u = 1 ; u <= n ; u++)
			{
				int count = 0;
				for (int i = head[u];~i;i=edge[i].next) // calculate every  edge from node u
				{
					int v = edge[i].to;
					next_a[v] += h[u]; // calculate next generation a
				       	next_h[u] += a[v]; // same
				}
			}
		double mxa = 0 ,mxh = 0;
		for (int u = 1 ; u <= n ; u++) // find maxa and maxh
			mxa = max(mxa,next_a[u]),
			mxh = max(mxh,next_h[u]);
		
		maxdiff = 0;
		for (int u = 1 ; u <= n ; u++) //normalize
			maxdiff = max(maxdiff , max( abs(a[u] - next_a[u] / mxa) , abs(h[u] - next_h[u] / mxh))),
			a[u] = next_a[u] / mxa,
			h[u] = next_h[u] / mxh;	
	}	
}

pid rk[200020];
bool cmp(pid a,pid b)
{
	return a.second > b.second;
}
void output()
{
	for (int i = 1 ; i <= n ; i++)
		rk[i] = make_pair(i,a[i]);	
	sort(rk+1,rk+1+n,cmp);

	for (int i = 1 ; i <= n ; i++)
		printf("node%d a = %f\n",rk[i].first,rk[i].second);
	
	for (int i = 1 ; i <= n ; i++)
		rk[i] = make_pair(i,h[i]);
	sort(rk+1,rk+1+n,cmp);

	for (int i = 1 ; i <= n ; i++)
		printf("node%d h = %f\n",rk[i].first,rk[i].second);
}
int main(int argc,char** argv)
{
	get_graph(argv[1]);
	solve();	
	output();
	return 0;
}
