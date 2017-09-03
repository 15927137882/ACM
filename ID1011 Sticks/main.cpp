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





/* 思想很简单，一个接一个的把木棍拼起来，最后把木棍用光。
*             关键的地方是几个剪枝技巧：
*                   设所有木棍的总长度为 Sum, 最终的答案（长度）是 L。
*             1. 首先要明白， Sum一定要能被 L 整除。
*             2. L 一定 大于等于 题目给出的最长的木棍的长度 Max。
*                  由上述两点，我们想到，可以从 Max 开始递增地枚举 L,
*                直到成功地拼出 Sum/L 支长度为 L 的木棍。
*                    搜索种的剪枝技巧：
*             3. 将输入的输入从大到小排序，这么做是因为一支长度为 K
*                的完整木棍，总比几支短的小木棍拼成的要好。
*                形象一些：
*                  如果我要拼 2 支长为8的木棍，第一支木棍我拼成
*                          5 + 3
*                  然后拼第二支木棍但是失败了，而我手中还有长为 2 和 1
*                  的木棍，我可以用 5 + 2 + 1 拼好第一支，再尝试拼第二
*                  支，仔细想一想，就会发现这样做没意义，注定要失败的。
*                  我们应该留下 2+1 因为 2+1 比 3 更灵活。
*             4. 相同长度的木棍不要搜索多次， 比如：
*                我手中有一些木棍, 其中有 2 根长为 4 的木棍， 当前搜索
*                状态是 5+4+.... (即表示长度为 5,4,2 的三支拼在一起,
*                ...表示深层的即将搜索的部分), 进行深搜后不成功，故我
*                没必要用另一个 4 在进行 5+4+...
*             5. 将开始搜索一支长为 L 的木棍时，我们总是以当前最长的未
*                被使用的 木棍开始，如果搜索不成功，那么以比它短的开始
*                那么也一定不能取得全局的成功。因为每一支题目给出的木棍
*                都要被用到。
*                如果，有
*                    4
*                    5 4 4 3 2
*                  想拼成长为 6 的木棍，那么从 5 开始， 但是显然没有能与 5
*                  一起拼成 6 的，那么我就没必要去尝试从 4 开始的，因为
*                  最终 5 一定会被遗弃。在拼第 2 3 ... 支木棍时，一样。
*             6. 最后的最简单的一个就是，
*                      for(int i = 0; i < n; i++)
*                          for(int j = 0; j < n; j++)
*                               {}
*                与
*                      for(int i = 0; i < n; i++)
*                          for(int j = i+1; j < n; j++)
*                               {}
*                的区别，这个不多说了。
*             7. 我用过的另一个剪枝，但是对 poj 的数据效果一般，
*                用一个数组， Sum[i] 保存 第 i 个木棍之后，即比第 i 枝
*                木棍短或与之相等所有的木棍的长度之和。
*                试想，如果剩余的所有木棍加在一起都不能和我当前的状态拼
*                出一直长为 L 的木棍(从长度来看)，还有必要搜下去么？
*/


/* 参考源码 ：
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <algorithm>

using namespace std;
int sticks[65],n,sum,num,l;//l最小的与木棒的长度 num：圆木棒的个数  sum:圆木棒的总长度
bool mark[65];
bool cmp(int a,int b)
{
    return a>b;
}

//s:已经组成的小木棒的个数，le:当前搜索时正在组成的小木条的长度。pos:要组合的小木条的下标位置
bool dfs(int s,int le,int pos)
{
    int i;
    bool sign = (le == 0?true:false);
    if(s==num)return true;
    for(i = pos + 1;i < n;i++)
    {
        if(mark[i])continue;//如果这个小木棒组合过则从下一个开始
        if(le + sticks[i]==l)//如果组合刚好组成l长度的木棒那么就要组合下一根木棒了即第s+1根
        {
            mark[i] = true;
            if(dfs(s+1,0,-1))//第s根已经组合成功了组合下一根
            return true;
            mark[i] = false;
            return false;//如果组合失败了那么就要返回false 而且这个木棒的状态应还原为没组合过
        }
        else if(le + sticks[i]<l)
        //如果组合当前这根后长度仍然小于l那么从i开始往下找继续组合第S根木棒
        {
            mark[i] = true;
            if(dfs(s,le+sticks[i],i))//如果可以组成就返回true
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
        sort(sticks,sticks+n,cmp);//将木棒从大到小排序
        for(l = sticks[0]; l <= sum; l++)//从最大的开始搜索
        {
            if(sum%l==0)//如果该长度可以被整除那么可能是结果，否则继续
            {
                num = sum/l;//num：记录该情况下可以组成的木棒的数目。
                memset(mark,false,sizeof(mark));//每种情况都要进行初始化，把所有的木棒的使用状态设为false
                if(dfs(1,0,-1))//当返回true时说明搜索成功了，可以组成该长度木条
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

int sticks_num;     //小木条的个数
int sticks_length[65];      //每根小木条的长度
bool marked[65];    //每根小木条的使用情况
int sum;            //所有小木条的长度之和
int bar_length;     //木棒的长度
int bar_num;        //木棒的个数


bool dfs(int fixed_bar,int now_bar_length,int now_stick_id)       //已经组装好了几个木棒，现在组装到了多长，现在开始搜索的是第几个木条
{
    bool sign = (now_bar_length == 0 ? true : false);

    if(fixed_bar == bar_num) return true;     //如果组装好了所有的木棒，说明成功
    for(int i = now_stick_id;i<=sticks_num;i++)     //搜索未使用过的小木条
    {
        if(marked[i]) continue;
        if(now_bar_length + sticks_length[i] == bar_length)
        {
            marked[i] = true;
            if(dfs(fixed_bar+1,0,1)) return true;   //如果组装成功，就组装下一根木棒，并且如果后面的木棒都组装成功，返回成功
            marked[i] = false;      //后面的木棒组装不成功，则这条路不通，停止搜索
            return false;
        }
        else if(now_bar_length + sticks_length[i] < bar_length)
        {
            marked[i] = true;
            if(dfs(fixed_bar,now_bar_length+sticks_length[i],i)) return true;  //搜索现有木条，组装木棒
            marked[i] = false;
            if(sign) return false;      //剪枝：当前最长的未被使用的木棍开始，如果搜索不成功，那么以比它短的开始，那么也一定不能取得全局的成功

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
        sum = 0;    //所有小木条的长度之和
        for(int i = 1;i<=sticks_num;i++)
        {
            cin>>sticks_length[i];
            sum += sticks_length[i];
        }

        sort(sticks_length,sticks_length + sticks_num,cmp);   //将小木条按长度从大到小排序

        for(bar_length = sticks_length[0];bar_length<=sum;bar_length++)
        {
            if(sum % bar_length == 0)      //剪枝，小木条的长度之和必须是木棒长度的整数倍
            {
                bar_num = sum / bar_length; //木棒的个数
                memset(marked,false,sizeof(marked));    //每根小木条的使用情况初始化为未使用
                if(dfs(1,0,1) == true)     //开始搜索，组装第一根木棒，该木棒当前长度为0，从第1个小木条开始搜索
                {
                    cout<<bar_length<<endl;
                    break;
                }
            }
        }

    }
    return 0;
}
