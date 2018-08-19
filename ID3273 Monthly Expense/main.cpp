/*
 * Description

Farmer John is an astounding accounting wizard and has realized he might run out of money to run the farm. He has already calculated and recorded the exact amount of money (1 ≤ moneyi ≤ 10,000) that he will need to spend each day over the next N (1 ≤ N ≤ 100,000) days.

FJ wants to create a budget for a sequential set of exactly M (1 ≤ M ≤ N) fiscal periods called "fajomonths". Each of these fajomonths contains a set of 1 or more consecutive days. Every day is contained in exactly one fajomonth.

FJ's goal is to arrange the fajomonths so as to minimize the expenses of the fajomonth with the highest spending and thus determine his monthly spending limit.

Input

Line 1: Two space-separated integers: N and M
Lines 2..N+1: Line i+1 contains the number of dollars Farmer John spends on the ith day
Output

Line 1: The smallest possible monthly limit Farmer John can afford to live with.
Sample Input

7 5
100
400
300
100
500
101
400
Sample Output

500
Hint

If Farmer John schedules the months so that the first two days are a month, the third and fourth are a month, and the last three are their own months, he spends at most $500 in any month. Any other method of scheduling gives a larger minimum monthly limit.
属于min(max)问题,使用二分搜所即可完成
 */

#include <cstdio>
#include <cassert>
#include <algorithm>

int fiscal_periods,days;
int cost[100016];

bool judge(int x)
{
    int least_period=0;
    int spend = 0;
    for(int i = 0;i<days;i++)
    {
        if(cost[i]>x) return false;
        spend += cost[i];
        if(spend > x)
        {
            least_period++;
            spend = cost[i];
        }
        else if(spend == x)
        {
            least_period++;
            spend = 0;
        }
    }
    if(spend > 0)
        least_period++;
    return least_period <= fiscal_periods;
}

int main()
{
    scanf("%d%d",&days,&fiscal_periods);
    assert(days >= fiscal_periods);
    for(int i = 0;i<days;i++)
        scanf("%d",&cost[i]);

    int ub = (*std::max_element(cost,cost + days)) * days;
    int lb = 0;
    int mid;
    while(ub - lb > 1)
    {
        mid =(ub + lb) / 2;
        if(judge(mid))
            ub = mid;
        else
            lb = mid;
    }
    printf("%d\n",ub);
    return 0;
}