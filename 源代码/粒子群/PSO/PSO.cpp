/************************************************************************/
/* Author:      yuzelin       -  https://github.com/AlieYu               */
/* Email:       zelinyu@qq.com                                            */
/* FileName:    PSO.cpp                                                  */         
/* LastChange:  2015-4-28                                                 */
/************************************************************************/ 

  

#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"PSO.h"
#include <cstdio>

//΢�����޲ι��캯��
PARTICLE::PARTICLE()
{
	X=0;
	V=0;
	XBest=0;
	Dim=0;
}
//΢�����вι��캯��
PARTICLE::PARTICLE(int n)
{
	Dim=n;
	X=new double[Dim];
	V=new double[Dim];
	XBest=new double[Dim];
}
//΢������������
PARTICLE::~PARTICLE()
{
	if(Dim)
	{
		delete[] X;
		delete[] V;
		delete[] XBest;
	}
}
//����΢����ά��
void PARTICLE::SetDim(int d)
{
	if(X)
	{
		delete[] X;
	}
	if(V)
	{
		delete[] V;
	}
	if(XBest)
	{
		delete[] XBest;
	}
	Dim=d;
	X=new double[Dim];
	V=new double[Dim];
	XBest=new double[Dim];
}

//PSO���޲ι��캯��
PSO::PSO()
{
	Particle=0;
	PNum=0;
	GBestIndex=0;
	Xup=0;
	Xdown=0;
//	W=1;
	W_max=1;
	W_min=0.6;

	C1=2;
	C2=2;
	Com=0;
}
//PSO���вι��캯��
PSO::PSO(int dim,int n)
{
	Particle=new PARTICLE[n];
	for(int i=0;i<n;i++)
	{
		Particle[i].SetDim(dim);
	}
	PNum=n;
	GBestIndex=0;
	Xup=new double[dim];
	Xdown=new double[dim];
	Vmax=new double[dim];
//	W=1;
	W_max=1;
	W_min=0.6;

	C1=2;
	C2=2;
	Com=0;
}
//PSO����������
PSO::~PSO()
{
	if(Particle)
	{
		delete[] Particle;
	}
	if(Xup)
	{
		delete[] Xup;
	}
	if(Xdown)
	{
		delete[] Xdown;
	}
	if(Vmax)
	{
		delete[] Vmax;
	}
}
//���������Ͻ�
void PSO::SetXup(double *up)
{
	if(!Particle)
	{
		return;
	}
	for(int i=0;i<Particle[0].Dim;i++)
	{
		Xup[i]=up[i];
	}
}
//���������½�
void PSO::SetXdown(double *d)
{
	if(!Particle)
	{
		return;
	}
	for(int i=0;i<Particle[0].Dim;i++)
	{
		Xdown[i]=d[i];
	}
}
//��������ٶ�
void PSO::SetVmax(double *max)
{
	if(!Particle)
	{
		return;
	}
	for(int i=0;i<Particle[0].Dim;i++)
	{
		Vmax[i]=max[i];
	}
}
void PSO::SetVmax(double p)
{
	if(!Particle)
	{
		return;
	}
	for(int i=0;i<Particle[0].Dim;i++)
	{
		Vmax[i]=(Xup[i]-Xdown[i])*p;
	}
}
//��ʼ��Ⱥ��
void PSO::Initialize()
{
	if(!Particle)
	{
		return;
	}
	static int kk=(unsigned)time(NULL);
	srand((unsigned)time(NULL)+kk++);

	GBestIndex=0;
	
	//��ʼ���������ӵĸ���
	for(int i=0;i<PNum;i++)
	{
		for(int j=0;j<Particle[i].Dim;j++)
		{
			Particle[i].X[j]=rand()/(double)RAND_MAX*(Xup[j]-Xdown[j])+Xdown[j];//�����ʼ������
			Particle[i].XBest[j]=Particle[i].X[j];
			Particle[i].V[j]=rand()/(double)RAND_MAX*Vmax[j]-Vmax[j]/2;//�����ʼ���ٶ�
		}
		Particle[i].Fit=GetFit(Particle[i]);//����ÿ��΢���ʺ϶�
		Particle[i].FitBest=Particle[i].Fit;//���������ʺ϶�ֵ
		if(Particle[i].Fit>Particle[GBestIndex].Fit)
		{
			//����������ʺ϶ȴ���Ⱥ�������ʺ϶ȵĻ�����¼�²���Ⱥ�������΢��
			GBestIndex=i;
		}
	}
}
//����Ⱥ�����΢�����ʺ϶�
void PSO::CalFit()
{
	if(!Particle)
	{
		return;
	}
	for(int i=0;i<PNum;i++)
	{
		Particle[i].Fit=GetFit(Particle[i]);
	}
}
//΢�����裬������һ��΢��
void PSO::ParticleFly()
{
	static double FitBak[100];//������ű��ݵ��ʺ϶�ֵ
	if(!Particle)
	{
		return;
	}
	static int tt=(unsigned)time(NULL);
	srand((unsigned)time(NULL)*tt++);

	static int kk=2;//��������
	double W;
	W=W_max-kk*(W_max-W_min)/IteorMax;
	kk++;

	//����Ⱥ������µ�λ��
	for(int i=0;i<PNum;i++)
	{
		for(int j=0;j<Particle[i].Dim;j++)
		{
			Particle[i].V[j]=W*Particle[i].V[j]+
							 rand()/(double)RAND_MAX*C1*(Particle[i].XBest[j]-Particle[i].X[j])+
							 rand()/(double)RAND_MAX*C2*(Particle[GBestIndex].XBest[j]-Particle[i].X[j]);

		}
		for(int j=0;j<Particle[i].Dim;j++)
		{
			if(Particle[i].V[j]>Vmax[j])
			{
				Particle[i].V[j]=Vmax[j];
			}
			if(Particle[i].V[j]<-Vmax[j])
			{
				Particle[i].V[j]=-Vmax[j];
			}
		}
		for(int j=0;j<Particle[i].Dim;j++)
		{
			Particle[i].X[j]+=Particle[i].V[j];//�޸�����
			if(Particle[i].X[j]>Xup[j])
			{
				Particle[i].X[j]=Xup[j];
			}
			if(Particle[i].X[j]<Xdown[j])
			{
				Particle[i].X[j]=Xdown[j];
			}
		}
	}
	
	//�����΢�����ʺ϶�
	CalFit();
	for(int i=0;i<PNum;i++)
	{
		FitBak[i]=Particle[i].Fit;
	}
	//���ø�������λ��
	for(int i=0;i<PNum;i++)
	{
		if(Particle[i].Fit>=Particle[i].FitBest)
		{
			Particle[i].FitBest=Particle[i].Fit;
			for(int j=0;j<Particle[i].Dim;j++)
			{
				Particle[i].XBest[j]=Particle[i].X[j];
			}
		}
	}

	//����Ⱥ�����µ����Ÿ���
	GBestIndex=0;
	for(int i=0;i<PNum;i++)
	{
		if( (Particle[i].FitBest>=Particle[GBestIndex].FitBest) && i!=GBestIndex)
		{
			GBestIndex=i;
		}
	}
	printf("��Ⱥ����ֵ��[%d] %f %f\n",GBestIndex,GetFit(Particle[GBestIndex]),Particle[GBestIndex].FitBest);//////////////////////////change here
}

//��������д�������Ⱥ���㷨��������������
PARTICLE& PSO::Run(int n)
{
	Initialize();
	double *opt_p=new double[Particle[0].Dim];//ͨѶ�����飬���ŵ�����
	double **opt_a=new double*[PNum];		  //ͨѶ�����飬���е�����

	for(int i=0;i<n;i++)
	{
		ParticleFly();
	}
	delete[] opt_p;
	delete[] opt_a;
	return Particle[GBestIndex];
}
//������ʺ϶�����Ⱥ���㷨
PARTICLE& PSO::Run(double fit)
{
	Initialize();
	double *opt_p=new double[Particle[0].Dim];//ͨѶ�����飬���ŵ�����
	double **opt_a=new double*[PNum];		  //ͨѶ�����飬���е�����

	do
	{
		ParticleFly();
		if(Com)			//ͨѶ�������ڣ����ͨѶ
		{
			for(int k=0;k<Particle[0].Dim;k++)
			{
				opt_p[k]=Particle[GBestIndex].XBest[k];//�������ŵ�����
			}
			for(int k=0;k<PNum;k++)
			{
				opt_a[k]=Particle[k].X;//ָ�����е�����
			}
			if(!Com(Particle[GBestIndex].FitBest,opt_p,opt_a,GBestIndex))
			{
				break;
			}
		}
	}while(Particle[GBestIndex].FitBest<fit);
	delete[] opt_p;
	delete[] opt_a;
	return Particle[GBestIndex];
}
//������Ѹ���
double PSO::GetBest(double *r)
{
	for(int i=0;i<Particle[GBestIndex].Dim;i++)
	{
		r[i]=Particle[GBestIndex].XBest[i];
	}
	return Particle[GBestIndex].FitBest;
}