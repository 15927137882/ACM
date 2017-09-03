/*
Description

Michaelϲ����ѩ���Ⲣ����֣� ��Ϊ��ѩ��ȷ�ܴ̼�������Ϊ�˻���ٶȣ������������������б�����ҵ��㻬���µף��㲻�ò��ٴ������»��ߵȴ������������㡣Michael��֪����һ����������׻��¡�������һ����ά��������������ÿ�����ִ����ĸ߶ȡ�������һ������
 1  2  3  4 5

16 17 18 19 6

15 24 25 20 7

14 23 22 21 8

13 12 11 10 9

һ���˿��Դ�ĳ���㻬���������������ĸ���֮һ�����ҽ����߶ȼ�С��������������У�һ���ɻ��еĻ���Ϊ24-17-16-1����Ȼ25-24-23-...-3-2-1��������ʵ�ϣ��������һ����
Input

����ĵ�һ�б�ʾ���������R������C(1 <= R,C <= 100)��������R�У�ÿ����C������������߶�h��0<=h<=10000��
Output

��������ĳ��ȡ�
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
