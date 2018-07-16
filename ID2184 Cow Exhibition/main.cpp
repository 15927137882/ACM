/*
分析
直覺可以想到是 0/1 背包，但又有點不一樣…

沒有類似總重量限制這個條件，並且要使 sum(s) + sum(f) 最大，sum(s), sum(f) > 0

那就將其中一個值當成重量吧，也就是說，固定其中一個值（sum(s)），最大化另一個值（sum(f)）。

針對 sum(s) 所有可能的值，都找出 對應 的最大 sum(f)，即可得知 sum(s) + sum(f) 最大是多少。

該如何找出對應的最大 sum(f)？這時就可以使用 0/1 背包

0/1 背包：
int dp[i][w] = 使用前 i+1 個物件，在總重 <= w 的限制下，所能得到的最大價值
要不要用第 i 項，有兩種可能，取較大者

dp[i][w] = max(dp[i-1][w - weight[i]] + price[i], dp[i-1][w])
此題：
int dp[i][w] = 考慮前 i+1 隻牛，在 sum(s) = w 的限制下，所能得到的最大 sum(f)
如果 w 是不可能達到的，則 dp[i][w] = IMPOSSIBLE = -0x3f3f3f3f
同樣基於使用或不使用第 i 項，可以得到：

dp[i][w] = max(dp[i-1][w - s[i]] + f[i], dp[i-1][w])
但前提是 w - s[i] 是可以 sum(s) 組得出來的，即 dp[i-1][w - s[i]] != IMPOSSIBLE；另外，當然地，下標必須是合法的（ 注意！s[i] 可能是正也可能是負 ）

實作
因 sum(s) 可能是負的，所以 dp 陣列得平移

如果照著定義寫，會 MLE，所以得優化，0/1 背包是可以優化成一維的，這題也可以，但有個陷阱。

0/1 背包告訴我們，在 s[i] > 0 的前提下， w 的順序是反過來的：

for (int i = 1; i < N; i++)
    for (int w = W; w >= s[i]; w--)
        dp[w] = max(dp[w], dp[w - s[i]] + f[i]);
但這題 s[i] 可能 < 0，仔細思考（想一下 dp 表格及其建表順序）可以得知， w 的順序變回正的：

for (int i = 1; i < N; i++)
    for (int w = s[i]; w <= W; w++)
        dp[w] = max(dp[w], dp[w - s[i]] + f[i]);
参考: https://gist.github.com/amoshyc/a6d5d9dec3188bbcbc65
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define INF -0x3f3f3f3f

struct cow{
    int smartness,funness;
};

const int offset = 1000*100;

int dp[2 * 100 * 1000 + 1];

cow cows[100];

int main()
{
    int num_cows;
    scanf("%d",&num_cows);
    for(int i = 0;i<num_cows;i++)
    {
        scanf("%d%d",&cows[i].smartness,&cows[i].funness);
//        if(cows[i].funness < 0 && cows[i].smartness < 0)
//        {
//            i--;
//            num_cows--;
//        }
    }


    //memset(dp,-0x3f,sizeof(dp));
    for (int w = 0; w < 2 * 100 * 1000; w++)
        dp[w] = INF;

    dp[0+offset] = 0;
    dp[cows[0].smartness + offset] = cows[0].funness;

//    for(int i = 1;i<num_cows;i++)
//    {
//        if(cows[i].smartness >= 0)
//            for(int w = 2 * 100 * 1000;w - cows[i].smartness >= 0;w--)
//                dp[w] = max(dp[w],dp[w-cows[i].smartness] + cows[i].funness);
//        else
//            for(int w = 0 ; w - cows[i].smartness <= 2*100*1000 ; w++)
//                dp[w] = max(dp[w],dp[w-cows[i].smartness] + cows[i].funness);
//    }

    for (int i = 1; i < num_cows; i++) {
        if (cows[i].smartness >= 0) {
            for (int w = 2 * 100 * 1000; w - cows[i].smartness >= 0; w--)
                dp[w] = max(dp[w], dp[w - cows[i].smartness] + cows[i].funness);
        }
        else {
            for (int w = 0; w - cows[i].smartness <= 2 * 100 * 1000; w++)
                dp[w] = max(dp[w], dp[w - cows[i].smartness] + cows[i].funness);
        }
    }

    int ans = 0;

    for(int i = offset;i<2*100*1000;i++)
    {
        if(dp[i]>=0 && (i - offset) + dp[i] > ans)
            ans = (i - offset) + dp[i];
    }

    printf("%d\n",ans);
    return 0;
}