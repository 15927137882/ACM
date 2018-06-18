/*
Description

Assume the coasting is an infinite straight line. Land is in one side of coasting, sea in the other. Each small island is a point locating in the sea side. And any radar installation, locating on the coasting, can only cover d distance, so an island in the sea can be covered by a radius installation, if the distance between them is at most d.

We use Cartesian coordinate system, defining the coasting is the x-axis. The sea side is above x-axis, and the land side below. Given the position of each island in the sea, and given the distance of the coverage of the radar installation, your task is to write a program to find the minimal number of radar installations to cover all the islands. Note that the position of an island is represented by its x-y coordinates.

Figure A Sample Input of Radar Installations


Input

The input consists of several test cases. The first line of each case contains two integers n (1<=n<=1000) and d, where n is the number of islands in the sea and d is the distance of coverage of the radar installation. This is followed by n lines each containing two integers representing the coordinate of the position of each island. Then a blank line follows to separate the cases.

The input is terminated by a line containing pair of zeros
Output

For each test case output one line consisting of the test case number followed by the minimal number of radar installations needed. "-1" installation means no solution for that case.
Sample Input

3 2
1 2
-3 1
2 1

1 2
0 2

0 0
Sample Output

Case 1: 2
Case 2: 1

贪心算法
思路：要找到最少雷达数，但是我们并不知道雷达位于x轴上哪个位置，所以我们可以以海岛坐标为圆中心点，
      以d为海岛的覆盖范围的圆与x轴交点所构成的区间就是雷达可以安装的区间，
     （假设d>海岛的纵坐标），因为在此区间任意位置安装雷达，都可以覆盖海岛，
      所以如果有另一个海岛雷达可安装区间和此海岛区间有公共区间，我们只要在公共区间内安装一个雷达即可覆盖两个海岛，
      以此类推，我们只需要算出最少的公共区间数就可以算出最少的雷达数。
      最少公共区间求法：
      按右端点从小到大进行排序，now_right初始化为第一个最小的右端点，并将此海岛标记为已经访问过，
      如果有未访问过的海岛的左端点next_left小于now_right，说明这两海岛存在公共区间，
      如果有未访问过得海岛的左端点next_left>now_right，说明它们之间不存在公共区间，雷达总数count增加，
      更新now_right为最新的海岛右端点。
*/

#include <iostream>
#include <utility>
#include <cmath>
#include <algorithm>

#define N 1010

using namespace std;



int n,d;
int ans;
int Case = 0;

pair<double,double> coordinate[N];
pair<double,double> range[N];

bool comp(pair<double,double> a,pair<double,double> b)
{
     return a.second < b.second;
}

int main()
{
    while(cin>>n>>d)
    {
        if(n == 0 && d == 0)
            break;
        else if(d < 0)
        {
            Case++;
            for(int i = 0;i<n;i++)
                cin>>coordinate[i].first>>coordinate[i].second;
            ans = -1;
        }

        else
        {
            double border;
            for(int i = 0;i<n;i++)
            {
                cin>>coordinate[i].first>>coordinate[i].second;
                if(coordinate[i].second > d)
                    ans = -1;
                border = sqrt((d*d) - (coordinate[i].second * coordinate[i].second));
                range[i].first = coordinate[i].first - border;
                range[i].second = coordinate[i].first + border;
            }

            if(ans != -1)
            {
                sort(range,range+n,comp);

                double start_interval = range[0].second;
                ans = 1;
                for(int i = 1;i<n;i++)
                {
                    if(range[i].first <= start_interval)
                        continue;
                    else
                    {
                        ans++;
                        start_interval = range[i].second;
                    }
                }
            }
            Case++;
        }

        cout<<"Case "<<Case<<": "<<ans<<endl;
        ans = 0;
    }

    return 0;
}
