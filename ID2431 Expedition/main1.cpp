#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct GasStation
{
    int distance;
    int capacity;
    int next;
};

struct Car
{
    int now_capacity;
    int current_distance;
    int next;
};

bool operator< (const GasStation &t1, const GasStation &t2)
{
    return t1.capacity<t2.capacity;
}

bool cmp(const GasStation &t1, const GasStation &t2)
{
    return t1.distance > t2.distance;
}

int main()
{
    int N;
    cin>>N;

    GasStation *p = new GasStation[N+1];
    for(int i = N-1;i>=0;i--) cin>>p[i].distance>>p[i].capacity;
    p[N].distance = 0;
    p[N].capacity = 0;
    p[N].next = 0;
    sort(p,p+N+1,cmp);

    int total_distance;
    cin>>total_distance;
    for(int i = 0;i<N+1;i++)
        p[i].distance = total_distance -p[i].distance;
    for(int i = 0;i<N-1;i++)
        p[i].next = p[i+1].distance-p[i].distance;
    p[N-1].next = total_distance-p[N-1].next;

    int initial_capacity;
    cin>>initial_capacity;

    priority_queue<GasStation> candidate;

    Car car;
    car.current_distance = 0;
    car.now_capacity = initial_capacity;
    car.next = p[0].distance;

    int ans = 0;
    for(int i = 0;i<N+1;)
    {
        if(car.now_capacity - car.next >= 0)
        {
            car.now_capacity -= car.next;
            candidate.push(p[i]);
            car.next = p[i].next;
            //cout<<"pass"<<car.now_capacity<<endl;
            i++;
        }
        else if(car.now_capacity - car.next < 0)
        {
            if(candidate.empty())
            {
                cout<<-1<<endl;
                delete [] p;
                return 0;
            }
            else
            {
                car.now_capacity += candidate.top().capacity;
                //cout<<"plus"<<candidate.top().capacity<<endl;
                candidate.pop();
                ans++;
            }
        }
    }
    cout<<ans<<endl;
    //for(int i = 0;i<N;i++) cout<<"["<<p[i].distance<<","<<p[i].capacity<<"]\n";
    //cout<<"["<<car.current_distance<<","<<car.now_capacity<<"]\n";

    delete [] p;
    return 0;
}
