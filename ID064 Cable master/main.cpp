/*
Description

        Inhabitants of the Wonderland have decided to hold a regional programming contest. The Judging Committee has volunteered and has promised to organize the most honest contest ever. It was decided to connect computers for the contestants using a "star" topology - i.e. connect them all to a single central hub. To organize a truly honest contest, the Head of the Judging Committee has decreed to place all contestants evenly around the hub on an equal distance from it.
To buy network cables, the Judging Committee has contacted a local network solutions provider with a request to sell for them a specified number of cables with equal lengths. The Judging Committee wants the cables to be as long as possible to sit contestants as far from each other as possible.
The Cable Master of the company was assigned to the task. He knows the length of each cable in the stock up to a centimeter,and he can cut them with a centimeter precision being told the length of the pieces he must cut. However, this time, the length is not known and the Cable Master is completely puzzled.
You are to help the Cable Master, by writing a program that will determine the maximal possible length of a cable piece that can be cut from the cables in the stock, to get the specified number of pieces.
Input

        The first line of the input file contains two integer numb ers N and K, separated by a space. N (1 = N = 10000) is the number of cables in the stock, and K (1 = K = 10000) is the number of requested pieces. The first line is followed by N lines with one number per line, that specify the length of each cable in the stock in meters. All cables are at least 1 meter and at most 100 kilometers in length. All lengths in the input file are written with a centimeter precision, with exactly two digits after a decimal point.
Output

        Write to the output file the maximal length (in meters) of the pieces that Cable Master may cut from the cables in the stock to get the requested number of pieces. The number must be written with a centimeter precision, with exactly two digits after a decimal point.
If it is not possible to cut the requested number of pieces each one being at least one centimeter long, then the output file must contain the single number "0.00" (without quotes).
Sample Input

4 11
8.02
7.43
4.57
5.39
Sample Output
2.00

假设可以产生K条长度为x的绳子，那么对于长度小于x的绳子，同样可以生成Kt条
 基于此性质,使用二分搜索不断逼近那个最大的长度即可。
*/

#include <cstdio>
#include <cmath>

const double inf = 100000;
double cable[10000];
int number,K;

bool C(double x)
{
    int num = 0;
    for(int i = 0;i<number;i++)
        num += int(cable[i] / x);
    return num >= K;
}

int main()
{
    scanf("%d%d",&number,&K);
    for(int i = 0;i<number;i++)
        scanf("%lf",&cable[i]);
    double lb = 0;
    double ub = inf;
    double mid;
    for(int i = 0;i<100;i++)
    {
        mid = (lb + ub) / 2;
        if(C(mid))
            lb = mid;
        else
            ub = mid;
    }

    printf("%.2f\n",floor(ub * 100) / 100); //不作舍入
    return 0;
}