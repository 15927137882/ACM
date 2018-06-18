/*
Description

Farmer John went to cut some wood and left N (2 �� N �� 100,000) cows eating the grass, as usual. When he returned, he found to his horror that the cluster of cows was in his garden eating his beautiful flowers. Wanting to minimize the subsequent damage, FJ decided to take immediate action and transport each cow back to its own barn.

Each cow i is at a location that is Ti minutes (1 �� Ti �� 2,000,000) away from its own barn. Furthermore, while waiting for transport, she destroys Di (1 �� Di �� 100) flowers per minute. No matter how hard he tries, FJ can only transport one cow at a time back to her barn. Moving cow i to its barn requires 2 �� Ti minutes (Ti to get there and Ti to return). FJ starts at the flower patch, transports the cow to its barn, and then walks back to the flowers, taking no extra time to get to the next cow that needs transport.

Write a program to determine the order in which FJ should pick up the cows so that the total number of flowers destroyed is minimized.

Input

Line 1: A single integer N
Lines 2..N+1: Each line contains two space-separated integers, Ti and Di, that describe a single cow's characteristics
Output

Line 1: A single integer that is the minimum number of destroyed flowers
Sample Input

6
3 1
2 5
2 3
3 2
4 1
1 6
Sample Output

86
Hint

FJ returns the cows in the following order: 6, 2, 3, 4, 1, 5. While he is transporting cow 6 to the barn, the others destroy 24 flowers; next he will take cow 2, losing 28 more of his beautiful flora. For the cows 3, 4, 1 he loses 16, 12, and 6 flowers respectively. When he picks cow 5 there are no more cows damaging the flowers, so the loss for that cow is zero. The total flowers lost this way is 24 + 28 + 16 + 12 + 6 = 86.
̰�ģ�
ѡ�����,
1 �ڶ����м�ѡ��֮��,�ܸ���time/eatС���Ǹ�Ϊ���Ž�
֤��:
�������� A,B,���Էֱ�Ϊ�ֱ�ΪeatA,timeA,eatB,timeB
ѡA��ʱ����ʧtimeA*eatB
ѡB��ʱ����ʧtimeB*eatA
˫��ͬ����eatA*eatB.
��time/eatΪһ����ı���x
����֤��xС���Ǹ�Ϊ���Ž�.

����,�����һ��ѡ����n��ѡ���������ŵ�,��ô(�ڰ������ѡ���)n-1��ѡ����Ҳ�����ŵ�,

�������,���һ��ѡ����n-1��ѡ���в������ŵ�,��ô��n��ѡ����Ҳ�������ŵ�.

����,���һ��ѡ����2��ѡ���в������ŵ�,��ô��n��ѡ����Ҳ�������ŵ�

���Խ����ձ���x����,�����ҵ�һ����A��������������ȽϵĹ����ж������ŵ�,

����˵����n-1������������������֮��ѡһ����ѡ���ʱ�������ŵ�,������n-1���������Ž��.
������A��nͷ�������Ž�

(���֤������x��ֵ���ǲ�ͬ��,��x��ͬ��֤��ֻ��Ҫ������,�ĳ�û�и��ż��� ^_^ )
*/

#include <cstdio>
#include <utility>
#include <algorithm>

typedef long long ll;

using namespace std;

int N;

bool cmp(pair<int,int> a,pair<int,int> b)
{
    return (float)a.first / (float)a.second <= (float)b.first / (float)b.second;
}

int main()
{
    scanf("%d",&N);
    pair<int,int> cow[N];
    ll sum = 0;
    for(int i = 0;i<N;i++)
    {
        scanf("%d%d",&cow[i].first,&cow[i].second);
        sum += cow[i].second;
    }


    sort(cow,cow+N,cmp);
    ll ans = 0;
    for(int i = 0;i<N;i++)
    {
        sum -= cow[i].second;
        ans += 2 * sum * cow[i].first;
    }

    printf("%I64d\n",ans);

    return 0;
}
