#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<conio.h>
void setcolor(int fg, int bg);
void setcursor(bool visible);
void gotoxy(int x, int y);
void draw_ship(int x, int y);
void erase_ship(int x, int y);
void draw_fire(int x, int y);
int main()
{
	setcursor(0);
	char ch = ' ' ;
	int x = 40, y = 20, direcship=0,loop,
		fire[5],xfire[5],yfire[5],bullet=0;
	for (loop = 0; loop < 5; loop++)
	{
		fire[loop] = 0;
		xfire[loop] = x;
		yfire[loop] = y;

	}
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			
			if (ch == 'd')
			{
				direcship = 1 ;
			}
			if (ch == 'a')
			{
				direcship = 2 ;
			}
			if (ch == 's')
			{
				direcship = 0;
			}
			if (ch == ' '&&bullet<5)
			{
				fire[bullet] = 1;
				yfire[bullet] = y - 1;
				bullet++;
				
			}
			fflush(stdin);
		}
		if (direcship == 1 && x < 80)
		{
			erase_ship(x, y);
			draw_ship(++x, y);
			
		}
		if (direcship == 2 && x > 0)
		{
			erase_ship(x, y);
			draw_ship(--x, y);
			
		}
		for (loop = 0; loop < 5; loop++)
		{
			if (fire[loop] == 0)
			{
				xfire[loop] = x;
			}
			if (fire[loop] == 1 && yfire[loop] >= 0)
			{
				if (yfire[loop] < 1)
				{
					erase_ship(xfire[loop], yfire[loop]);
					fire[loop] = 0;
					if (loop == 5 - 1)
					{
						bullet = 0;
					}

				}
				else
				{
					erase_ship(xfire[loop], yfire[loop]);
					draw_fire(xfire[loop], --yfire[loop]);
				}

			}
		}
		Sleep(100);
	} while (ch != 'x');
	return 0;
}
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(
	GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	setcolor(4, 15);
	gotoxy(x, y);
	printf(" <^I^> ");
}

void erase_ship(int x, int y)
{
	setcolor(0, 0);
	gotoxy(x, y);
	printf("       ");
}

void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void draw_fire(int x, int y)
{
	setcolor(7, 12);
	gotoxy(x+3, y);
	printf("^");
}

