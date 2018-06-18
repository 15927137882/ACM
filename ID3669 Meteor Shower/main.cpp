/*
Description

Bessie hears that an extraordinary meteor shower is coming; reports say that these meteors will crash into earth and destroy anything they hit. Anxious for her safety, she vows to find her way to a safe location (one that is never destroyed by a meteor) . She is currently grazing at the origin in the coordinate plane and wants to move to a new, safer location while avoiding being destroyed by meteors along her way.

The reports say that M meteors (1 �� M �� 50,000) will strike, with meteor i will striking point (Xi, Yi) (0 �� Xi �� 300; 0 �� Yi �� 300) at time Ti (0 �� Ti  �� 1,000). Each meteor destroys the point that it strikes and also the four rectilinearly adjacent lattice points.

Bessie leaves the origin at time 0 and can travel in the first quadrant and parallel to the axes at the rate of one distance unit per second to any of the (often 4) adjacent rectilinear points that are not yet destroyed by a meteor. She cannot be located on a point at any time greater than or equal to the time it is destroyed).

Determine the minimum time it takes Bessie to get to a safe place.

Input

* Line 1: A single integer: M
* Lines 2..M+1: Line i+1 contains three space-separated integers: Xi, Yi, and Ti

Output

* Line 1: The minimum time it takes Bessie to get to a safe place or -1 if it is impossible.

Sample Input

4
0 0 2
2 1 2
1 1 2
0 3 5
Sample Output

5
*/

/*����������Ϊ���Թ������·�������⣬�յ��ǰ�ȫ�����ҵ�ͼ����Щ����Ҫ�ڹ涨�����ڲſɷ��ʣ��������ǽ��
  ע�ⲻҪ��ͬһ�������Σ���Ϊ�ⲻ������ѡ�����뺯��Ҫѡ��scanf�������TLE����������ͻ�����ͨ��bfs����
  ��·������
*/

#include <iostream>
#include <cstring>
#include <queue>
#include <cstdio>

using namespace std;

struct node
{
    int x,y,time;
};

int dx[5] = {1,0,-1,0,0} , dy[5] = {0,-1,0,1,0};
int M;
int Map[310][310];

int bfs()
{
    if(Map[0][0] == -1)     //һ��ʼ�ڰ�ȫ��
        return 0;
    if(Map[0][0] == 0)      //һ��ʼ������
        return -1;
    queue<node> que;
    node now,next;
    now = {0,0,0};
    que.push(now);
    while(!que.empty())
    {
        now = que.front();
        que.pop();
        for(int i = 0;i < 4;i++)
        {
            next.x = now.x + dx[i];
            next.y = now.y + dy[i];
            next.time = now.time + 1;
            if(next.x < 0 || next.x >= 310 || next.y < 0 || next.y >= 310)
                continue;
            else if(Map[next.x][next.y] == -1)
                return next.time;
            else if(Map[next.x][next.y] <= next.time)
                continue;
            else
            {
                Map[next.x][next.y] = next.time;		//�����߻�ͷ·
                que.push(next);
            }
        }
    }

    return -1;
}


int main()
{
    while(cin>>M && M != 0)
    {
        memset(Map,-1,sizeof(Map));
        int x,y,t,tmpx,tmpy;
        while(M--)
        {
            scanf("%d%d%d",&x,&y,&t);
            for(int i = 0;i<5; i++)
            {
                tmpx = x + dx[i];
                tmpy = y + dy[i];
                if(tmpx >= 310 || tmpx < 0 || tmpy >= 310 || tmpy < 0)
                    continue;
                else if(Map[tmpx][tmpy] == -1)
                    Map[tmpx][tmpy] = t;
                else
                    Map[tmpx][tmpy] = min(Map[tmpx][tmpy],t);
            }
        }
        cout<<bfs()<<endl;
    }
    return 0;
}
