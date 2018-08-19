/*
 * Description

        Farmer John has been elected mayor of his town! One of his campaign promises was to bring internet connectivity to all farms in the area. He needs your help, of course.
Farmer John ordered a high speed connection for his farm and is going to share his connectivity with the other farmers. To minimize cost, he wants to lay the minimum amount of optical fiber to connect his farm to all the other farms.
Given a list of how much fiber it takes to connect each pair of farms, you must find the minimum amount of fiber needed to connect them all together. Each farm must connect to some other farm such that a packet can flow from any one farm to any other farm.
The distance between any two farms will not exceed 100,000.
Input

        The input includes several cases. For each case, the first line contains the number of farms, N (3 <= N <= 100). The following lines contain the N x N conectivity matrix, where each element shows the distance from on farm to another. Logically, they are N lines of N space-separated integers. Physically, they are limited in length to 80 characters, so some lines continue onto others. Of course, the diagonal will be 0, since the distance from farm i to itself is not interesting for this problem.
Output

        For each case, output a single integer length that is the sum of the minimum length of fiber required to connect the entire set of farms.
Sample Input

4
0 4 9 21
4 0 8 17
9 8 0 16
21 17 16 0
Sample Output

28
 Prim算法求最小生成树
*/


#include <cstdio>
#include <cstring>
#include <iostream>


int dist[105][105];
int min_cost[105];
bool used[105];

using namespace std;
int main()
{
    int N;
    while(cin>>N) {
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                scanf("%d", &dist[i][j]);

        memset(min_cost, 0x3f, sizeof(min_cost));
        memset(used, 0, sizeof(used));

        min_cost[1] = 0;

        int ans = 0;
        while (true) {
            int v = -1;
            for (int i = 1; i <= N; i++) {
                if ( !used[i] && (v == -1 || min_cost[v] > min_cost[i]))
                    v = i;
            }
            if ( v == -1 ) break;
            used[v] = true;
            ans += min_cost[v];
            for (int i = 1; i <= N; i++)
                min_cost[i] = min(min_cost[i], dist[v][i]);
            for(int i = 1;i<=N;i++)
                cout<<min_cost[i];
            cout<<endl;
        }
        printf("%d\n",ans);
    }

    return 0;
}