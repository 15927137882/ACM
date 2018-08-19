/*
 * Description

Every year the cows hold an event featuring a peculiar version of hopscotch that involves carefully jumping from rock to rock in a river. The excitement takes place on a long, straight river with a rock at the start and another rock at the end, L units away from the start (1 ≤ L ≤ 1,000,000,000). Along the river between the starting and ending rocks, N (0 ≤ N ≤ 50,000) more rocks appear, each at an integral distance Di from the start (0 < Di < L).

To play the game, each cow in turn starts at the starting rock and tries to reach the finish at the ending rock, jumping only from rock to rock. Of course, less agile cows never make it to the final rock, ending up instead in the river.

Farmer John is proud of his cows and watches this event each year. But as time goes by, he tires of watching the timid cows of the other farmers limp across the short distances between rocks placed too closely together. He plans to remove several rocks in order to increase the shortest distance a cow will have to jump to reach the end. He knows he cannot remove the starting and ending rocks, but he calculates that he has enough resources to remove up to M rocks (0 ≤ M ≤ N).

FJ wants to know exactly how much he can increase the shortest distance *before* he starts removing the rocks. Help Farmer John determine the greatest possible shortest distance a cow has to jump after removing the optimal set of M rocks.

Input

Line 1: Three space-separated integers: L, N, and M
Lines 2..N+1: Each line contains a single integer indicating how far some rock is away from the starting rock. No two rocks share the same position.
Output

Line 1: A single integer that is the maximum of the shortest distance a cow has to jump after removing M rocks
Sample Input

25 5 2
2
14
11
21
17
Sample Output

4
Hint

Before removing any rocks, the shortest jump was a jump of 2 from 0 (the start) to 2. After removing the rocks at 2 and 14, the shortest required jump is a jump of 4 (from 17 to 21 or from 21 to 25).
 同样使用二分搜索完成，注意要将头尾两个点也加入到数组中
 */

#include <cstdio>
#include <algorithm>

typedef long long LL;
LL L;
int N,M;
LL position[50016];

bool judge(LL x)
{
    int last = 0;
    for(int i = 1;i<N-M;i++)
    {
        int crt = last + 1;
        while(crt < N && position[crt] - position[last] < x)
            crt++;
        if(crt == N) return false;
        last = crt;
    }
    return true;
}

int main()
{
    scanf("%lld%d%d",&L,&N,&M);

    for(int i = 0;i<N;i++)
        scanf("%lld",&position[i]);

    position[N++] = 0;
    position[N++] = L;
    std::sort(position,position+N);
    LL lb,ub,mid;
    lb = 0;
    ub = L+1;

    while(ub - lb > 1)
    {
        mid = (ub + lb) / 2;
        if(judge(mid))
            lb = mid;
        else
            ub = mid;
    }
    printf("%lld\n",lb);

    return 0;
}