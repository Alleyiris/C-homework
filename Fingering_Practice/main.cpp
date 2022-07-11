#include <stdio.h>
#include <stdlib.h>
#include <easyx.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
/*����*/
IMAGE Welcome;
IMAGE background;
struct Block
{
	int x;
	int y;
	IMAGE block_yan, block_real;
}block;
struct Drop
{
	int x;
	int y;
	char symbol;
};
struct Drop drop[5];
struct Person
{
	char person[10];
	char password[10];
	char music;
	int difficult;
	int score;
};
struct Person* p = NULL;
//����ʱ��
DWORD t1 = GetTickCount();
DWORD t2 = GetTickCount();
//��������붪ʧ
int score = 0;
int lose = 0;
/*��ʼ��*/
void InitGame()
{
	//��ʼ������+loading
	initgraph(1000, 500);
	setbkmode(TRANSPARENT);//����͸������
	loadimage(&Welcome, L"jiazai.jpg", 1000, 500);//���ؽ���ȴ�ͼƬ

	//��ӡ��ʼ����
	putimage(0, 0, &Welcome);
	Sleep(2000);//�����Ե��ӳ�����...
	//���ر���
	loadimage(&background, L"background.jpg", 1000, 500);
	//���ط���
	loadimage(&(block.block_yan), L"_1 fuben.png", 60, 50);
	loadimage(&(block.block_real), L"_1.png", 60, 50);
	block.x = 55;
	block.y = 400;
	//���ص���
	for (int i = 0; i < 5; i++)
	{
		drop[i].x = 65 + 160 * i;
		drop[i].y = -100 - rand() % 100 * 10;
		drop[i].symbol = rand() % 26 + 65;
	}
}
//��¼��������
void gotoxy(int x, int y)//�������
{
	COORD pos = { x,y };
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, pos);
}
int Login()//�ȵ�¼������Ϸ
{
	gotoxy(20, 10);
	printf("�Ƿ�Ҫ����һ�����û�����Y/N):");
	char select;
	scanf("%c", &select);
	system("cls");
	p = (struct Person*)malloc(sizeof(struct Person));
	if (select == 'Y' || select == 'y')
	{
		gotoxy(20, 10);
		printf("�������û�����10���ַ�֮�ڣ���");
		scanf("%s", p->person);
		gotoxy(20, 11);
		printf("���������루10���ַ�֮�ڣ�:");
		scanf("%s", p->password);
		FILE* fp = fopen(p->person, "w");
		if (fp == NULL)
		{
			gotoxy(20, 12);
			printf("�ļ�У��ʧ�ܣ������������û��������룡");
			Sleep(1000);
			return ( - 1);
		}
		fprintf(fp, "%s\n", p->person);
		fprintf(fp, "%s\n", p->password);
		gotoxy(20, 12);
		printf("�����ɹ���\n");
		gotoxy(20, 13);
		getchar();//�Ե�Ī������Ļس�
		printf("��Ҫ�����𣿣�Y/N):");
		scanf("%c", &(p->music));
		switch (p->music)
		{
		case 'Y':
			PlaySound(TEXT("Windy Hill.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			break;
		default:
			break;
		}
		fprintf(fp, "%c\n", p->music);
		gotoxy(20, 14);
		printf("��ѡ����Ϸ�Ѷȣ�1-3����");
		scanf("%d", &(p->difficult));
		fprintf(fp, "%d\n", p->difficult);
		fclose(fp);
		return 1;
	}
	else
	{
		gotoxy(20, 10);
		char name[10];
		printf("�������û�����10���ַ�֮�ڣ���");
		scanf("%s", name);
		FILE* fp_check = fopen(name, "r");
		if (fp_check == NULL)
		{
			printf("�û�������,���������룡");
			Sleep(1000);
			return ( - 1);
		}
		gotoxy(20, 11);
		char password[10];
		printf("���������루10���ַ�֮�ڣ�:");
		scanf("%s", password);
		fscanf(fp_check, "%s\n%s\n%c\n%d\n%d\n", p->person, p->password, &(p->music), &(p->difficult), &(p->score));
		if (!strcmp(p->password, password))
		{
			gotoxy(20, 12);
			printf("��¼�ɹ���\n");
			switch (p->music)
			{
			case 'Y':
				PlaySound(TEXT("Windy Hill.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				break;
			default:
				break;
			}
			gotoxy(20, 13);
			printf("�Ƿ��޸��Ѷ�������Ϸ��Y/N):");
			getchar();//�Ե�Ī������Ļس�
			char select_speed;
			scanf("%c", &select_speed);
			getchar();//�Ե�Ī������Ļس�
			if (select_speed == 'Y' || select_speed == 'y')
			{
				score = 0;
				p->score = score;
				gotoxy(20, 14);
				printf("�޸ĵ��Ѷ�Ϊ��");
				scanf("%d", &(p->difficult));
				gotoxy(20, 15);
				printf("�޸��Ѷȳɹ����Ժ󽫽�����Ϸ...");
			}
			else
			{
				score = p->score;
				gotoxy(20, 15);
				printf("����������Ϸ...");
			}
			Sleep(1000);
			return 1;
		}
		else
		{
			gotoxy(20, 12);
			printf("��������޷�������Ϸ,���Ժ��������룡");
			Sleep(1000);
			return ( - 1);
		}
		fclose(fp_check);
	}
}
/*����*/
void DrawGame()
{
	BeginBatchDraw();//��ʼ������ͼ
	//��ӡ����
	putimage(0, 0, &background);
	//��ӡ����
	putimage(block.x, block.y, &block.block_yan, SRCPAINT);//������
	putimage(block.x, block.y, &block.block_real, SRCAND);//������

	setbkmode(TRANSPARENT);//����͸������
	//��ӡ����
	settextstyle(20, 10, L"���Ŀ���");
	settextcolor(RGB(255, 255, 255));
	outtextxy(800, 25, L"�û�����");
	outtextxy(800, 50, L"�÷֣� ");
	outtextxy(800, 75, L"�ٶȣ�");
	//�����ַ�
	settextstyle(40, 15, L"���Ŀ���");
	settextcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
	for (int i = 0; i < 5; i++)
		outtextxy(drop[i].x, drop[i].y, drop[i].symbol);

	settextstyle(20, 10, L"���Ŀ���");
	settextcolor(RGB(255, 255, 255));
	//��ӡ�û���
	TCHAR help[100];
	swprintf_s(help, L"%S", p->person);
	outtextxy(900, 26, help);
	//��ӡ����
	TCHAR help_1[100];
	swprintf_s(help_1, L"%d", score);
	outtextxy(900, 51, help_1);
	//��ӡ�ٶ�
	TCHAR help_2[100];
	swprintf_s(help_2, L"%d", p->difficult);
	outtextxy(900, 76, help_2);
	EndBatchDraw();//����������ͼ
}
/*����*/
int FreshGame()
{
	char move;
	//ʯ����²���
	if (_kbhit())
	{
		move = _getch();
		//�ж�ˢ�²���
		for (int i = 0; i < 5; i++)
		{
			if (drop[i].symbol == move && drop[i].x - 10 == block.x)
			{
				drop[i].y = -100 - rand() % 100 * 10;
				drop[i].symbol = rand() % 57 + 33;
				score += 1;
			}
		}
		switch (move)
		{
		case 75://��
			if (block.x > 65)
				block.x -= 160;
			break;
		case 77://��
			if (block.x < 545)
				block.x += 160;
			break;
		}
	}
	//������²���
	if (t2 - t1 > (10 - p->difficult) * 20)
	{
		for (int i = 0; i < 5; i++)
		{
			if (drop[i].y > 400)
			{
				drop[i].y = -100;
				lose = 1;
			}
			drop[i].y += 10;
			t1 = t2;
		}
	}
	t2 = GetTickCount();
	//�ж���������
	if (lose == 1)
	{
		MessageBoxA(NULL, "Game Over��", "giao", MB_OK | MB_SYSTEMMODAL);
		return ( - 1);
	}
	//�ж�����
	if (score != 0 && score % 10 == 0)
	{
		p->difficult += 1;
		score += 1;
	}
	//�ж�����
	if (score == 61)//���ﵽ60�ֵ�ʱ��ͨ��
	{
		MessageBoxA(NULL, "You have won ! ", "giao", MB_OK | MB_SYSTEMMODAL);
		return ( - 1);
	}
}
//������
int main()
{
	srand((unsigned int)time(NULL));//��ϵͳʱ���ʼ�����������
	while (1)
	{
		int value = Login();
		if (value == -1)
			continue;
		if (value == 1)
			break;
	}
	InitGame();
	int value_end = 0;
	while (1)
	{
		DrawGame();
		value_end = FreshGame();
		if (value_end == -1)
		{
			p->score = score;
			FILE* fp = fopen(p->person, "w");
			if (fp == NULL)
			{
				printf("�ļ�д��ʧ��");
				return ( - 1);
			}
			fprintf(fp, "%s\n%s\n%c\n%d\n%d\n", p->person, p->password, p->music, p->difficult, p->score);
			fclose(fp);
			break;
		}
	}
	return 0;
}