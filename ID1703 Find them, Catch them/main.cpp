/*
Description

The police office in Tadu City decides to say ends to the chaos, as launch actions to root up the TWO gangs in the city, Gang Dragon and Gang Snake. However, the police first needs to identify which gang a criminal belongs to. The present question is, given two criminals; do they belong to a same clan? You must give your judgment based on incomplete information. (Since the gangsters are always acting secretly.)

Assume N (N <= 10^5) criminals are currently in Tadu City, numbered from 1 to N. And of course, at least one of them belongs to Gang Dragon, and the same for Gang Snake. You will be given M (M <= 10^5) messages in sequence, which are in the following two kinds:

1. D [a] [b]
where [a] and [b] are the numbers of two criminals, and they belong to different gangs.

2. A [a] [b]
where [a] and [b] are the numbers of two criminals. This requires you to decide whether a and b belong to a same gang.
Input

The first line of the input contains a single integer T (1 <= T <= 20), the number of test cases. Then T cases follow. Each test case begins with a line with two integers N and M, followed by M lines each containing one message as described above.
Output

For each message "A [a] [b]" in each case, your program should give the judgment based on the information got before. The answers might be one of "In the same gang.", "In different gangs." and "Not sure yet."
Sample Input

1
5 5
A 1 2
D 1 2
A 1 2
D 2 4
A 1 4
Sample Output

Not sure yet.
In different gangs.
In the same gang.

 使用并查集，对于每个案件x，分为x-A,x-B;
 当遇到D信息时，合并(x-A,y-B),(x-B,y-A)
 当检查时
 如果x-A与y-A在同一集合时，表明属于同一集合
 如果x-A与y-B在同一集合时，表明不属于同一集合
 否则，还不知道是否属于统一集合
 */

#include <cstdio>
#define NUM 200010
#define DIFF 100001

class UnionFind{
public:
    UnionFind();
    int find(int x);
    bool same(int x,int y);
    void unite(int x,int y);
private:
    int parent[NUM];
    int rank[NUM];
};

UnionFind::UnionFind() {
    for(int i = 0;i<NUM;i++)
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

bool UnionFind::same(int x, int y) {
    return find(x) == find(y);
}

void UnionFind::unite(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y)
        return;
    else if(rank[x]<rank[y])
        parent[x] = y;
    else
    {
        parent[y] = x;
        if(rank[x] == rank[y])
            rank[x]++;
    }

    return;
}


int main() {
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        int N, M, first, second;
        char info[2];
        scanf("%d%d", &N, &M);
        UnionFind union_set = UnionFind();
        for (int i = 0; i < M; i++) {
            scanf("%s", info);
            if ( info[0] == 'D' ) {
                scanf("%d%d", &first, &second);
                union_set.unite(first, second + DIFF);
                union_set.unite(second, first + DIFF);
            } else {
                scanf("%d%d", &first, &second);
                if ( union_set.same(first, second))
                    printf("In the same gang.\n");
                else if (union_set.same(first, second + DIFF))
                    printf("In different gangs.\n");
                else
                    printf("Not sure yet.\n");
            }
        }

    }
    return 0;
}