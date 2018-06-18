/*
Description

Farmer John commanded his cows to search for different sets of numbers that sum to a given number. The cows use only numbers that are an integer power of 2. Here are the possible sets of numbers that sum to 7:

1) 1+1+1+1+1+1+1
2) 1+1+1+1+1+2
3) 1+1+1+2+2
4) 1+1+1+4
5) 1+2+2+2
6) 1+2+4

Help FJ count all possible representations for a given integer N (1 <= N <= 1,000,000).
Input

A single line with a single integer, N.
Output

The number of ways to represent N as the indicated sum. Due to the potential huge size of this number, print only last 9 digits (in base 10 representation).
Sample Input

7
Sample Output

6

动态规划，考虑状态的切换
1.当N为奇数时，每一个组合都包含一个1，当减去这个1时，会与N-1的组合数一一对应，dp[N] = dp[N-1]
2.当N为偶数时，组合类型可以分为两部分，第一部分是含1的组合,这部分与第一类情况分析类似，第二部分是不含1的组合，
  即组合中全部为偶数，这时与N/2的组合数一一对应，如(2,2,4)->(1,1,2)等，dp[N] = dp[N-1] + dp[N/2]
*/

#include <iostream>

#define MAX 1000000
#define SCALED 1000000000

using namespace std;

int dp[MAX+1];

int main()
{
    dp[1] = 1;
    for(int i = 2;i<=MAX;i++)
    {
        if(i % 2)
            dp[i] = dp[i-1];
        else
            dp[i] = (dp[i-1] + dp[i>>1]) % SCALED;
    }

    int n;
    cin>>n;
    cout<<dp[n]<<endl;
    return 0;
}
