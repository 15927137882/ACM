/*
 * Description

The ministers of the cabinet were quite upset by the message from the Chief of Security stating that they would all have to change the four-digit room numbers on their offices.
— It is a matter of security to change such things every now and then, to keep the enemy in the dark.
— But look, I have chosen my number 1033 for good reasons. I am the Prime minister, you know!
— I know, so therefore your new number 8179 is also a prime. You will just have to paste four new digits over the four old ones on your office door.
— No, it’s not that simple. Suppose that I change the first digit to an 8, then the number will read 8033 which is not a prime!
— I see, being the prime minister you cannot stand having a non-prime number on your door even for a few seconds.
— Correct! So I must invent a scheme for going from 1033 to 8179 by a path of prime numbers where only one digit is changed from one prime to the next prime.

Now, the minister of finance, who had been eavesdropping, intervened.
— No unnecessary expenditure, please! I happen to know that the price of a digit is one pound.
— Hmm, in that case I need a computer program to minimize the cost. You don't know some very cheap software gurus, do you?
— In fact, I do. You see, there is this programming contest going on... Help the prime minister to find the cheapest prime path between any two given four-digit primes! The first digit must be nonzero, of course. Here is a solution in the case above.
1033
1733
3733
3739
3779
8779
8179
The cost of this solution is 6 pounds. Note that the digit 1 which got pasted over in step 2 can not be reused in the last step – a new 1 must be purchased.
Input

One line with a positive number: the number of test cases (at most 100). Then for each test case, one line with two numbers separated by a blank. Both numbers are four-digit primes (without leading zeros).
Output

One line for each case, either with a number stating the minimal cost or containing the word Impossible.
Sample Input

3
1033 8179
1373 8017
1033 1033
Sample Output

6
7
0

 埃氏筛法+bfs求最短路径
 */

#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

bool is_prime[10005];
int dp[10005];

void sieve()
{
    is_prime[0] = false;
    is_prime[1] = false;
    for(int i = 2;i<10005;i++)
    {
        if(is_prime[i])
        {
            for(int j = 2*i;j<10005;j+=i)
                is_prime[j] = false;
        }
    }
}

int get_next(int a, int pos,int num)
{
    switch(pos)
    {
        case 0:
            return (a / 10) * 10 + num;
        case 1:
            return (a / 100) * 100 + num * 10 + a % 10;
        case 2:
            return (a / 1000) * 1000 + num * 100 + a % 100;
        case 3:
            return (a % 1000) + num * 1000;
    }
    return 0;
}

int main()
{
    memset(is_prime,true,sizeof(is_prime));
    sieve();
    int cases = 0;
    cin>>cases;
    while(cases--)
    {
        int start,end;
        memset(dp,0x3f,sizeof(dp));
        cin>>start>>end;
        dp[start] = 0;
        queue<int> route;
        route.push(start);
        while(route.size())
        {
            int cur = route.front();
            route.pop();
            for(int i = 0;i<4;i++)
            {
                for(int j = 0;j<10;j++)
                {
                    if(i == 3 && j == 0)
                        continue;
                    int next = get_next(cur,i,j);
                    if(!is_prime[next] || dp[next] < dp[cur] + 1)
                        continue;
                    dp[next] = dp[cur] + 1;
                    route.push(next);
                }
            }
        }

        if(dp[end] == 0x3f3f3f3f)
            cout<<"Impossible\n";
        else
            cout<<dp[end]<<endl;

    }

    return 0;
}