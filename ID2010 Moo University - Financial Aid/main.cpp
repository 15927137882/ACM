/*
 Description

Bessie noted that although humans have many universities they can attend, cows have none. To remedy this problem, she and her fellow cows formed a new university called The University of Wisconsin-Farmside,"Moo U" for short.

Not wishing to admit dumber-than-average cows, the founders created an incredibly precise admission exam called the Cow Scholastic Aptitude Test (CSAT) that yields scores in the range 1..2,000,000,000.

Moo U is very expensive to attend; not all calves can afford it.In fact, most calves need some sort of financial aid (0 <= aid <=100,000). The government does not provide scholarships to calves,so all the money must come from the university's limited fund (whose total money is F, 0 <= F <= 2,000,000,000).

Worse still, Moo U only has classrooms for an odd number N (1 <= N <= 19,999) of the C (N <= C <= 100,000) calves who have applied.Bessie wants to admit exactly N calves in order to maximize educational opportunity. She still wants the median CSAT score of the admitted calves to be as high as possible.

Recall that the median of a set of integers whose size is odd is the middle value when they are sorted. For example, the median of the set {3, 8, 9, 7, 5} is 7, as there are exactly two values above 7 and exactly two values below it.

Given the score and required financial aid for each calf that applies, the total number of calves to accept, and the total amount of money Bessie has for financial aid, determine the maximum median score Bessie can obtain by carefully admitting an optimal set of calves.

Input

* Line 1: Three space-separated integers N, C, and F

* Lines 2..C+1: Two space-separated integers per line. The first is the calf's CSAT score; the second integer is the required amount of financial aid the calf needs
Output

* Line 1: A single integer, the maximum median score that Bessie can achieve. If there is insufficient money to admit N calves,output -1.
Sample Input

3 5 70
30 25
50 21
20 20
5 18
35 30
Sample Output

35
Hint

Sample output:If Bessie accepts the calves with CSAT scores of 5, 35, and 50, the median is 35. The total financial aid required is 18 + 30 + 21 = 69 <= 70.

贪心+优先队列
先将奶牛排序，考虑每个奶牛作为中位数时，比它分数低（前面的）的那群牛（并且该群牛的得分最高）的学费总和lower_i，后面的总和（并且该群牛的得分最高）upper_i。
然后从分数高往分数低扫描，满足aid_i + lower_i + upper_i <= F的第一个解就是最优解。
*/

#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>

const int INF = 0x3f3f3f3f;
using namespace std;

pair<int,int> cows[100005];
int lower[100005],upper[100005];

int main()
{
    int N,C,F;
    scanf("%d%d%d",&N,&C,&F);
    int middle_point = N / 2;
    for(int i = 0;i<C;i++)
        scanf("%d%d",&cows[i].first,&cows[i].second);
    sort(cows,cows+C);

    priority_queue<int,vector<int>,less<int> > p;
    p = priority_queue<int,vector<int>,less<int> >();
    int sum = 0;
    for(int i = 0;i<C;i++)
    {
        lower[i] = p.size() == middle_point ? sum : INF;
        sum += cows[i].second;
        p.push(cows[i].second);
        if(p.size() > middle_point)
        {
            sum -= p.top();
            p.pop();
        }
    }

    sum = 0;
    p = priority_queue<int,vector<int>,less<int> >();
    for(int i = C-1;i>=0;i--)
    {
        upper[i] = p.size() == middle_point ? sum : INF;
        sum += cows[i].second;
        p.push(cows[i].second);
        if(p.size() > middle_point)
        {
            sum -= p.top();
            p.pop();
        }
    }

    int ans = -1;
    for (int i = C - 1; i >= 0; --i)
    {
        if (lower[i] + cows[i].second + upper[i] <= F)
        {
            ans = cows[i].first;
            break;
        }
    }
    printf("%d\n",ans);
    return 0;
}