#include <stdio.h>
#include <stdlib.h>
#include <easyx.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
/*定义*/
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
//定义时间
DWORD t1 = GetTickCount();
DWORD t2 = GetTickCount();
//定义分数与丢失
int score = 0;
int lose = 0;
/*初始化*/
void InitGame()
{
	//初始化界面+loading
	initgraph(1000, 500);
	setbkmode(TRANSPARENT);//设置透明背景
	loadimage(&Welcome, L"jiazai.jpg", 1000, 500);//加载进入等待图片

	//打印初始界面
	putimage(0, 0, &Welcome);
	Sleep(2000);//象征性的延迟两秒...
	//加载背景
	loadimage(&background, L"background.jpg", 1000, 500);
	//加载方块
	loadimage(&(block.block_yan), L"_1 fuben.png", 60, 50);
	loadimage(&(block.block_real), L"_1.png", 60, 50);
	block.x = 55;
	block.y = 400;
	//加载掉落
	for (int i = 0; i < 5; i++)
	{
		drop[i].x = 65 + 160 * i;
		drop[i].y = -100 - rand() % 100 * 10;
		drop[i].symbol = rand() % 26 + 65;
	}
}
//登录界面制作
void gotoxy(int x, int y)//坐标控制
{
	COORD pos = { x,y };
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, pos);
}
int Login()//先登录再玩游戏
{
	gotoxy(20, 10);
	printf("是否要建立一个新用户？（Y/N):");
	char select;
	scanf("%c", &select);
	system("cls");
	p = (struct Person*)malloc(sizeof(struct Person));
	if (select == 'Y' || select == 'y')
	{
		gotoxy(20, 10);
		printf("请输入用户名（10个字符之内）：");
		scanf("%s", p->person);
		gotoxy(20, 11);
		printf("请输入密码（10个字符之内）:");
		scanf("%s", p->password);
		FILE* fp = fopen(p->person, "w");
		if (fp == NULL)
		{
			gotoxy(20, 12);
			printf("文件校验失败，请重新输入用户名和密码！");
			Sleep(1000);
			return ( - 1);
		}
		fprintf(fp, "%s\n", p->person);
		fprintf(fp, "%s\n", p->password);
		gotoxy(20, 12);
		printf("创建成功！\n");
		gotoxy(20, 13);
		getchar();//吃掉莫名其妙的回车
		printf("需要音乐吗？（Y/N):");
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
		printf("请选择游戏难度（1-3）：");
		scanf("%d", &(p->difficult));
		fprintf(fp, "%d\n", p->difficult);
		fclose(fp);
		return 1;
	}
	else
	{
		gotoxy(20, 10);
		char name[10];
		printf("请输入用户名（10个字符之内）：");
		scanf("%s", name);
		FILE* fp_check = fopen(name, "r");
		if (fp_check == NULL)
		{
			printf("用户名错误,请重新输入！");
			Sleep(1000);
			return ( - 1);
		}
		gotoxy(20, 11);
		char password[10];
		printf("请输入密码（10个字符之内）:");
		scanf("%s", password);
		fscanf(fp_check, "%s\n%s\n%c\n%d\n%d\n", p->person, p->password, &(p->music), &(p->difficult), &(p->score));
		if (!strcmp(p->password, password))
		{
			gotoxy(20, 12);
			printf("登录成功！\n");
			switch (p->music)
			{
			case 'Y':
				PlaySound(TEXT("Windy Hill.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				break;
			default:
				break;
			}
			gotoxy(20, 13);
			printf("是否修改难度重新游戏（Y/N):");
			getchar();//吃掉莫名其妙的回车
			char select_speed;
			scanf("%c", &select_speed);
			getchar();//吃掉莫名其妙的回车
			if (select_speed == 'Y' || select_speed == 'y')
			{
				score = 0;
				p->score = score;
				gotoxy(20, 14);
				printf("修改的难度为：");
				scanf("%d", &(p->difficult));
				gotoxy(20, 15);
				printf("修改难度成功！稍后将进入游戏...");
			}
			else
			{
				score = p->score;
				gotoxy(20, 15);
				printf("即将进入游戏...");
			}
			Sleep(1000);
			return 1;
		}
		else
		{
			gotoxy(20, 12);
			printf("密码错误！无法进入游戏,请稍后重新输入！");
			Sleep(1000);
			return ( - 1);
		}
		fclose(fp_check);
	}
}
/*绘制*/
void DrawGame()
{
	BeginBatchDraw();//开始批量绘图
	//打印背景
	putimage(0, 0, &background);
	//打印方块
	putimage(block.x, block.y, &block.block_yan, SRCPAINT);//或运算
	putimage(block.x, block.y, &block.block_real, SRCAND);//与运算

	setbkmode(TRANSPARENT);//设置透明背景
	//打印侧栏
	settextstyle(20, 10, L"华文楷体");
	settextcolor(RGB(255, 255, 255));
	outtextxy(800, 25, L"用户名：");
	outtextxy(800, 50, L"得分： ");
	outtextxy(800, 75, L"速度：");
	//绘制字符
	settextstyle(40, 15, L"华文楷体");
	settextcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
	for (int i = 0; i < 5; i++)
		outtextxy(drop[i].x, drop[i].y, drop[i].symbol);

	settextstyle(20, 10, L"华文楷体");
	settextcolor(RGB(255, 255, 255));
	//打印用户名
	TCHAR help[100];
	swprintf_s(help, L"%S", p->person);
	outtextxy(900, 26, help);
	//打印分数
	TCHAR help_1[100];
	swprintf_s(help_1, L"%d", score);
	outtextxy(900, 51, help_1);
	//打印速度
	TCHAR help_2[100];
	swprintf_s(help_2, L"%d", p->difficult);
	outtextxy(900, 76, help_2);
	EndBatchDraw();//结束批量绘图
}
/*更新*/
int FreshGame()
{
	char move;
	//石块更新操作
	if (_kbhit())
	{
		move = _getch();
		//判定刷新操作
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
		case 75://左
			if (block.x > 65)
				block.x -= 160;
			break;
		case 77://右
			if (block.x < 545)
				block.x += 160;
			break;
		}
	}
	//掉落更新操作
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
	//判定结束操作
	if (lose == 1)
	{
		MessageBoxA(NULL, "Game Over！", "giao", MB_OK | MB_SYSTEMMODAL);
		return ( - 1);
	}
	//判定进阶
	if (score != 0 && score % 10 == 0)
	{
		p->difficult += 1;
		score += 1;
	}
	//判定结束
	if (score == 61)//当达到60分的时候即通关
	{
		MessageBoxA(NULL, "You have won ! ", "giao", MB_OK | MB_SYSTEMMODAL);
		return ( - 1);
	}
}
//主函数
int main()
{
	srand((unsigned int)time(NULL));//用系统时间初始化随机数种子
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
				printf("文件写入失败");
				return ( - 1);
			}
			fprintf(fp, "%s\n%s\n%c\n%d\n%d\n", p->person, p->password, p->music, p->difficult, p->score);
			fclose(fp);
			break;
		}
	}
	return 0;
}