#include <iostream>
#include <cmath>     //abs函数
#include <algorithm>

using namespace std;

//全局变量、函数
const int N=1000;
int InMap[N][2];           //存放输入数据
int OutMap[N*9][2];        //存放输出数据
int total=0;
int width;

int cmp(const void *a, const void *b);
int getvalue(int pos);
int getcode(int pos);

int main()
{
    int pairv,pairn;
    while(cin>>width && width)
    {
        int p=0;
        total=0;
        while(cin>>pairv>>pairn && pairn)
        {
            InMap[p][0]=pairv;
            InMap[p++][1]=pairn;
            total+=pairn;           //所有像素点的个数
        }
        int pairN=p;                //输入像素对的个数
        cout<<width<<endl;
        int pos=0,k=0,tpos;
        p=0;
        while(p<pairN)
        {
            int row=pos/width;
            int col=pos%width;
            for(int i=row-1;i<=row+1;i++)
                for(int j=col-1;j<=col+1;j++)
                {
                    tpos=i*width+j;          //每个标记点附近像素点的一维位置
                    if(i<0||j<0||j>width||tpos>total-1) continue;//j==width为下一行第一个，也需要处理。即为跨行处理。
                    OutMap[k][0]=tpos;
                    OutMap[k++][1]=getcode(tpos);              //获得该像素点的输出值
                }
            pos+=InMap[p++][1];     //pos为每个标记点的一维位置
        }
        //处理最后一行第一个
        OutMap[k][0]=total-width;
        OutMap[k++][1]=getcode(total-width);
        int OutN=k;

        qsort(OutMap,OutN,sizeof(OutMap[0]),cmp);

        k=0;
        int temp0,temp1;
        temp1=OutMap[k][1];
        temp0=OutMap[k][0];
        while(k<OutN)
        {
            if (OutMap[k][1]==temp1)
            {
                k++;
                continue;
            }
            cout<<temp1<<" "<<OutMap[k][0]-temp0<<endl;
            temp1=OutMap[k][1];
            temp0=OutMap[k++][0];
        }
        cout<<temp1<<" "<<total-temp0<<endl;
        cout<<"0 0"<<endl;
    }
    cout << "0" << endl;
    return 0;
}

int cmp(const void *a, const void *b)
{
    int *x=(int*)a;
    int *y=(int*)b;
    return *x-*y;
}

int getvalue(int pos)
{
    int p=0,k=0;
    while(k<=pos)
        k+=InMap[p++][1];
    return InMap[--p][0];
}

int getcode(int pos)
{
    int code=0;
    int m1=getvalue(pos),m2,tpos;
    int r=pos/width;
    int l=pos%width;
    for(int i=r-1;i<=r+1;i++)
        for(int j=l-1;j<=l+1;j++)
        {
            tpos=i*width+j;
            if(i<0||j<0||j>width-1||tpos>total-1||tpos==pos)
                continue;
            m2=getvalue(tpos);
            code=abs(m1-m2)>code?abs(m1-m2):code;
        }
    return code;
}

