#include "dFunction.h" //�൱�ڼ����
class dMain  //�൱�ڶ���һ������������Main����
{
public:
    static void myMain()//�൱��main����
    {
        int a;
        a=dFunction::putInt();
        a=StepCross(a);
        dFunction::showInt(a);
    }
    static int StepCross(int n)
    {
        if (n==0||n==1) return 1;
        else return n*StepCross(n-1);
    }


};


int main()
{
    dMain::myMain();
    return 0;
}
