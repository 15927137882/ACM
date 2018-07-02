/*
Description

There is a pile of n wooden sticks. The length and weight of each stick are known in advance. The sticks are to be processed by a woodworking machine in one by one fashion. It needs some time, called setup time, for the machine to prepare processing a stick. The setup times are associated with cleaning operations and changing tools and shapes in the machine. The setup times of the woodworking machine are given as follows:
(a) The setup time for the first wooden stick is 1 minute.
(b) Right after processing a stick of length l and weight w , the machine will need no setup time for a stick of length l' and weight w' if l <= l' and w <= w'. Otherwise, it will need 1 minute for setup.
You are to find the minimum setup time to process a given pile of n wooden sticks. For example, if you have five sticks whose pairs of length and weight are ( 9 , 4 ) , ( 2 , 5 ) , ( 1 , 2 ) , ( 5 , 3 ) , and ( 4 , 1 ) , then the minimum setup time should be 2 minutes since there is a sequence of pairs ( 4 , 1 ) , ( 5 , 3 ) , ( 9 , 4 ) , ( 1 , 2 ) , ( 2 , 5 ) .
Input

The input consists of T test cases. The number of test cases (T) is given in the first line of the input file. Each test case consists of two lines: The first line has an integer n , 1 <= n <= 5000 , that represents the number of wooden sticks in the test case, and the second line contains 2n positive integers l1 , w1 , l2 , w2 ,..., ln , wn , each of magnitude at most 10000 , where li and wi are the length and weight of the i th wooden stick, respectively. The 2n integers are delimited by one or more spaces.
Output

The output should contain the minimum setup time in minutes, one per line.
Sample Input

3
5
4 9 5 2 2 1 3 5 1 4
3
2 2 1 1 2 2
3
1 3 2 2 3 1
Sample Output
2
1
3
偏序Dilworth定理+最长下降子序列动态规划，参考http://www.voidcn.com/article/p-wrvhxahf-dg.html
 */

#include <cstdio>
#include <algorithm>

struct sticks
{
    int length,weight;
};

bool comp(sticks a,sticks b)
{
    if (a.length==b.length)
    {
        return a.weight<b.weight;
    }
    else
    {
        return a.length<b.length;
    }
}


using namespace std;

sticks sequence[5005];
int dp[5005];

int main()
{
    int cases;

    scanf("%d",&cases);
    int N;

    while(cases--)
    {
        scanf("%d",&N);

        for(int i = 0;i<N;i++)
            scanf("%d%d",&sequence[i].length,&sequence[i].weight);

        sort(sequence,sequence+N,comp);


        for(int i = 0;i<N;i++)
        {
            dp[i] = 1;
            for(int j = 0;j<i;j++)
            {
                if(sequence[i].weight < sequence[j].weight && dp[j] + 1 > dp[i])
                    dp[i] = dp[j]+ 1;
            }
        }

        int ans = dp[0];
        for(int i = 1;i<N;i++)
            ans = max(ans,dp[i]);

        printf("%d\n",ans);
    }

    return 0;
}