#include <iostream>
#include <cmath>
#include <stdio.h>
using namespace std;
double f(double x)
{
    return pow(x+1,1.0/3);
}
int main()
{
    double x0,x1,x2;
    double e;
    int N,i;
    cout<<"�������ֵ��\n";
    cin>>x0;
    cout<<"������������������\n";
    cin>>N;
    cout<<"�����뾫�ȣ�\n";
    cin>>e;
    for (i=0;i<N;i++)
    {
        x1=f(x0);
        x2=f(x1);
        x2-=pow(x2-x1,2)/(x2-2*x1+x0);
        if (fabs(x2-x0)<e) break;
        x0=x2;
    }
    if (i==N) cout<<"����ʧ��\n";
    else printf("���Ϊ%.9lf,����%d�ε���\n",x2,i);
    return 0;
}
