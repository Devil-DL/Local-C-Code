#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#define OMEGA 48
#define MIN_PHE 1e-8
#define ANT_AMOUNT 48
#define CITY_AMOUNT 48
#define GENERATION_TIMES 300000
#define FIRST_PHER 1e-6 /////////////////////////////////////////////////////////////////////////
int bre;
int counter;
using namespace std;
ofstream out;/////////////////////////////////////////////////////////
int MinRoute=-1;
int MinTour[CITY_AMOUNT+1]={0};
int distant[CITY_AMOUNT][CITY_AMOUNT]={0};
double pheromone[CITY_AMOUNT][CITY_AMOUNT]={0};
double choice_info[CITY_AMOUNT][CITY_AMOUNT]={0};
double selection_pro[CITY_AMOUNT]={0};
int x_pos[CITY_AMOUNT]={0};
int y_pos[CITY_AMOUNT]={0};
struct Ant
{
    int tour_length;
    int tour[CITY_AMOUNT+1];
    bool visited[CITY_AMOUNT];
    Ant ()
    {
        for (int i=0;i<CITY_AMOUNT;i++) visited[i]=false;
    }
};

Ant a[ANT_AMOUNT];

void GetData()
{
    int mycount=0;
    int xtemp;
    int ytemp;
    int flag=1;
    char c[9000];
    ifstream in;
    in.open("C:\\Users\\Administrator\\Desktop\\att48.txt");
    in.getline(c,9000,'\0');
    char *p=c;
    while(mycount<CITY_AMOUNT)
    {
        if (*p==' ')
        {
            if (*(p+1)==' ') {p++;continue;}
            if (flag==0) {flag=1;ytemp=0;x_pos[mycount]=xtemp;p++;}
            else
                {
                    flag=0;
                    xtemp=0;
                    p++;
                }
        }
        else if (*p>='0'&&*p<='9')
        {
            if (flag==0) {xtemp=xtemp*10+*p-'0';p++;}
            else {ytemp=ytemp*10+*p-'0';p++;}
        }
        else if (*p=='\n')
        {
            y_pos[mycount]=ytemp;
            mycount++;
            p++;
        }
        else p++;

    }
    for (int i=0;i<CITY_AMOUNT;i++) cout<<x_pos[i]<<' ';
    cout<<endl;
    for (int i=0;i<CITY_AMOUNT;i++) cout<<y_pos[i]<<' ';
    cout<<endl;
    in.close();

}

int HowFar(int m,int n)
{
   double temp=sqrt((x_pos[m]-x_pos[n])*(x_pos[m]-x_pos[n])+(y_pos[m]-y_pos[n])*(y_pos[m]-y_pos[n]));
   if (2*(temp-(int) temp)>=1) return (int)temp+1;
   else return (int)temp;
}
void Prepare()
{
    GetData();
    for (int i=0;i<CITY_AMOUNT;i++)
        for (int j=i+1;j<CITY_AMOUNT;j++) distant[i][j]=distant[j][i]=HowFar(i,j);
    for (int i=0;i<CITY_AMOUNT;i++)
        for (int j=0;j<CITY_AMOUNT;j++) pheromone[i][j]=FIRST_PHER;
    for (int i=0;i<CITY_AMOUNT;i++)
        for (int j=i+1;j<CITY_AMOUNT;j++) choice_info[i][j]=choice_info[j][i]=pheromone[i][j]*1.0/(distant[i][j]*distant[i][j]);

}

void ASDecisionRule(int k,int step)
{
    int current=a[k].tour[step-1];
    double sum_pro=0.0;
    for (int i=0;i<CITY_AMOUNT;i++)
    {
        if (a[k].visited[i]==true) selection_pro[i]=0;
        else
        {
            selection_pro[i]=choice_info[current][i];
            sum_pro+=selection_pro[i];
        }
    }
    if (sum_pro==0)
    {for (int i=0;i<CITY_AMOUNT;i++) cout<<a[k].visited[i]<<' ';
    cout<<endl;
    cin>>bre;
    for (int i=0;i<CITY_AMOUNT;i++)
    {
        if (a[k].visited[i]==false) {cout<<choice_info[current][i]<<endl;cout<<pheromone[current][i]<<endl;}
    }
    cin>>bre;
    }

    double r=0;
    do
    {
        r=rand()/(RAND_MAX+1.0)*sum_pro;
    } while (r<=0);
    int j=0;
    double p=selection_pro[j];
    if (p>r&&a[k].visited[0]==true) cout<<"fuckfuckfuckfuckfuckfuckfuckfuckfuckfuckfuckfuck"<<endl;
    while (p<r)
    {
        j++;
        p+=selection_pro[j];
    }
    a[k].tour[step]=j;
    if (a[k].visited[j]==true)
    {
        cout<<"wrong "<<j<<endl;
        for (int i=0;i<=step;i++) cout<<a[k].tour[i]<<' ';
        cout<<endl;
        cout<<r<<endl;
        cout<<selection_pro[0]<<endl;
        cout<<a[k].visited[0]<<endl;
        cin>>bre;
    }
    a[k].visited[j]=true;
}

int ComputeLengh(int k)
{
    int temp=0;
    for (int i=0;i<CITY_AMOUNT;i++) temp+=distant[a[k].tour[i]][a[k].tour[i+1]];
    return temp;
}

void Move()
{
    for (int i=0;i<ANT_AMOUNT;i++)
        for (int j=0;j<CITY_AMOUNT;j++) a[i].visited[j]=false;//�������ϵķ��ʼ������
    int step=0;
    for (int i=0;i<ANT_AMOUNT;i++)
    {
        int r=rand()%CITY_AMOUNT;
        a[i].tour[0]=r;
        a[i].visited[r]=true;
    }
    while (step<CITY_AMOUNT-1)
    {
        step++;
        for (int i=0;i<ANT_AMOUNT;i++) ASDecisionRule(i,step);
    }
    for (int i=0;i<ANT_AMOUNT;i++)
    {
        a[i].tour[CITY_AMOUNT]=a[i].tour[0];
        a[i].tour_length=ComputeLengh(i);
    }
    for (int i=0;i<ANT_AMOUNT;i++)
        if (MinRoute<0||a[i].tour_length<MinRoute)
        {
            MinRoute=a[i].tour_length;
            out<<"["<<counter<<"] ";
            out<<MinRoute<<endl;
            for (int k=0;k<CITY_AMOUNT+1;k++) MinTour[k]=a[i].tour[k];
        }

}

void PheUpdate()
{
    for (int i=0;i<CITY_AMOUNT;i++)
        for (int j=i+1;j<CITY_AMOUNT;j++)
        {
            pheromone[i][j]=pheromone[i][j]/2.0;
            if (pheromone[i][j]<MIN_PHE) pheromone[i][j]=MIN_PHE;
            pheromone[j][i]=pheromone[i][j];
        }
    for (int i=0;i<ANT_AMOUNT;i++)
    {
        double delta=1.0/a[i].tour_length;
        for (int k=0;k<CITY_AMOUNT;k++)
        {
            int j=a[i].tour[k];
            int l=a[i].tour[k+1];
            pheromone[j][l]+=delta;
            pheromone[l][j]=pheromone[j][l];
        }
    }
    if (MinRoute>0)//���������ֵ�����·����ǿ��
    {
        double delta=1.0/MinRoute;
        for (int k=0;k<CITY_AMOUNT;k++)
        {
            int j=MinTour[k];
            int l=MinTour[k+1];
            pheromone[j][l]+=OMEGA*delta;//1��Ũ��
            pheromone[l][j]=pheromone[j][l];
        }
    }
    for (int i=0;i<CITY_AMOUNT;i++)
        for (int j=i+1;j<CITY_AMOUNT;j++) choice_info[i][j]=choice_info[j][i]=pheromone[i][j]*1.0/(distant[i][j]*distant[i][j]);


}

int main()
{
    Prepare();
    fstream out2("C:\\Users\\Administrator\\Desktop\\result2.txt");
    cout<<"begin"<<endl;
    for (int i=0;i<CITY_AMOUNT;i++) cout<<x_pos[i]<<' '<<y_pos[i]<<endl;
    cin>>bre;
    srand(time(0));
    out.open("C:\\Users\\Administrator\\Desktop\\result.txt");//////////////////////////
    for (counter=0;counter<GENERATION_TIMES;counter++)
    {
        Move();
        PheUpdate();
        cout<<"["<<counter+1<<"]      "<<MinRoute<<endl;
    }
    cout<<"shortest is "<<MinRoute<<endl;
    for (int k=0;k<CITY_AMOUNT+1;k++) cout<<MinTour[k]<<' ';
    for (int k=0;k<CITY_AMOUNT+1;k++)
    {
        out2<<x_pos[MinTour[k]]<<','<<y_pos[MinTour[k]]<<';'<<endl;
    }
    cout<<endl;
    out2.close();
    out.close();////////////////////////////////////////////////////////
    return 0;
}
