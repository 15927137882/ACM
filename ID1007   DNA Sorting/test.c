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

void resolve_array(char *a,int low,int high,char *temp,int *point);			//ʵ��������������򣨺��ֽⲿ�֣��ݹ�ʵ��) 
void merge_array(char *a, int low, int mid, int high, char *temp,int *point);	//ʵ�������������������,�鲢����
int cmp( const void *a ,const void *b); 								//�ȽϺ���,//������ֵ����������������ظ�ֵ�����������  

struct node			//DNA������Ϣ�ṹ�� 
{
	int num;		//������ 
	char *p;		//���ַ����ڲֿ��е�λ�� 
};
 
char reposity[100][51];		//�ַ����ֿ� 
struct node N[100];

int main()
{
	
	char array[50];		//���������� 
	char temp[50];		//��ʱ���� 
	int low = 0;		//����ͷ 
	int high;			//����β 
	int m,n,temp_m;			//m����(0-100)��n����(0-50)
	int i = 0,j;
	int *point;			//ָ����������ָ�� 
	int count=0;		//���������� 
	
	point = &count;
	scanf("%d%d",&n,&m);		//�������У��������� 
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
	if(low<high)	//��low=highʱ������ݹ���ڣ�Ҳ����ÿ������ֻ��һ��Ԫ��
	{
		int mid;
		mid = (low+high)/2;
		/* �൱�ں�������õݹ����ṹ */ 
		resolve_array(a,low,mid,temp,point);	//��֤���˳�� 
		resolve_array(a,mid+1,high,temp,point);	//��֤�ұ�˳��
		merge_array(a, low, mid, high, temp,point);	//�����߹鲢
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
	return 1;		//������ֵ����������������ظ�ֵ����������� 
}

