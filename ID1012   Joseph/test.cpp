/*
Description
The Joseph's problem is notoriously known. For those who are not familiar with the original problem: from among n people, numbered 1, 2, . . ., n, standing in circle every mth is going to be executed and only the life of the last remaining person will be saved. Joseph was smart enough to choose the position of the last remaining person, thus saving his life to give us the message about the incident. For example when n = 6 and m = 5 then the people will be executed in the order 5, 4, 6, 2, 3 and 1 will be saved.
Suppose that there are k good guys and k bad guys. In the circle the first k are good guys and the last k bad guys. You have to determine such minimal m that all the bad guys will be executed before the first good guy.

Input
The input file consists of separate lines containing k. The last line in the input file contains 0. You can suppose that 0 < k < 14.

Output
The output file will consist of separate lines containing m corresponding to k in the input file.

Sample Input
3
4
0

Sample Output
5
30
*/

//暴力搜索算法

#include <iostream>

using namespace std;

int main()
{
         int result[14] = {0};           //存放结果,题中只要求 0 < k < 14
         int delete_pos[50] = {0};        //存放退出元素的下标，从0开始计数
         int k;

         delete_pos[0] = 0;          //删除元素过程始终是从第一个元素开始的

         while((cin>>k) != 0 && k != 0)
         {
                  if(result[k] != 0)
                  {
                           cout<<result[k]<<endl;
                           continue;
                  }

                  int len = 2*k;             //整个参与的人数
                  int m = 1;                 //跳跃区间
                  for(int i  = 1;i<=k;i++)              //只需要循环k次，将坏人剔除即可
                  {
                           delete_pos[i] = (delete_pos[i-1] + m - 1) % (len - i + 1);             //下一个退出游戏的人的位置，取决于上一个退出游戏的人的位置加上跳跃区间，再对目前还在游戏中的人数取余即可
                           if(delete_pos[i] < k)      //如果前面的k个人有退出的话，这是好人区间
                           {
                                    i = 0;            //重新开始计算
                                    m++;           //跳跃区间加1
                           }
                  }

                  result[k] = m;             //将结果存入
                  cout<<result[k]<<endl;
         }
         return 0;
}
