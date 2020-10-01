#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<conio.h>

void gotoxy(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void setcursor(bool visible) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void setcolor(int fg, int bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void draw_ship(int x, int y) {
	gotoxy(x, y);
	setcolor(2, 4);
	printf(" <-0-> ");
}
void draw_bullet(int x, int y) {
	gotoxy(x, y);
	printf("H");
}
void erase_bullet(int x, int y) {
	gotoxy(x, y);
	setcolor(7, 0);
	printf(" ");
}
void erase_ship(int x, int y) {
	gotoxy(x, y);
	setcolor(2, 0);
	printf("       ");
}

int main() {
	char ch = '.', bt = '.';
	int x = 38, y = 20, index = -1, kx[6], ky[6], keep = 0, i;
	setcursor(0);
	draw_ship(x, y);
	int dir = 0; //go
	int bullet[6] = { 0 }; // 0 = off , 1 = on
	do {
		if (_kbhit()) {
			bt = _getch();
			if (bt == ' ' && keep < 5) {
				index++;
				bullet[index % 5] = 1;
				kx[index % 5] = x + 3;
				ky[index % 5] = y - 1;
				keep++;
			}
			else { ch = bt; }
		}
		if (ch == 'a') { dir = 1; }
		if (ch == 'd') { dir = 2; }
		if (ch == 's') { dir = 0; }

		for (i = 0; i <= 4; i++) {
			if (bullet[i] == 1 && ky[i] > 0) {
				erase_bullet(kx[i], ky[i]);
				draw_bullet(kx[i], --ky[i]);
				if (ky[i] == 0) {
					Sleep(100);
					erase_bullet(kx[i], ky[i]);
					keep--;
					ky[i] = 0;
				}
			}
		}

		if (x > 0 && x < 75) {
			if (dir == 0);
			else if (dir == 1) {
				erase_ship(x, y);
				draw_ship(--x, y);
				Sleep(20);
			}
			else {
				erase_ship(x, y);
				draw_ship(++x, y);
				Sleep(20);
			}
		}
		if (ch == 'a' && x == 75) {
			erase_ship(x, y);
			draw_ship(--x, y);
			Sleep(20);
		}
		if (ch == 'd' && x == 0) {
			erase_ship(x, y);
			draw_ship(++x, y);
			Sleep(20);
		}
		fflush(stdin);
		Sleep(50);
	} while (ch != 'x');
	return 0;
}