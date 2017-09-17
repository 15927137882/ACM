/*
Description
Bessie has moved to a small farm and sometimes enjoys returning to visit one of her best friends.
She does not want to get to her old home too quickly, because she likes the scenery along the way.
She has decided to take the second-shortest rather than the shortest path. She knows there must be some second-shortest path.
The countryside consists of R (1 ≤ R ≤ 100,000) bidirectional roads, each linking two of the N (1 ≤ N ≤ 5000) intersections, conveniently numbered 1..N.
Bessie starts at intersection 1, and her friend (the destination) is at intersection N.
The second-shortest path may share roads with any of the shortest paths, and it may backtrack i.e., use the same road or intersection more than once.
The second-shortest path is the shortest path whose length is longer than the shortest path(s) (i.e., if two or more shortest paths exist,
the second-shortest path is the one whose length is longer than those but no longer than any other path).

Input
Line 1: Two space-separated integers: N and R
Lines 2..R+1: Each line contains three space-separated integers: A, B, and D that describe a road that
connects intersections A and B and has length D (1 ≤ D ≤ 5000)

Output
Line 1: The length of the second shortest path between node 1 and node N

Sample Input
4 4
1 2 100
2 4 200
2 3 250
3 4 100

Sample Output
450

Hint
Two routes: 1 -> 2 -> 4 (length 100+200=300) and 1 -> 2 -> 3 -> 4 (length 100+250+100=450)
*/


#include <iostream>
#include <vector>
#include <limits>
#include <queue>


using namespace std;

typedef pair<int,int> P;

struct edge
{
    int to,cost;
    edge(int to_, int cost_) : to(to_),cost(cost_) {}
};

struct table_head
{
    vector<edge> adjacency_edge;
};

int N,R;
int *dist,*dist2;
int INF = (numeric_limits<int>::max)();
vector<table_head> adjacency_list;

void inatial_adjacency_list(int N);//初始化邻接表头函数

int main()
{
    priority_queue< P,vector<P>,greater<P> > que;    //当前可以更新的点(最短/次短距离，顶点编号）
    cin>>N>>R;
    inatial_adjacency_list(N);  //初始化邻接表头

    dist = new int[N];
    dist2 = new int[N];

    for(int i = 0;i<R;i++)     //邻接表构造
    {
        int A,B,D;
        cin>>A>>B>>D;
        A--;
        B--;
        edge temp(B,D);
        adjacency_list[A].adjacency_edge.push_back(temp);
        temp.to = A;
        adjacency_list[B].adjacency_edge.push_back(temp);
    }

    /* 初始化结果数组 */
    fill(dist,dist+N,INF);
    fill(dist2,dist2+N,INF);
    dist[0] = 0;
    que.push(P(0,0));

    while(!que.empty())
    {
        P p = que.top();
        que.pop();
        int v = p.second;
        int d = p.first;
        if(dist2[v] < d) continue;  //不是次短和最短信息，就不更新
        for(int i = 0;i<(int)adjacency_list[v].adjacency_edge.size();i++)
        {
            edge &e = adjacency_list[v].adjacency_edge[i];
            int d2 = d + e.cost;
            if(dist[e.to] > d2)     //如果现在的距离信息比原始距离信息短，更新
            {
                swap(dist[e.to],d2);
                que.push(P(dist[e.to],e.to));
            }
            if(d2 < dist2[e.to] && dist[e.to] < d2) //如果现在的距离信息比次短距离信息短，更新
            {
                dist2[e.to] = d2;
                que.push(P(dist2[e.to],e.to));
            }
        }
    }

    /*
    for(int i = 0;i<N;i++)      //结果数组输出
        cout<<dist[i]<<' ';
    cout<<endl;
    for(int i = 0;i<N;i++)
        cout<<dist2[i]<<' ';
    cout<<endl;
    */

    /*for(int i = 0;i<N;i++)     //邻接表输出
    {
        for(int j = 0;j<(int)adjacency_list[i].adjacency_edge.size();j++)
            cout<<i<<" to "<<adjacency_list[i].adjacency_edge[j].to<<" "
                <<adjacency_list[i].adjacency_edge[j].cost<<endl;
    }
    */

    cout<<dist2[N-1]<<endl;
    delete [] dist;
    delete [] dist2;
    return 0;
}


void inatial_adjacency_list(int N)
{
        for(int i = 0;i<N;i++)
        {
            table_head temp;
            adjacency_list.push_back(temp);
        }
}
