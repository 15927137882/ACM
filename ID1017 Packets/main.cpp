/*
Description

A factory produces products packed in square packets of the same height h and of the sizes 1*1, 2*2, 3*3, 4*4, 5*5, 6*6. These products are always delivered to customers in the square parcels of the same height h as the products have and of the size 6*6. Because of the expenses it is the interest of the factory as well as of the customer to minimize the number of parcels necessary to deliver the ordered products from the factory to the customer. A good program solving the problem of finding the minimal number of parcels necessary to deliver the given products according to an order would save a lot of money. You are asked to make such a program.
Input

The input file consists of several lines specifying orders. Each line specifies one order. Orders are described by six integers separated by one space representing successively the number of packets of individual size from the smallest size 1*1 to the biggest size 6*6. The end of the input file is indicated by the line containing six zeros.
Output

The output file contains one line for each line in the input file. This line contains the minimal number of parcels into which the order from the corresponding line of the input file can be packed. There is no line in the output file corresponding to the last ``null'' line of the input file.
Sample Input

0 0 4 0 0 1
7 5 1 0 0 0
0 0 0 0 0 0
Sample Output

2
1
贪心O(1)复杂度，此题技巧性较大，记得先排面积大的，后排面积小的，以及向上取整的操作
*/


#include <cstdio>

using namespace std;

int parcel[7];
int left[4] = {0,5,3,1};
int ans;

int main()
{
    while(scanf("%d%d%d%d%d%d",&parcel[1],&parcel[2],&parcel[3],&parcel[4],&parcel[5],&parcel[6]) &&
          parcel[1]+parcel[2]+parcel[3]+parcel[4]+parcel[5]+parcel[6] != 0)
    {
        ans = 0;
        ans += parcel[6] + parcel[5] + parcel[4] + ( (parcel[3]+3)/4 );     // x+(n-1)/n 是 x/n向上取整
        int available2 = 5 * parcel[4] + left[parcel[3] % 4];   //可以填2*2包裹的空位
        if(available2 < parcel[2])   //不够的再补
            ans += (parcel[2] - available2 + 8) / 9;  // x+(n-1)/n 是 x/n向上取整
        int available1 = 36 * ans - 36 * parcel[6] - 25 * parcel[5]
                        - 16 * parcel[4] - 9 * parcel[3] - 4 * parcel[2];  //可以填1*1包裹的空位
        if(available1 < parcel[1])   //不够的再补
            ans += (parcel[1] - available1 + 35) / 36;
        printf("%d\n",ans);
    }
    return 0;
}

