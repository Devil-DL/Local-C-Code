#include <iostream>
#include <cmath>
#include <stdio.h>
using namespace std;
double f(double x)
{
    return pow(x,3)-x-1;
}
int main()
{
    double a,b,c;
    double e;
    cout<<"������߽�a,bֵ"<<endl;
    cin>>a>>b;
    printf("�����뾫��\n");
    cin>>e;
    while (fabs(b-a)>e)
    {
        printf("a=%.7lf, b=%.7lf\n",a,b);
        c=(a+b)/2;
        if (f(a)*f(c)<0) b=c;
        else a=c;
    }
    printf("%.7f\n",a);
    return 0;
}
