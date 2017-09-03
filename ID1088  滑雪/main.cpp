/*
Description

Michael喜欢滑雪百这并不奇怪， 因为滑雪的确很刺激。可是为了获得速度，滑的区域必须向下倾斜，而且当你滑到坡底，你不得不再次走上坡或者等待升降机来载你。Michael想知道载一个区域中最长底滑坡。区域由一个二维数组给出。数组的每个数字代表点的高度。下面是一个例子
 1  2  3  4 5

16 17 18 19 6

15 24 25 20 7

14 23 22 21 8

13 12 11 10 9

一个人可以从某个点滑向上下左右相邻四个点之一，当且仅当高度减小。在上面的例子中，一条可滑行的滑坡为24-17-16-1。当然25-24-23-...-3-2-1更长。事实上，这是最长的一条。
Input

输入的第一行表示区域的行数R和列数C(1 <= R,C <= 100)。下面是R行，每行有C个整数，代表高度h，0<=h<=10000。
Output

输出最长区域的长度。
Sample Input

5 5
1 2 3 4 5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9
Sample Output

25
*/


#include <iostream>

#define ROW 105
#define COLUMN 105

using namespace std;

int num[ROW][COLUMN];
int hop[ROW][COLUMN];
int n,m;

int dp(int i,int j)
{
    if(hop[i][j] != 0)return hop[i][j];
	int maxn = 0;
	if(i - 1 > 0 && j > 0 && num[i][j] > num[i - 1][j] && dp(i - 1,j) > maxn)
	{
		maxn = hop[i - 1][j];
	}
	if(i > 0 && j - 1 > 0 && num[i][j] > num[i][j - 1] && dp(i,j - 1) > maxn)
	{
		maxn = hop[i][j - 1];
	}
	if(i > 0 && j + 1 <= m && num[i][j] > num[i][j + 1] && dp(i, j + 1) > maxn)
	{
		maxn = hop[i][j + 1];
	}
	if(i + 1 <= n && j > 0 && num[i][j] > num[i + 1][j] && dp(i + 1,j) > maxn)
	{
		maxn = hop[i + 1][j];
	}
	hop[i][j] = maxn + 1;
	return hop[i][j];
}


int main()
{
    for(int i=0;i<ROW;i++)
    {
        for(int j =0;j<COLUMN;j++)
        {
            num[i][j] = 0;
            hop[i][j] = 0;
        }
    }

    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>num[i][j];
        }
    }

    int result=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            hop[i][j] = dp(i,j);
            if(hop[i][j]>result)
                result = hop[i][j];
        }
    }

    cout<<result<<endl;

}
