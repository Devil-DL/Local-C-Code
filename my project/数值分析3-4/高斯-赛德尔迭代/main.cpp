#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;
int main()
{
    int n,k,N;
    cout<<"����δ֪Ԫ����\n";
    cin>>n;
    double a[n][n];
    double b[n],x[n],y[n];
    double mmax,e;
    cout<<"��������������\n";
    cin>>N;
    cout<<"���뾫��\n";
    cin>>e;
    cout<<"�����Ӧ����\n";
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++) cin>>a[i][j];
        cin>>b[i];
    }
    cout<<"���������ֵ\n";
    for (int i=0;i<n;i++)
    {
        cin>>x[i];
        y[i]=x[i];
    }
    for (k=0;k<N;k++)
    {
        double temp;
        for (int i=0;i<n;i++)
        {
            temp=0;
            for (int j=0;j<n;j++)
            {
                if (i==j) continue;
                temp+=a[i][j]*y[j];
            }
            y[i]=(b[i]-temp)/a[i][i];
        }
        mmax=fabs(y[0]-x[0]);
        for (int i=0;i<n;i++)
        {
            if (fabs(y[i]-x[i])>mmax) mmax= fabs(y[i]-x[i]);
        }
        if  (mmax<e) break;
        for (int i=0;i<n;i++) x[i]=y[i];
    }
    if (k==N) cout<<"����ʧ��\n";
    else
    {
        printf("����%d�ε�������Ϊ��\n",k);
        for (int i=0;i<n;i++) printf("%.8lf\n",y[i]);
    }
    return 0;
}
