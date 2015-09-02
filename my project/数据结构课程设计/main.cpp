#include <iostream>
#define  DEFAULTSIZE 100
#define DEFAULTSIZE_QUE 3
using namespace std;

template <class T> //����
class MyQueue
{
private:
    int head;
    int tail;
    int maxSize;//�����������ɵ����Ԫ�ظ���
    T *elem;
    void _overFlow(void);  //ok
public:
    MyQueue (){maxSize=DEFAULTSIZE_QUE;head=tail=0;elem=new T[maxSize];} //ok
    MyQueue (MyQueue<T> &Q); //ok
    ~MyQueue () {delete []elem;} //ok
    void EnQueue (T &x); //ok
    T DeQueue (); //ok
    T &getFront();  //ok
    int Lengh();
    bool IsEmpty(){return tail==head;}
};

template <class T>
T MyQueue<T>::DeQueue ()
{
    T ret;
   if (head==tail)
   {
       cout<<"�����ѿգ��ܾ�����,��������ֵ "<<endl;
       return ret;
   }
   T temp=elem[head];
   head=(head+1)%maxSize;
   return temp;
}

template <class T>
void MyQueue<T>::EnQueue (T &x)
{
    if ((tail+1)%maxSize==head) _overFlow();
    elem[tail]=x;
    tail=(tail+1)%maxSize;
}

template <class T>
void MyQueue<T>::_overFlow(void)
{
    T *temp=new T[maxSize+DEFAULTSIZE_QUE];
    int i=0;
    while (head!=tail)
    {
        temp[i]=elem[head];
        head=(head+1)%maxSize;
        i++;
    }
    maxSize+=DEFAULTSIZE_QUE;
    delete elem;
    head=0;
    tail=i;
    elem=temp;
}

template <class T>
T &MyQueue<T>::getFront()
{
    T ret;
    if (head==tail)
    {
        cout<<"�����ѿգ��޷���ȡ����Ԫ��"<<endl;
        return ret;
    }
    return elem[head];
}

template <class T>
MyQueue<T>::MyQueue (MyQueue<T> &Q)
{
    maxSize=Q.maxSize;
    head=Q.head;
    tail=Q.tail;
    elem=new T[maxSize];
    int i;
    for (i=0;i<maxSize;i++) elem[i]=Q.elem[i];
}

template <class T>
int MyQueue<T>::Lengh()
{
    return (maxSize+tail-head)%maxSize;
}

template <class T>//ջ���
struct Node
{
	T data;
	Node<T> * next;
	Node() {next=NULL;}
};

template <class T>//ջ�Ķ���
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






















template <class T>
struct TreeNode
{
	T data;
	TreeNode<T> *leftChild;
	TreeNode<T> *rightChild;
	TreeNode() {leftChild=NULL;rightChild=NULL;data=0;}
	TreeNode(T value) {leftChild=NULL;rightChild=NULL;data=value;}
};


template <class T>
class BinTree
{
private:
	TreeNode<T> *root;
public:
    int TellDep (T x);
    int TellDep(TreeNode<T> *subTree);
    TreeNode<T>* Search(TreeNode<T> *subTree,T x) ;//��subTree�������а���ǰ��������ҵ�һ��ֵΪx�Ľ��
	BinTree () {root=NULL;}           //���캯�� ok
	BinTree (BinTree<T> & B);        //���ƹ��캯��
	void Chop (TreeNode<T> *& subTree);         //ɾ��subTreeָ������� ok
	~BinTree () {Chop(root);}       //��������  ok
	void InOrderInMirror(TreeNode<T> *subTree,void(*visit)(TreeNode<T> *p,MyQueue<T> & Q),MyQueue<T> & Q);//�������еľ����������
	void PreOrder(TreeNode<T> *subTree,T arr[DEFAULTSIZE],int &i);
	friend TreeNode<char> * Input(BinTree<char> & B);
	friend void Output(BinTree<char> &B);
};


template <class T>
void BinTree<T>::PreOrder(TreeNode<T> *subTree,T arr[DEFAULTSIZE],int &i)
{
    if (subTree==NULL) return;
    arr[i++]=subTree->data;
    if (subTree->leftChild||subTree->rightChild) arr[i++]='(';
    PreOrder(subTree->leftChild,arr,i);
    PreOrder(subTree->rightChild,arr,i);
    if (subTree->leftChild||subTree->rightChild) arr[i++]=')';
}

TreeNode<char> *  Input (BinTree<char> & B) //������Ϊģ��������Ԫ���������Է���������ʵ��
{
	if (B.root!=NULL) {cout<<"�����Ѵ���"<<endl;return NULL;}
    char c[DEFAULTSIZE];
	char *ch=c;  //�ַ�ָ��
	cin>>ch;
	MyStack<TreeNode<char> *> S;//������ָ���ջ
	B.root=new TreeNode<char>(*ch);
	int flag;
	TreeNode<char> *p=B.root;
	while (ch++,*ch!='#')
	{
		if (*ch=='(') {flag=1;S.Push(p);}
		else if (*ch==',') flag=2;
		     else if(*ch==')') S.Pop();
			 else
			 {
				 if (flag==1) p=S.GetTop()->leftChild=new TreeNode<char>(*ch);
				 else p=S.GetTop()->rightChild=new TreeNode<char>(*ch);
			 }
	}
	return B.root;
}

template <class T>
void BinTree<T>::Chop (TreeNode<T> *& subTree)
{
	if (subTree==NULL) return;
	Chop (subTree->leftChild);
	Chop (subTree->rightChild);
    delete subTree;
    subTree=NULL;
}


template <class T>
void BinTree<T>::InOrderInMirror(TreeNode<T> *subTree,void(*visit)(TreeNode<T> *p,MyQueue<T> & Q),MyQueue<T> & Q)
{
    if (subTree==NULL) return;
    InOrderInMirror(subTree->rightChild,visit,Q);
    visit (subTree,Q);
    InOrderInMirror(subTree->leftChild,visit,Q);
}

template <class T>
TreeNode<T>* BinTree<T>::Search(TreeNode<T> *subTree,T x)
{
    TreeNode<T>* p;
    if (subTree==NULL) return NULL;
    if (subTree->data==x) return subTree;
    if (p=Search(subTree->leftChild,x)) return p;
    if (p=Search(subTree->rightChild,x)) return p;
    return NULL;
}

template <class T> //ͨ������ָ�뷵�����
int BinTree<T>::TellDep(TreeNode<T> *subTree)
{
    if (subTree==NULL) return 0;
    int a,b,m;
    m=((a=TellDep(subTree->leftChild))>(b=TellDep(subTree->rightChild)))?a+1:b+1;
    return m;
}

template <class T> //ͨ������ǰ��������������ָ�룬���ظ�ָ��ָ������������
int BinTree<T>::TellDep (T x)
{
    return TellDep(Search(root,x));
}

void Show(TreeNode<char> *p,MyQueue<char> &Q)
{
   Q.EnQueue (p->data);
}

int NumCal (char arr[DEFAULTSIZE],char x)
{
    int i=1;
    int j=0;
    while (arr[j]!=x)
    {
        if (arr[j]=='(') i++;
        if (arr[j]==')') i--;
        j++;
    }
    return i;
}

void Output(BinTree<char> &B)
{
    int num;
    MyQueue<char> Q;
    B.InOrderInMirror(B.root,Show,Q);
    int i=0;
    char arr[DEFAULTSIZE];
    B.PreOrder(B.root,arr,i);
    while (!Q.IsEmpty())
    {
        num=NumCal(arr,Q.getFront());
        for (i=1;i<num;i++) cout<<"  ";
        cout<<Q.DeQueue()<<endl;
    }
}



int main()
{
	BinTree<char> B,temp;
    Input(B);
    Output(B);
    char ch;
    cout<<"����Ҫ���ҵ�Ԫ��"<<endl;
    cin>>ch;
	while (ch!='q')
	{
		cout<<"Ԫ��ֵΪ"<<ch<<"��Ӧ�������Ϊ��";
		cout<<B.TellDep(ch);
		cin>>ch;
	}
	return 0;
}
