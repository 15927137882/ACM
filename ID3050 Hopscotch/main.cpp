/*
Description

The cows play the child's game of hopscotch in a non-traditional way. Instead of a linear set of numbered boxes into which to hop, the cows create a 5x5 rectilinear grid of digits parallel to the x and y axes.

They then adroitly hop onto any digit in the grid and hop forward, backward, right, or left (never diagonally) to another digit in the grid. They hop again (same rules) to a digit (potentially a digit already visited).

With a total of five intra-grid hops, their hops create a six-digit integer (which might have leading zeroes like 000201).

Determine the count of the number of distinct integers that can be created in this manner.
Input

* Lines 1..5: The grid, five integers per line
Output

* Line 1: The number of distinct integers that can be constructed
Sample Input

1 1 1 1 1
1 1 1 1 1
1 1 1 1 1
1 1 1 2 1
1 1 1 1 1
Sample Output

15
Hint

OUTPUT DETAILS:
111111, 111112, 111121, 111211, 111212, 112111, 112121, 121111, 121112, 121211, 121212, 211111, 211121, 212111, and 212121 can be constructed. No other values are possible.

ºÚµ•dfsº”◊¥Ã¨÷ÿ÷√
*/

#include <iostream>
#include <set>
#include <string>

using namespace std;

char MAP[5][5];
set<string> SET;
int ans;
string seq;
int dx[4] = {0,-1,0,1},dy[4] = {1,0,-1,0};

void dfs(int i,int j,int k)
{
    if(k == 5)
    {
        seq += MAP[i][j];
        if(SET.find(seq) == SET.end())
        {
            SET.insert(seq);
            ans++;
        }
        seq.erase(k);
        return;
    }
    else
    {
        seq += MAP[i][j];
        for(int l = 0;l<4;l++)
        {
            int ni = i + dx[l],nj = j + dy[l];
            if(ni >= 0 && ni<5 && nj >=0 && nj < 5)
            {
                dfs(ni,nj,k+1);
            }
        }
    }
    seq.erase(k);
    return;
}

int main()
{
    for(int i = 0;i<5;i++)
        for(int j = 0;j<5;j++)
            cin>>MAP[i][j];

    ans = 0;
    for(int i = 0;i<5;i++)
        for(int j = 0;j<5;j++)
            dfs(i,j,0);


    cout<<ans<<endl;
    return 0;
}
