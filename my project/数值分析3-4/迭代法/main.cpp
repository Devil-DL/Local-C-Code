#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;
double f(double x)
{
    return exp(-x);
}
int main()
{
    int N,i;
    cout<<"����������������\n";
    cin>>N;
    double x,y,e;
    cout<<"���������ֵ"<<endl;
    cin>>x;
    cout<<"�����뾫��"<<endl;
    cin>>e;
    for (i=0;i<N;i++)
    {
        y=f(x);
        if (fabs(y-x)<e) break;
        x=y;
    }
    if (i==N) printf("����ʧ��\n");
    else printf("���̵Ľ�Ϊ:%.9lf,����%d�ε���\n",y,i);
    return 0;
}
