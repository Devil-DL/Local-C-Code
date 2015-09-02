#include <iostream>
using namespace std;
template<class T>
struct Node
{
    T data;
    Node<T> *point;
    Node () {point=NULL;}
};

template <class T>
class List
{
private:
    Node<T> *head;
public:
    List () {head=new Node<T>;}//ok
    List (List<T> &L);//ok
    ~List ();//��������ok
    void MakeEmpty();//�ѱ��ɿձ���������ͷ�ڵ�ok
    int Length();//���ر�ok
    Node<T> *GetHead(void) {return head;}//����head ok
    Node<T> *Search(T x) ;//����x�����ڷ��ؽ���ַ����֮����NULL  ok
    bool GetData(int i,T &x);//����i��Ԫ�ظ���x������ֵ����ɹ���� ok
    bool SetData (int i,T x);//��x��Ԫ�ظ�ֵ������ֵΪ�Ƿ�ɹ�����̲Ĳ�ͬ��ok
    bool Insert (int i,T x);//�ڵ�i��Ԫ�غ����x ok
    bool Remove (int i);//ɾ����i��Ԫ��(��̲Ĳ�ͬ) ok
    bool IsEmpty() {return Length()==0;} //ok
    void Show(void); //ok
    bool PutInEnd(T x); //ok
};

template<class T>
List<T>::List (List<T> &L)
{
    Node<T> *po=L.head;
    Node<T> *pi=head=new Node<T>;
    while(po->point!=NULL)//��Poָ��Ľڵ������һ���ڵ��ʱ��
    {
        pi->point=new Node<T>;
        po=po->point;
        pi=pi->point;
        pi->data=po->data;
    }
}

template<class T>
void List<T>::MakeEmpty()
{
    Node<T> *p;
    while (head->point!=NULL)
    {
        p=head->point;
        head->point=head->point->point;
        delete p;
    }
}

template<class T>
List<T>::~List ()
{
    Node<T> *p=head;
    MakeEmpty();
    delete p;
}

template<class T>
int List<T>::Length()
{
    Node<T> *p=head;
    int count=0;
    while (p->point!=NULL)
    {
        p=p->point;
        count++;
    }
    return count;
}

template <class T>
Node<T> *List<T>::Search(T x)
{
    Node<T> *p=head;
    while (p->point!=0)
    {
        p=p->point;
        if (p->data==x) return p;
    }
    cout<<"�Ҳ�����Ԫ��"<<endl;
    return NULL;
}


template<class T>
bool List<T>::GetData(int i,T &x)
{
    Node<T>* p=head;
    int length=Length();
    int count=0;
    if (i>0&&i<=length)
    {
        for (count=0;count<i;count ++) p=p->point;
        x=p->data;
        return true ;
    }
    else
    {
        cout<<"ȡֵ�����Ƿ�"<<endl;
        return false;
    }
}

template<class T>
bool List<T>::SetData (int i,T x)
{
    Node<T>* p=head;
    int length=Length();
    int count=0;
    if (i>0&&i<=length)
    {
        for (count=0;count<i;count ++) p=p->point;
        p->data=x;
        return true ;
    }
    else
    {
        cout<<"�趨ֵ�����Ƿ�"<<endl;
        return false;
    }

}

template<class T>
bool  List<T>::Insert (int i,T x)
{
    Node<T>* p=head;
    Node<T>*p_temp;
    int length=Length();
    int count=0;
    if (i>0&&i<=length)
    {
        for (count=0;count<i;count ++) p=p->point;//��ʱpָ���i��Ԫ��
        p_temp=new Node<T>;
        p_temp->point=p->point;
        p_temp->data=x;
        p->point=p_temp;
        return true;
    }
    else
    {
        cout<<"��������Ƿ�"<<endl;
        return false;
    }

}

template<class T>
bool List<T>::Remove (int i)
{
    Node<T>* p=head;
    Node<T>*p_temp;
    int length=Length();
    int count=0;
    if (i>0&&i<=length)
    {
        for (count=0;count<i-1;count ++) p=p->point;//��ʱpָ���i-1��Ԫ��
        p_temp=p->point;
        p->point=p_temp->point;
        delete p_temp;
        return true;
    }
    else
    {
        cout<<"ɾ�������Ƿ�"<<endl;
        return false;
    }
}

template <class T>
void List<T>::Show()
{
    Node<T> *p=head;
    while (p->point!=NULL)
    {
        p=p->point;
        cout<<p->data<<' ';
    }
    cout<<endl;
}

template <class T>
bool List<T>::PutInEnd(T x)
{
    Node<T> *p=head;
    Node<T> *p_temp;
    while (p->point!=NULL)
    {
        p=p->point;
    }
    p_temp=new Node<T>;
    if (p_temp==NULL) return false;
    p_temp->data=x;
    p->point=p_temp;
    return true;
}











int main()
{

    return 0;
}
