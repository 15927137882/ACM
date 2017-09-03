/*
Description

The "Gold Bar"bank received information from reliable sources that in their last group of N coins exactly one coin is false and differs in weight from other coins (while all other coins are equal in weight). After the economic crisis they have only a simple balance available (like one in the picture). Using this balance, one is able to determine if the weight of objects in the left pan is less than, greater than, or equal to the weight of objects in the right pan.
In order to detect the false coin the bank employees numbered all coins by the integers from 1 to N, thus assigning each coin a unique integer identifier. After that they began to weight various groups of coins by placing equal numbers of coins in the left pan and in the right pan. The identifiers of coins and the results of the weightings were carefully recorded.
You are to write a program that will help the bank employees to determine the identifier of the false coin using the results of these weightings.


Input

The first line of the input file contains two integers N and K, separated by spaces, where N is the number of coins (2<=N<=1000 ) and K is the number of weightings fulfilled (1<=K<=100). The following 2K lines describe all weightings. Two consecutive lines describe each weighting. The first of them starts with a number Pi (1<=Pi<=N/2), representing the number of coins placed in the left and in the right pans, followed by Pi identifiers of coins placed in the left pan and Pi identifiers of coins placed in the right pan. All numbers are separated by spaces. The second line contains one of the following characters: '<', '>', or '='. It represents the result of the weighting:
'<' means that the weight of coins in the left pan is less than the weight of coins in the right pan,
'>' means that the weight of coins in the left pan is greater than the weight of coins in the right pan,
'=' means that the weight of coins in the left pan is equal to the weight of coins in the right pan.


Output

Write to the output file the identifier of the false coin or 0, if it cannot be found by the results of the given weightings.

Sample Input
5 3
2 1 2 3 4
<
1 1 4
=
1 2 5
=

Sample Output
3
*/




#include <iostream>

using namespace std;

inline int abs(int x)
{
    return x>=0?x:-x;
}

int main()
{
    int N;  //硬币数量（2—1000）
    int K;  //称量次数（1—100）

    int coin_id[1010];      //记录硬币id
    for(int i=0;i<1010;i++) coin_id[i] = 0;

    bool must_be_true[1010];
    for(int i=0;i<1010;i++) must_be_true[i] = false;

    int left_pan[110][520];  //左盘称量记录
    for(int i=0;i<110;i++)
    {
        for(int j=0;j<520;j++)
            left_pan[i][j] = -1;
    }

    int right_pan[110][520]; //右盘称量记录
    for(int i=0;i<110;i++)
    {
        for(int j=0;j<520;j++)
            right_pan[i][j] = -1;
    }

    char result[110];       //每次称量结果记录
    for(int i=0;i<110;i++) result[i] = '#';

    cin>>N>>K;
    for(int i = 1;i<=K;i++)
    {
        int number;
        cin>>number;
        for(int j=1;j<=number;j++)
            cin>>left_pan[i][j];
        for(int j=1;j<=number;j++)
            cin>>right_pan[i][j];
        cin>>result[i];
    }

    /* 对于一定为真币的处理 */
    for(int i = 1;i<=K;i++)
    {
        if(result[i] == '=')
        {
            for(int j = 1;left_pan[i][j]!= -1;j++)
            {
                must_be_true[left_pan[i][j]] = true;
                must_be_true[right_pan[i][j]] = true;
            }
        }
    }

    for(int i = 1;i<=K;i++)
    {
        if(result[i] == '>')
        {
            for(int j = 1;left_pan[i][j]!= -1;j++)
            {
                if(must_be_true[left_pan[i][j]] != true)
                    coin_id[left_pan[i][j]]++;
                if(must_be_true[right_pan[i][j]] != true)
                    coin_id[right_pan[i][j]]--;
            }
        }
        if(result[i] == '<')
        {
            for(int j = 1;left_pan[i][j]!= -1;j++)
            {
                if(must_be_true[left_pan[i][j]] != true)
                    coin_id[left_pan[i][j]]--;
                if(must_be_true[right_pan[i][j]] != true)
                    coin_id[right_pan[i][j]]++;
            }
        }
    }

    int max_index = 0;
    int min_index = 0;
    int max_id;
    int min_id;
    int count = 0;
    int latest_fake_id = 0;
    for(int i = 1;i<=N;i++)
    {
        if(must_be_true[i] == false)
        {
            count++;
            latest_fake_id = i;
            if(coin_id[i]>max_index)
            {
                max_index = coin_id[i];
                max_id = i;
            }
            if(coin_id[i]<min_index)
            {
                min_index = coin_id[i];
                min_id = i;
            }
        }
    }
    int sum_heavy = 0;
    int sum_light = 0;

    if(count == 1)
    {
        cout<<latest_fake_id<<endl;
    }

    else if(max_index == abs(min_index))
    {
        cout<<0<<endl;
    }
    else
    {
        if(max_index + min_index > 0)
        {
            for(int i = 1;i<=N;i++)
                if(coin_id[i] == max_index) sum_heavy++;
            if(sum_heavy > 1) cout<<0<<endl;
            else cout<<max_id<<endl;
        }
        else if(max_index+min_index < 0)
        {
            for(int i = 1;i<=N;i++)
                if(coin_id[i] == min_index) sum_light++;
            if(sum_light > 1) cout<<0<<endl;
            else cout<<min_id<<endl;
        }
    }

    return 0;
}
