/* 并查集结构 */
/*
Description
动物王国中有三类动物A,B,C，这三类动物的食物链构成了有趣的环形。A吃B， B吃C，C吃A。
现有N个动物，以1－N编号。每个动物都是A,B,C中的一种，但是我们并不知道它到底是哪一种。
有人用两种说法对这N个动物所构成的食物链关系进行描述：
第一种说法是"1 X Y"，表示X和Y是同类。
第二种说法是"2 X Y"，表示X吃Y。
此人对N个动物，用上述两种说法，一句接一句地说出K句话，这K句话有的是真的，有的是假的。当一句话满足下列三条之一时，这句话就是假话，否则就是真话。
1）	当前的话与前面的某些真的话冲突，就是假话；
2）	当前的话中X或Y比N大，就是假话；
3）	当前的话表示X吃X，就是假话。
你的任务是根据给定的N（1 <= N <= 50,000）和K句话（0 <= K <= 100,000），输出假话的总数。

Input
第一行是两个整数N和K，以一个空格分隔。
以下K行每行是三个正整数 D，X，Y，两数之间用一个空格隔开，其中D表示说法的种类。
若D=1，则表示X和Y是同类。
若D=2，则表示X吃Y。

Output
只有一个整数，表示假话的数目。

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


//并查集
void init(int n)
{
    for(int i = 0;i<n;i++)
    {
        par[i] = i;
        rank_[i] = 0;
    }
}

int find(int x) //找到该元素的根
{
    if(par[x] == x) return x;
    else return par[x] = find(par[x]);  //迭代寻找该元素的父亲节点并进行路径压缩
}

void unite(int x,int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return;
    if(rank_[x]<rank_[y])   //平衡处理
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
