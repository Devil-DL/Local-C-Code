#include <iostream>
using namespace std;

template <class T>
struct Node
{
    T data;
    Node<T> *next;
    Node () {next=NULL;}
};

template <class T>
class CirList
{
private:
    Node<T> *now;
    void _makeEmpty(void);//���f
public:
    Node<T> *GetNow(){return now;}
    bool IsEmpty() //�п�f
    {
        if (now==NULL) return true;
        else return false;
    }
    T& GetData(){return now->data;} //��õ�ǰ����f
    CirList () {now=NULL;} //���캯��f
    CirList (CirList<T> &a);//���ƹ��캯��f
    ~CirList () {_makeEmpty();} //��������f
    void Next(void) {now=now->next;}//ָ������f
    void Insert (T x);//��Ԫ�ز�������ǰ������f
    bool Remove (void);//ɾ����ǰ֮���Ԫ��f
    void Show(void);
};

template <class T>
CirList<T>::CirList(CirList<T> &a)
{
    Node<T> *po=a.now;
    Node<T> *pi=now=new Node<T>;
    pi->data=po->data;
    while (po->next!=a.now)//��po����һ��Ԫ�ز����ʼԪ��ʱ
    {
        po=po->next;
        pi->next=new Node<T>;
        pi=pi->next;
        pi->data=po->data;
    }
    pi->next=now;
}

template <class T>
void CirList<T>::Insert (T x)
{
    if (now==NULL)
    {
        now=new Node<T>;
        now->data=x;
        now->next=now;
        return;
    }
    Node<T> *temp=new Node<T>;
    temp->data=x;
    temp->next=now->next;
    now->next=temp;
}

template <class T>
bool CirList<T>::Remove (void)
{
    if (now==NULL) {cout<<"ɾ���Ƿ�"<<endl;return false;}
    if (now->next==now) {delete now;now=NULL;return true;}
    Node<T> *temp=now->next;
    now->next=temp->next;
    delete temp;
    return true;
}

template<class T>
 void CirList<T>::_makeEmpty(void)
 {
     while (!IsEmpty())
     {
         Remove();
     }
 }

 template<class T>
 void CirList<T>::Show(void)
 {
     cout<<now->data<<' ';
     Node<T> *temp=now->next;
     while (temp!=now)
     {
         cout<<temp->data<<' ';
         temp=temp->next;
     }
     cout<<endl;
 }




int main()
{
    Node<int> *temp;
    int win=0;
    CirList<int> L;
    int m=20,n=50;
    L.Insert(1);
    for (int i=2;i<=n;i++) {L.Insert(i);L.Next();}
    L.Next();
    L.Show();
    while (1)
    {
        for (int i=1;i<=m-2;i++) L.Next();
        temp=L.GetNow();
        cout<<temp->next->data<<"����"<<endl;
        L.Remove();
        if (L.IsEmpty()) break;
        L.Next();
        win=L.GetData();
    }
    cout<<endl;
    cout<<"the winner is "<<win<<endl;
    return 0;
}
