/*
 * Description

In a certain course, you take n tests. If you get ai out of bi questions correct on test i, your cumulative average is defined to be

.

Given your test scores and a positive integer k, determine how high you can make your cumulative average if you are allowed to drop any k of your test scores.

Suppose you take 3 tests with scores of 5/5, 0/1, and 2/6. Without dropping any tests, your cumulative average is . However, if you drop the third test, your cumulative average becomes .

Input

The input test file will contain multiple test cases, each containing exactly three lines. The first line contains two integers, 1 ≤ n ≤ 1000 and 0 ≤ k < n. The second line contains n integers indicating ai for all i. The third line contains n positive integers indicating bi for all i. It is guaranteed that 0 ≤ ai ≤ bi ≤ 1, 000, 000, 000. The end-of-file is marked by a test case with n = k = 0 and should not be processed.

Output

For each test case, write a single line with the highest cumulative average possible after dropping k of the given test scores. The average should be rounded to the nearest integer.

Sample Input

3 1
5 0 2
5 1 6
4 2
1 2 7 9
5 6 7 9
0 0
Sample Output

83
100
Hint

To avoid ambiguities due to rounding errors, the judge tests have been constructed so that all answers are at least 0.001 away from a decision boundary (i.e., you can assume that the average is never 83.4997).
二分搜索
 */
#include <cstdio>
#include <algorithm>

int n,k;
int a[1008];
int b[1008];
double y[1008];

bool judge(double x)
{
    for(int i = 0;i < n;i++)
        y[i] = a[i] - x*b[i];

    std::sort(y,y+n);

    double sum = 0;
    for(int i = 0;i<k;i++)
        sum += y[n-i-1];
    return sum >= 0;
}

int main()
{
    while(scanf("%d%d",&n,&k) && (n || k))
    {
        for(int i = 0;i<n;i++)
            scanf("%d",&a[i]);
        for(int i = 0;i<n;i++)
            scanf("%d",&b[i]);

        k = n-k;
        double lb = 0;
        double ub = 1.1;
        double mid;
        for(int i = 0;i<100;i++)
        {
            mid = (lb + ub) / 2;
            if(judge(mid))
                lb = mid;
            else
                ub = mid;
        }

        //printf("%lf\n",lb);
        printf("%d\n",int(100*lb + 0.5));
    }
    return 0;
}