/*
Description

        A straight dirt road connects two fields on FJ's farm, but it changes elevation more than FJ would like. His cows do not mind climbing up or down a single slope, but they are not fond of an alternating succession of hills and valleys. FJ would like to add and remove dirt from the road so that it becomes one monotonic slope (either sloping up or down).

You are given N integers A1, ... , AN (1 ≤ N ≤ 2,000) describing the elevation (0 ≤ Ai ≤ 1,000,000,000) at each of N equally-spaced positions along the road, starting at the first field and ending at the other. FJ would like to adjust these elevations to a new sequence B1, . ... , BN that is either nonincreasing or nondecreasing. Since it costs the same amount of money to add or remove dirt at any position along the road, the total cost of modifying the road is

|A1 - B1| + |A2 - B2| + ... + |AN - BN |
Please compute the 要使minimum cost of grading his road so it becomes a continuous slope. FJ happily informs you that signed 32-bit integers can certainly be used to compute the answer.

Input

        * Line 1: A single integer: N
        * Lines 2..N+1: Line i+1 contains a single integer elevation: Ai

        Output

* Line 1: A single integer that is the minimum cost for FJ to grade his dirt road so it becomes nonincreasing or nondecreasing in elevation.

Sample Input

7
1
3
2
4
5
3
9
Sample Output
3
动态规划+数组滚动，因为要使修改后的海拔最小，则修改后的结果要么与前者一致，要么与后者一致，所以可以选择的结果一定是已经存在与原序列中的结果
将这些候选结果存放于数组B中(B是升序，求出来的是让道路持续上升的情况；如果是让B降序，求出来的是让道路持续下降的情况；
可以对比两个结果，求出最优解，本题数据较弱，只需考虑道路持续上升的情况即可)。
设dp[i][j]表示要让长度为i的序列单调且最后一个元素为B[j]，需要的最小成本。
则dp[i][j] = min(dp[i-1][0..j]) + |A[i] - B[j]|
因为只涉及两个阶段的状态，所以可以使用滚动数组来提高存储效率
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int A[2005],B[2005];
int dp[2][2005];
int candidate_num;

int main()
{
    int road_length;
    scanf("%d",&road_length);
    for(int i = 0;i<road_length;i++)
        scanf("%d",&A[i]);
    memcpy(B,A,sizeof(A));
    sort(B,B+road_length);

    // collect possible elevation
    candidate_num = unique(B,B+road_length) - B;
//    printf("%d\n",candidate_num);
//    for(int i = 0;i<candidate_num;i++)
//        printf("%d ",B[i]);

    for(int i = 0;i<candidate_num;i++)
        dp[0][i] = 0;
    int *pre = dp[0],*nxt = dp[1];
    for(int i = 1;i<=road_length;i++)
    {
        int tmp = pre[0];
        for(int j = 0;j<candidate_num;j++)
        {
            tmp = min(tmp,pre[j]);
            nxt[j] = tmp + abs(A[i]-B[j]);
        }
        swap(pre,nxt);
    }

    int ans = nxt[0];
    for(int i = 1 ; i<candidate_num;i++)
        ans = min(ans,nxt[i]);

    printf("%d\n",ans);
    return 0;
}