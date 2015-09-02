#include <iostream>
using namespace std;
int nixushu (int c[],int);
void quanpailie (int c[],int);
int jiecheng (int);
int main()
{
	int i,j,k,n,p;
	double a[9][10],b[10][9][9],h[10],r[10];
	int c[9];
	cout<<"这是一个求解线性方程组的小程序，您可以使用它计算三元至九元的线性方程组"<<endl;
    aga:cout<<"请输入所要求解方程组的未知数个数"<<endl;
	cin>>n;
	cout<<"请输入该方程的对应矩阵"<<endl;
	for (i=0;i<n+1;i++) h[i]=0;
	for (i=0;i<n;i++)
	{
		for (j=0;j<n+1;j++) cin>>a[i][j];
	}
	cout<<"您输入的矩阵为："<<endl;
	for (i=0;i<n;i++)
	{
		for (j=0;j<n+1;j++) cout<<a[i][j]<<"  ";
		cout<<endl;
	}
	cout<<"确认请输入1，重新输入请输入0"<<endl;
	cin>>i;
	if (i==0) goto aga;
	for (i=0;i<n;i++)
	{
		for (j=0;j<n;j++) b[0][i][j]=a[i][j];
	}
	for (k=1;k<n+1;k++)
	{
		for (i=0;i<n;i++) b[k][i][k-1]=a[i][n];
		if (k>1)
		{
			for (i=0;i<n;i++)
			{
				for (j=0;j<k-1;j++) b[k][i][j]=b[0][i][j];
			}
		}
		if (k<n)
		{
			for (i=0;i<n;i++)
			{
				for (j=k;j<n;j++) b[k][i][j]=b[0][i][j];
			}
		}
	}
	for (i=0;i<n;i++) c[i]=i;
	for (j=1;j<jiecheng (n)+1;j++)
	{
		p=nixushu (c,n);
		for (i=0;i<n+1;i++) r[i]=1;
		for (k=0;k<n+1;k++)
		{
			for (i=0;i<n;i++) r[k]=r[k]*b[k][i][c[i]];
		}
		for (i=0;i<n+1;i++) h[i]=h[i]+p*r[i];
		if (j==jiecheng (n)) break;
		quanpailie (c,n);
	}
	if (h[0]==0) cout<<"该方程组无解";
	else
	{   cout<<"该方程组的解为:"<<endl;
		for (i=1;i<n+1;i++) cout<<"x"<<i<<"="<<h[i]/h[0]<<endl;
	}
	cout<<"如需退出请输入0，再次计算请输入1"<<endl;
	cin>>i;
	if (i==1) goto aga;
	cout<<"谢谢使用"<<endl;
	cout<<"输入0退出程序"<<endl;
	cin>>i;
	return 0;
}

int nixushu (int c[],int n)
{
	int t=0,i,j,p;
	for (i=0;i<n-1;i++)
	{
		for (j=i+1;j<n;j++) if (c[i]>c[j]) t++;
	}
	if ((t+2)%2==0) p=1;
	else p=-1;
	return p;
}

void quanpailie (int c[],int n)
{
	int k,i,min,temp,j;
	for (i=0;i<n-1;i++)
	{
		for (j=i+1;j<n;j++)
		{
			if (c[i]<c[j])
			{
				k=i;
				break;
			}
		}
	}
	for (i=k+1;i<n;i++)
	{
		if (c[i]>c[k])
			min=i;
	}
	temp=c[k];
	c[k]=c[min];
	c[min]=temp;
	for (i=1;i<(n-1-k);i++)
	{
		for (j=k+1;j<n-1;j++)
		{
			if (c[j]>c[j+1])
			{
				temp=c[j];
				c[j]=c[j+1];
				c[j+1]=temp;
			}
		}
	}
}
int jiecheng (int n)
{
	int i;
	int s=1;
	for (i=1;i<n+1;i++) s=s*i;
	return s;
}
