#include <iostream>
using namespace std;
int final_row,final_col,r[10][10]={0},c[10][10]={0},p[10][10]={0};
int a[10][10]={0};
int find_the_next (void);
int find_the_first (void);
void set_c (void);
void set_r (void);
void set_p (void);
int main()
{
	int i,j,m,n;
	cout<<"please input the line one"<<endl;
	cin>>a[1][1]>>a[1][2]>>a[1][3]>>a[1][4]>>a[1][5]>>a[1][6]>>a[1][7]>>a[1][8]>>a[1][9];
	cout<<"please input the line two"<<endl;
	cin>>a[2][1]>>a[2][2]>>a[2][3]>>a[2][4]>>a[2][5]>>a[2][6]>>a[2][7]>>a[2][8]>>a[2][9];
    cout<<"please input the line three"<<endl;
    cin>>a[3][1]>>a[3][2]>>a[3][3]>>a[3][4]>>a[3][5]>>a[3][6]>>a[3][7]>>a[3][8]>>a[3][9];
    cout<<"please input the line four"<<endl;
	cin>>a[4][1]>>a[4][2]>>a[4][3]>>a[4][4]>>a[4][5]>>a[4][6]>>a[4][7]>>a[4][8]>>a[4][9];
    cout<<"please input the line five"<<endl;
	cin>>a[5][1]>>a[5][2]>>a[5][3]>>a[5][4]>>a[5][5]>>a[5][6]>>a[5][7]>>a[5][8]>>a[5][9];
    cout<<"please input the line six"<<endl;
    cin>>a[6][1]>>a[6][2]>>a[6][3]>>a[6][4]>>a[6][5]>>a[6][6]>>a[6][7]>>a[6][8]>>a[6][9];
    cout<<"please input the line seven"<<endl;
    cin>>a[7][1]>>a[7][2]>>a[7][3]>>a[7][4]>>a[7][5]>>a[7][6]>>a[7][7]>>a[7][8]>>a[7][9];
    cout<<"please input the line eight"<<endl;
	cin>>a[8][1]>>a[8][2]>>a[8][3]>>a[8][4]>>a[8][5]>>a[8][6]>>a[8][7]>>a[8][8]>>a[8][9];
    cout<<"please input the line nine"<<endl;
	cin>>a[9][1]>>a[9][2]>>a[9][3]>>a[9][4]>>a[9][5]>>a[9][6]>>a[9][7]>>a[9][8]>>a[9][9];
	set_c();
	set_r();
	set_p();
	for (m=9;m>=1;m--)
	{
		for (n=9;n>=1;n--)
		{
			if (a[m][n]==0)
			{
				final_row=m;
				final_col=n;
				goto next;
			}
		}
	}
next:
	i=find_the_first();
	if (i==0) cout<<"no answer"<<endl;
	else
	{
		cout<<"after searching, the answer is:"<<endl;
		for (i=1;i<=9;i++)
		{
			for (j=1;j<=9;j++)  cout<<a[i][j]<<" ";
		    cout<<endl;
		}
	}
	cin>>i;
	return 0;
}

void set_r(void)
{
	int i,j;
	for (i=1;i<=9;i++)
	{
		for (j=1;j<=9;j++)
		{
			if (a[i][j]!=0) r[i][a[i][j]]=1;
		}
	}
}

void set_c(void)
{
	int i,j;
	for (i=1;i<=9;i++)
	{
		for (j=1;j<=9;j++)
		{
			if (a[i][j]!=0) c[j][a[i][j]]=1;
		}
	}
}

void set_p (void)
{
	int i,j;
	for (i=1;i<=9;i++)
	{
		for (j=1;j<=9;j++)
		{
			if (a[i][j]!=0) p[3*((i-1)/3)+(j-1)/3+1][a[i][j]]=1;
		}
	}
}

int find_the_next (void)
{
	int row,col,k,condition;
	for (row=1;row<=9;row++)
	{
		for (col=1;col<=8;col++)
		{
			if (a[row][col]==0) break;
		}
		if (a[row][col]==0) break;
	}
	for (k=1;k<=9;k++)
	  {
		  if (r[row][k]!=0||p[3*((row-1)/3)+(col-1)/3+1][k]!=0||c[col][k]!=0)  continue;
		  a[row][col]=k;
		  r[row][k]=1;
		  c[col][k]=1;
		  p[3*((row-1)/3)+(col-1)/3+1][k]=1;
		  if (row==final_row&&col==final_col) return 1;
		  condition=find_the_next();
		  if (condition==1) return 1;
		  a[row][col]=0;
		  r[row][k]=0;
		  c[col][k]=0;
		  p[3*((row-1)/3)+(col-1)/3+1][k]=0;
	  }
	  return 0;
}

int find_the_first (void)
{
	int row,col,k,condition;
	for (row=1;row<=9;row++)
	{
		for (col=1;col<=8;col++)
		{
			if (a[row][col]==0) break;
		}
		if (a[row][col]==0) break;
	}
	for (k=1;k<=9;k++)
	  {
		  if (r[row][k]!=0||p[3*((row-1)/3)+(col-1)/3+1][k]!=0||c[col][k]!=0)  continue;
		  a[row][col]=k;
		  r[row][k]=1;
		  c[col][k]=1;
		  p[3*((row-1)/3)+(col-1)/3+1][k]=1;
		  if (row==final_row&&col==final_col) return 1;
		  condition=find_the_next();
		  if (condition==1) return 1;
		  a[row][col]=0;
		  r[row][k]=0;
		  c[col][k]=0;
		  p[3*((row-1)/3)+(col-1)/3+1][k]=0;
	  }
	  return 0;
}









