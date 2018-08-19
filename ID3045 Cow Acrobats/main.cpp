/*
 * Description

Farmer John's N (1 <= N <= 50,000) cows (numbered 1..N) are planning to run away and join the circus. Their hoofed feet prevent them from tightrope walking and swinging from the trapeze (and their last attempt at firing a cow out of a cannon met with a dismal failure). Thus, they have decided to practice performing acrobatic stunts.

The cows aren't terribly creative and have only come up with one acrobatic stunt: standing on top of each other to form a vertical stack of some height. The cows are trying to figure out the order in which they should arrange themselves ithin this stack.

Each of the N cows has an associated weight (1 <= W_i <= 10,000) and strength (1 <= S_i <= 1,000,000,000). The risk of a cow collapsing is equal to the combined weight of all cows on top of her (not including her own weight, of course) minus her strength (so that a stronger cow has a lower risk). Your task is to determine an ordering of the cows that minimizes the greatest risk of collapse for any of the cows.
Input

* Line 1: A single line with the integer N.

* Lines 2..N+1: Line i+1 describes cow i with two space-separated integers, W_i and S_i.
Output

* Line 1: A single integer, giving the largest risk of all the cows in any optimal ordering that minimizes the risk.
Sample Input

3
10 3
2 5
3 3
Sample Output

2
Hint

OUTPUT DETAILS:

Put the cow with weight 10 on the bottom. She will carry the other two cows, so the risk of her collapsing is 2+3-3=2. The other cows have lower risk of collapsing.
贪心搜索即可
 */

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

int N;

struct cow{
    int weight,strength;
    bool operator<(const cow& b) const
    {
        return weight + strength > b.weight + b.strength;
    }
};

cow Cow[50016];

int main()
{
    int total = 0;
    cin>>N;
    for(int i =0;i<N;i++)
    {
        scanf("%d%d",&Cow[i].weight,&Cow[i].strength);
        total += Cow[i].weight;
    }


    sort(Cow,Cow+N);
    for(int i = 0;i<N;i++)
        cout<<Cow[i].weight<<endl;

    int risk = 0x80808080;
    for(int i = 0;i<N;i++)
    {
        total -= Cow[i].weight;
        risk = max(risk,total - Cow[i].strength);
    }

    cout<<risk;
    return 0;
}