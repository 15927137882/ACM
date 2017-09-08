/* ���鼯�ṹ */
/*
Description
���������������ද��A,B,C�������ද���ʳ������������Ȥ�Ļ��Ρ�A��B�� B��C��C��A��
����N�������1��N��š�ÿ�����ﶼ��A,B,C�е�һ�֣��������ǲ���֪������������һ�֡�
����������˵������N�����������ɵ�ʳ������ϵ����������
��һ��˵����"1 X Y"����ʾX��Y��ͬ�ࡣ
�ڶ���˵����"2 X Y"����ʾX��Y��
���˶�N���������������˵����һ���һ���˵��K�仰����K�仰�е�����ģ��е��Ǽٵġ���һ�仰������������֮һʱ����仰���Ǽٻ�����������滰��
1��	��ǰ�Ļ���ǰ���ĳЩ��Ļ���ͻ�����Ǽٻ���
2��	��ǰ�Ļ���X��Y��N�󣬾��Ǽٻ���
3��	��ǰ�Ļ���ʾX��X�����Ǽٻ���
��������Ǹ��ݸ�����N��1 <= N <= 50,000����K�仰��0 <= K <= 100,000��������ٻ���������

Input
��һ������������N��K����һ���ո�ָ���
����K��ÿ�������������� D��X��Y������֮����һ���ո����������D��ʾ˵�������ࡣ
��D=1�����ʾX��Y��ͬ�ࡣ
��D=2�����ʾX��Y��

Output
ֻ��һ����������ʾ�ٻ�����Ŀ��

Sample Input
100 7
1 101 1
2 1 2
2 2 3
2 3 3
1 1 3
2 3 1
1 5 5

Sample Output
3
*/
#include <stdio.h>

const int MAX_N = 50050;

int par[3*MAX_N];
int rank_[3*MAX_N];

void init(int n);
int find(int x);
void unite(int x,int y);
bool same(int x,int y);

using namespace std;

int main()
{
    int N,K;
    int ans = 0;
    scanf("%d%d",&N,&K);
   // for(int i=0;i<K;i++)
   //     cin>>T[i]>>X[i]>>Y[i];
    init(3*N);

    int t;
    int x,y;
    while(K--)
    {
        scanf("%d%d%d",&t,&x,&y);
        x--;
        y--;

        if(x < 0 || x >= N || y < 0 || y >= N)
        {
            ans++;
            continue;
        }
        if(t == 1)
        {
            if(same(x,y+N) || same(x,y+2*N)) ans++;
            else
            {
                unite(x,y);
                unite(x+N,y+N);
                unite(x+2*N,y+2*N);
            }
        }
        else
        {
            if(same(x,y) || same(x,y+2*N)) ans++;
            else
            {
                unite(x,y+N);
                unite(x+N,y+2*N);
                unite(x+2*N,y);
            }
        }
    }

    printf("%d\n",ans);

    return 0;
}


//���鼯
void init(int n)
{
    for(int i = 0;i<n;i++)
    {
        par[i] = i;
        rank_[i] = 0;
    }
}

int find(int x) //�ҵ���Ԫ�صĸ�
{
    if(par[x] == x) return x;
    else return par[x] = find(par[x]);  //����Ѱ�Ҹ�Ԫ�صĸ��׽ڵ㲢����·��ѹ��
}

void unite(int x,int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return;
    if(rank_[x]<rank_[y])   //ƽ�⴦��
        par[x] = y;
    else
    {
        par[y] = x;
        if(rank_[x] == rank_[y]) rank_[x]++;
    }
}

bool same(int x,int y)
{
    return find(x) == find(y);
}
