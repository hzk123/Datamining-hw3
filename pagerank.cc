#include <bits/stdc++.h>
#define eps 1e-6
#define pid pair<int,double>

using namespace std;
const double d = 0.15;
struct Edge
{
	int to;
	int next;
}edge[200020];
int n;
int head[200020],cnt;
double pagerank[200020] , next_pagerank[200020];
int out[200020];
void init()
{
	cnt = 0;
	n = 0;
	memset(out,0,sizeof out);
	memset(head,-1,sizeof head);
}

void add(int u , int v)
{
	edge[cnt].next = head[u];
	edge[cnt].to = v;
	head[u] = cnt++;
	out[u]++;
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


void solve() // use iteration to calculate pagerank
{
	double maxdiff = 233333;
	for (int u = 1 ; u <= n ; u++)
		pagerank[u] = 1;

	while ( maxdiff > eps)
	{
		for (int u = 1 ; u <= n ; u++)
			next_pagerank[u] = 0;
		for (int u = 1 ; u <= n ; u++)
			{
				for (int i = head[u];~i;i=edge[i].next)
				{
					int v = edge[i].to;
					next_pagerank[v] += pagerank[u]/out[u] ;
				}
			}
		maxdiff = 0;
		for (int u = 1 ; u <= n ; u++)
			maxdiff = max(maxdiff , abs(pagerank[u] - ((1 - d ) + d * next_pagerank[u]))),
			pagerank[u] = (1 - d ) + d * next_pagerank[u];
	    printf("%f\n",maxdiff);
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
		rk[i] = make_pair(i,pagerank[i]);
	sort(rk+1,rk+1+n,cmp);

	for (int i = 1 ; i <= n ; i++)
		printf("node%d:%f\n",rk[i].first,rk[i].second);

}
int main(int argc,char** argv)
{
	get_graph(argv[1]);
	solve();
	output();
	return 0;
}
