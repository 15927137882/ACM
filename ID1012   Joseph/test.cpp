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

//���������㷨

#include <iostream>

using namespace std;

int main()
{
         int result[14] = {0};           //��Ž��,����ֻҪ�� 0 < k < 14
         int delete_pos[50] = {0};        //����˳�Ԫ�ص��±꣬��0��ʼ����
         int k;

         delete_pos[0] = 0;          //ɾ��Ԫ�ع���ʼ���Ǵӵ�һ��Ԫ�ؿ�ʼ��

         while((cin>>k) != 0 && k != 0)
         {
                  if(result[k] != 0)
                  {
                           cout<<result[k]<<endl;
                           continue;
                  }

                  int len = 2*k;             //�������������
                  int m = 1;                 //��Ծ����
                  for(int i  = 1;i<=k;i++)              //ֻ��Ҫѭ��k�Σ��������޳�����
                  {
                           delete_pos[i] = (delete_pos[i-1] + m - 1) % (len - i + 1);             //��һ���˳���Ϸ���˵�λ�ã�ȡ������һ���˳���Ϸ���˵�λ�ü�����Ծ���䣬�ٶ�Ŀǰ������Ϸ�е�����ȡ�༴��
                           if(delete_pos[i] < k)      //���ǰ���k�������˳��Ļ������Ǻ�������
                           {
                                    i = 0;            //���¿�ʼ����
                                    m++;           //��Ծ�����1
                           }
                  }

                  result[k] = m;             //���������
                  cout<<result[k]<<endl;
         }
         return 0;
}
