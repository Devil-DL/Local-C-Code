#include <iostream>
#include <cmath>
#include <assert.h>
#define MAXSIZE 100
using namespace std;

template <class T>
struct Node
{
	T data;
	Node<T> * next;
	Node() {next=NULL;}
};

template <class T>
class MyStack
{
private:
	Node<T> *top;
	void _makeEmpty();//��պ��� ok
public:
	MyStack();//���캯�� ok
    MyStack(MyStack<T> & S);//���ƹ��캯�� ok
	~MyStack(){	_makeEmpty();delete top;}//�������� ok
	void Push(T x);// ok
	T Pop();//����ջ�� ok
	T& GetTop();//�õ�ջ��Ԫ�� ok
	bool IsEmpty(){if (top->next==NULL) return true;else return false;}
};

template <class T>
MyStack<T>::MyStack()
{
	top=new Node<T>;//�½���ͷ�ڵ�
}

template <class T>
MyStack<T>::MyStack(MyStack<T> & S)
{
	Node<T> *pi=top=new Node<T>;
	Node<T> *po=S.top;
	while (po->next!=NULL)
	{
		pi->data=po->data;
        pi->next=new Node<T>;
		pi=pi->next;
		po=po->next;
	}
	pi->data=po->data;
}


template <class T>
void MyStack<T>::Push(T x)
{
	Node<T> *temp=new Node<T>;
	temp->data=x;
	temp->next=top->next;
	top->next=temp;
}

template <class T>
T MyStack<T>::Pop()
{
	T atrtemp;
	if (top->next!=NULL)//���ǿ�
	{
		Node<T> *temp;
		temp=top->next;
		atrtemp=temp->data;
		top->next=temp->next;
        delete temp;
	}
	else {cout<<"ջ�ѿգ��޷���ջ"<<endl;}
	return atrtemp;
}

template <class T>
T& MyStack<T>::GetTop()
{
    T rubbish;
	if (top->next!=NULL)//���ǿ�
	{
		return top->next->data;
	}
	else cout<<"ջ�ѿ�"<<endl;
	return rubbish;
}

template <class T>
void MyStack<T>::_makeEmpty()
{
	while (top->next!=NULL)
	{
		Pop();
	}
}







bool IsRight (char *c) //�жϱ��ʽ�Ƿ�Ϸ�
{
	int i=1;
	for (i=1;1;i++)
	{
		if (i>MAXSIZE) return false;
		if (c[i]=='.') continue;
		if (c[i]>='0'&&c[i]<='9') continue ;
		if (c[i]=='+'||c[i]=='-'||c[i]=='*'||c[i]=='/') continue ;
		if (c[i]=='('||c[i]==')') continue ;
		if (c[i]=='=') break;
		return false;
	}
	return true;
}

int icp(char x)//ջ�����ȼ�
{
	if (x=='=') return 0;
	if (x==')') return 1;
	if (x=='+'||x=='-') return 2;
	if (x=='*'||x=='/') return 4;
	if (x=='(') return 8;
	return -1;

}

int isp(char x) //ջ�����ȼ�
{
	if (x=='=') return 0;
	if (x==')') return 8;
	if (x=='+'||x=='-') return 3;
	if (x=='*'||x=='/') return 5;
	if (x=='(') return 1;
	return -1;

}


int main()
{
	MyStack<char> s;
	char c[MAXSIZE+1]={'='};//�������������ַ�����
	char temp[MAXSIZE+20];//���ܵ�һ��ת�������ʱ����
	cin>>c+1;
	assert(IsRight(c));//����������ȷ
	char *ch=c+1;
	char *t=temp;
	MyStack<double> ds;
	s.Push('=');
	while ((*ch)!='='||s.GetTop()!='=')
    {
        if (*ch>='0'&&*ch<='9') //����ǲ�����
        {
            while (((*ch)!='+')&&((*ch)!='-')&&((*ch)!='*')&&((*ch)!='/')&&((*ch)!='=')&&((*ch)!='(')&&((*ch)!=')'))
            {
                *t=*ch;
                ch++;
                t++;//ÿ��t��ָ��յ�λ��
            }//������ʱ��chָ�������
            *t='?';
            t++;
        }
        if (icp(*ch)==isp(s.GetTop()))
        {

            if (s.Pop()=='(') {ch++;continue;}
            else break;
        }
        if (icp(*ch)>isp(s.GetTop())) { s.Push(*ch); ch++;continue;}
        if (icp(*ch)<isp(s.GetTop())) {*t=s.Pop();t++;}
    }
    *t='\0';
    t++;
    double x,y;//����������
    t=temp;//��ʼ��ָ��t
    while (*t!='\0')
    {
        if ((*t)>='0'&&(*t)<='9')//��Ϊ����
        {
            bool pointFlag=false;
            int befp=0,myCount=1;
            double aftp=0;
            while (1)
                {
                    if (*t=='?')
                    {
                        if (pointFlag==true) {aftp=aftp/myCount;ds.Push(aftp+befp);t++;break;}
                        else {ds.Push(befp);t++;break;}
                    }
                    if (*t=='.') {pointFlag=true;t++;continue;}
                    if (pointFlag==false) {befp=befp*10+*t-'0';t++;continue;}
                    if (pointFlag==true) {myCount*=10;aftp=10*aftp+*t-'0';t++;continue;}
                }
            continue;
        }
        else
        {
            y=ds.Pop();
            x=ds.Pop();
            if (*t=='+') ds.Push(x+y);
            if (*t=='-') ds.Push(x-y);
            if (*t=='*') ds.Push(x*y);
            if (*t=='/') {assert(fabs(y)>0.0000001);ds.Push(x/y);}
            t++;

        }

    }
    cout<<ds.Pop();
	return 0;
}
