/*
Description

Marsha and Bill own a collection of marbles. They want to split the collection among themselves so that both receive an equal share of the marbles. This would be easy if all the marbles had the same value, because then they could just split the collection in half. But unfortunately, some of the marbles are larger, or more beautiful than others. So, Marsha and Bill start by assigning a value, a natural number between one and six, to each marble. Now they want to divide the marbles so that each of them gets the same total value. Unfortunately, they realize that it might be impossible to divide the marbles in this way (even if the total value of all marbles is even). For example, if there are one marble of value 1, one of value 3 and two of value 4, then they cannot be split into sets of equal value. So, they ask you to write a program that checks whether there is a fair partition of the marbles.
Input

Each line in the input file describes one collection of marbles to be divided. The lines contain six non-negative integers n1 , . . . , n6 , where ni is the number of marbles of value i. So, the example from above would be described by the input-line "1 0 1 2 0 0". The maximum total number of marbles will be 20000.
The last line of the input file will be "0 0 0 0 0 0"; do not process this line.
Output

For each collection, output "Collection #k:", where k is the number of the test case, and then either "Can be divided." or "Can't be divided.".
Output a blank line after each test case.
Sample Input

1 0 1 2 0 0
1 0 0 0 1 1
0 0 0 0 0 0
Sample Output

Collection #1:
Can't be divided.

Collection #2:
Can be divided.
*/


#include <iostream>

using namespace std;

int input[7] = {0};
int sum = 0;
int half_sum = 0;
bool flag = false;

void DFS(int value_now,int level_now)
{
    if(flag) return;
    if(value_now == half_sum)
    {
        flag = true;
        return;
    }
    for(int i = level_now;i>=1;i--)
    {
        if(input[i])
        {
            if(value_now+i<=half_sum)
            {
                input[i]--;
                DFS(value_now+i,i);
                if(flag) break;
            }
        }
    }
    return;
}

int main()
{
    int count = 1;
    while(cin>>input[1]>>input[2]>>input[3]>>input[4]>>input[5]>>input[6])
    {
        for(int i=1;i<=6;i++) sum += i*input[i];
        if(sum == 0) break;
        if(sum%2)    //sum为奇数，无法平分
        {
            cout<<"Collection #"<<count++<<':'<<endl;
            cout<<"Can't be divided."<<endl<<endl;    //注意有空行
            continue;
        }
        half_sum = sum / 2;

        flag = false;


        DFS(0,6);

        if(flag)
        {
            cout<<"Collection #"<<count++<<':'<<endl;
            cout<<"Can be divided."<<endl<<endl;
            continue;
        }
        else
        {
            cout<<"Collection #"<<count++<<':'<<endl;
            cout<<"Can't be divided."<<endl<<endl;
            continue;
        }

    }

    return 0;
}
