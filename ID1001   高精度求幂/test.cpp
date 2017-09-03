/*

Description

对数值很大、精度很高的数进行高精度计算是一类十分常见的问题。比如，对国债进行计算就是属于这类问题。 

现在要你解决的问题是：对一个实数R( 0.0 < R < 99.999 )，要求写程序精确计算 R 的 n 次方(Rn)，其中n 是整数并且 0 < n <= 25。

Input

T输入包括多组 R 和 n。 R 的值占第 1 到第 6 列，n 的值占第 8 和第 9 列。

Output

对于每组输入，要求输出一行，该行包含精确的 R 的 n 次方。输出需要去掉前导的 0 后不要的 0 。如果输出是整数，不要输出小数点。

Sample Input

95.123 12
0.4321 20
5.1234 15
6.7592  9
98.999 10
1.0100 12

Sample Output

548815620517731830194541.899025343415715973535967221869852721
.00000005148554641076956121994511276767154838481760200726351203835429763013462401
43992025569.928573701266488041146654993318703707511666295476720493953024
29448126.764121021618164430206909037173276672
90429072743629540498.107596019456651774561044010001
1.126825030131969720661201

*/


#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

string big_add(string s1,string s2);	//大型整数相加算法
string big_mul(string s1,string s2);	//大型整数与常规整数相乘算法
string big_pow(string s1,int n);			//大型整数的n次幂
string sci_pow(string s,int n);		//算法主函数

int main()
{
	string s;
	int n;
	
	//ifstream fin("d:\\data.txt");  
    //while (fin>>s>>n)  
	while(cin>>s>>n)
	{
		cout<<sci_pow(s,n)<<endl;
	}
	return 0;
}

string big_add(string s1,string s2)
{
	int len1 = s1.size();
	int len2 = s2.size();
	int max_len,min_len;
	string max_str,min_str;

/* 获得两个输入的相对大小 */
	if(len1<=len2)
	{
		max_len = len2;
		min_len = len1;
		max_str = s2;
		min_str = s1;
	}
	else
	{
		max_len = len1;
		min_len = len2;
		max_str = s1;
		min_str = s2;
	}
	
	string result_str(max_len+1,'0');	//初始结果容器，大小为max_len+1,用0填充
	int i,j;	//初始游标
	int temp;	//一位相加容器
	
	/* 对min_str部分相加算法 */
	for(i=min_len-1,j=max_len-1;i>=0;i--,j--)
	{
		temp = (min_str[i]-'0') + (max_str[j]-'0') + (result_str[j+1]-'0');
		result_str[j+1] = temp%10 +'0';
		result_str[j] = temp/10 +'0';
	}
	/* 对max_str剩余部分的处理 */
	for(j=max_len-min_len-1;j>=0;j--)
	{
		temp = (max_str[j]-'0') + (result_str[j+1]-'0');
		result_str[j+1] = temp%10 +'0';
		result_str[j] = temp/10 +'0';
	}
	
	/*结果优化*/
	if(result_str[0] == '0')
	{
		return result_str.substr(1);	//如果最高位为0，删去最高位
	}
	else
		return result_str;
}

string big_mul(string smaller,string bigger)
{
	long num = atoi(smaller.c_str());		//将smaller字符串对象转换为字符数组，进而转换为long_int数
	int bias = 0;	//中间数据偏移量
	vector<string> vec;
	vec.clear();	//创建用于存放中间结果的容器
	
	/* 计算中间结果 */
	for(int i=bigger.size()-1;i>=0;i--)
	{
		long j = (bigger[i]-'0');
		long temp = j*num;
		ostringstream oss;	//创建字符串流对象
		oss<<temp;			//将中间结果写入字符串流对象
		string s;
		s = oss.str();		//将temp转化为字符串对象
		s.append(bias,'0');	//给中间结果添加k个偏移量
		vec.push_back(s);	//将中间结果存入vec容器中
		bias++;
	}
	
	/* 相加中间结果 */
	string result;
	if(vec.size()>=2)
	{
		result = big_add(vec[0],vec[1]);
		for(int i=2;i<vec.size();i++)
		{
			result = big_add(result,vec[i]);
		}
	}
	else
		result = vec[0];
	
	return result;
}

string big_pow(string s1,int n)
{
	string result = s1;
	if(n == 0)
	{
		result = "1";
		return result;
	}
	while(--n)	//先赋值，后引用
	{
		result = big_mul(s1,result);
	}
	return result;
}

string sci_pow(string s,int n)
{
	string result;
	int count = 0;
	
	/* 对输入为0情况的处理 */
	for(int i=0;i<s.size();i++)
	{
		if(s[i]=='0' || s[i]=='.') count++;
	}
	if(count==s.size()) 
	{
		result = "0";
	}
	/* 对输入是正数的处理 */
	else
	{
		int pos = s.find('.');	//确定小数点位置
		int num;		//result需要移动的小数点位数
		if(pos!=s.npos)		//输入为小数的情况
		{
			int exp = s.size()-(pos+1);	//输入中小数部分的位数
			s.erase(pos,1);		//去除小数点，比如1.01变为101(小数变整数)  
			int num=exp*n;  //最后结果移动的小数点位(比如1.01的立方=101*101*101向左移动2*3位
			int i;
			for(i=0;i<s.size();i++)
			{
				if (s[i]!='0')  
                {  
                    s=s.substr(i);  //去除整型大数前面的0，比如0101变为101  
                    break;  
                } 
			}
			/* 计算结果 */
			result = big_pow(s,n);
			
			/* 对小数点的处理 */
			int p=result.size()-num;  
            if (p<0)  //处理一种特殊情况，向左进的位大于结果的位数  
            {  
                result.insert(0,-p,'0'); 
                result.insert(0,1,'.');  
            }  
            else  
                result.insert(p,1,'.');  //移动小数点位，得到正确的结果  
		}
		else	//输入是整数的情况
		{
			int i;
			for (i=0;i<s.size();i++)
			{
				if (s[i]!='0')  
				{  
					s=s.substr(i);    //去除整型大数前面的0，比如0101变为101  
					break;
				}  
			}
            result=big_pow(s,n);  
		}
		pos=result.find('.');  
        if (pos!=result.npos)  
        {  
			int i;	
            for (i=result.size()-1;i>=pos;i--)  
            {  
                if (result[i]=='0')  
                {  
                    result.erase(i,1);     //去除小数点后面表示精度的0，比如1.2000变为1.2  
                }  
                else  
                   break;  
            }  
        }  
			
		int len=result.size();  
        if (result[len-1]=='.')  
        {  
            result.erase((len-1),1);   //处理一种特殊情况，比如10.变为10  
        }
	}
		return result;
}










