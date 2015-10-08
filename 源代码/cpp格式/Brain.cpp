#include <iostream>
#include <cstdio>
#define CSLENGTH 2048
#define DSLENGTH 2048
#define SSLENGTH 256
using namespace std;
typedef void (*Fun)(void);
Fun fp[128];
struct Program
{
	char cs[CSLENGTH];//�����
	unsigned int ip;//ָ��ָ��
	short ds[DSLENGTH];//���ݶ�
	unsigned int bp;//����ָ��
	unsigned short ss[SSLENGTH];//��ջ��
	int sp;//��ջָ��
	Program()  //��ʼ������
	{
		for (int i=0; i<CSLENGTH; i++) cs[i]=0;
		for (int i=0; i<DSLENGTH; i++) ds[i]=0;
		for (int i=0; i<SSLENGTH; i++) ss[i]=0;
		ip=0;
		sp=-1;
		bp=0;
	}
};
Program P;
void ToWard(void)
{
	P.bp++;
}

void BackWard(void)
{
	P.bp--;
}

void increase(void)
{
	P.ds[P.bp]++;
}

void decrease(void)
{
	P.ds[P.bp]--;
}

void WhileBegin(void)
{
	if (P.ds[P.bp]!=0)
	{
		P.ss[++P.sp]=P.ip;
	}
	else
	{
		int flag=1;
		while (flag!=0)   //����ƥ��
		{
			P.ip++;
			if (P.cs[P.ip]=='[') flag++;
			if (P.cs[P.ip]==']') flag--;
		}
	}
}

void WhileEnd(void)
{
	if (P.ds[P.bp]!=0)
	{
		P.ip=P.ss[P.sp];
	}
	else
	{
		P.sp--;
	}
}

void Input(void)
{
	P.ds[P.bp]=getchar();
}

void Output(void)
{
	cout<<(char)P.ds[P.bp];
}

void Set(void)
{
	fp[(int)'>']=ToWard;
	fp[(int)'<']=BackWard;
	fp[(int)'+']=increase;
	fp[(int)'-']=decrease;
	fp[(int)',']=Input;
	fp[(int)'.']=Output;
	fp[(int)'[']=WhileBegin;
	fp[(int)']']=WhileEnd;
}

void GetCode(char *ch)
{
	freopen(ch,"r",stdin);
	char c;
	int count=0;
	while ((c=getchar())!=EOF)
	{
		if (c=='+'||c=='-'||c=='<'||c=='>'||c==','||c=='.'||c=='['||c==']')
		{
			P.cs[count++]=c;
		}
	}
	P.cs[count]='\0';
	freopen("CON", "r", stdin);
}


void Run(void)
{
	while (P.cs[P.ip]!='\0')
	{
		fp[(int)P.cs[P.ip]]();
		P.ip++;
	}
}

int main(int argv,char *argc[])
{
	if (argv==2)
	{
		Set();
		GetCode(argc[1]);
		Run();
	}
	else printf("Failed!\n");
	return 0;
}
