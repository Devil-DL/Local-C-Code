#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
using namespace std;
int main(int argc,char *argv[])
{
	if (argc==2)
	{
		ofstream myout("C:\\Users\\Administrator\\Desktop\\resultOutput.txt");
		myout<<"the argument you have input is:   ";
		for (int i=0;argv[1][i]!='\0';i++)
		{
			if (argv[1][i]=='\\') myout<<'\\';
			myout<<argv[1][i];
		}
		cout<<"����������� resultOutput�ļ���"<<endl;
	}
	else cout<<" ��δ������Ӧ����"<<endl;
	system("pause");
	return 0;
}