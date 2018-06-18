/*
Description

Our chemical biologists have invented a new very useful form of life called stripies (in fact, they were first called in Russian - polosatiki, but the scientists had to invent an English name to apply for an international patent). The stripies are transparent amorphous amebiform creatures that live in flat colonies in a jelly-like nutrient medium. Most of the time the stripies are moving. When two of them collide a new stripie appears instead of them. Long observations made by our scientists enabled them to establish that the weight of the new stripie isn't equal to the sum of weights of two disappeared stripies that collided; nevertheless, they soon learned that when two stripies of weights m1 and m2 collide the weight of resulting stripie equals to 2*sqrt(m1*m2). Our chemical biologists are very anxious to know to what limits can decrease the total weight of a given colony of stripies.
You are to write a program that will help them to answer this question. You may assume that 3 or more stipies never collide together.
Input

The first line of the input contains one integer N (1 <= N <= 100) - the number of stripies in a colony. Each of next N lines contains one integer ranging from 1 to 10000 - the weight of the corresponding stripie.
Output

The output must contain one line with the minimal possible total weight of colony with the accuracy of three decimal digits after the point.
Sample Input

3
72
30
50
Sample Output

120.000
贪心：重量越大的越先参与合并，并且最大的两个参与合并后的结果仍然在菌落中是重量最大的
*/

#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

int N;

double solve(double *colony)
{
    double ans = colony[N-1];
    for(int i = N-2;i>=0;i--)
        ans = 2 * sqrt(ans * colony[i]);
    return ans;
}

int main()
{
    scanf("%d",&N);
    double colony[N];
    for(int i = 0;i<N;i++)
        scanf("%lf",&colony[i]);

    sort(colony,colony+N);

    double ans = solve(colony);

    printf("%.3f\n",ans);

    return 0;
}
