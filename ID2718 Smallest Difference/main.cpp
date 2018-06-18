/*
Description

Given a number of distinct decimal digits, you can form one integer by choosing a non-empty subset of these digits and writing them in some order. The remaining digits can be written down in some order to form a second integer. Unless the resulting integer is 0, the integer may not start with the digit 0.

For example, if you are given the digits 0, 1, 2, 4, 6 and 7, you can write the pair of integers 10 and 2467. Of course, there are many ways to form such pairs of integers: 210 and 764, 204 and 176, etc. The absolute value of the difference between the integers in the last pair is 28, and it turns out that no other pair formed by the rules above can achieve a smaller difference.
Input

The first line of input contains the number of cases to follow. For each case, there is one line of input containing at least two but no more than 10 decimal digits. (The decimal digits are 0, 1, ..., 9.) No digit appears more than once in one line of the input. The digits will appear in increasing order, separated by exactly one blank space.
Output

For each test case, write on a single line the smallest absolute difference of two integers that can be written from the given digits as described by the rules above.
Sample Input

1
0 1 2 4 6 7
Sample Output

28

遍历+剪枝
*/


#include <iostream>
#include <string>
#include <algorithm>
#include <bitset>

#define MAX_INT (((unsigned int)(-1))>>1)

using namespace std;

int main()
{
    int N;
    cin>>N;
    cin.ignore();
    while(N--)
    {
        string all;
        getline(cin,all);
        all.erase(remove(all.begin(),all.end(),' '),all.end());
        int length = all.size();
        unsigned int cut_point = length / 2;     //剪枝处理，因为要想差值最小，首先要保证两个数位数差值最小,length/2
        int ans = MAX_INT;
        int permutate = 1<<length;
        do
        {
            bitset<10> used = static_cast< bitset<10> >(permutate);
            string num1,num2;           //构建两个桶，分别存放需要排列的元素
            for(int i = 0;i<length;i++)
            {
                if(used[i])
                    num1 += all[i];
                else
                    num2 += all[i];
            }

            if(num1.size() != cut_point)
                continue;

            if(num1[0]== '0' )    //选元素具有对称性，对于有0元素的数，为节省时间，只检查1次即可，交给num2检查
                continue;

            do
            {
                int a1 = atoi(num1.c_str());
                do
                {
                    if(num2[0] == '0' && num2.size() > 1)
                        continue;


                    int a2 = atoi(num2.c_str());

                    ans = min(ans,abs(a1-a2));

                } while(next_permutation(num2.begin(),num2.end()));

            } while(next_permutation(num1.begin(),num1.end()));
        } while(--permutate);

        cout<<ans<<endl;
    }
    return 0;
}
