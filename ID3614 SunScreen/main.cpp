/*
 Description

To avoid unsightly burns while tanning, each of the C (1 ≤ C ≤ 2500) cows must cover her hide with sunscreen when they're at the beach. Cow i has a minimum and maximum SPF rating (1 ≤ minSPFi ≤ 1,000; minSPFi ≤ maxSPFi ≤ 1,000) that will work. If the SPF rating is too low, the cow suffers sunburn; if the SPF rating is too high, the cow doesn't tan at all........

The cows have a picnic basket with L (1 ≤ L ≤ 2500) bottles of sunscreen lotion, each bottle i with an SPF rating SPFi (1 ≤ SPFi ≤ 1,000). Lotion bottle i can cover coveri cows with lotion. A cow may lotion from only one bottle.

What is the maximum number of cows that can protect themselves while tanning given the available lotions?

Input

* Line 1: Two space-separated integers: C and L
* Lines 2..C+1: Line i describes cow i's lotion requires with two integers: minSPFi and maxSPFi
* Lines C+2..C+L+1: Line i+C+1 describes a sunscreen lotion bottle i with space-separated integers: SPFi and coveri

Output

A single line with an integer that is the maximum number of cows that can be protected while tanning

Sample Input

3 2
3 10
2 5
1 5
6 2
4 1
Sample Output

2

贪心，先用SPF小的防晒霜涂牛，牛也要先按（先下界，后上届）排序，之后用小顶堆维护下界低于当前防晒霜SPF的奶牛，
每次取出下界最小的一个奶牛，检查是否可以涂防晒霜，否则直接丢弃，因为以后该头牛以后也不会被涂。
 */

#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>

using namespace std;
typedef pair<int,int> cow;
typedef pair<int,int> sunscreen;

cow cows[2505];
sunscreen sunscreens[2505];


int main()
{
    int C,L;
    scanf("%d%d",&C,&L);
    for(int i = 0;i<C;i++)
        scanf("%d%d",&cows[i].first,&cows[i].second);
    for(int i = 0;i<L;i++)
        scanf("%d%d",&sunscreens[i].first,&sunscreens[i].second);

    sort(cows,cows+C);
    sort(sunscreens,sunscreens+L);

    priority_queue<int,vector<int>,greater<int> > candidate;

    int l = 0;
    int ans = 0;
    for(int i = 0;i<L;i++)
    {
        while(l<C && cows[l].first <= sunscreens[i].first)
        {
            candidate.push(cows[l].second);
            l++;
        }
        while(!candidate.empty() && sunscreens[i].second != 0)
        {
            int cur = candidate.top();
            candidate.pop();
            if(cur < sunscreens[i].first) continue;
            ans++;
            sunscreens[i].second--;
        }
    }

    printf("%d\n",ans);

    return 0;
}