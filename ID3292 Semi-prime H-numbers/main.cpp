/*
 * Description

This problem is based on an exercise of David Hilbert, who pedagogically suggested that one study the theory of 4n+1 numbers. Here, we do only a bit of that.

An H-number is a positive number which is one more than a multiple of four: 1, 5, 9, 13, 17, 21,... are the H-numbers. For this problem we pretend that these are the only numbers. The H-numbers are closed under multiplication.

As with regular integers, we partition the H-numbers into units, H-primes, and H-composites. 1 is the only unit. An H-number h is H-prime if it is not the unit, and is the product of two H-numbers in only one way: 1 × h. The rest of the numbers are H-composite.

For examples, the first few H-composites are: 5 × 5 = 25, 5 × 9 = 45, 5 × 13 = 65, 9 × 9 = 81, 5 × 17 = 85.

Your task is to count the number of H-semi-primes. An H-semi-prime is an H-number which is the product of exactly two H-primes. The two H-primes may be equal or different. In the example above, all five numbers are H-semi-primes. 125 = 5 × 5 × 5 is not an H-semi-prime, because it's the product of three H-primes.

Input

Each line of input contains an H-number ≤ 1,000,001. The last line of input contains 0 and this line should not be processed.

Output

For each inputted H-number h, print a line stating h and the number of H-semi-primes between 1 and h inclusive, separated by one space in the format shown in the sample.

Sample Input

21
85
789
0
Sample Output

21 0
85 5
789 62

 使用变形的埃氏筛法打表
 */

#include<cstdio>
#include <cstring>

#define maxn 1000010
int H_primes[maxn],H_semi_primes[maxn];
int num_primes[maxn];

void table()
{
    memset(H_primes,1,sizeof(H_primes));
    int i,j;
    H_primes[1]=0;
    //*********艾氏筛法********
    for(i=5;i<maxn;i+=4)
    {
        if(!H_primes[i])    //是组合数的话就跳过
            continue;
        for(j=i*5;j<maxn;j+=i*4)      //是素数
            H_primes[j]=0;
    }
    //*************************
    int cnt;
    for(i=5;i<maxn;i+=4)//确定H-semi-primes
    {
        for(j=5;j<maxn;j+=4)
        {
            if(i*j>maxn)//注意这里优化
                break;
            if(H_primes[i]&&H_primes[j])
                H_semi_primes[i*j]=1;
        }
    }
    cnt=0;
    for(i=5;i<maxn;++i)//统计从0到i的H-semi-primes的个数
    {
        if(H_semi_primes[i])
            num_primes[i]=++cnt;
        else
            num_primes[i]=cnt;
    }
}

int main()
{
    int n;
    table();
    while(scanf("%d",&n)&&n)
        printf("%d %d\n",n,num_primes[n]);
    return 0;
}
