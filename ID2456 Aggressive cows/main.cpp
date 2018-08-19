/*
 * Description

Farmer John has built a new long barn, with N (2 <= N <= 100,000) stalls. The stalls are located along a straight line at positions x1,...,xN (0 <= xi <= 1,000,000,000).

His C (2 <= C <= N) cows don't like this barn layout and become aggressive towards each other once put into a stall. To prevent the cows from hurting each other, FJ want to assign the cows to the stalls, such that the minimum distance between any two of them is as large as possible. What is the largest minimum distance?
Input

* Line 1: Two space-separated integers: N and C

* Lines 2..N+1: Line i+1 contains an integer stall location, xi
Output

* Line 1: One integer: the largest minimum distance
Sample Input

5 3
1
2
8
4
9
Sample Output

3
Hint

OUTPUT DETAILS:

FJ can put his 3 cows in the stalls at positions 1, 4 and 8, resulting in a minimum distance of 3.

Huge input data,scanf is recommended.

最大化最小值问题
用C(d)表示可以安排牛的位置使得最近的两头牛距离不小于d，则任何小于d的值都能使C(d)成立
则可以用二分法求解
 */
#include <cstdio>
#include <algorithm>

typedef long long LL;
const LL inf = 1000000000;
LL stalls[100000];
int cows_number,stalls_num;

bool C(LL x)
{
    int last = 0;
    int crt;
    for(int i = 1;i<cows_number;i++)
    {
        crt = last + 1;
        while(crt < stalls_num && stalls[crt] -stalls[last] < x)
            crt++;
        if(crt == stalls_num)
            return false;
        last = crt;
    }
    return true;
}

int main()
{
    scanf("%d%d",&stalls_num,&cows_number);
    for(int i = 0;i<stalls_num;i++)
        scanf("%lld",&stalls[i]);
    std::sort(stalls,stalls+stalls_num);
    LL lb = 0;
    LL ub = inf;
    LL mid;
    while(ub -lb > 1)
    {
        mid = (lb + ub) / 2;
        if(C(mid))
            lb = mid;
        else
            ub = mid;
    }

    printf("%lld\n",lb);
    return 0;
}