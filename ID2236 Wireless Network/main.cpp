/*
 Description

An earthquake takes place in Southeast Asia. The ACM (Asia Cooperated Medical team) have set up a wireless network with the lap computers, but an unexpected aftershock attacked, all computers in the network were all broken. The computers are repaired one by one, and the network gradually began to work again. Because of the hardware restricts, each computer can only directly communicate with the computers that are not farther than d meters from it. But every computer can be regarded as the intermediary of the communication between two other computers, that is to say computer A and computer B can communicate if computer A and computer B can communicate directly or there is a computer C that can communicate with both A and B.

In the process of repairing the network, workers can take two kinds of operations at every moment, repairing a computer, or testing if two computers can communicate. Your job is to answer all the testing operations.
Input

The first line contains two integers N and d (1 <= N <= 1001, 0 <= d <= 20000). Here N is the number of computers, which are numbered from 1 to N, and D is the maximum distance two computers can communicate directly. In the next N lines, each contains two integers xi, yi (0 <= xi, yi <= 10000), which is the coordinate of N computers. From the (N+1)-th line to the end of input, there are operations, which are carried out one by one. Each line contains an operation in one of following two formats:
1.	"O p" (1 <= p <= N), which means repairing computer p.
2.	"S p q" (1 <= p, q <= N), which means testing whether computer p and q can communicate.

The input will not exceed 300000 lines.
Output

For each Testing operation, print "SUCCESS" if the two computers can communicate, or "FAIL" if not.
Sample Input

4 1
0 1
0 2
0 3
0 4
O 1
O 2
O 4
S 1 4
O 3
S 1 4

 用并查集来保存电脑互相的连通情况。
每次修好电脑后，将它可以通信的电脑(距离满足且已修好)与它进行连通。
 */

#include <cstdio>
#include <iostream>
#include <utility>
#include <cstring>
#include <vector>

#define DIST(a,b) (((a.first - b.first) * (a.first - b.first)) + ((a.second - b.second) * (a.second - b.second)))

using namespace std;

class UnionFind
{
private:
    int parent[1005];
    int rank[1005];
public:
    UnionFind();
    int find(int a);
    bool same(int a ,int b);
    void unite(int a,int b);
};

UnionFind::UnionFind() {
    for(int i = 0;i<1005;i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}

int UnionFind::find(int x) {
    if(x == parent[x])
        return x;
    else
        return parent[x] = find(parent[x]);
}


bool UnionFind::same(int a, int b) {
    return find(a) == find(b);
}


void UnionFind::unite(int a, int b) {
    int c = find(b);
    parent[c] = a;
    return;
}

using namespace std;

pair<int,int> computers[1005];
bool repaired[1005];
vector<int> neighbor[1005];
int main()
{
    int N,D;
    scanf("%d%d",&N,&D);
    D = D*D;
    for(int i = 1;i<=N;i++)
        scanf("%d %d\n",&computers[i].first,&computers[i].second);

    for(int i=1; i<=N; i++)
        for(int j=i+1; j<=N; j++)
        {
            if( DIST(computers[i],computers[j]) <= D)
            {
                neighbor[j].push_back(i);
                neighbor[i].push_back(j);
            }
        }

    char operation[2];


    UnionFind union_set = UnionFind();
    memset(repaired,0,sizeof(repaired));
    while(~scanf("%s", operation))
    {

        if(operation[0] == 'O')
        {
            int a;
            scanf("%d",&a);
            cin.get();
            repaired[a] = true;
            for(int i = 0;i<neighbor[a].size();i++)
            {
                if(repaired[neighbor[a][i]])
                    union_set.unite(a,neighbor[a][i]);
            }
        }
        else if(operation[0] == 'S')
        {
            int a,b;
            scanf("%d%d",&a,&b);
            if(union_set.same(a,b))
                printf("SUCCESS\n");
            else
                printf("FAIL\n");
        }
    }

    return 0;
}