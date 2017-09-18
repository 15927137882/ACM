/*
Description
Windy has a country, and he wants to build an army to protect his country.
He has picked up N girls and M boys and wants to collect them to be his soldiers.
To collect a soldier without any privilege, he must pay 10000 RMB. There are some
relationships between girls and boys and Windy can use these relationships to reduce his cost.
If girl x and boy y have a relationship d and one of them has been collected, Windy can collect
the other one with 10000-d RMB. Now given all the relationships between girls and boys, your assignment
is to find the least amount of money Windy has to pay. Notice that only one relationship can be used when collecting one soldier.

Input
The first line of input is the number of test case.
The first line of each test case contains three integers, N, M and R.
Then R lines followed, each contains three integers xi, yi and di.
There is a blank line before each test case.

1 ≤ N, M ≤ 10000
0 ≤ R ≤ 50,000
0 ≤ xi < N
0 ≤ yi < M
0 < di < 10000

Output
For each test case output the answer in a single line.

Sample Input
2

5 5 8
4 3 6831
1 3 4583
0 0 6592
0 1 3063
3 3 4975
1 3 2049
4 2 2104
2 2 781

5 5 10
2 4 9820
3 2 6236
3 1 8864
2 4 8326
2 0 5156
2 0 1463
4 1 2439
0 4 4373
3 4 8889
2 4 3133

Sample Output
71071
54223
*/

#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;
struct edge
{
    int u,v,cost;
    edge(int u_ = -1,int v_ = -1,int cost_ = -1) : u(u_), v(v_), cost(cost_) {}
};

bool comp(const edge& e1,const edge& e2)
{
    return e1.cost <e2.cost;
}

int kruskal();
void init(int n);
int find(int x);
void unite(int x,int y);
bool same(int x,int y);

//并查集数据结构
const int MAX_N = 50050;
int par[3*MAX_N];
int rank_[3*MAX_N];


int N,M,R;  //男兵数，女兵数，边数
int V,E;    //统计图的点数与边数
edge *es;

int main()
{
    int Case;
    scanf("%d",&Case);

    while(Case--)
    {
        scanf("%d%d%d",&N,&M,&R);
        V = N+M;
        E = R;
        es = new edge[R];
        for(int i = 0;i<R;i++)
        {
            int x,y,d;
            scanf("%d%d%d",&x,&y,&d);
            es[i] = edge(x,N+y,-d);
        }

        cout<<10000*(N+M) + kruskal()<<endl;
        delete [] es;

    }

    return 0;
}

int kruskal()       //kruskal算法生成树或森林
{
    sort(es,es+E,comp);
    init(V);
    int res = 0;
    for(int i = 0;i<E;i++)
    {
        edge e = es[i];
        if(!same(e.u,e.v))
        {
            unite(e.u,e.v);
            res+=e.cost;
        }
    }
    return res;
}


//并查集
void init(int n)
{
    for(int i = 0;i<n;i++)
    {
        par[i] = i;
        rank_[i] = 0;
    }
}

int find(int x) //找到该元素的根
{
    if(par[x] == x) return x;
    else return par[x] = find(par[x]);  //迭代寻找该元素的父亲节点并进行路径压缩
}

void unite(int x,int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return;
    if(rank_[x]<rank_[y])   //平衡处理
        par[x] = y;
    else
    {
        par[y] = x;
        if(rank_[x] == rank_[y]) rank_[x]++;
    }
}

bool same(int x,int y)
{
    return find(x) == find(y);
}
