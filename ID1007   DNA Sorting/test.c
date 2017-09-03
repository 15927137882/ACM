/* 
Description
One measure of ``unsortedness'' in a sequence is the number of pairs of entries that are out of order with respect to each other. For instance, in the letter sequence ``DAABEC'', this measure is 5, since D is greater than four letters to its right and E is greater than one letter to its right. This measure is called the number of inversions in the sequence. The sequence ``AACEDGG'' has only one inversion (E and D)---it is nearly sorted---while the sequence ``ZWQM'' has 6 inversions (it is as unsorted as can be---exactly the reverse of sorted). 
You are responsible for cataloguing a sequence of DNA strings (sequences containing only the four letters A, C, G, and T). However, you want to catalog them, not in alphabetical order, but rather in order of ``sortedness'', from ``most sorted'' to ``least sorted''. All the strings are of the same length. 

Input
The first line contains two integers: a positive integer n (0 < n <= 50) giving the length of the strings; and a positive integer m (0 < m <= 100) giving the number of strings. These are followed by m lines, each containing a string of length n.

Output
Output the list of input strings, arranged from ``most sorted'' to ``least sorted''. Since two strings can be equally sorted, then output them according to the orginal order.

Sample Input
10 6
AACATGAAGG
TTTTGGCCAA
TTTGGCCAAA
GATCAGATTT
CCCGGGGGGA
ATCGATGCAT

Sample Output
CCCGGGGGGA
AACATGAAGG
GATCAGATTT
ATCGATGCAT
TTTTGGCCAA
TTTGGCCAAA
*/ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void resolve_array(char *a,int low,int high,char *temp,int *point);			//实现无序数组的排序（含分解部分，递归实现) 
void merge_array(char *a, int low, int mid, int high, char *temp,int *point);	//实现两个有序数组的排列,归并部分
int cmp( const void *a ,const void *b); 								//比较函数,//返回正值，按升序输出；返回负值，按降序输出  

struct node			//DNA序列信息结构体 
{
	int num;		//逆序数 
	char *p;		//该字符串在仓库中的位置 
};
 
char reposity[100][51];		//字符串仓库 
struct node N[100];

int main()
{
	
	char array[50];		//待排序数组 
	char temp[50];		//临时数组 
	int low = 0;		//数组头 
	int high;			//数组尾 
	int m,n,temp_m;			//m是行(0-100)，n是列(0-50)
	int i = 0,j;
	int *point;			//指向逆序数的指针 
	int count=0;		//逆序数计数 
	
	point = &count;
	scanf("%d%d",&n,&m);		//先输入列，后输入行 
	temp_m = m;
	while(temp_m--)
	{
		scanf("%s",array);
		strcpy(reposity[i],array);
		high = strlen(array)-1;
		resolve_array(array,low,high,temp,point);
		N[i].num = count;
		N[i].p = reposity[i];
		count = 0;
		i++;
	}
	
	qsort(N,m,sizeof(struct node),cmp);
	
	for(i=0;i<m;i++)
		printf("%s\n",N[i].p);

	return 0; 
}


void resolve_array(char *a,int low,int high,char *temp,int *point)
{
	if(low<high)	//当low=high时，到达递归出口，也就是每个组内只有一个元素
	{
		int mid;
		mid = (low+high)/2;
		/* 相当于后序遍历该递归树结构 */ 
		resolve_array(a,low,mid,temp,point);	//保证左边顺序 
		resolve_array(a,mid+1,high,temp,point);	//保证右边顺序
		merge_array(a, low, mid, high, temp,point);	//将两边归并
	}
}


void merge_array(char *a, int low, int mid, int high, char *temp,int *point)
{  
    int i = low, j = mid + 1;  
    int m = mid,   n = high;  
    int k = 0;  
      
    while (i <= m && j <= n)  
    {  
        if (a[i] <= a[j])  
            temp[k++] = a[i++];  
        else  
        {
			temp[k++] = a[j++];  
			*point += mid-i+1; 
        }    
    }  
      
    while (i <= m)  
        temp[k++] = a[i++];  
      
    while (j <= n)  
        temp[k++] = a[j++];  
      
    for (i = 0; i < k; i++)  
        a[low + i] = temp[i];  
}  

int cmp( const void *a ,const void *b)
{
	struct node *c = (struct node *)a; 
	struct node *d = (struct node *)b;
	if(c->num != d->num)
	{
		return c->num - d->num;
	}
	else 
	return 1;		//返回正值，按升序输出；返回负值，按降序输出 
}

