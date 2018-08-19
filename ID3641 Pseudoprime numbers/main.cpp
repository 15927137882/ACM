/*
 * Description

Fermat's theorem states that for any prime number p and for any integer a > 1, ap = a (mod p). That is, if we raise a to the pth power and divide by p, the remainder is a. Some (but not very many) non-prime values of p, known as base-a pseudoprimes, have this property for some a. (And some, known as Carmichael Numbers, are base-a pseudoprimes for all a.)

Given 2 < p ≤ 1000000000 and 1 < a < p, determine whether or not p is a base-a pseudoprime.

Input

Input contains several test cases followed by a line containing "0 0". Each test case consists of a line containing p and a.

Output

For each test case, output "yes" if p is a base-a pseudoprime; otherwise output "no".

Sample Input

3 2
10 3
341 2
341 3
1105 2
1105 3
0 0
Sample Output

no
no
yes
no
yes
yes

 关键在于快速求幂与快速求积，并注意及时取余，防止溢出
 */

#include <iostream>
typedef long long LL;

bool is_prime(LL p)
{
    if(p == 1)
        return false;
    for(int i = 2;i*i<=p;i++)
    {
        if(p % i == 0)
            return false;
    }
    return true;
}

LL multi(LL a,LL b,LL mod)
{
    LL ans = 0;
    a = a % mod;
    while (b)
    {
        if(b & 1)
        {
            ans = ans + a;
            while(ans >= mod) ans -= mod;
        }
        b >>= 1;
        a <<= 1;
        while(a >= mod) a -= mod;
    }

    return ans;
}

bool test(LL p,LL a)
{
    if(is_prime(p))
        return false;
    LL mod = p;
    LL multiplier = a % mod;
    LL ans = 1;
    while(p)
    {
        if(p & 1) ans = multi(ans,multiplier,mod);
        p>>=1;
        multiplier = multi(multiplier,multiplier,mod);
    }
    return a == ans;
}


using namespace std;
int main()
{
    int p,a;

    while(cin>>p>>a && p && a)
    {
        if(test(p,a))
            cout<<"yes\n";
        else
            cout<<"no\n";
    }
    return 0;
}