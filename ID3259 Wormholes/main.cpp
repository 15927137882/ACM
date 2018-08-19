/*
 * Description

While exploring his many farms, Farmer John has discovered a number of amazing wormholes. A wormhole is very peculiar because it is a one-way path that delivers you to its destination at a time that is BEFORE you entered the wormhole! Each of FJ's farms comprises N (1 ≤ N ≤ 500) fields conveniently numbered 1..N, M (1 ≤ M ≤ 2500) paths, and W (1 ≤ W ≤ 200) wormholes.

As FJ is an avid time-traveling fan, he wants to do the following: start at some field, travel through some paths and wormholes, and return to the starting field a time before his initial departure. Perhaps he will be able to meet himself :) .

To help FJ find out whether this is possible or not, he will supply you with complete maps to F (1 ≤ F ≤ 5) of his farms. No paths will take longer than 10,000 seconds to travel and no wormhole can bring FJ back in time by more than 10,000 seconds.

Input

Line 1: A single integer, F. F farm descriptions follow.
Line 1 of each farm: Three space-separated integers respectively: N, M, and W
Lines 2..M+1 of each farm: Three space-separated numbers (S, E, T) that describe, respectively: a bidirectional path between S and E that requires T seconds to traverse. Two fields might be connected by more than one path.
Lines M+2..M+W+1 of each farm: Three space-separated numbers (S, E, T) that describe, respectively: A one way path from S to E that also moves the traveler back T seconds.
Output

Lines 1..F: For each farm, output "YES" if FJ can achieve his goal, otherwise output "NO" (do not include the quotes).
Sample Input

2
3 3 1
1 2 2
1 3 4
2 3 1
3 1 3
3 2 1
1 2 3
2 3 4
3 1 8
Sample Output

NO
YES
Hint

For farm 1, FJ cannot travel back in time.
For farm 2, FJ could travel back in time by the cycle 1->2->3->1, arriving back at his starting location 1 second before he leaves. He could start from anywhere on the cycle to accomplish this.

 问题本质是判定图中是否有负圈，使用Bellman-Ford算法可以求解，复杂度为O(E*V)
 Floyd-Warshall也可以求解，复杂度为O(V^3)
 */


#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>


int dp[505];

struct edge{
    int start,end,cost;
    edge(int _start,int _end,int _cost) : start(_start), end(_end), cost(_cost){}

};

std::vector<edge> e;

int main()
{
    int farms;
    scanf("%d",&farms);
    while(farms--)
    {
        memset(dp,0,sizeof(dp));
        e.clear();
        int N,M,W;
        scanf("%d%d%d",&N,&M,&W);

        for(int i = 0;i<M; i++)
        {
            int start,end,cost;
            scanf("%d%d%d",&start,&end,&cost);
                e.push_back(edge(start,end,cost));
                e.push_back(edge(end,start,cost));
        }
        for(int i = 0;i<W;i++)
        {
            int start,end,cost;
            scanf("%d%d%d",&start,&end,&cost);
            e.push_back(edge(start,end,-cost));
        }

        bool flag = false;
        for(int i = 0;i<N;i++)
        {
            for(int j = 0;j<e.size();j++)
            {
                if(dp[e[j].end] > dp[e[j].start] + e[j].cost)
                {
                    dp[e[j].end] = dp[e[j].start] + e[j].cost;
                    if(i == N-1) {
                        flag = true;
                        break;
                    }
                }
            }
        }

        if(!flag)
            printf("NO\n");
        else
            printf("YES\n");
    }

    return 0;
}