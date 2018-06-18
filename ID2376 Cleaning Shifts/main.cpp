/*
Description

Farmer John is assigning some of his N (1 <= N <= 25,000) cows to do some cleaning chores around the barn. He always wants to have one cow working on cleaning things up and has divided the day into T shifts (1 <= T <= 1,000,000), the first being shift 1 and the last being shift T.

Each cow is only available at some interval of times during the day for work on cleaning. Any cow that is selected for cleaning duty will work for the entirety of her interval.

Your job is to help Farmer John assign some cows to shifts so that (i) every shift has at least one cow assigned to it, and (ii) as few cows as possible are involved in cleaning. If it is not possible to assign a cow to each shift, print -1.
Input

* Line 1: Two space-separated integers: N and T

* Lines 2..N+1: Each line contains the start and end times of the interval during which a cow can work. A cow starts work at the start time and finishes after the end time.
Output

* Line 1: The minimum number of cows Farmer John needs to hire or -1 if it is not possible to assign a cow to each shift.
Sample Input

3 10
1 7
3 6
6 10
Sample Output

2
Hint

This problem has huge input data,use scanf() instead of cin to read data to avoid time limit exceed.

INPUT DETAILS:

There are 3 cows and 10 shifts. Cow #1 can work shifts 1..7, cow #2 can work shifts 3..6, and cow #3 can work shifts 6..10.

OUTPUT DETAILS:

By selecting cows #1 and #3, all shifts are covered. There is no way to cover all the shifts using fewer than 2 cows.

贪心(在所有可行奶牛（开始工作的时间小于等于上一个工作奶牛的结束时间，否则无解）中，选择完工时间最晚的一个）
*/

#include <cstdio>
#include <cassert>
#include <utility>
#include <algorithm>

#define interval pair<int,int>

using namespace std;



int N,T;

int main()
{
    scanf("%d%d",&N,&T);
    assert(N >= 1 && N <= 25000 && T >= 1 && T <= 1000000);

    pair<int,int> candidate[N+1];
    candidate[0] = interval(N,N);
    int start_time,end_time;
    for(int i = 1;i<=candidate[0].first;i++)
    {
        scanf("%d%d",&start_time,&end_time);
        candidate[i] = interval(start_time,end_time);
    }

    sort(candidate + 1,candidate + N + 1);

    int ans = 0;
    start_time = end_time = 1;
    for(int i = 1;i<=candidate[0].first;i++)
    {
        if(candidate[i].first <= start_time)
        {
            while(candidate[i].first <= start_time)
            {
                if(candidate[i].second>end_time)
                    end_time = candidate[i].second;
                i++;
            }
            i--;
            start_time = end_time + 1;
            ans++;
            if(end_time >= T)
                break;
        }
        else
        {
            ans = -1;
            break;
        }
    }

    if(end_time < T)
        ans = -1;

    printf("%d",ans);

    return 0;
}
