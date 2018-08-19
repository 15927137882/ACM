/*
 * Description

Demy has n jewels. Each of her jewels has some value vi and weight wi.

Since her husband John got broke after recent financial crises, Demy has decided to sell some jewels. She has decided that she would keep k best jewels for herself. She decided to keep such jewels that their specific value is as large as possible. That is, denote the specific value of some set of jewels S = {i1, i2, …, ik} as

.

Demy would like to select such k jewels that their specific value is maximal possible. Help her to do so.

Input

The first line of the input file contains n — the number of jewels Demy got, and k — the number of jewels she would like to keep (1 ≤ k ≤ n ≤ 100 000).

The following n lines contain two integer numbers each — vi and wi (0 ≤ vi ≤ 106, 1 ≤ wi ≤ 106, both the sum of all vi and the sum of all wi do not exceed 107).

Output

Output k numbers — the numbers of jewels Demy must keep. If there are several solutions, output any one.

Sample Input

3 2
1 1
1 2
1 3
Sample Output

1 2
 二分搜索
 */

#include <cstdio>
#include <algorithm>

int n,k;
int a[1000008];
int b[1000008];


struct jewels{
    double value;
    int id;
    bool operator<(const jewels& b) const
    {
        return value < b.value;
    }
};

jewels y[1000008];

bool judge(double x)
{
    for(int i = 0;i < n;i++)
    {
        y[i].value = a[i] - x*b[i];
        y[i].id = i + 1;
    }


    std::sort(y,y+n);

    double sum = 0;
    for(int i = 0;i<k;i++)
        sum += y[n-i-1].value;
    return sum >= 0;
}

int main()
{
    double max_s = 0;
    scanf("%d%d",&n,&k);
    for(int i = 0;i<n;i++)
    {
        scanf("%d%d",&a[i],&b[i]);
        max_s = std::max(max_s, (double)a[i] / b[i]);
    }


    double lb = 0;
    double ub = max_s;
    double mid;
    for(int i = 0;i<50;i++)
    {
        mid = (lb + ub) / 2;
        if(judge(mid))
            lb = mid;
        else
            ub = mid;
    }

    for(int i = 0;i<k;i++)
        printf("%d ",y[n-i-1].id);

    printf("\n");

    return 0;
}