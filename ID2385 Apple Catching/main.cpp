/*
Description

It is a little known fact that cows love apples. Farmer John has two apple trees (which are conveniently numbered 1 and 2) in his field, each full of apples. Bessie cannot reach the apples when they are on the tree, so she must wait for them to fall. However, she must catch them in the air since the apples bruise when they hit the ground (and no one wants to eat bruised apples). Bessie is a quick eater, so an apple she does catch is eaten in just a few seconds.

Each minute, one of the two apple trees drops an apple. Bessie, having much practice, can catch an apple if she is standing under a tree from which one falls. While Bessie can walk between the two trees quickly (in much less than a minute), she can stand under only one tree at any time. Moreover, cows do not get a lot of exercise, so she is not willing to walk back and forth between the trees endlessly (and thus misses some apples).

Apples fall (one each minute) for T (1 <= T <= 1,000) minutes. Bessie is willing to walk back and forth at most W (1 <= W <= 30) times. Given which tree will drop an apple each minute, determine the maximum number of apples which Bessie can catch. Bessie starts at tree 1.
Input

* Line 1: Two space separated integers: T and W

* Lines 2..T+1: 1 or 2: the tree that will drop an apple each minute.
Output

* Line 1: The maximum number of apples Bessie can catch without walking more than W times.
Sample Input

7 2
2
1
1
2
2
1
1
Sample Output

6
Hint

INPUT DETAILS:

Seven apples fall - one from tree 2, then two in a row from tree 1, then two in a row from tree 2, then two in a row from tree 1. Bessie is willing to walk from one tree to the other twice.

OUTPUT DETAILS:

Bessie can catch six apples by staying under tree 1 until the first two have dropped, then moving to tree 2 for the next two, then returning back to tree 1 for the final two.

动态规划: 状态的转化取决于跳还是不跳，dp[i][j]表示在第i个阶段，且跳了j次的情况下，最多能收获的苹果数，在第0个时刻，不论跳多少次，能收获的苹果数均为0
则有以下动态规划式：
    dp[i][j] = max(dp[i-1][j] + 在i时刻跳了j次时，此轮是否有苹果收获 ; dp[i-1][j-1] + 在i时刻跳了j-1次时，此轮是否有苹果收获)
*/

#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int main()
{
    int T,W;
    scanf("%d%d",&T,&W);
    int apple[T];
    int dp[T+1][W+1];
    for(int i = 0;i<T;i++)
    {
        scanf("%d",&apple[i]);
    }

    memset(dp,0,(W+1)*sizeof(int));
    for(int i = 1;i<=T;i++)
    {
        for(int j = 0;j<=W;j++)
        {
            if(j) dp[i][j] = max(dp[i-1][j-1] + ((j-1) % 2 + 1 == apple[i-1]), dp[i-1][j] + (j % 2 + 1 == apple[i-1]));
            else dp[i][j] = dp[i-1][j] + (j % 2 + 1 == apple[i-1]);
        }
    }

    int ans = dp[T][0];
    for(int j = 1;j<=W;j++)
    {
        ans = max(ans,dp[T][j]);
    }
    printf("%d\n",ans);
    return 0;
}
