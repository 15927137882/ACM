/*
Description

FJ and his cows enjoy playing a mental game. They write down the numbers from 1 to N (1 <= N <= 10) in a certain order and then sum adjacent numbers to produce a new list with one fewer number. They repeat this until only a single number is left. For example, one instance of the game (when N=4) might go like this:

    3   1   2   4

      4   3   6

        7   9

         16
Behind FJ's back, the cows have started playing a more difficult game, in which they try to determine the starting sequence from only the final total and the number N. Unfortunately, the game is a bit above FJ's mental arithmetic capabilities.

Write a program to help FJ play the game and keep up with the cows.
Input

Line 1: Two space-separated integers: N and the final sum.
Output

Line 1: An ordering of the integers 1..N that leads to the given sum. If there are multiple solutions, choose the one that is lexicographically least, i.e., that puts smaller numbers first.
Sample Input

4 16
Sample Output

3 1 2 4
Hint

Explanation of the sample:

There are other possible sequences, such as 3 2 1 4, but 3 1 2 4 is the lexicographically smallest.

题目规模小，直接暴搜
*/

#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int Set[11] = {0,1,2,3,4,5,6,7,8,9,10};

int main()
{
    int N,final_sum;
    cin>>N>>final_sum;
    assert(N>=1 && N<=10);

    int sum[N];
    Set[0] = N;

    do
    {
        memcpy(sum,Set+1,sizeof(int)*N);
        int col = N;
        for(int i = 0;i<N-1;i++)
        {
            for(int j = 0;j<col-1;j++)
            {
                sum[j] = sum[j] + sum[j+1];
            }
            col--;
        }
        if(sum[0] == final_sum)
        {
            memcpy(sum,Set+1,sizeof(int)*N);
            break;
        }

    } while(next_permutation(Set+1,Set+N+1));

    for(int i = 0;i<N;i++)
    {
        cout<<sum[i]<<" ";
    }
    cout<<endl;
}
