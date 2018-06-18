/*
Description

The cows don't use actual bowling balls when they go bowling. They each take a number (in the range 0..99), though, and line up in a standard bowling-pin-like triangle like this:

          7



        3   8



      8   1   0



    2   7   4   4



  4   5   2   6   5
Then the other cows traverse the triangle starting from its tip and moving "down" to one of the two diagonally adjacent cows until the "bottom" row is reached. The cow's score is the sum of the numbers of the cows visited along the way. The cow with the highest score wins that frame.

Given a triangle with N (1 <= N <= 350) rows, determine the highest possible sum achievable.
Input

Line 1: A single integer, N

Lines 2..N+1: Line i+1 contains i space-separated integers that represent row i of the triangle.
Output

Line 1: The largest sum achievable using the traversal rules
Sample Input

5
7
3 8
8 1 0
2 7 4 4
4 5 2 6 5
Sample Output

30
Hint

Explanation of the sample:

          7

         *

        3   8

       *

      8   1   0

       *

    2   7   4   4

       *

  4   5   2   6   5
The highest score is achievable by traversing the cows as shown above.

动态规划：best[i][j]表示第i行，j列的最大得分，递推公式如下
    best[0][0] = bowling_pin[0][0]
    best[i][j] = max(best[i-1][j-1],best[i-1][j]) + bowling_pin[i][j]
*/

#include <cstdio>
#include <algorithm>

using namespace std;

int N;

int main()
{
    scanf("%d",&N);
    int bowling_pin[N][N];
    for(int i = 0;i<N;i++)
        for(int j = 0;j<=i;j++)
            scanf("%d",&bowling_pin[i][j]);


    for(int i = 1;i<N;i++)
    {
        bowling_pin[i][0] += bowling_pin[i-1][0];
        for(int j = 1;j<i;j++)
            bowling_pin[i][j] += max(bowling_pin[i-1][j-1],bowling_pin[i-1][j]);
        bowling_pin[i][i] += bowling_pin[i-1][i-1];
    }

    for(int j = 1;j<=N-1;j++)
        bowling_pin[N-1][0] = max(bowling_pin[N-1][0],bowling_pin[N-1][j]);
    printf("%d\n",bowling_pin[N-1][0]);


    return 0;
}
