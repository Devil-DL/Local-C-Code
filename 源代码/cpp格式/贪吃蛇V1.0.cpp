#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
using namespace std;
int food_x,food_y;
int map[33][24]={0};

struct snake //�ߵĽṹ�壬x��ʾ��Ļ�����꣬y��ʾ��Ļ�����꣬before��ʾǰһ����
{
	int x;
	int y;
	snake *before;
};

void snakeMove(snake *body)//�ƶ��ߵĺ���������Ϊ��βָ�룬����β��ʼ����ǰһ���ߵ����꣨��ͷ���ֲ��䣩
{
	while (1)
	{
		if (body->before ==NULL) return;
		body->x =body->before->x;
		body->y =body->before->y;
		body =body->before;
	}
}

void HideCursor()//���ع�꺯��
{
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}

void gotoxy (int x,int y)//����ƶ�����
{
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void drawMap(void)//���Ƶ�ͼ���������Ƴ����᷽��31�񣨺�������仯2Ϊһ�񣩣����᷽��22��ĵ�ͼ
{
	int i;
	for (i=0;i<24;i++) map[0][i]=1;
	for (i=0;i<24;i++) map[32][i]=1;
	for (i=0;i<33;i++) map[i][0]=1;
	for (i=0;i<33;i++) map[i][23]=1; // �ڵ�ͼ�б�Ǳ߿�

	cout<<"�����������������������������������������������������������������ש�������������";
	cout<<"��                                                              ��  ̰����    ��";
	cout<<"��                                                              ��  ����̨    ��";
	cout<<"��                                                              ��  С��Ϸ    ��";
	cout<<"��                                                              ����������������";
	cout<<"��                                                              ��            ��";
	cout<<"��                                                              ��            ��";
	cout<<"��                                                              ��            ��";
	cout<<"��                                                              ��            ��";
	cout<<"��                                                              ��            ��";
	cout<<"��                                                              ��            ��";
	cout<<"��                                                              ��            ��";
	cout<<"��                                                              ��            ��";
	cout<<"��                                                              ��            ��";
	cout<<"��                                                              ����������������";
	cout<<"��                                                              �� W    ��    ��";
	cout<<"��                                                              ��            ��";
	cout<<"��                                                              �� S    ��    ��";
	cout<<"��                                                              ��            ��";
	cout<<"��                                                              �� A    ��    ��";
	cout<<"��                                                              ��            ��";
	cout<<"��                                                              �� D    ��    ��";
	cout<<"��                                                              ��            ��";
	cout<<"�����������������������������������������������������������������ߩ�������������";
	cout<<"  V1.0                                                             �����ˣ����� ";
	gotoxy(0,0);
}

void setFood(void)//����ʳ�ﺯ�����ڵ�ͼ��û�л����ߵĵط��������
{
	while (1)
	{
		int ran=(rand()%682)+1;
		food_y=(ran-1)/31+1;
		food_x=ran-(food_y-1)*31;//�˿̵�food_x,food_yΪ��ͼ�����꣨����Ļ���꣩
		if (map[food_x][food_y]==0)
		{
			food_x=2*food_x;//���껻Ϊ��Ļ����
			gotoxy(food_x,food_y);
			cout<<'*';
			return;
		}

	}

}

char opposite (char direction) //�෴������������෴�ķ���
{
	if (direction==UP) return DOWN;
	if (direction==DOWN) return UP;
	if (direction==LEFT) return RIGHT;
	if (direction==RIGHT) return LEFT;
}

int main()
{
	int head_x=2*10,head_y=15,tail_x=2*8,tail_y=15,food=0; //��ʼ��ͷβ��Ļ����
    char direction=RIGHT,lastDirection=RIGHT;//��ʼ������
	char name[20];
	snake *S_head,*S_tail;//�����ߵ�ͷβָ��
	HideCursor();//���ع��
	drawMap();//���Ƶ�ͼ
	srand(time(0));//����ϵͳʱ���������������
	getch();
	map[10][15]=1;
	map[9][15]=1;
	map[8][15]=1;//��ͼ��ȷ���ߵ�λ��
	S_head=new snake;
	S_tail=new snake;
	S_tail->x =tail_x;
	S_tail->y =tail_y;
	S_tail->before =new snake;
	S_tail->before->x =2*9;
	S_tail->before->y =tail_y;
	S_tail->before->before =S_head;
	S_head->x =head_x;
	S_head->y =head_y;
	S_head->before =NULL;//��ʼ�������ߵĽṹ��
	gotoxy(tail_x,tail_y);
	cout<<"������";//�����ߵĳ�ʼ״̬
    while (1)
	{
		if (food==0)    //ʳ��Ϊ0ʱ������ʳ��
		{
			setFood();
			food=1;
		}
		if (kbhit()!=0)            //���̻��������ڰ���ʱ���������
		{
			direction=getch();
		}
		if (direction==opposite(lastDirection)) direction=lastDirection;
		switch (direction)
		{
		  case UP:
			  {
				  if (S_head->x ==food_x && S_head->y-1==food_y)
				  {
					  S_head->before=new snake;
					  *(S_head->before)=*S_head;
					  S_head=S_head->before;
					  S_head->before=NULL;
					  S_head->y+=-1;
					  gotoxy(S_head->x,S_head->y);
					  cout<<"��";
					  if (map[S_head->x/2][S_head->y]==1) goto over;
					  map[S_head->x/2][S_head->y]=1;
					  food=0;
					  lastDirection=direction;
					  break;
				  }
				  gotoxy(S_tail->x,S_tail->y);
				  cout<<" ";
				  map[S_tail->x/2][S_tail->y]=0;
				  snakeMove(S_tail);
				  S_head->y+=-1;
				  gotoxy(S_head->x,S_head->y);
				  cout<<"��";
				  if (map[S_head->x/2][S_head->y]==1) goto over;
				  map[S_head->x/2][S_head->y]=1;
				  lastDirection=direction;
				  break;
			  }
		  case DOWN:
			  {
				  if (S_head->x ==food_x && S_head->y+1==food_y)
				  {
					  S_head->before=new snake;
					  *(S_head->before)=*S_head;
					  S_head=S_head->before;
					  S_head->before=NULL;
					  S_head->y+=1;
					  gotoxy(S_head->x,S_head->y);
					  cout<<"��";
					  if (map[S_head->x/2][S_head->y]==1) goto over;
					  map[S_head->x/2][S_head->y]=1;
					  food=0;
					  lastDirection=direction;
					  break;
				  }
				  gotoxy(S_tail->x,S_tail->y);
				  cout<<" ";
				  map[S_tail->x/2][S_tail->y]=0;
				  snakeMove(S_tail);
				  S_head->y+=1;
				  gotoxy(S_head->x,S_head->y);
				  cout<<"��";
				  if (map[S_head->x/2][S_head->y]==1) goto over;
				  map[S_head->x/2][S_head->y]=1;
				  lastDirection=direction;
				  break;
			  }
		  case LEFT:
			  {
				  if (S_head->x-2 ==food_x && S_head->y==food_y)
				  {
					  S_head->before=new snake;
					  *(S_head->before)=*S_head;
					  S_head=S_head->before;
					  S_head->before=NULL;
					  S_head->x+=-2;
					  gotoxy(S_head->x,S_head->y);
					  cout<<"��";
					  if (map[S_head->x/2][S_head->y]==1) goto over;
					  map[S_head->x/2][S_head->y]=1;
					  food=0;
					  lastDirection=direction;
					  break;
				  }
				  gotoxy(S_tail->x,S_tail->y);
				  cout<<" ";
				  map[S_tail->x/2][S_tail->y]=0;
				  snakeMove(S_tail);
				  S_head->x+=-2;
				  gotoxy(S_head->x,S_head->y);
				  cout<<"��";
				  if (map[S_head->x/2][S_head->y]==1) goto over;
				  map[S_head->x/2][S_head->y]=1;
				  lastDirection=direction;
				  break;
			  }
		  case RIGHT:
			  {
				  if (S_head->x+2 ==food_x && S_head->y==food_y)
				  {
					  S_head->before=new snake;
					  *(S_head->before)=*S_head;
					  S_head=S_head->before;
					  S_head->before=NULL;
					  S_head->x+=2;
					  gotoxy(S_head->x,S_head->y);
					  cout<<"��";
					  if (map[S_head->x/2][S_head->y]==1) goto over;
					  map[S_head->x/2][S_head->y]=1;
					  food=0;
					  lastDirection=direction;
					  break;
				  }
				  gotoxy(S_tail->x,S_tail->y);
				  cout<<" ";
				  map[S_tail->x/2][S_tail->y]=0;
				  snakeMove(S_tail);
				  S_head->x+=2;
				  gotoxy(S_head->x,S_head->y);
				  cout<<"��";
				  if (map[S_head->x/2][S_head->y]==1) goto over;
				  map[S_head->x/2][S_head->y]=1;
				  lastDirection=direction;
				  break;
			  }
		  default :
			  {
				  direction=lastDirection;
				  if (direction==UP)
				  {
					  if (S_head->x ==food_x && S_head->y-1==food_y)
					  {
						  S_head->before=new snake;
						  *(S_head->before)=*S_head;
						  S_head=S_head->before;
						  S_head->before=NULL;
						  S_head->y+=-1;
						  gotoxy(S_head->x,S_head->y);
						  cout<<"��";
						  if (map[S_head->x/2][S_head->y]==1) goto over;
						  map[S_head->x/2][S_head->y]=1;
						  food=0;
						  break;
					  }

					  gotoxy(S_tail->x,S_tail->y);
					  cout<<" ";
					  map[S_tail->x/2][S_tail->y]=0;
					  snakeMove(S_tail);
					  S_head->y+=-1;
					  gotoxy(S_head->x,S_head->y);
					  cout<<"��";
					  if (map[S_head->x/2][S_head->y]==1) goto over;
					  map[S_head->x/2][S_head->y]=1;
					  break;
				  }
				  if (direction==DOWN)
				  {
					  if (S_head->x ==food_x && S_head->y+1==food_y)
					  {
						  S_head->before=new snake;
						  *(S_head->before)=*S_head;
						  S_head=S_head->before;
						  S_head->before=NULL;
						  S_head->y+=1;
						  gotoxy(S_head->x,S_head->y);
						  cout<<"��";
						  if (map[S_head->x/2][S_head->y]==1) goto over;
						  map[S_head->x/2][S_head->y]=1;
						  food=0;
						  break;
					  }
					  gotoxy(S_tail->x,S_tail->y);
					  cout<<" ";
					  map[S_tail->x/2][S_tail->y]=0;
					  snakeMove(S_tail);
					  S_head->y+=1;
					  gotoxy(S_head->x,S_head->y);
					  cout<<"��";
					  if (map[S_head->x/2][S_head->y]==1) goto over;
					  map[S_head->x/2][S_head->y]=1;
					  break;
				  }
				  if (direction==LEFT)
				  {
					  if (S_head->x-2 ==food_x && S_head->y==food_y)
					  {
						  S_head->before=new snake;
						  *(S_head->before)=*S_head;
						  S_head=S_head->before;
						  S_head->before=NULL;
						  S_head->x+=-2;
						  gotoxy(S_head->x,S_head->y);
						  cout<<"��";
						  if (map[S_head->x/2][S_head->y]==1) goto over;
						  map[S_head->x/2][S_head->y]=1;
						  food=0;
						  break;
					  }
					  gotoxy(S_tail->x,S_tail->y);
					  cout<<" ";
					  map[S_tail->x/2][S_tail->y]=0;
					  snakeMove(S_tail);
					  S_head->x+=-2;
					  gotoxy(S_head->x,S_head->y);
					  cout<<"��";
					  if (map[S_head->x/2][S_head->y]==1) goto over;
					  map[S_head->x/2][S_head->y]=1;
					  break;
				  }
				  if (direction==RIGHT)
				  {
					  if (S_head->x+2 ==food_x && S_head->y==food_y)
					  {
						  S_head->before=new snake;
						  *(S_head->before)=*S_head;
						  S_head=S_head->before;
						  S_head->before=NULL;
						  S_head->x+=2;
						  gotoxy(S_head->x,S_head->y);
						  cout<<"��";
						  if (map[S_head->x/2][S_head->y]==1) goto over;
						  map[S_head->x/2][S_head->y]=1;
						  food=0;
						  break;
					  }
					  gotoxy(S_tail->x,S_tail->y);
					  cout<<" ";
					  map[S_tail->x/2][S_tail->y]=0;
					  snakeMove(S_tail);
					  S_head->x+=2;
					  gotoxy(S_head->x,S_head->y);
					  cout<<"��";
					  if (map[S_head->x/2][S_head->y]==1) goto over;
					  map[S_head->x/2][S_head->y]=1;
					  break;
				  }
			  }
		}
		Sleep(200);
	}
over:gotoxy(33*2,10);
	cout<<"��Ϸ����";
	Sleep(3000);
	getch();
	return 0;
}
