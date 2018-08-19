/*
Description

        Given a positive integer X, an X-factor chain of length m is a sequence of integers,

1 = X0, X1, X2, …, Xm = X

satisfying

        Xi < Xi+1 and Xi | Xi+1 where a | b means a perfectly divides into b.

Now we are interested in the maximum length of X-factor chains and the number of chains of such length.

Input

        The input consists of several test cases. Each contains a positive integer X (X ≤ 220).

Output

        For each test case, output the maximum length and the number of such X-factors chains.

Sample Input

2
3
4
10
100
Sample Output

1 1
1 1
2 1
2 2
4 6


因子链的长度取决于该数的质因子个数，比如100->2,2,5,5,为4。
而链的数量为这些因子不全相异的全排列数：A!/(a1!a2!a3!..)
*/

#include <iostream>
#include <cmath>

using namespace std;

int factor[25];
int cnt[25];

int main()
{
    int number;
    while(cin>>number)
    {
        int diff_factor = 0;
        for(int i = 2;i<=sqrt(number);i++)
        {
            if(number % i == 0)
            {
                factor[diff_factor] = i;
                cnt[diff_factor] = 0;
                cnt[diff_factor++]++;
                number /= i;
                while(number % i == 0)
                {
                    cnt[diff_factor - 1]++;
                    number /= i;
                }
            }
        }
        if(number > 1)      //考虑是否还剩下一个最大的质因子
        {
            factor[diff_factor] = number;
            cnt[diff_factor++] = 1;
        }

        int length = 0;
        for(int i = 0;i<diff_factor;i++)
            length += cnt[i];

        int ans = 1;
        for(int i = cnt[0] + 1;i<=length;i++)   // 提前除以a[0]!
            ans *= i;
        for(int i = 1;i<diff_factor;i++)
        {
            for(int j = 1;j<=cnt[i];j++)
                ans /= j;
        }
        cout<<length<<" "<<ans<<endl;
    }
    return 0;
}