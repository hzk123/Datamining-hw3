#include <bits/stdc++.h>
#define eps 1e-4
#define pid pair<int,double>

using namespace std;

const double df = 0.15;
struct Edge
{
	int to;
	int next;
}edge[2333];
int n;
int head[2333],cnt;

double simrank[2333][2333];
double next_simrank[2333][2333];
int in[2333];
const double C = 0.85;

void init()
{
	cnt = 0;
	n = 0;
	memset(in,0,sizeof in);
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
		add(v,u),  // get inverse edge
		in[u]++;
		n = max(n , max(u,v));
}


void solve() //get  simrank martix
{

	double maxdiff = 2333333;
	for (int i = 1 ; i <= n ; i++)
		for (int j = 1 ; j <= n ; j++)
			if (i == j )
				simrank[i][j] = 1 ;
			else
				simrank[i][j] = 0;
	for (; maxdiff > 1e-10 ;)
	{
		for (int u = 1 ; u <= n ; u++)
			for (int v = 1 ; v <= n ; v++)
			if (u != v)
			{
				double sum = 0;
				for (int i = head[u] ; ~i ; i = edge[i].next)
					for (int j = head[v]; ~j ; j = edge[j].next)
						{
							//cout << u << "  " << v << " " << edge[i].to << " " << edge[j].to << endl;
							sum += simrank[edge[i].to][edge[j].to];
						}
				//cout << u << " " << v<< " " <<sum << endl;
				if (in[u] * in[v])
					next_simrank[u][v] = ( C / (in[u] * in[v] ) ) * sum;
				else
					next_simrank[u][v] = 0;
			}
			else
				next_simrank[u][v] = 1;
		maxdiff = 0;
		for (int u = 1 ; u <= n ; u++)
			for (int v = 1 ; v <= n ; v++)
				maxdiff = max( maxdiff , abs(simrank[u][v] - next_simrank[u][v])),
				simrank[u][v] = next_simrank[u][v];

		//cout << maxdiff << endl;
	}

}

struct r
{
	int x,y;
	double simrank;
}rk[2333*2333];
bool cmp(r a,r b)
{
	return a.simrank > b.simrank;
}
void output()
{
	int tot = 0;
	for (int i = 1 ; i <= n ; i++)
		for (int j = 1 ; j <= n ; j++)
			if (i!=j)
			rk[++tot].x = i,rk[tot].y=j,rk[tot].simrank = simrank[i][j];
	sort(rk+1,rk+1+tot,cmp);

    printf("all result that simrank > 0\n");
	for (int i = 1 ; i <= tot; i++)
    {
        if (rk[i].simrank > eps )
		printf("(%d,%d) : simrank = %.4f\n",rk[i].x,rk[i].y,rk[i].simrank);
    }
}
int main(int argc,char** argv)
{
	get_graph(argv[1]);
	solve();
	output();
	return 0;
}
