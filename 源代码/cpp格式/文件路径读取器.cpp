#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;
int main(int argc,char *argv[])
{
	if (argc==2)
	{
		ofstream myout("C:\\resultOutput.txt");
		myout<<"the argument you have input is:   ";
		myout<<argv[1]<<endl;
		cout<<"���������������C�� resultOutput�ļ���"<<endl;
	}
	else cout<<" ��δ������Ӧ����"<<endl;
	system("pause");
	return 0;
}