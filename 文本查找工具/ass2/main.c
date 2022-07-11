#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*定义文本结构体*/
struct Text
{
	char q[200];//保存每行的字符
	char* p;//移动指针
	int cishu;//记录出现多少次
};

//定义文本数组
struct Text text[100];
//定义行数
int cnt = 1;
//定义拼接容器
char save[100][200] = { '\0' };
//记录行数
int num_hang = 0;

int main()
{
	//初始化
	for (int i = 0; i < 100; i++)
	{
		text[i].cishu = 0;
		save[i][1] = '\0';
	}

	//子串输入
	printf("子串：");
	char zichuan[200] = { '\0' };
	scanf("%s", zichuan);
	getchar();//吃掉缓冲区的回车

	//文本输入
	printf("文本：");
	char ch;//判断是否输入EOF
	while ((ch = getchar()) != EOF)//getchar 吃掉了第一个字符,在ch中
	{
        if (ch == '\n')
		{
			num_hang++;
			save[cnt][0] = ch;
			text[cnt].p = save[cnt];
			cnt++;
			continue;
		}
		else
		{
			num_hang++;
		}
		fgets(text[cnt].q, sizeof(text[cnt].q), stdin);//从标准输入读字符串，到\n停止，吃掉了\n

		//拼接字符串
		save[cnt][0] = ch;
		strcat(save[cnt], text[cnt].q);//save成为最终的存储，cnt仍然对应；
		text[cnt].p = save[cnt];//便于判断移动
		cnt++;//推动换行
	}

	//进行判断
	for (int i = 1; i <= num_hang; i++)//循环每行
	{
		while (*(text[i].p) != '\n')//因为fgets把\n吃掉了
		{
			if (strncmp(text[i].p, zichuan, strlen(zichuan)) != 0)
			{
				text[i].p++;
			}
			else
			{
				text[i].cishu++;
				text[i].p += strlen(zichuan);
			}
		}

	}

	//进行输出
	int num_printf = 0;
	for (int i = 1; i <= num_hang; i++)
	{
		if (text[i].cishu != 0)
		{
			printf("第%d行 ", i);
			printf("出现%d次 ", text[i].cishu);
			printf("%s", save[i]);
			num_printf++;//记录是否有输出
		}
	}

	if (num_printf == 0)
	{
		printf("\n任何一行都没有\n");
	}
	system("pause");
	return 0;
}
