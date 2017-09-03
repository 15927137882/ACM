/*
Description

George took sticks of the same length and cut them randomly until all parts became at most 50 units long. Now he wants to return sticks to the original state, but he forgot how many sticks he had originally and how long they were originally. Please help him and design a program which computes the smallest possible original length of those sticks. All lengths expressed in units are integers greater than zero.

Input

The input contains blocks of 2 lines. The first line contains the number of sticks parts after cutting, there are at most 64 sticks. The second line contains the lengths of those parts separated by the space. The last line of the file contains zero.

Output

The output should contains the smallest possible length of original sticks, one per line.

Sample Input
9
5 2 1 5 2 1 5 2 1
4
1 2 3 4
0


Sample Output
6
5
*/





/* ˼��ܼ򵥣�һ����һ���İ�ľ��ƴ����������ľ���ù⡣
*             �ؼ��ĵط��Ǽ�����֦���ɣ�
*                   ������ľ�����ܳ���Ϊ Sum, ���յĴ𰸣����ȣ��� L��
*             1. ����Ҫ���ף� Sumһ��Ҫ�ܱ� L ������
*             2. L һ�� ���ڵ��� ��Ŀ���������ľ���ĳ��� Max��
*                  ���������㣬�����뵽�����Դ� Max ��ʼ������ö�� L,
*                ֱ���ɹ���ƴ�� Sum/L ֧����Ϊ L ��ľ����
*                    �����ֵļ�֦���ɣ�
*             3. �����������Ӵ�С������ô������Ϊһ֧����Ϊ K
*                ������ľ�����ܱȼ�֧�̵�Сľ��ƴ�ɵ�Ҫ�á�
*                ����һЩ��
*                  �����Ҫƴ 2 ֧��Ϊ8��ľ������һ֧ľ����ƴ��
*                          5 + 3
*                  Ȼ��ƴ�ڶ�֧ľ������ʧ���ˣ��������л��г�Ϊ 2 �� 1
*                  ��ľ�����ҿ����� 5 + 2 + 1 ƴ�õ�һ֧���ٳ���ƴ�ڶ�
*                  ֧����ϸ��һ�룬�ͻᷢ��������û���壬ע��Ҫʧ�ܵġ�
*                  ����Ӧ������ 2+1 ��Ϊ 2+1 �� 3 ����
*             4. ��ͬ���ȵ�ľ����Ҫ������Σ� ���磺
*                ��������һЩľ��, ������ 2 ����Ϊ 4 ��ľ���� ��ǰ����
*                ״̬�� 5+4+.... (����ʾ����Ϊ 5,4,2 ����֧ƴ��һ��,
*                ...��ʾ���ļ��������Ĳ���), �������Ѻ󲻳ɹ�������
*                û��Ҫ����һ�� 4 �ڽ��� 5+4+...
*             5. ����ʼ����һ֧��Ϊ L ��ľ��ʱ�����������Ե�ǰ���δ
*                ��ʹ�õ� ľ����ʼ������������ɹ�����ô�Ա����̵Ŀ�ʼ
*                ��ôҲһ������ȡ��ȫ�ֵĳɹ�����Ϊÿһ֧��Ŀ������ľ��
*                ��Ҫ���õ���
*                �������
*                    4
*                    5 4 4 3 2
*                  ��ƴ�ɳ�Ϊ 6 ��ľ������ô�� 5 ��ʼ�� ������Ȼû������ 5
*                  һ��ƴ�� 6 �ģ���ô�Ҿ�û��Ҫȥ���Դ� 4 ��ʼ�ģ���Ϊ
*                  ���� 5 һ���ᱻ��������ƴ�� 2 3 ... ֧ľ��ʱ��һ����
*             6. ������򵥵�һ�����ǣ�
*                      for(int i = 0; i < n; i++)
*                          for(int j = 0; j < n; j++)
*                               {}
*                ��
*                      for(int i = 0; i < n; i++)
*                          for(int j = i+1; j < n; j++)
*                               {}
*                �������������˵�ˡ�
*             7. ���ù�����һ����֦�����Ƕ� poj ������Ч��һ�㣬
*                ��һ�����飬 Sum[i] ���� �� i ��ľ��֮�󣬼��ȵ� i ֦
*                ľ���̻���֮������е�ľ���ĳ���֮�͡�
*                ���룬���ʣ�������ľ������һ�𶼲��ܺ��ҵ�ǰ��״̬ƴ
*                ��һֱ��Ϊ L ��ľ��(�ӳ�������)�����б�Ҫ����ȥô��
*/


/* �ο�Դ�� ��
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <algorithm>

using namespace std;
int sticks[65],n,sum,num,l;//l��С����ľ���ĳ��� num��Բľ���ĸ���  sum:Բľ�����ܳ���
bool mark[65];
bool cmp(int a,int b)
{
    return a>b;
}

//s:�Ѿ���ɵ�Сľ���ĸ�����le:��ǰ����ʱ������ɵ�Сľ���ĳ��ȡ�pos:Ҫ��ϵ�Сľ�����±�λ��
bool dfs(int s,int le,int pos)
{
    int i;
    bool sign = (le == 0?true:false);
    if(s==num)return true;
    for(i = pos + 1;i < n;i++)
    {
        if(mark[i])continue;//������Сľ����Ϲ������һ����ʼ
        if(le + sticks[i]==l)//�����ϸպ����l���ȵ�ľ����ô��Ҫ�����һ��ľ���˼���s+1��
        {
            mark[i] = true;
            if(dfs(s+1,0,-1))//��s���Ѿ���ϳɹ��������һ��
            return true;
            mark[i] = false;
            return false;//������ʧ������ô��Ҫ����false �������ľ����״̬Ӧ��ԭΪû��Ϲ�
        }
        else if(le + sticks[i]<l)
        //�����ϵ�ǰ����󳤶���ȻС��l��ô��i��ʼ�����Ҽ�����ϵ�S��ľ��
        {
            mark[i] = true;
            if(dfs(s,le+sticks[i],i))//���������ɾͷ���true
            return true;
            mark[i] = false;
            if(sign)return false;
            while(sticks[i]==sticks[i+1])i++;
        }
    }
    return false;
}

int main()
{
    while(scanf("%d",&n)!=EOF,n)
    {
        sum = 0;

        for(int i = 0; i < n; i++)
        {
            scanf("%d",&sticks[i]);
            sum += sticks[i];
        }
        sort(sticks,sticks+n,cmp);//��ľ���Ӵ�С����
        for(l = sticks[0]; l <= sum; l++)//�����Ŀ�ʼ����
        {
            if(sum%l==0)//����ó��ȿ��Ա�������ô�����ǽ�����������
            {
                num = sum/l;//num����¼������¿�����ɵ�ľ������Ŀ��
                memset(mark,false,sizeof(mark));//ÿ�������Ҫ���г�ʼ���������е�ľ����ʹ��״̬��Ϊfalse
                if(dfs(1,0,-1))//������trueʱ˵�������ɹ��ˣ�������ɸó���ľ��
                {
                    printf("%d\n",l);
                    break;
                }
            }
        }
    }
    return 0;
}
*/

#include <iostream>
#include <cstring>
#include <algorithm>


using namespace std;

int sticks_num;     //Сľ���ĸ���
int sticks_length[65];      //ÿ��Сľ���ĳ���
bool marked[65];    //ÿ��Сľ����ʹ�����
int sum;            //����Сľ���ĳ���֮��
int bar_length;     //ľ���ĳ���
int bar_num;        //ľ���ĸ���


bool dfs(int fixed_bar,int now_bar_length,int now_stick_id)       //�Ѿ���װ���˼���ľ����������װ���˶೤�����ڿ�ʼ�������ǵڼ���ľ��
{
    bool sign = (now_bar_length == 0 ? true : false);

    if(fixed_bar == bar_num) return true;     //�����װ�������е�ľ����˵���ɹ�
    for(int i = now_stick_id;i<=sticks_num;i++)     //����δʹ�ù���Сľ��
    {
        if(marked[i]) continue;
        if(now_bar_length + sticks_length[i] == bar_length)
        {
            marked[i] = true;
            if(dfs(fixed_bar+1,0,1)) return true;   //�����װ�ɹ�������װ��һ��ľ����������������ľ������װ�ɹ������سɹ�
            marked[i] = false;      //�����ľ����װ���ɹ���������·��ͨ��ֹͣ����
            return false;
        }
        else if(now_bar_length + sticks_length[i] < bar_length)
        {
            marked[i] = true;
            if(dfs(fixed_bar,now_bar_length+sticks_length[i],i)) return true;  //��������ľ������װľ��
            marked[i] = false;
            if(sign) return false;      //��֦����ǰ���δ��ʹ�õ�ľ����ʼ������������ɹ�����ô�Ա����̵Ŀ�ʼ����ôҲһ������ȡ��ȫ�ֵĳɹ�

            while(sticks_length[i] == sticks_length[i+1]) i++;
        }
    }

    return false;
}


bool cmp(int a,int b)
{
    return a>b;
}

int main()
{
    while(cin>>sticks_num && sticks_num != 0)
    {
        sum = 0;    //����Сľ���ĳ���֮��
        for(int i = 1;i<=sticks_num;i++)
        {
            cin>>sticks_length[i];
            sum += sticks_length[i];
        }

        sort(sticks_length,sticks_length + sticks_num,cmp);   //��Сľ�������ȴӴ�С����

        for(bar_length = sticks_length[0];bar_length<=sum;bar_length++)
        {
            if(sum % bar_length == 0)      //��֦��Сľ���ĳ���֮�ͱ�����ľ�����ȵ�������
            {
                bar_num = sum / bar_length; //ľ���ĸ���
                memset(marked,false,sizeof(marked));    //ÿ��Сľ����ʹ�������ʼ��Ϊδʹ��
                if(dfs(1,0,1) == true)     //��ʼ��������װ��һ��ľ������ľ����ǰ����Ϊ0���ӵ�1��Сľ����ʼ����
                {
                    cout<<bar_length<<endl;
                    break;
                }
            }
        }

    }
    return 0;
}
