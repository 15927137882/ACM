/*
 * Description

The cows have run out of hay, a horrible event that must be remedied immediately. Bessie intends to visit the other farms to survey their hay situation. There are N (2 <= N <= 2,000) farms (numbered 1..N); Bessie starts at Farm 1. She'll traverse some or all of the M (1 <= M <= 10,000) two-way roads whose length does not exceed 1,000,000,000 that connect the farms. Some farms may be multiply connected with different length roads. All farms are connected one way or another to Farm 1.

Bessie is trying to decide how large a waterskin she will need. She knows that she needs one ounce of water for each unit of length of a road. Since she can get more water at each farm, she's only concerned about the length of the longest road. Of course, she plans her route between farms such that she minimizes the amount of water she must carry.

Help Bessie know the largest amount of water she will ever have to carry: what is the length of longest road she'll have to travel between any two farms, presuming she chooses routes that minimize that number? This means, of course, that she might backtrack over a road in order to minimize the length of the longest road she'll have to traverse.
Input

* Line 1: Two space-separated integers, N and M.

* Lines 2..1+M: Line i+1 contains three space-separated integers, A_i, B_i, and L_i, describing a road from A_i to B_i of length L_i.
Output

* Line 1: A single integer that is the length of the longest road required to be traversed.
Sample Input

3 3
1 2 23
2 3 1000
1 3 43
Sample Output

43
 求最小连通图，使用Kruskal算法，并保存搜索过程中的最大边权值
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
    return a.cost < b.cost;
}

edge E[10005];

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

    sort(E,E+M,comp);

    int ans = 0;
    init(N);
    for(int i = 0;i<M;i++)
    {
        if(!same(E[i].a,E[i].b))
        {
            unite(E[i].a,E[i].b);
            ans = max(ans,E[i].cost);
        }
    }

    printf("%d\n",ans);

    return 0;
}