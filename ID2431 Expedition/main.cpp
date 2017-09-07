/*
Description
A group of cows grabbed a truck and ventured on an expedition deep into the jungle. Being rather poor drivers, the cows unfortunately managed to run over a rock and puncture the truck's fuel tank. The truck now leaks one unit of fuel every unit of distance it travels. 
To repair the truck, the cows need to drive to the nearest town (no more than 1,000,000 units distant) down a long, winding road. On this road, between the town and the current location of the truck, there are N (1 <= N <= 10,000) fuel stops where the cows can stop to acquire additional fuel (1..100 units at each stop). 
The jungle is a dangerous place for humans and is especially dangerous for cows. Therefore, the cows want to make the minimum possible number of stops for fuel on the way to the town. Fortunately, the capacity of the fuel tank on their truck is so large that there is effectively no limit to the amount of fuel it can hold. The truck is currently L units away from the town and has P units of fuel (1 <= P <= 1,000,000). 
Determine the minimum number of stops needed to reach the town, or if the cows cannot reach the town at all. 

Input
* Line 1: A single integer, N 
* Lines 2..N+1: Each line contains two space-separated integers describing a fuel stop: The first integer is the distance from the town to the stop; the second is the amount of fuel available at that stop. 
* Line N+2: Two space-separated integers, L and P

Output
* Line 1: A single integer giving the minimum number of fuel stops necessary to reach the town. If it is not possible to reach the town, output -1.

Sample Input
4
4 4
5 2
11 5
15 10
25 10

Sample Output
2

Hint
INPUT DETAILS: 
The truck is 25 units away from the town; the truck has 10 units of fuel. Along the road, there are 4 fuel stops at distances 4, 5, 11, and 15 from the town (so these are initially at distances 21, 20, 14, and 10 from the truck). These fuel stops can supply up to 4, 2, 5, and 10 units of fuel, respectively. 

OUTPUT DETAILS: 
Drive 10 units, stop to acquire 10 more units of fuel, drive 4 more units, stop to acquire 5 more units of fuel, then drive to the town.
*/

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct GasStation
{
    int a,b;
};


bool operator< (const GasStation &t1, const GasStation &t2)
{
    return t1.b<t2.b;
}

bool cmp(const GasStation &t1, const GasStation &t2)
{
    return t1.a < t2.a;
}


int main()
{
    int N;
    cin>>N;
    GasStation *A = new GasStation[N+1];
    for(int i = 0;i<N;i++)
        cin>>A[i].a>>A[i].b;
    int L,P;
    cin>>L>>P;
    for(int i = 0;i<N;i++)
        A[i].a = L - A[i].a;
    A[N].a = L;
    A[N].b = 0;
    N++;

    sort(A,A+N,cmp);

    priority_queue<GasStation> que;
    int ans = 0,pos = 0,tank = P;

    for(int i = 0;i<N;i++)
    {
        int d = A[i].a-pos;
        /* 一直加油，加到能跑为止 */
        while(tank-d<0)
        {
            if(que.empty())
            {
                cout<<-1;
                return 0;
            }
            tank += que.top().b;
            que.pop();
            ans++;
        }
        tank-=d;
        pos = A[i].a;
        que.push(A[i]);
    }

    cout<<ans;


    delete [] A;

    return 0;
}

