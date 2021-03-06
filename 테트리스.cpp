// 테트리스_.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#define LEN 20 // 가로 20
#define HIG 25 // 세로 25
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32
#define X x*2
void background();
int move();
int autodown();
int gameover();
int blocksave();
void start();
int removeblock();
void movedown(int);
void displayscore();
int random();
//함수 선언
int wall[HIG][LEN] = { 0 };
int x = LEN / 2, y = 1;
float score = 20.0;
float totalscore = 0.0;
float scorebonus = 0.01;
float removescore = 100.0;
int block[7][4][4][4] = {{{{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0} },{{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0} },{{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0} },{{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}}},{{{0,1,1,1}, {0,0,0,1},{0,0,0,0},{0,0,0,0}},{{0,0,0,1},{0,0,0,1},{0,0,1,1},{0,0,0,0}},{{0,1,0,0},{0,1,1,1},{0,0,0,0},{0,0,0,0}},{{0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}}},{{{0,1,1,1},{0,0,1,0},{0,0,0,0},{0,0,0,0}},{{0,0,0,1},{0,0,1,1},{0,0,0,1},{0,0,0,0}},{{0,0,1,0},{0,1,1,1},{0,0,0,0},{0,0,0,0}},{{0,0,1,0},{0,0,1,1},{0,0,1,0},{0,0,0,0}}},{{{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}},{{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},{{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}},{{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}}},{{{0,1,1,1},{0,1,0,0},{0,0,0,0},{0,0,0,0}},{{0,1,1,0},{0,0,1,0},{0,0,1,0},{0,0,0,0}},{{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},{{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}}},{{{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},{{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}},{{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},{{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}}},{{{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},{{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},{{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},{{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0} } } };
//전역 변수
int main()
{
	srand((unsigned int)time(NULL));
	if (HIG < 12)
	{
		printf("게임을 실행할 수 없습니다.");
		return 0;
	}
	if (LEN < 3)
	{
		printf("게임을 실행할 수 없습니다.");
		return 0;
	}
	start();
	background();// 배경 출력
	gotoxy(X, y);
	printf("□"); // 첫 블럭 생성
	while (1) {
		if (_kbhit()) {
			move(); // 블록 키보드제어
		}
		if (!blocksave()) { // 블럭저장
			if (!_kbhit()) {
				autodown();
			}
		}
		else {
			x = LEN / 2; y = 1; // 새 블럭 생성
			gotoxy(X, y);
			printf("□");
			if (wall[y + 1][x])
			{
				Sleep(1000);
				wall[y][x] = 1;
				gameover();
			}
		}
		if (gameover()) // 게임오버
		{
			system("cls");
			gotoxy(LEN, HIG / 2);
			printf("Game Over\n");
			return 0;
		}
		removeblock();
		displayscore();
	}
	return 0;
}

int blocksave()
{
	if (wall[y + 1][x])
	{
		score = score + (score * scorebonus);
		totalscore += score;
		wall[y][x] = 1;
		return 1;
	}
	return 0;
}

int move()
{
	int keyinput;
	gotoxy(X, y);
	printf("□");
	keyinput = _getch();
	if (keyinput == SPACE)
	{
		for (int i = 1; i < HIG; i++)
		{
			if (wall[i][x])//하드드롭
			{
				gotoxy(X, y);
				printf("  ");
				wall[i - 1][x] = 1;
				y = i - 1;
				gotoxy(X, y);
				printf("□");
				break;
			}
		}
	}
	if (keyinput == 224)
	{
		keyinput = _getch();
		switch (keyinput)
		{
		case UP: break;
		case LEFT: if (wall[y][x - 1]) break;
			gotoxy(X, y);
			printf("  ");
			x--;
			gotoxy(X, y);
			printf("□");
			break;
		case RIGHT: if (wall[y][x + 1]) break;
			gotoxy(X, y);
			printf("  ");
			x++;
			gotoxy(X, y);
			printf("□");
			break;
		case DOWN: gotoxy(X, y); printf("  "); y++; gotoxy(X, y); printf("□"); break;
		}
	}
	return 0;
}


int autodown()
{
	for (int i = 0; i < 75; i++)
	{
		Sleep(10);
		if (_kbhit())return 0;
	}
	gotoxy(X, y);
	printf("  ");
	y++;
	gotoxy(X, y);
	printf("□");
	return 0;
}

void background()
{
	for (int i = 0; i < LEN; i++)
	{
		wall[0][i] = 1;
		wall[HIG - 1][i] = 1;
	}
	for (int i = 0; i < HIG; i++)
	{
		wall[i][0] = 1;
		wall[i][LEN - 1] = 1;
	}
	for (int i = 0; i < HIG; i++)
	{
		for (int j = 0; j < LEN; j++)
		{
			if (wall[i][j] == 1)
			{
				gotoxy(j * 2, i);
				printf("■");
			}
		}
	}
	gotoxy(LEN * 2, HIG - 12);
	printf("■■■■■■■■■");
	gotoxy(LEN * 2, HIG - 11);
	printf("                ■");
	gotoxy(LEN * 2, HIG - 10);
	printf("   ↑방향전환   ■");
	gotoxy(LEN * 2, HIG - 9);
	printf("   ↔좌우이동   ■");
	gotoxy(LEN * 2, HIG - 8);
	printf(" space 하드드롭 ■");
	gotoxy(LEN * 2, HIG - 7);
	printf("                ■");
	gotoxy(LEN * 2, HIG - 6);
	printf("■■■■■■■■■");
	gotoxy(LEN * 2, HIG - 5);
	printf("                ■");
	gotoxy(LEN * 2, HIG - 4);
	printf("      점 수     ■");
	gotoxy(LEN * 2, HIG - 3);
	printf("                ■");
	gotoxy(LEN * 2, HIG - 2);
	printf("                ■");
	gotoxy(LEN * 2, HIG - 1);
	printf("■■■■■■■■■");
}

int gameover()
{
	for (int i = 1; i < LEN - 2; i++)
	{
		if (wall[1][i])
		{
			return 1;
		}
	}
	return 0;
}

int removeblock()
{
	int count = 0, i, j;
	for (i = HIG - 2; i > 1; i--)
	{
		for (j = 1; j < LEN - 1; j++)
		{
			if (wall[i][j] == 0)
			{
				break;
			}
			if (j == LEN - 2)
			{
				count++;
			}
		}
		if (count == 1)
		{
			break;
		}
	}
	if (count == 1)
	{
		for (j = 1; j < LEN - 1; j++)
		{
			gotoxy(j * 2, i);
			printf("  ");
		}
		movedown(i);
		totalscore += removescore;
		removescore += removescore*scorebonus; // 줄 지웠을때 점수
	}
	return 0;
}

void movedown(int i)
{
	for (int k = 1; k < LEN - 1; k++)
	{
		wall[i][k] = 0;
	}
	i--;
	for (; i > 1; i--)
	{
		for (int k = 1; k < LEN - 1; k++) {
			if (wall[i][k] == 1)
			{
				wall[i][k] = 0;
				gotoxy(k * 2, i);
				printf("  ");
				wall[i + 1][k] = 1;
				gotoxy(k * 2, i + 1);
				printf("□");
			}
		}
	}
}

void start()
{
	int key;
	gotoxy(46, 1);
	printf("■");
	gotoxy(46, 2);
	printf("■");
	gotoxy(40, 4);
	printf("■");
	gotoxy(42, 5);
	printf("■");
	gotoxy(44, 6);
	printf("■■");
	for (int i = 0; i < 7; i++)
	{
		gotoxy(4, i);
		printf("■");
		gotoxy(12, i);
		printf("■");
		gotoxy(29, i);
		printf("■");
		gotoxy(38, i);
		printf("■");
		gotoxy(51, i);
		printf("■");
	}
	for (int i = 0; i < 5; i++)
	{
		gotoxy(0 + i * 2, 0);
		printf("■");
		gotoxy(12 + (i * 2), 0);
		printf("■");
		gotoxy(12 + (i * 2), 3);
		printf("■");
		gotoxy(12 + (i * 2), 6);
		printf("■");
		gotoxy(25 + i * 2, 0);
		printf("■");
		if (i != 4)
		{
			gotoxy(38 + i * 2, 0);
			printf("■");
			gotoxy(58 + i * 2, 0);
			printf("■");
			gotoxy(56 + i * 2, 6);
			printf("■");
		}
		if (i < 3)
		{
			gotoxy(58 + i * 2, 3);
			printf("■");
		}
		gotoxy(38 + i * 2, 3);
		printf("■");
	}
	gotoxy(56, 1);
	printf("■");
	gotoxy(56, 2);
	printf("■");
	gotoxy(64, 5);
	printf("■");
	gotoxy(64, 4);
	printf("■");
	gotoxy(20, 7);
	printf("게임을 시작하려면 방향키 위를 눌러주세요");
	while (1)
	{
		key = _getch();
		if (key == UP)
		{
			system("cls");
			break;
		}
	}
}

void displayscore()
{
	gotoxy(LEN * 2 + 5, HIG - 3);
	printf("%07.0f", totalscore);
}


// 243줄, 80줄

int random()
{
	int a;
	a = rand() % 7;
	return a;
}