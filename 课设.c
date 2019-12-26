#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char record[19][21] = {0};//用于记录最短路径
void fuzhi();//用于给最短路径赋值
int StepNumber = 0;//记录走了多远
int ShortStepNumber = 1000;//用于记录最短步数
int num = 1;//记录多少条路

char arr[19][21] = {
		{'2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2','2'},
		{'2','2','2','2','2','2','2','A','A','A','A','A','A','A','A','A','A','A','A','2','2'},
		{'2','B','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','I','2'},
		{'2','B','0','C','C','0','D','D','0','E','E','0','F','F','F','F','F','F','0','I','2'},
		{'2','B','0','C','C','0','D','D','0','E','E','0','F','F','F','F','F','F','0','I','2'},
		{'2','B','0','C','C','0','D','D','0','E','E','0','0','0','0','0','0','0','0','I','2'},
		{'2','B','0','C','C','0','D','D','0','E','E','0','G','G','G','G','G','G','0','I','2'},
		{'2','B','0','C','C','0','D','D','0','E','E','0','G','G','G','G','G','G','0','I','2'},
		{'2','B','0','C','C','0','D','D','0','E','E','0','0','0','0','0','0','0','0','I','2'},
		{'2','B','0','C','C','0','D','D','0','E','E','0','H','H','H','H','H','H','0','I','2'},
		{'2','B','0','C','C','0','D','D','0','E','E','0','H','H','H','H','H','H','0','I','2'},
		{'2','B','0','C','C','0','D','D','0','0','0','0','0','0','0','0','0','0','0','8','9'},
		{'2','B','0','0','0','0','0','0','0','K','K','K','K','K','0','L','L','L','0','M','2'},
		{'2','B','0','J','J','J','J','J','0','K','K','K','K','K','0','L','L','L','0','M','2'},
		{'2','B','0','J','J','J','J','J','0','K','K','K','K','K','0','L','L','L','0','M','2'},
		{'2','B','0','J','J','J','J','J','0','K','K','K','K','K','0','L','L','L','0','M','2'},
		{'2','B','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','M','2'},
		{'2','2','5','2','2','2','2','1','6','1','1','6','1','1','6','1','2','2','2','2','2'},
		{'2','2','7','2','2','2','2','1','7','1','1','7','1','1','7','1','2','2','2','2','2'}
	};

struct Point{
	int x;
	int y;
	char name[30];
	char description[9999];
};

struct Point point[] = {
	{16,2,"entrance","从此进入超市"},
	{16,8,"exit1","超市的第一个出口"},
	{16,11,"exit2","超市的第二个出口"},
	{16,14,"exit3","超市的第三个出口"},
	{2,13,"A","A区：进口商品区"},
	{10,2,"B","B区：酒水饮料区"},
	{7,5,"C","C区：主食调味品区"},
	{7,8,"D","D区：服饰鞋帽区"},
	{7,11,"E","E区：零食区"},
	{5,15,"F","F区：洗护用品区"},
	{8,15,"G","G区：办公用品区"},
	{11,15,"H","H区：灯具电器用品区"},
	{6,18,"I","I区：体育益智区"},
	{16,5,"J","J区：食品特价区"},
	{16,12,"K","K区：日用品特价区"},
	{16,16,"L","L区：常温乳制品区"},
	{14,18,"M","M区：冷藏乳制品区"},
	{-1,-1,"No Found","没有找到该位置"}
};

void PrintMap(char arr[19][21], int StepNumber)
{
	int i = 0, j = 0;
	for(i = 0; i < 19; i++)
	{
		for(j = 0; j < 21; j++)
		{
			switch(arr[i][j])
			{
			case '0':printf("  ");break;
			case '1':printf("$$");break;
			case '2':printf("█");break;
			case '3':printf("▓");break;
			case '5':printf("入");break;
			case '6':printf("出");break;
			case '7':printf("口");break;
			case '8':printf("仓");break;
			case '9':printf("库");break;
			case 'A':printf("AA");break;
			case 'B':printf("BB");break;
			case 'C':printf("CC");break;
			case 'D':printf("DD");break;
			case 'E':printf("EE");break;
			case 'F':printf("FF");break;
			case 'G':printf("GG");break;
			case 'H':printf("HH");break;
			case 'I':printf("II");break;
			case 'J':printf("JJ");break;
			case 'K':printf("KK");break;
			case 'L':printf("LL");break;
			case 'M':printf("MM");break;
			}
		}
		printf("\n");
	}
	if(StepNumber > 0)
	{
		printf("您需要行走的步数为%d\n", StepNumber);
	}
	printf("entrance\n");
	printf("exit1\n");
	printf("exit2\n");
	printf("exit3\n");
	printf("A：进口商品区\n");
	printf("B：酒水饮料区\n");
	printf("C：主食调味品区\n");
	printf("D：服饰鞋帽区\n");
	printf("E：零食区\n");
	printf("F：洗护用品区\n");
	printf("G：办公用品区\n");
	printf("H：灯具电器用品区\n");
	printf("I：体育益智区\n");
	printf("J：食品特价区\n");
	printf("K：日用品特价区\n");
	printf("L：常温乳制品区\n");
	printf("M：冷藏乳制品区\n");
	printf("$：收银台\n");
}

void fuzhi()
{
	int i, j;
	for(i = 0; i < 19; i++)
		for(j = 0; j < 21; j++)
			record[i][j] = arr[i][j];
}

struct Point * SelectName(int n)
{
	int i;
	char name[20];
	scanf("%s", name);
	for(i = 0; i < n; i++)
	{
		if(strcmp(point[i].name, name) == 0)
		{
			return & point[i];
		}
	}
	printf("\n");
	return & point[17];
}

void visit(int startX, int startY, int endX, int endY, int x)
{
	char n = arr[startX][startY];
	arr[startX][startY] = '3';
	StepNumber++;
	if(startX == endX && startY == endY)
	{
		if(x)
		{
			printf("第%d条线路\n",(num++));
			PrintMap(arr, StepNumber);
		}
		if(ShortStepNumber > StepNumber)
		{
			ShortStepNumber = StepNumber;
			fuzhi();
		}
	}
	if(arr[startX][startY + 1] == '0')    visit(startX, startY + 1, endX, endY, x);
	if(arr[startX + 1][startY] == '0')    visit(startX + 1, startY, endX, endY, x);
	if(arr[startX][startY - 1] == '0')    visit(startX, startY - 1, endX, endY, x);
	if(arr[startX - 1][startY] == '0')    visit(startX - 1, startY, endX, endY, x);
	arr[startX][startY] = n;
	StepNumber--;
}

void Navigate(int x)
{
	ShortStepNumber = 1000;
	struct Point * start;
	struct Point * end;
	int startX, startY, endX, endY;
	int c;
	int i = 1;

	while(i == 1)
	{
		printf("请输入您所在位置：");
		start = SelectName(20);
		if((-1) == start->x)
		{
			printf("是否重新输入你所在地:(1/0)\n");
			scanf("%d", &c);
			if(c == 1)
				i = 1;
			else
				return;
		}
		else
			i = 0;
	}
	i= 1;
	while(i == 1)
	{
		printf("请输入您的目的地：");
		end = SelectName(20);
		if((-1) == start->x)
		{
			printf("是否重新输入你所在地:(1/0)\n");
			scanf("%d", &c);
			if(c == 1)
				i = 1;
			else
				return;
		}
		else
			i = 0;
	}
	startX = start->x;
	startY = start->y;
	endX = end->x;
	endY = end->y;
	num = 1;
	visit(startX, startY, endX, endY, x);

	printf("其中最短路径为:\n");
	PrintMap(record, StepNumber);
}

int main()
{
	int i;
	int n = 20;
	struct Point * shelf;
	while(1)
	{
		printf("欢迎来到沈阳航空航天大学南区超市，我们将为您提供最精准的导航服务\n");
		printf("****************************************************************\n");
		printf("                     1.超市整体布局\n");
		printf("                     2.兴趣点查询\n");
		printf("                     3.导航\n");
		printf("                     4.显示最短路径\n");
		printf("                     5.退出\n");
		printf("****************************************************************\n");
		scanf("%d", &i);
		switch(i)
		{
			case 1: 
				printf("查询位置\n"); 
				PrintMap(arr,0); 
				break;
			case 2:
				printf("请输入查询兴趣点的名称:\n");
				shelf = SelectName(n);
				if((-1) != shelf->x)
				{
					printf("该货架所在的坐标为%d %d\n",shelf->x,shelf->y);
					printf("%s\n", shelf->description);
				}
				break;
			case 3:
				printf("导航\n");
				Navigate(1);
				break;
			case 4:
				printf("其中最短路径为:\n");
				Navigate(0);
				break;
			case 5:
				printf("退出\n");
				exit(0);
				break;
		}
	}
	return 0;
}
