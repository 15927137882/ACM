/*
 * Description

Bessie has been hired to build a cheap internet network among Farmer John's N (2 <= N <= 1,000) barns that are conveniently numbered 1..N. FJ has already done some surveying, and found M (1 <= M <= 20,000) possible connection routes between pairs of barns. Each possible connection route has an associated cost C (1 <= C <= 100,000). Farmer John wants to spend the least amount on connecting the network; he doesn't even want to pay Bessie.

Realizing Farmer John will not pay her, Bessie decides to do the worst job possible. She must decide on a set of connections to install so that (i) the total cost of these connections is as large as possible, (ii) all the barns are connected together (so that it is possible to reach any barn from any other barn via a path of installed connections), and (iii) so that there are no cycles among the connections (which Farmer John would easily be able to detect). Conditions (ii) and (iii) ensure that the final set of connections will look like a "tree".
Input

* Line 1: Two space-separated integers: N and M

* Lines 2..M+1: Each line contains three space-separated integers A, B, and C that describe a connection route between barns A and B of cost C.
Output

* Line 1: A single integer, containing the price of the most expensive tree connecting all the barns. If it is not possible to connect all the barns, output -1.
Sample Input

5 8
1 2 3
1 3 7
2 3 10
2 4 4
2 5 8
3 4 6
3 5 2
4 5 17
Sample Output

42
Hint

OUTPUT DETAILS:

The most expensive tree has cost 17 + 8 + 10 + 7 = 42. It uses the following connections: 4 to 5, 2 to 5, 2 to 3, and 1 to 3.

 Kruskal算法求解最大生成树，
 */


#include <cstdio>
#include <algorithm>

using namespace std;

int par[1005];
int height[1005];

struct edge{
    int a,b,cost;
};



bool comp(edge a,edge b)
{
    return a.cost > b.cost;
}

edge E[20005];

void init(int n)
{
    for(int i = 1; i<=n;i++)
    {
        par[i] = i;
        height[i] = 1;
    }
}

int find(int a)
{
    if(par[a] == a)
        return a;
    else
        return par[a] = find(par[a]);
}

bool same(int a ,int b)
{
    return find(a) == find(b);
}

void unite(int a,int b)
{
    a = find(a);
    b = find(b);
    if(a == b) return;
    else
    {
        if(height[a] > height[b])
            par[b] = a;
        else
        {
            par[a] = b;
            if(height[a] == height[b])
                height[b]++;
        }
    }
}

int main()
{
    int N,M;
    scanf("%d%d",&N,&M);
    for(int i = 0;i<M;i++)
        scanf("%d%d%d",&E[i].a,&E[i].b,&E[i].cost);

    int in_trees = 1;
    sort(E,E+M,comp);

    int ans = 0;
    init(N);
    for(int i = 0;i<M;i++)
    {
        if(!same(E[i].a,E[i].b))
        {
            unite(E[i].a,E[i].b);
            ans += E[i].cost;
            in_trees++;
        }
    }

    if(in_trees < N) printf("-1\n");
    else printf("%d\n",ans);

    return 0;
}