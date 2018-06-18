/*
Description

Farmer John went to cut some wood and left N (2 ≤ N ≤ 100,000) cows eating the grass, as usual. When he returned, he found to his horror that the cluster of cows was in his garden eating his beautiful flowers. Wanting to minimize the subsequent damage, FJ decided to take immediate action and transport each cow back to its own barn.

Each cow i is at a location that is Ti minutes (1 ≤ Ti ≤ 2,000,000) away from its own barn. Furthermore, while waiting for transport, she destroys Di (1 ≤ Di ≤ 100) flowers per minute. No matter how hard he tries, FJ can only transport one cow at a time back to her barn. Moving cow i to its barn requires 2 × Ti minutes (Ti to get there and Ti to return). FJ starts at the flower patch, transports the cow to its barn, and then walks back to the flowers, taking no extra time to get to the next cow that needs transport.

Write a program to determine the order in which FJ should pick up the cows so that the total number of flowers destroyed is minimized.

Input

Line 1: A single integer N
Lines 2..N+1: Each line contains two space-separated integers, Ti and Di, that describe a single cow's characteristics
Output

Line 1: A single integer that is the minimum number of destroyed flowers
Sample Input

6
3 1
2 5
2 3
3 2
4 1
1 6
Sample Output

86
Hint

FJ returns the cows in the following order: 6, 2, 3, 4, 1, 5. While he is transporting cow 6 to the barn, the others destroy 24 flowers; next he will take cow 2, losing 28 more of his beautiful flora. For the cows 3, 4, 1 he loses 16, 12, and 6 flowers respectively. When he picks cow 5 there are no more cows damaging the flowers, so the loss for that cow is zero. The total flowers lost this way is 24 + 28 + 16 + 12 + 6 = 86.
贪心：
选择策略,
1 在二个中间选择之中,能根据time/eat小的那个为最优解
证明:
二个羊中 A,B,属性分别为分别为eatA,timeA,eatB,timeB
选A的时候损失timeA*eatB
选B的时候损失timeB*eatA
双方同除以eatA*eatB.
令time/eat为一个羊的比率x
可以证明x小的那个为最优解.

定理,如果有一个选择在n个选择中是最优的,那么(在包含这个选择的)n-1个选择中也是最优的,

逆否命题,如果一个选择在n-1个选择中不是最优的,那么在n个选择中也不是最优的.

推论,如果一个选择在2个选择中不是最优的,那么在n个选择中也不是最优的

所以将羊按照比率x排序,可以找到一个羊A在与其它所有羊比较的过程中都是最优的,

或者说其它n-1的羊在与别的羊做两个之间选一个的选择的时候不是最优的,所有这n-1个羊不是最优解的.
所以羊A是n头羊中最优解

(这个证明先令x的值都是不同的,对x相同的证明只需要将最优,改成没有更优即可 ^_^ )
*/

#include <cstdio>
#include <utility>
#include <algorithm>

typedef long long ll;

using namespace std;

int N;

bool cmp(pair<int,int> a,pair<int,int> b)
{
    return (float)a.first / (float)a.second <= (float)b.first / (float)b.second;
}

int main()
{
    scanf("%d",&N);
    pair<int,int> cow[N];
    ll sum = 0;
    for(int i = 0;i<N;i++)
    {
        scanf("%d%d",&cow[i].first,&cow[i].second);
        sum += cow[i].second;
    }


    sort(cow,cow+N,cmp);
    ll ans = 0;
    for(int i = 0;i<N;i++)
    {
        sum -= cow[i].second;
        ans += 2 * sum * cow[i].first;
    }

    printf("%I64d\n",ans);

    return 0;
}
