#include <iostream>

using namespace std;
double f(double x,double y)
{
    return (y-2*x/y);
}

int main()
{
    double x,y;
    cout<<"��������"<<endl;
    cin>>x>>y;
    int n;
    cout<<"����n"<<endl;
    cin>>n;
    double num;
    cout<<"���������"<<endl;
    cin>>num;
    double h=(num-x)/n;
    double yt;
    for (int i=0;i<n;i++)
    {
        yt=y+h*f(x,y);
        y=y+h*(f(x,y)+f(x+h,y+h*f(x,y)))/2;
        x=x+h;
    }
    cout<<y<<endl;
    return 0;
}

