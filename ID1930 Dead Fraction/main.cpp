/*
 * Description

Mike is frantically scrambling to finish his thesis at the last minute. He needs to assemble all his research notes into vaguely coherent form in the next 3 days. Unfortunately, he notices that he had been extremely sloppy in his calculations. Whenever he needed to perform arithmetic, he just plugged it into a calculator and scribbled down as much of the answer as he felt was relevant. Whenever a repeating fraction was displayed, Mike simply reccorded the first few digits followed by "...". For instance, instead of "1/3" he might have written down "0.3333...". Unfortunately, his results require exact fractions! He doesn't have time to redo every calculation, so he needs you to write a program (and FAST!) to automatically deduce the original fractions.
To make this tenable, he assumes that the original fraction is always the simplest one that produces the given sequence of digits; by simplest, he means the the one with smallest denominator. Also, he assumes that he did not neglect to write down important digits; no digit from the repeating portion of the decimal expansion was left unrecorded (even if this repeating portion was all zeroes).
Input

There are several test cases. For each test case there is one line of input of the form "0.dddd..." where dddd is a string of 1 to 9 digits, not all zero. A line containing 0 follows the last case.
Output

For each case, output the original fraction.
Sample Input

0.2...
0.20...
0.474612399...
0
Sample Output

2/9
1/5
1186531/2500000
Hint

Note that an exact decimal fraction has two repeating expansions (e.g. 1/5 = 0.2000... = 0.19999...).

 * 纯循环
用9做分母，有多少个循环数就几个9，比如0.3，3的循环就是9分之3，0.654，654的循环就是999分之654， 0.9，9的循环就是9分之9（1），以此类推。

混循环
先来看几个例子

例：把混循环小数0.228˙化为分数：

解：0.228˙

=[（228/1000）+8/9000）]

=228/（900+100）+8/9000

=[（228/900）-（228/9000）]+（8/9000）

=（228/900）+[（8/9000）-（228/9000）]

=（228/900）-（22/900）

=（228-22）/900

=206/900

=103/450；

例：把混循环小数0.123˙68˙化成分数：

解：0.123˙68˙=(0.12368+0.00000˙68˙)

=(12368/100000)+（68/9900000）

=[（12368/99000）-（12368/990000）]+（68/9900000）

=（12368/99000）+[（68/9900000）-（12368/9900000）]

=（12368/99000）-（12300/9900000）

=(12368-123)/99000

公式

1.用9和0做分母，首先有几个循环节就几个9，接着有几个没加入循环的数就加几个0，再用小数点后面的数减 没加入循环的数，比如0.43，3的循环，
 有一位数没加入循环，就在9后面加一个0做分母，再用43减4做分子，得 90分之39，0.145，5的循环就用9后面加2个0做分母，再用145减14做分子，
 得900分之131，0.549，49的循环，就 用99后面加1个0做分母，用549减5做分子，最后得990分之545，以此类推，能约分的要化简。
2.关键点在于题目在玩文字游戏，循环小数到底从哪一位开始没有明说，所以无脑暴力穷举一遍就行了。


 */

#include <iostream>
#include <string>
#include <numeric>
#include <limits>
#include <cstdlib>

using namespace std;

typedef unsigned long long ULL;

ULL ten_power(unsigned int a)
{
    ULL ans = 1;
    while(a--)
        ans *= 10;
    return ans;

}

ULL gcd(ULL a,ULL b)
{
    if(b==0)
        return a;
    else
        return gcd(b,a%b);
}

int main()
{
    string origin_input;
    while(cin>>origin_input)
    {
        if(origin_input == "0")
            break;
        string sub_string = origin_input.substr(2,origin_input.length()-5);
        ULL fraction = atoi(sub_string.c_str());
        int length = sub_string.length();
        ULL miny = numeric_limits<ULL>::max();
        ULL minx = 0;
        for(int i = 1;i<=length;i++)
        {
            string nonrepeat = sub_string.substr(0,length-i);
            ULL x = fraction - atoi(nonrepeat.c_str());
            ULL y = ten_power(length) - ten_power(length - i);
            ULL common = gcd(x,y);
            x/=common;
            y/=common;
            if(y<miny)
            {
                minx = x;
                miny = y;
            }
        }
        cout<<minx<<"/"<<miny<<endl;
    }
    return 0;
}