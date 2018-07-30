/*
Description

        The cows have been making movies lately, so they are ready to play a variant of the famous game "Six Degrees of Kevin Bacon".

The game works like this: each cow is considered to be zero degrees of separation (degrees) away from herself. If two distinct cows have been in a movie together, each is considered to be one 'degree' away from the other. If a two cows have never worked together but have both worked with a third cow, they are considered to be two 'degrees' away from each other (counted as: one degree to the cow they've worked with and one more to the other cow). This scales to the general case.

The N (2 <= N <= 300) cows are interested in figuring out which cow has the smallest average degree of separation from all the other cows. excluding herself of course. The cows have made M (1 <= M <= 10000) movies and it is guaranteed that some relationship path exists between every pair of cows.
Input

        * Line 1: Two space-separated integers: N and M

* Lines 2..M+1: Each input line contains a set of two or more space-separated integers that describes the cows appearing in a single movie. The first integer is the number of cows participating in the described movie, (e.g., Mi); the subsequent Mi integers tell which cows were.
Output

        * Line 1: A single integer that is 100 times the shortest mean degree of separation of any of the cows.
Sample Input

4 2
3 1 2 3
2 3 4
Sample Output

100
Hint

[Cow 3 has worked with all the other cows and thus has degrees of separation: 1, 1, and 1 -- a mean of 1.00 .]

 使用Floyd-Warshall算法(动态规划)求任意两点间的最短距离
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

#define INF 0x3f3f3f3f

int act_list[305];
int dp[305][305];

int main()
{
    memset(dp,INF,sizeof(dp));
    int N,M;
    scanf("%d%d",&N,&M);
    for(int i = 1;i<=N;i++)
        dp[i][i] = 0;
    for(int i = 0;i<M; i++)
    {
        int actors;
        scanf("%d",&actors);
        for(int j = 0;j<actors;j++)
            scanf("%d",&act_list[j]);
        for(int m = 0;m<actors;m++)
            for(int n = m + 1;n<actors;n++)
            {
                dp[act_list[m]][act_list[n]] = 1;
                dp[act_list[n]][act_list[m]] = 1;
            }
    }

    for(int k = 1;k <= N;k++)
    {
        for(int i = 1;i<=N;i++)
            for(int j = 1;j<=N;j++)
                dp[i][j] = std::min(dp[i][j],dp[i][k]+dp[k][j]);
    }

    double ans = INF;
    for(int i = 1;i<=N;i++)
    {
        double tmp = 0;
        for(int j = 1;j<=N;j++)
            tmp += dp[i][j];
        tmp /= N-1;
        ans = std::min(ans,tmp);
    }

    ans*=100;
    printf("%d\n",(int)ans);
//    for(int i = 1;i<=N;i++)
//    {
//        for(int j = 1 ;j<=N;j++)
//            printf("%d ",dp[i][j]);
//        printf("\n");
//    }

    return 0;
}