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









int main()
{

	return 0;
}
