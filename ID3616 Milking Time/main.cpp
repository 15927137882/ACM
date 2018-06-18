/*
Description

Bessie is such a hard-working cow. In fact, she is so focused on maximizing her productivity that she decides to schedule her next N (1 ≤ N ≤ 1,000,000) hours (conveniently labeled 0..N-1) so that she produces as much milk as possible.

Farmer John has a list of M (1 ≤ M ≤ 1,000) possibly overlapping intervals in which he is available for milking. Each interval i has a starting hour (0 ≤ starting_houri ≤ N), an ending hour (starting_houri < ending_houri ≤ N), and a corresponding efficiency (1 ≤ efficiencyi ≤ 1,000,000) which indicates how many gallons of milk that he can get out of Bessie in that interval. Farmer John starts and stops milking at the beginning of the starting hour and ending hour, respectively. When being milked, Bessie must be milked through an entire interval.

Even Bessie has her limitations, though. After being milked during any interval, she must rest R (1 ≤ R ≤ N) hours before she can start milking again. Given Farmer Johns list of intervals, determine the maximum amount of milk that Bessie can produce in the N hours.

Input

* Line 1: Three space-separated integers: N, M, and R
* Lines 2..M+1: Line i+1 describes FJ's ith milking interval withthree space-separated integers: starting_houri , ending_houri , and efficiencyi

Output

* Line 1: The maximum number of gallons of milk that Bessie can product in the N hours

Sample Input

12 4 2
1 2 8
10 12 19
3 6 24
7 10 31
Sample Output

43
动态规划:dp[i]表示在第i个阶段挤奶能获得的最大量
则dp[i] = max(dp[i-1],dp[i-2],dp[i-j],dp[0]) + 该阶段奶量（注：前面的挤奶阶段只有与当前阶段不冲突时才可以参与比较）
*/

#include <cstdio>
#include <algorithm>

using namespace std;

struct Cow{
    int start,endt,efficiency;
};

bool cmp(const Cow &a,const Cow &b)
{
    return a.endt <= b.endt;
}

int main()
{
    int N,M,R;
    scanf("%d%d%d",&N,&M,&R);
    Cow cow[M];
    for(int i = 0;i<M;i++)
    {
        scanf("%d%d%d",&cow[i].start,&cow[i].endt,&cow[i].efficiency);
    }

    sort(cow,cow+M,cmp);

    int dp[M];
    int ans = 0;
    for(int i = 0;i<M;i++)
        dp[i] = cow[i].efficiency;

    for(int i = 0;i < M;i++)
    {
        for(int j = 0;j<i;j++)
            if(cow[j].endt + R <= cow[i].start)     //冲突检查
                dp[i] = max(dp[i],dp[j]+cow[i].efficiency);
        ans = max(ans,dp[i]);
    }

    printf("%d\n",ans);
    return 0;
}
