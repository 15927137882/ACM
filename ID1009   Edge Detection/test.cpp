/*
Description

IONU Satellite Imaging, Inc. records and stores very large images using run length encoding. You are to write a program that reads a compressed image, finds the edges in the image, as described below, and outputs another compressed image of the detected edges. 
A simple edge detection algorithm sets an output pixel's value to be the maximum absolute value of the differences between it and all its surrounding pixels in the input image. Consider the input image below: 
The upper left pixel in the output image is the maximum of the values |15-15|,|15-100|, and |15-100|, which is 85. The pixel in the 4th row, 2nd column is computed as the maximum of |175-100|, |175-100|, |175-100|, |175-175|, |175-25|, |175-175|,|175-175|, and |175-25|, which is 150. 
Images contain 2 to 1,000,000,000 (109) pixels. All images are encoded using run length encoding (RLE). This is a sequence of pairs, containing pixel value (0-255) and run length (1-109). Input images have at most 1,000 of these pairs. Successive pairs have different pixel values. All lines in an image contain the same number of pixels. 
Input

Input consists of information for one or more images. Each image starts with the width, in pixels, of each image line. This is followed by the RLE pairs, one pair per line. A line with 0 0 indicates the end of the data for that image. An image width of 0 indicates there are no more images to process. The first image in the example input encodes the 5x7 input image above. 
Output

Output is a series of edge-detected images, in the same format as the input images, except that there may be more than 1,000 RLE pairs. 
Sample Input

7
15 4
100 15
25 2
175 2
25 5
175 2
25 5
0 0
10
35 500000000
200 500000000
0 0
3
255 1
10 1
255 2
10 1
255 2
10 1
255 1
0 0
0
Sample Output

7
85 5
0 2
85 5
75 10
150 2
75 3
0 2
150 2
0 4
0 0
10
0 499999990
165 20
0 499999990
0 0
3
245 9
0 0
0
Hint

A brute force solution that attempts to compute an output value for every individual pixel will likely fail due to space or time constraints. 
*/ 

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


using namespace std;

struct Coordinate			//����ṹ�壬���и����ص�ĺ������� ����1��ʼ�� 
{
	int row;
	int column;
};

struct Continuous_pixel_segment		//һ�����������ص�Σ�ֵ�Ĵ�С����ʼ��λ�ã���0��ʼ�� ��������λ�ã��öε�һ�����ص������ 
{
	int value;
	int start_pos,end_pos;
	Coordinate xy; 
};

struct code_pixel
{
	int length;
	int output;
};

int get_information(Continuous_pixel_segment* M,int value,int length,int width);	//��ȡ�������ص�ε���Ϣ,������ͼ�񳤶� 
int get_value(int row,int column,vector<Continuous_pixel_segment> p,int width,int capacity);	//��ȡ��Ӧ�����ص�ֵ 
void get_matrix(int row,int column,int max_row,vector<Continuous_pixel_segment> vec,int width,int count,int matrix[3][3]);	
//��ȡ��Ӧλ�õ��������ݣ����� �У��У�ͼ���������������ض�������ͼ����������ͬ���ضεĸ�����3*3���� 
int calculate_matrix(int matrix[3][3]);	//�����Ӧ���ص�����ֵ 
void get_marked_pixel_surround_output(int row,int column,int max_row,int width,int count,vector<Continuous_pixel_segment> vec,int output_matrix[3][3]);
//��ȡ��ǵ���Χ�����ص����ֵ��-1��ʾ�߽磨���� �У��У�ͼ��������ͼ����������ͬ���ضθ������������ص�����������������
bool cmp(code_pixel a,code_pixel b); 


int main()
{
	int width;		//ͼ����
	

	cin>>width;
	while(width!=0)
	{
		int value,length;	//���ص��ֵ�Լ���Ӧ����
		Continuous_pixel_segment* temp = new Continuous_pixel_segment;
		vector<code_pixel> output_vec;
		code_pixel* point = new code_pixel;
		/*��vector������ض���Ϣ*/ 
		vector<Continuous_pixel_segment> vec;
		vector<Continuous_pixel_segment>::iterator it;
		
		int max_row=0;	//������ͳ�������Լ�vec���� 
		
		temp->end_pos = 0;	//ʹend_pos,start_pos��1��ʼ���� 

		cin>>value>>length;
		
		/* ���ÿ��ͼ�����Ϣ */ 
		while(value!=0 && length!=0)
		{
			max_row = get_information(temp,value,length,width); 
			vec.push_back(*temp);
			cin>>value>>length;
		}
		cout<<width<<endl;
		
		
		int row,column;
		int output_matrix[3][3];
		for(it = vec.begin();it != vec.end();it++)
		{		 	
			row = (*it).xy.row;
			column = (*it).xy.column;
  		 	get_marked_pixel_surround_output(row,column,max_row,width,vec.size(),vec,output_matrix);
  		 	for(int i = -1;i<=1;i++)
			{
				for(int j = -1;j<=1;j++)
				{
					if(output_matrix[i+1][j+1]!=-1)
					{
						point->length =  (*it).start_pos + i*width + j;
						point->output = output_matrix[i+1][j+1];
						output_vec.push_back(*point);
					}
				}
			}		 	
		}
	
		
		sort(output_vec.begin(),output_vec.end(),cmp);
		vector<code_pixel> reduced_output_vec;
		
		for(int i=0;i<output_vec.size()-1;i++)
		{
			if(output_vec[i].length != output_vec[i+1].length)
			reduced_output_vec.push_back(output_vec[i]);
		}
		
		if(reduced_output_vec[reduced_output_vec.size()-1].length != output_vec[output_vec.size()-1].length)
		{
			reduced_output_vec.push_back(output_vec[output_vec.size()-1]);
		}

		int this_first = reduced_output_vec[0].length;
		int next_first;
		vector<code_pixel> final_output_vec;
	
		for(int i=0;i<reduced_output_vec.size();i++)
		{
			if(reduced_output_vec[i].output != reduced_output_vec[i+1].output)
			{
				next_first= reduced_output_vec[i+1].length;
				point->length = next_first-this_first;
				point->output = reduced_output_vec[i].output;
				final_output_vec.push_back(*point);
				this_first = next_first;
			}
		}
		int sum = 0;
		for(int i=0;i<final_output_vec.size()-1;i++)
		{
			sum+= final_output_vec[i].length;
		}
		
		final_output_vec[final_output_vec.size()-1].length = width*max_row-sum;
		
		vector<code_pixel>::iterator output_it;
				
		for(output_it = final_output_vec.begin();output_it != final_output_vec.end();output_it++)
  		{
  		 	cout<<(*output_it).output<<" "<<(*output_it).length<<" "<<endl;
		}

		cout<<"0 0"<<endl;
		cin>>width;
		
	}
	
	cout<<"0";
	return 0;
}


int get_information(Continuous_pixel_segment* temp,int value,int length,int width)
{
	temp->value = value;
	temp->end_pos = temp->end_pos+length;
	temp->start_pos = temp->end_pos-length+1;
	temp->xy.row = temp->start_pos/width+1;
	temp->xy.column = temp->start_pos%width;
	if(temp->xy.column == 0)
	{
		temp->xy.row--;
		temp->xy.column = width;
	}
	return temp->end_pos/width;
}

int get_value(int row,int column,vector<Continuous_pixel_segment> p,int width,int capacity)
{
	int length = (row-1)*width + column;
	int value;
	for(int i=0;i<capacity;i++)
	{
		if(length>=p[i].start_pos) value = p[i].value;
		else if(length<p[i].start_pos) break;
	} 
	return value;
}

void get_matrix(int row,int column,int max_row,vector<Continuous_pixel_segment> vec,int width,int count,int matrix[3][3])
{
	int value = get_value(row,column,vec,width,count);
	matrix[1][1] = value; 
	if(row == 1)
	{
		if(column == 1) 
		{
			matrix[0][0] = matrix[0][1] = matrix[0][2] = matrix[1][0] = matrix[2][0]=value;
			matrix[1][2] = get_value(row,column+1,vec,width,count);
			matrix[2][1] = get_value(row+1,column,vec,width,count);
			matrix[2][2] = get_value(row+1,column+1,vec,width,count);
		} 
		else if(column==width)
		{
			matrix[0][0] = matrix[0][1] = matrix[0][2] = matrix[1][2] = matrix[2][2]=value;
			matrix[1][0] = get_value(row,column-1,vec,width,count);
			matrix[2][0] = get_value(row+1,column-1,vec,width,count);
			matrix[2][1] = get_value(row+1,column,vec,width,count);
		}
		else 
		{
			matrix[0][0] = matrix[0][1] = matrix[0][2] = value;
			matrix[1][0] = get_value(row,column-1,vec,width,count);
			matrix[1][2] = get_value(row,column+1,vec,width,count);
			matrix[2][0] = get_value(row+1,column-1,vec,width,count);
			matrix[2][1] = get_value(row+1,column,vec,width,count);
			matrix[2][2] = get_value(row+1,column+1,vec,width,count);
		}
	}
	else if(row == max_row)
	{
		if(column == 1) 
		{
			matrix[0][0] = matrix[1][0] = matrix[2][0] = matrix[2][1] = matrix[2][2]=value;
			matrix[0][1] = get_value(row-1,column,vec,width,count);
			matrix[0][2] = get_value(row-1,column+1,vec,width,count);
			matrix[1][2] = get_value(row,column+1,vec,width,count);
		}
		else if(column==width) 
		{
			matrix[2][0] = matrix[2][1] = matrix[2][2] = matrix[1][2] = matrix[0][2]=value;
			matrix[0][0] = get_value(row-1,column-1,vec,width,count);
			matrix[0][1] = get_value(row-1,column,vec,width,count);
			matrix[1][0] = get_value(row,column-1,vec,width,count);
		}
		else
		{
			matrix[2][0] = matrix[2][1] = matrix[2][2] = value;
			matrix[0][0] = get_value(row-1,column-1,vec,width,count);
			matrix[0][1] = get_value(row-1,column,vec,width,count);
			matrix[0][2] = get_value(row-1,column+1,vec,width,count);
			matrix[1][0] = get_value(row,column-1,vec,width,count);
			matrix[1][2] = get_value(row,column+1,vec,width,count);
		}
	}
	else if(column == 1)
	{
		matrix[0][0] = matrix[1][0] = matrix[2][0] = value;
		matrix[0][1] = get_value(row-1,column,vec,width,count);
		matrix[2][1] = get_value(row+1,column,vec,width,count);
		matrix[0][2] = get_value(row-1,column+1,vec,width,count);
		matrix[1][2] = get_value(row,column+1,vec,width,count);
		matrix[2][2] = get_value(row+1,column+1,vec,width,count);
	}
	else if(column == width)
	{
		matrix[0][2] = matrix[1][2] = matrix[2][2] = value;
		matrix[0][0] = get_value(row-1,column-1,vec,width,count);
		matrix[1][0] = get_value(row,column-1,vec,width,count);
		matrix[2][0] = get_value(row+1,column-1,vec,width,count);
		matrix[0][1] = get_value(row-1,column,vec,width,count);
		matrix[2][1] = get_value(row+1,column,vec,width,count);
	}
	else
	{
		matrix[0][0] = get_value(row-1,column-1,vec,width,count);
		matrix[0][1] = get_value(row-1,column,vec,width,count);
		matrix[0][2] = get_value(row-1,column+1,vec,width,count);
		matrix[1][0] = get_value(row,column-1,vec,width,count);
		matrix[1][2] = get_value(row,column+1,vec,width,count);
		matrix[2][0] = get_value(row+1,column-1,vec,width,count);
		matrix[2][1] = get_value(row+1,column,vec,width,count);
		matrix[2][2] = get_value(row+1,column+1,vec,width,count);
				
	}
}

int calculate_matrix(int matrix[3][3])
{
	int max = 0,temp;
	for(int i = 0;i<3;i++)
	{
		for(int j = 0;j<3;j++)
		{
			temp = abs(matrix[i][j]-matrix[1][1]);
			if(temp>=max) max = temp;
		}
	}
	return max;
} 

void get_marked_pixel_surround_output(int row,int column,int max_row,int width,int count,vector<Continuous_pixel_segment> vec,int output_matrix[3][3])
{
	int matrix[3][3];

		
	get_matrix(row-1,column-1,max_row,vec,width,count,matrix);
	output_matrix[0][0] =  calculate_matrix(matrix);
		
	get_matrix(row-1,column,max_row,vec,width,count,matrix);
	output_matrix[0][1] =  calculate_matrix(matrix);
		
	get_matrix(row-1,column+1,max_row,vec,width,count,matrix);
	output_matrix[0][2] =  calculate_matrix(matrix);
			
	get_matrix(row,column-1,max_row,vec,width,count,matrix);
	output_matrix[1][0] =  calculate_matrix(matrix);
			
	get_matrix(row,column,max_row,vec,width,count,matrix);
	output_matrix[1][1] =  calculate_matrix(matrix);
			
	get_matrix(row,column+1,max_row,vec,width,count,matrix);
	output_matrix[1][2] =  calculate_matrix(matrix);
			
	get_matrix(row+1,column-1,max_row,vec,width,count,matrix);
	output_matrix[2][0] =  calculate_matrix(matrix);
			
	get_matrix(row+1,column,max_row,vec,width,count,matrix);
	output_matrix[2][1] =  calculate_matrix(matrix);
			
	get_matrix(row+1,column+1,max_row,vec,width,count,matrix);
	output_matrix[2][2] =  calculate_matrix(matrix);
			
			
	if(row == 1)
	{
		if(column == 1) 
		{
			output_matrix[0][0] = output_matrix[0][1] = output_matrix[0][2] = output_matrix[1][0] = output_matrix[2][0]=-1;
		} 
		else if(column==width)
		{
			output_matrix[0][0] = output_matrix[0][1] = output_matrix[0][2] = output_matrix[1][2] = output_matrix[2][2]=-1;
		}
		else 
		{
			output_matrix[0][0] = output_matrix[0][1] = output_matrix[0][2] = -1;
		}		
	}
	else if(row == max_row)
	{
		if(column == 1) 
		{
			output_matrix[0][0] = output_matrix[1][0] = output_matrix[2][0] = output_matrix[2][1] = output_matrix[2][2]=-1;
		}
		else if(column==width) 
		{
			output_matrix[2][0] = output_matrix[2][1] = output_matrix[2][2] = output_matrix[1][2] = output_matrix[0][2]=-1;
		}
		else
		{
			output_matrix[2][0] = output_matrix[2][1] = output_matrix[2][2] = -1;
		}
	}
	else if(column == 1)
	{
		output_matrix[0][0] = output_matrix[1][0] = output_matrix[2][0] = -1;
	}
	else if(column == width)
	{
		output_matrix[0][2] = output_matrix[1][2] = output_matrix[2][2] = -1;
	}
}

bool cmp(code_pixel a,code_pixel b)
{
	return a.length<=b.length;
}

