/*
 * Description

One cow from each of N farms (1 ≤ N ≤ 1000) conveniently numbered 1..N is going to attend the big cow party to be held at farm #X (1 ≤ X ≤ N). A total of M (1 ≤ M ≤ 100,000) unidirectional (one-way roads connects pairs of farms; road i requires Ti (1 ≤ Ti ≤ 100) units of time to traverse.

Each cow must walk to the party and, when the party is over, return to her farm. Each cow is lazy and thus picks an optimal route with the shortest time. A cow's return route might be different from her original route to the party since roads are one-way.

Of all the cows, what is the longest amount of time a cow must spend walking to the party and back?

Input

Line 1: Three space-separated integers, respectively: N, M, and X
Lines 2..M+1: Line i+1 describes road i with three space-separated integers: Ai, Bi, and Ti. The described road runs from farm Ai to farm Bi, requiring Ti time units to traverse.
Output

Line 1: One integer: the maximum of time any one cow must walk.
Sample Input

4 8 2
1 2 4
1 3 2
1 4 7
2 1 1
2 3 5
3 1 2
3 4 4
4 2 3
Sample Output

10
Hint

Cow 4 proceeds directly to the party (3 units) and returns via farms 1 and 3 (7 units), for a total of 10 time units.

使用Floyd-Warshall算法会超时，采用Dijkstra算法，
 第一次以X为起点，计算X到其他点的最短距离，
 第二次将图的方向置反，可以计算其他点到X的最短距离
 */


#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

struct edge{
    int end,cost;
    edge(int _end,int _cost) : end(_end),cost(_cost){}
};

using namespace std;

vector< vector<edge> > Graph(1005);
vector<vector<edge> > InverseGraph(1005);
typedef  pair<int,int> node;
int d[1005],rd[1005];

void dijkstra(int start)
{
    memset(d,0x3f,sizeof(d));
    d[start] = 0;
    priority_queue< node,vector<node>,greater<node> > que;
    que.push(node(start,0));
    while(!que.empty())
    {
        node tmp = que.top();
        que.pop();
        int point = tmp.first;
        if(tmp.second > d[point]) continue;
        for(int i = 0;i<Graph[point].size();i++)
        {
            edge e = Graph[point][i];
            if(d[point] + e.cost < d[e.end])
            {
                d[e.end] = d[point] + e.cost;
                que.push(node(e.end,d[e.end]));
            }
        }
    }
}

int main()
{
    int N,M,X;
    scanf("%d%d%d",&N,&M,&X);
    for(int i = 0;i<M;i++)
    {
        int start,end,cost;
        scanf("%d%d%d",&start,&end,&cost);
        Graph[start].push_back(edge(end,cost));
        InverseGraph[end].push_back(edge(start,cost));
    }

    dijkstra(X);
    memcpy(rd,d,sizeof(d));

    Graph = InverseGraph;
    dijkstra(X);

    for(int i = 1;i<=N;i++)
        d[i] += rd[i];


    printf("%d\n",*max_element(d+1,d+N+1));

    return 0;
}