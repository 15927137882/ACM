/*
Description

Oh those picky N (1 <= N <= 50,000) cows! They are so picky that each one will only be milked over some precise time interval A..B (1 <= A <= B <= 1,000,000), which includes both times A and B. Obviously, FJ must create a reservation system to determine which stall each cow can be assigned for her milking time. Of course, no cow will share such a private moment with other cows.

Help FJ by determining:
The minimum number of stalls required in the barn so that each cow can have her private milking period
An assignment of cows to these stalls over time
Many answers are correct for each test dataset; a program will grade your answer.
Input

Line 1: A single integer, N

Lines 2..N+1: Line i+1 describes cow i's milking interval with two space-separated integers.
Output

Line 1: The minimum number of stalls the barn must have.

Lines 2..N+1: Line i+1 describes the stall to which cow i will be assigned for her milking period.
Sample Input

5
1 10
2 4
3 6
5 8
4 7
Sample Output

4
1
2
3
2
4
Hint

Explanation of the sample:

Here's a graphical schedule for this output:

Time     1  2  3  4  5  6  7  8  9 10

Stall 1 c1>>>>>>>>>>>>>>>>>>>>>>>>>>>

Stall 2 .. c2>>>>>> c4>>>>>>>>> .. ..

Stall 3 .. .. c3>>>>>>>>> .. .. .. ..

Stall 4 .. .. .. c5>>>>>>>>> .. .. ..
Other outputs using the same number of stalls are possible.

贪心，每次有新奶牛，加入结束时间最早的stall，否则新开一个stall，这样利用的stall最少
*/
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>

using namespace std;

struct cow{
    int pos;
    int startt,endt;
    bool operator<(const cow& b) const  //重载<操作符
    {
        if(endt == b.endt)
            return startt > b.startt;
        return endt > b.endt;
    }
};

bool comp(cow a,cow b)        //按开始时间升序排列
{
    if(a.startt == b.startt)
        return a.endt < b.endt;
    return a.startt < b.startt;
}

int N;

int main()
{
    scanf("%d",&N);
    cow candidate[N];
    int used[N];
    for(int i = 0;i<N;i++)
    {
        scanf("%d%d",&candidate[i].startt,&candidate[i].endt);
        candidate[i].pos = i;
    }

    sort(candidate,candidate + N,comp);   //该比较器再返回false的时候调整

    priority_queue<cow> stall_set;   //该比较器在返回true的时候进行调整,因为优先队列维护大顶堆，默认使用<操作符比较
    stall_set.push(candidate[0]);
    used[candidate[0].pos] = 1;
    int ans = 1;

    for(int i = 1;i<N;i++)
    {
        cow tmp = stall_set.top();
        if(candidate[i].startt > tmp.endt)
        {
            used[candidate[i].pos] = used[tmp.pos];
            stall_set.pop();
            stall_set.push(candidate[i]);
        }
        else
        {
            ans++;
            used[candidate[i].pos] = ans;
            stall_set.push(candidate[i]);
        }
    }

    printf("%d\n",ans);
    for(int i = 0;i<N;i++)
        printf("%d\n",used[i]);

    return 0;
}

