#include<iostream>
#include<conio.h>
#include<graphics.h>
#include<time.h>
using namespace std;
int r, j, c = 77,score;
int map[60][80] = {0};
struct snake {
	int x;
	int y;
};
snake a[1000];
void creatmap() {
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 60; i++) {
		for (int m = 0; m < 80; m++) {
			switch (map[i][m]) {
			case 0:
				setfillcolor(RGB(221, 119, 216));
				solidrectangle(10 * m, 10 * i, 10 + 10 * m, 10 + 10 * i);
				break;
			case 2:
				setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
				solidrectangle(10 * m, 10 * i, 10 + 10 * m, 10 + 10 * i);
				break;
			case 3:
				setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
				solidcircle(5 + 10 * m, 5 + 10 * i, 5);
				break;
			}
		}
		cout << endl;
	}
}
void food() {
	srand((unsigned int)time(NULL));
	while (1) {
		r = rand() % 60;
		j = rand() % 80;
		if (map[r][j] != 2) {
			map[r][j] = 3;
			break;
		}
	}
}
void creatsnake(int n) {
	for (int i = 0; i < n; i++)
	{
		a[i].x = 10 - i;
		a[i].y = 10;
		map[a[i].y][a[i].x] = 2;
	}
}
int endplay(int n) {
	int t = 0;
	if (a[0].x == 80 || a[0].x == -1 || a[0].y == 60 || a[0].y == -1)
		return 1;
	for (int i = 1; i < n; i++)
		if (a[0].x == a[i].x && a[0].y == a[i].y)
			t = 1;
	if (t)
		return 1;

	return 0;
}
void move(int n, int c) {
	for (int i = n - 1; i > 0; i--)
	{
		map[a[i].y][a[i].x] -= 2;
		a[i].x = a[i - 1].x;
		a[i].y = a[i - 1].y;
	}
	switch (c) {
	case 72:
		a[0].y--;
		break;
	case 80:
		a[0].y++;
		break;
	case 75:
		a[0].x--;
		break;
	case 77:
		a[0].x++;
		break;
	}
	for (int i = 0; i < n; i++)
	{
		map[a[i].y][a[i].x] = 2;
	}
}

void pushkey(int& t) {
	int m, b;
	if (_kbhit()) {
		b = _getch();
		if (b == 224) {
			m =_getch();
			if (c == 72 && m != 80 || c == 80 && m != 72 || c == 75 && m != 77 || c == 77 && m != 75)
				c = m;
		}
		if (b == 112)
			if (t <= 0)
				t = 0;
			else
				t -= 100;
	}
}
int main() {
	initgraph(800, 600);
	setbkcolor(RGB(221,119,216));
	cleardevice();
	int t = 300;
	int n = 4;
	food();
	creatsnake(n);
	creatmap();
	while (1) {
		char s[20] = "";
		sprintf_s(s, "得分：%d", score);
		settextcolor(YELLOW);
		outtextxy(600, 100, s);
		pushkey(t);
		move(n, c);
		creatmap();
		if (a[0].x == j && a[0].y == r)
		{
			score += 10;
			n++;
			food();
		}
		if (endplay(n))
			break;
		Sleep(100);
	}
	
	settextstyle(80, 60, "斜体");
	settextcolor(GREEN);
	outtextxy(100, 300, "Game Over！");
	_getch();
	return 0;
}