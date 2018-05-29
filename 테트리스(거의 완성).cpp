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
int move();
int autodown();
int gameover();
int blocksave();
void start();
int removeblock();
void movedown(int);
void displayscore();
int random();
int printblock(int);
int Rend();
int Lend();
int befsave();
//함수 선언
int wall[HIG][LEN] = { 0 };
int x = LEN / 2, y = 1;
int rotate = 0;
int bltype;
float score = 20.0;
float totalscore = 0.0;
float scorebonus = 0.01;
float removescore = 100.0;
int block[7][4][4][4] = {{{
{1,1,1,1}, // ㅁㅁㅁㅁ
{0,0,0,0},
{0,0,0,0},
{0,0,0,0} },{
{0,1,0,0}, //  ㅁ
{0,1,0,0}, //  ㅁ
{0,1,0,0}, //  ㅁ
{0,1,0,0} },{//ㅁ
{1,1,1,1}, // ㅁㅁㅁㅁ
{0,0,0,0},
{0,0,0,0},
{0,0,0,0} },{
{0,1,0,0},//    ㅁ
{0,1,0,0},//    ㅁ
{0,1,0,0},//    ㅁ
{0,1,0,0}}},{{//ㅁ
{0,1,1,1}, //  ㅁㅁㅁ
{0,0,0,1},//       ㅁ
{0,0,0,0},
{0,0,0,0}},{
{0,0,0,1},//      ㅁ
{0,0,0,1},//      ㅁ
{0,0,1,1},//    ㅁㅁ
{0,0,0,0}},{
{0,1,0,0},//  ㅁ
{0,1,1,1},//  ㅁㅁㅁ
{0,0,0,0},
{0,0,0,0}},{
{0,1,1,0},//  ㅁㅁ
{0,1,0,0},//  ㅁ
{0,1,0,0},//  ㅁ
{0,0,0,0}}},{{
{0,1,1,1},//   ㅁㅁㅁ
{0,0,1,0},//     ㅁ
{0,0,0,0},
{0,0,0,0}},{
{0,0,0,1},//      ㅁ
{0,0,1,1},//    ㅁㅁ
{0,0,0,1},//      ㅁ
{0,0,0,0}},{
{0,0,1,0},//      ㅁ
{0,1,1,1},//    ㅁㅁㅁ
{0,0,0,0},
{0,0,0,0}},{
{0,0,1,0},//    ㅁ
{0,0,1,1},//    ㅁㅁ
{0,0,1,0},//    ㅁ
{0,0,0,0}}},{{
{1,0,0,0},//ㅁ
{1,1,0,0},//ㅁㅁ
{0,1,0,0},//  ㅁ
{0,0,0,0}},{
{0,1,1,0},//  ㅁㅁ
{1,1,0,0},//ㅁㅁ
{0,0,0,0},
{0,0,0,0}},{
{1,0,0,0},//ㅁ
{1,1,0,0},//ㅁㅁ
{0,1,0,0},//  ㅁ
{0,0,0,0}},{
{0,1,1,0},//  ㅁㅁ
{1,1,0,0},//ㅁㅁ
{0,0,0,0},
{0,0,0,0}}},{{
{1,1,1,0},//  ㅁㅁㅁ
{1,0,0,0},//  ㅁ
{0,0,0,0},
{0,0,0,0}},{
{1,1,0,0},//  ㅁㅁ
{0,1,0,0},//    ㅁ
{0,1,0,0},//    ㅁ
{0,0,0,0}},{
{0,0,0,1},//    ㅁ
{0,1,1,1},//ㅁㅁㅁ
{0,0,0,0},
{0,0,0,0}},{
{1,0,0,0},//  ㅁ
{1,0,0,0},//  ㅁ
{1,1,0,0},//  ㅁㅁ
{0,0,0,0}}},{{
{1,1,0,0},// ㅁㅁ
{0,1,1,0},//   ㅁㅁ
{0,0,0,0},
{0,0,0,0}},{
{0,1,0,0},//  ㅁ
{1,1,0,0},//ㅁㅁ
{1,0,0,0},//ㅁ
{0,0,0,0}},{
{1,1,0,0},//ㅁㅁ
{0,1,1,0},//  ㅁㅁ
{0,0,0,0},
{0,0,0,0}},{
{0,1,0,0},//  ㅁ
{1,1,0,0},//ㅁㅁ
{1,0,0,0},//ㅁ
{0,0,0,0}}},{{
{1,1,0,0},//ㅁㅁ
{1,1,0,0},//ㅁㅁ
{0,0,0,0},
{0,0,0,0}},{
{1,1,0,0},//ㅁㅁ
{1,1,0,0},//ㅁㅁ
{0,0,0,0},
{0,0,0,0}},{
{1,1,0,0},//ㅁㅁ
{1,1,0,0},//ㅁㅁ
{0,0,0,0},
{0,0,0,0}},{
{1,1,0,0},//ㅁㅁ
{1,1,0,0},//ㅁㅁ
{0,0,0,0},
{0,0,0,0} } } };
//전역 변수
int main()
{
	int savecnt = 0;
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
	start();// 배경 출력
	bltype = random();
	gotoxy(X, y);
	printblock(bltype);
	while (1) {
		if (_kbhit()) {
			move(); // 블록 키보드제어
			savecnt = 0;
		}
		if (!blocksave()) { // 블럭저장
			if (!_kbhit()) {
				autodown();
			}
		}
		else {
			if (savecnt == 100)
			{
				befsave();
				x = LEN / 2; y = 1; // 새 블럭 생성
				gotoxy(X, y);
				printblock(bltype);
			}
			else savecnt++;
			if (wall[y + 1][x])
			{
				Sleep(1000);
				wall[y][x] = 1;
				gameover();
			}
		}
		Sleep(10);
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

int befsave()
{
	/*int j;
	for (int i = 0; i < 2; i++)
	{
		if (_kbhit()) {
			move(); continue;
		}
		for (j = 0; j < 20; j++)
		{
			Sleep(50);
			if (_kbhit()) break;
		}
		if(j>=99)break;
		else {
			i = 0; continue;
		}
	}*/
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[bltype][rotate][i][j] == 1)
			{
				wall[y + i][x + j] = 1;
			}
		}
	}
	score = score + (score * scorebonus);
	totalscore += score;
	bltype = random();
	return 0;
}

int blocksave() // 저장 시 1 반환, 아니면 0 반환
{
	//int count = 0;
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 0; j < 4; j++)
		{
			if (wall[y + i + 1][x + j] == 1 && block[bltype][rotate][i][j] == 1)
			{
				/*if (count == 0) {
					count = 1;
					i = 3;
					j = 0;*/ // 블럭을 저장해야하는지 확인.
					return 1;
				//}
			}
			//if (count != 0 && block[bltype][rotate][i][j] == 1)
			//{
			//	wall[y + i][x + j] = 1;//블럭이 저장된 부분을 1로 저장.
			//}
		}
	}
	/*if (count != 0)
	{
		return 1;
	}*/
	return 0;
}

int move()
{
	int keyinput;
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
		case UP: //위키 누르면 방향전환
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (block[bltype][rotate][i][j] == 1)
				{
					gotoxy(X + j * 2, y + i);
					printf("  ");
				}
			}
		}
		rotate++; rotate = rotate % 4;
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (block[bltype][rotate][i][j] == 1)
				{
					if (x + j >= LEN - 1)
					{
						x--;
					}
					if (x + j <= 0)
					{
						x++;
					}
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (block[bltype][rotate][i][j] == 1)
				{
					gotoxy(X + j * 2, y + i);
					printf("□");
				}
			}
		}
		break;
		case LEFT: if (wall[y][x +Lend()- 1]) break; // 왼쪽키 누르면 한칸 왼쪽으로
			for (int j = 0; j < 4; j++)
			{
				for (int i = 0; i < 4; i++)
				{
					if (block[bltype][rotate][i][j] == 1)
					{
						gotoxy(X + j * 2, y + i);
						printf("  ");
						x--;
						gotoxy(X+j*2, y+i);
						printf("□");
						x++;
					}
				}
			}
			x--;
			break;
		case RIGHT: if (wall[y][x + Rend()+1]) break; // 오른쪽키 누르면 오른쪽으로 한칸
			for (int j = 3; j >= 0; j--)
			{
				for (int i = 0; i < 4; i++)
				{
					if (block[bltype][rotate][i][j] == 1)
					{
						gotoxy(X + j * 2, y + i);
						printf("  ");
						x++;
						gotoxy(X + j * 2, y + i);
						printf("□");
						x--;
					}
				}
			}
			x++;
			break;
		case DOWN: // 아래키 누르면 한칸 아래로
			for (int i = 3; i >= 0; i--)
			{
				for (int j = 0; j < 4; j++)
				{
					if (block[bltype][rotate][i][j] == 1)
					{
						gotoxy(X + j * 2, y + i);
						printf("  ");
						y++;
						gotoxy(X + j * 2, y + i);
						printf("□");
						y--;
					}
				}
			}
		y++; break;
		}
	}
	return 0;
}


int autodown() //  1초에 한칸씩 내려옴
{
	for (int i = 0; i < 75; i++)
	{
		Sleep(10);
		if (_kbhit())return 0;
	}
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[bltype][rotate][i][j] == 1)
			{
				if (wall[i + y + 1][j + x] == 1)return 0;
				gotoxy(X + j * 2, y + i);
				printf("  ");
				y++;
				gotoxy(X + j * 2, y + i);
				printf("□");
				y--;
			}
		}
	}
	y++;
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

int printblock(int bltype)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (block[bltype][rotate][i][j] == 1)
			{
				gotoxy(X + j * 2, y+i);
				printf("□");
			}
			else
			{
				gotoxy(X + j * 2, y+i);
				printf("  ");
			}
		}
		printf("\n");
	}
	return 0;
}
int Lend()// 블럭의 왼쪽 끝을 찾음.
{
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (block[bltype][rotate][i][j] == 1)
			{
				gotoxy(0, 26);
				printf("%d", j);
				return j;
			}
		}
	}
	return 0;
}
int Rend()// 블럭의 오른쪽 끝을 찾음.
{
	for (int j = 3; j >= 0; j--)
	{
		for (int i = 0; i<4 ; i++)
		{
			if (block[bltype][rotate][i][j] == 1)
			{
				gotoxy(5, 26);
				printf("%d", j);
				return j;
			}
		}
	}
	return 0;
}
 // 아래로는 아마 건드릴곳 없음
//
//
//
//
//
//
//
int random()
{
	int a;
	a = rand() % 7;
	return a;
}
void displayscore()
{
	gotoxy(LEN * 2 + 5, HIG - 3);
	printf("%07.0f", totalscore);
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
		removescore += removescore * scorebonus; // 줄 지웠을때 점수
	}
	return 0;
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

//하드드롭, 끼워넣기 만듭시다