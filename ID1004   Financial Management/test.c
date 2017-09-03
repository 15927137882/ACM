/*
Description

Larry graduated this year and finally has a job. He's making a lot of money, but somehow never seems to have enough. Larry has decided that he needs to grab hold of his financial portfolio and solve his financing problems. The first step is to figure out what's been going on with his money. Larry has his bank account statements and wants to see how much money he has. Help Larry by writing a program to take his closing balance from each of the past twelve months and calculate his average account balance.

Input
The input will be twelve lines. Each line will contain the closing balance of his bank account for a particular month. Each number will be positive and displayed to the penny. No dollar sign will be included.

Output
The output will be a single number, the average (mean) of the closing balances for the twelve months. It will be rounded to the nearest penny, preceded immediately by a dollar sign, and followed by the end-of-line. There will be no other spaces or characters in the output.

Sample Input
100.00
489.12
12454.12
1234.10
823.05
109.20
5.27
1542.25
839.18
83.99
1295.01
1.75

Sample Output 
$1581.42 

*/
 
#include <stdio.h>

int main()
{
	float closing_balance[12];
	int i;
	float temp;
	float result=0.0;
	for(i = 0;i<12;i++)
	{
		scanf("%f",&temp);
		closing_balance[i] = temp;
	}
	for(i = 0;i<12;i++)
	{
		result += closing_balance[i];
	}
	result = result/12.0;
	printf("$%.2f",result);
	return 0;
}
