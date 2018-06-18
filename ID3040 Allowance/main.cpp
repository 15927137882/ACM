/*
Description

As a reward for record milk production, Farmer John has decided to start paying Bessie the cow a small weekly allowance. FJ has a set of coins in N (1 <= N <= 20) different denominations, where each denomination of coin evenly divides the next-larger denomination (e.g., 1 cent coins, 5 cent coins, 10 cent coins, and 50 cent coins).Using the given set of coins, he would like to pay Bessie at least some given amount of money C (1 <= C <= 100,000,000) every week.Please help him ompute the maximum number of weeks he can pay Bessie.
Input

* Line 1: Two space-separated integers: N and C

* Lines 2..N+1: Each line corresponds to a denomination of coin and contains two integers: the value V (1 <= V <= 100,000,000) of the denomination, and the number of coins B (1 <= B <= 1,000,000) of this denomation in Farmer John's possession.
Output

* Line 1: A single integer that is the number of weeks Farmer John can pay Bessie at least C allowance
Sample Input

3 6
10 1
1 100
5 120
Sample Output

111
Hint

INPUT DETAILS:
FJ would like to pay Bessie 6 cents per week. He has 100 1-cent coins,120 5-cent coins, and 1 10-cent coin.

OUTPUT DETAILS:
FJ can overpay Bessie with the one 10-cent coin for 1 week, then pay Bessie two 5-cent coins for 10 weeks and then pay Bessie one 1-cent coin and one 5-cent coin for 100 weeks.

贪心
1.按照面值从大到小取，面值大于等于C的，直接取光。
2.再按面值从大到小取，凑近C，可以小于等于C，但不能大于C。
3.最后从小到大取，凑满C，这里的凑满可以等于大于C。然后将上述2,3步取到的面值全部取走，再转入步骤2，这样每次找到的取法就是当前最优取法，直到所剩下的金币总价值不够C结束。
*/


#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int combination[20];
int N,C;

struct money{
    int denomination;
    int number;
};

bool comp(const money &a,const money &b)
{
    return a.denomination > b.denomination;
}

int main()
{
    scanf("%d%d",&N,&C);
    money money_set[N];
    for(int i = 0;i<N;i++)
        scanf("%d%d",&money_set[i].denomination,&money_set[i].number);
    sort(money_set,money_set + N,comp);

    int ans = 0;

    for(int i = 0;i<N;i++)
    {
        if(money_set[i].denomination >= C)
        {
            ans += money_set[i].number;
            money_set[i].number -= money_set[i].number;
        }
        else
            break;
    }

    while(1)
    {
        int resi = C;
        memset(combination,0,sizeof(combination));

        for(int i = 0 ; i<N ; i++)      //首先用大的填，尽量不浪费
        {
            if(money_set[i].number)
            {
                int num = min(money_set[i].number,resi / money_set[i].denomination);
                resi -= num * money_set[i].denomination;
                combination[i] = num;
            }
            if(resi == 0)
                break;
        }


        if(resi)                        //不够的用小的补，万不得已浪费一点
        {
            for(int i = N-1;i>=0;i--)
            {
                while(money_set[i].number > combination[i])
                {
                    combination[i]++;
                    resi -= money_set[i].denomination;
                    if(resi <= 0)
                        break;
                }

                if(resi <= 0)
                    break;
            }
        }
        if(resi > 0)                    //最后无法满足最小供应标准，结束
            break;

        int multi = 0x3f3f;
        for(int i = 0;i<N;i++)
        {
            if(combination[i])
                multi = min(multi, money_set[i].number / combination[i]);
        }

        ans += multi;
        for(int i = 0;i<N;i++)
        {
            money_set[i].number -= multi * combination[i];
        }
    }

    printf("%d\n",ans);

    return 0;
}
