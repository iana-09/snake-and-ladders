#include <stdio.h>	  //  declares functions that deal with standard input and output
#include <graphics.h> // used to drawing various geometrical shapes
#include <conio.h>	  // built-in functions embedded in it they generally perform input/output on the console
#include <malloc.h>	  // memory allocation, dynamically allocate a single large block of memory with the specified size.
#include <stdlib.h>	  // standard library utilities
#include <dos.h>	  // handling interrupts, producing sound, date and time functions
#include <iostream>	  // standard input-output stream
#include <ctime>	  // returns the string representing the localtime based on the argument timer
#include <math.h>

// Global Variables
int k = 1, i, user = 0, dice = 0, x1 = 49, y1 = 402, x2 = 68, y2 = 402, dir1 = 0,
	dir2 = 0,
	ch;
int cnt1 = 1, cnt2 = 1;
void *obj1, *obj2, *o1, *o2, *dot, *back, *turn, *ready;
unsigned int size;
float octave[] = {130.81, 146.83, 164.81, 174.61, 196, 220, 246.94};
const int TOKEN_SIZE = 16;

const int ROLL_LEFT = 475, ROLL_TOP = 325, ROLL_RIGHT = 690, ROLL_BOTTOM = 365;
const int QUIT_LEFT = 475, QUIT_TOP = 375, QUIT_RIGHT = 690, QUIT_BOTTOM = 405;

void drawButton(int left, int top, int right, int bottom, int color, char *label)
{
	setcolor(color);
	setfillstyle(SOLID_FILL, color);
	bar(left, top, right, bottom);
	rectangle(left, top, right, bottom);
	setbkcolor(color);
	setcolor(BLACK);
	settextstyle(BOLD_FONT, HORIZ_DIR, 1);
	int textX = left + (right - left - textwidth(label)) / 2;
	int textY = top + (bottom - top - textheight(label)) / 2;
	outtextxy(textX, textY, label);
	setbkcolor(BLACK);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
}

int waitForAction()
{
	while (1)
	{
		if (kbhit())
		{
			int key = getch();
			if (key == 13)
				return 1;
			if (key == 27)
				return 0;
		}

		if (ismouseclick(WM_LBUTTONDOWN))
		{
			int mouseX, mouseY;
			getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
			if (mouseX >= ROLL_LEFT && mouseX <= ROLL_RIGHT &&
				mouseY >= ROLL_TOP && mouseY <= ROLL_BOTTOM)
				return 1;
			if (mouseX >= QUIT_LEFT && mouseX <= QUIT_RIGHT &&
				mouseY >= QUIT_TOP && mouseY <= QUIT_BOTTOM)
				return 0;
		}
		delay(20);
	}
}

void drawPawn(int left, int top, int pawnColor)
{
	// Clean, round tokens stay legible at every board position.
	setcolor(BLACK);
	setfillstyle(SOLID_FILL, BLACK);
	fillellipse(left + 8, top + 8, 9, 9);
	setcolor(WHITE);
	setfillstyle(SOLID_FILL, pawnColor);
	fillellipse(left + 8, top + 8, 7, 7);
	setfillstyle(SOLID_FILL, WHITE);
	fillellipse(left + 5, top + 5, 2, 2);
}

void setupLadder1()
{
	int m = 0, n = 0;
	setcolor(DARKGRAY);
	for (m = 0; m <= 250; m += 250)
		for (n = 0; n <= m; n += 250)
		{

			line(53 + m, 57 + n, 55 + m, 55 + n);
			line(53 + m, 57 + n, 133 + m, 137 + n);
			line(55 + m, 55 + n, 135 + m, 135 + n);
			line(133 + m, 137 + n, 135 + m, 135 + n);
			setfillstyle(SOLID_FILL, YELLOW);
			floodfill(55 + m, 58 + n, DARKGRAY);

			line(68 + m, 42 + n, 70 + m, 40 + n);
			line(68 + m, 42 + n, 148 + m, 122 + n);
			line(70 + m, 40 + n, 150 + m, 120 + n);
			line(148 + m, 122 + n, 150 + m, 120 + n);
			floodfill(70 + m, 43 + n, DARKGRAY);

			line(65 + m, 65 + n, 78 + m, 52 + n);
			line(68 + m, 68 + n, 81 + m, 55 + n);
			floodfill(79 + m, 54 + n, DARKGRAY);

			line(75 + m, 75 + n, 88 + m, 62 + n);
			line(78 + m, 78 + n, 91 + m, 65 + n);
			floodfill(89 + m, 64 + n, DARKGRAY);

			line(85 + m, 85 + n, 98 + m, 72 + n);
			line(88 + m, 88 + n, 101 + m, 75 + n);
			floodfill(99 + m, 74 + n, DARKGRAY);

			line(95 + m, 95 + n, 108 + m, 82 + n);
			line(98 + m, 98 + n, 111 + m, 85 + n);
			floodfill(109 + m, 84 + n, DARKGRAY);

			line(105 + m, 105 + n, 118 + m, 92 + n);
			line(108 + m, 108 + n, 121 + m, 95 + n);
			floodfill(119 + m, 94 + n, DARKGRAY);

			line(115 + m, 115 + n, 128 + m, 102 + n);
			line(118 + m, 118 + n, 131 + m, 105 + n);
			floodfill(129 + m, 104 + n, DARKGRAY);

			line(125 + m, 125 + n, 138 + m, 112 + n);
			line(128 + m, 128 + n, 141 + m, 115 + n);
			floodfill(139 + m, 114 + n, DARKGRAY);
		}
}

void setupLadder2()
{
	int p, q = 0;
	for (p = 0; p <= 180; p += 155)
	{
		line(100 + p, 330 - q, 140 + p, 290 - q);
		line(100 + p, 330 - q, 102 + p, 332 - q);
		line(102 + p, 332 - q, 142 + p, 292 - q);
		line(142 + p, 292 - q, 140 + p, 290 - q);
		floodfill(141 + p, 292 - q, 8);
		line(115 + p, 345 - q, 155 + p, 305 - q);
		line(115 + p, 345 - q, 117 + p, 347 - q);
		line(117 + p, 347 - q, 157 + p, 307 - q);
		line(157 + p, 307 - q, 155 + p, 305 - q);
		floodfill(155 + p, 307 - q, 8);
		line(112 + p, 322 - q, 125 + p, 335 - q);
		line(114 + p, 320 - q, 127 + p, 333 - q);
		floodfill(125 + p, 334 - q, 8);
		line(122 + p, 312 - q, 135 + p, 325 - q);
		line(124 + p, 310 - q, 137 + p, 323 - q);
		floodfill(135 + p, 324 - q, 8);
		line(132 + p, 302 - q, 145 + p, 315 - q);
		line(134 + p, 300 - q, 147 + p, 313 - q);
		floodfill(145 + p, 314 - q, 8);
		q += 95;
	}
}

void drawSnake(int headX, int headY, int tailX, int tailY, int bodyColor, int waveDirection)
{
	const int parts = 30;
	int snakeX[parts + 1], snakeY[parts + 1];
	double deltaX = tailX - headX;
	double deltaY = tailY - headY;
	double length = sqrt(deltaX * deltaX + deltaY * deltaY);
	double normalX = -deltaY / length;
	double normalY = deltaX / length;

	for (int n = 0; n <= parts; n++)
	{
		double progress = (double)n / parts;
		double wave = sin(progress * 5.0 * 3.14159265) * 15.0 * waveDirection;
		snakeX[n] = (int)(headX + deltaX * progress + normalX * wave);
		snakeY[n] = (int)(headY + deltaY * progress + normalY * wave);
	}

	// Overlapping circles produce a soft, smooth cartoon body without sharp joints.
	setcolor(BLACK);
	setfillstyle(SOLID_FILL, BLACK);
	for (int n = 0; n < parts - 2; n++)
		fillellipse(snakeX[n], snakeY[n], 8, 8);
	setcolor(bodyColor);
	setfillstyle(SOLID_FILL, bodyColor);
	for (int n = 0; n < parts - 2; n++)
		fillellipse(snakeX[n], snakeY[n], 6, 6);

	// Taper the tail using progressively smaller rounded sections.
	setcolor(BLACK);
	setfillstyle(SOLID_FILL, BLACK);
	fillellipse(snakeX[parts - 2], snakeY[parts - 2], 6, 6);
	fillellipse(snakeX[parts - 1], snakeY[parts - 1], 4, 4);
	setfillstyle(SOLID_FILL, bodyColor);
	fillellipse(snakeX[parts - 2], snakeY[parts - 2], 4, 4);
	fillellipse(snakeX[parts - 1], snakeY[parts - 1], 2, 2);

	// Contrasting body spots make the shape read as scales.
	setcolor(YELLOW);
	setfillstyle(SOLID_FILL, YELLOW);
	for (int n = 5; n < parts - 4; n += 6)
		fillellipse(snakeX[n], snakeY[n], 3, 3);

	// Small friendly head, wide-set eyes, and a smile.
	setcolor(BLACK);
	setfillstyle(SOLID_FILL, bodyColor);
	fillellipse(headX, headY, 11, 10);
	setfillstyle(SOLID_FILL, WHITE);
	fillellipse(headX - 4, headY - 3, 3, 3);
	fillellipse(headX + 4, headY - 3, 3, 3);
	setfillstyle(SOLID_FILL, BLACK);
	fillellipse(headX - 4, headY - 3, 1, 1);
	fillellipse(headX + 4, headY - 3, 1, 1);
	setcolor(BLACK);
	arc(headX, headY + 1, 205, 335, 5);
	setlinestyle(SOLID_LINE, 0, 1);
}

void snake1()
{
	drawSnake(105, 48, 265, 160, LIGHTRED, 1);       // 99 down to 66
	drawSnake(420, 82, 345, 240, LIGHTMAGENTA, -1); // 90 down to 48
}

void snake2()
{
	drawSnake(105, 145, 105, 400, LIGHTGREEN, 1); // 62 down to 2
	drawSnake(225, 280, 385, 400, LIGHTCYAN, -1); // 36 down to 9
}

void snake3()
{
	arc(255, 118, 320, 0, 170);
	arc(265, 118, 305, 0, 170);
	line(384, 229, 361, 260);
	line(425, 120, 429, 105);
	line(428, 105, 435, 120);
	line(428, 105, 429, 100);
	circle(430, 115, 1);
	setfillstyle(1, 2);
	floodfill(430, 117, 8);
}

void numbering()
{
	char number[4];
	for (int row = 0; row < 10; row++)
	{
		for (int col = 0; col < 10; col++)
		{
			int left = 45 + col * 40;
			int top = 20 + row * 40;
			int boardRow = 9 - row;
			int cellNumber = boardRow * 10 + ((boardRow % 2 == 0) ? col + 1 : 10 - col);
			int cellColor = ((row + col) % 2 == 0) ? BLUE : CYAN;
			setfillstyle(SOLID_FILL, cellColor);
			bar(left, top, left + 40, top + 40);
			setcolor(DARKGRAY);
			rectangle(left, top, left + 40, top + 40);
			sprintf(number, "%d", cellNumber);
			setbkcolor(cellColor);
			setcolor(WHITE);
			outtextxy(left + 4, top + 4, number);
		}
	}
	setbkcolor(BLACK);
	setcolor(LIGHTCYAN);
	outtextxy(520, 30, (char *)"CLASSIC GAME");
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setcolor(YELLOW);
	outtextxy(515, 52, (char *)"SNAKES &");
	outtextxy(525, 72, (char *)"LADDERS");
	setcolor(WHITE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
}

void status()
{
	setcolor(LIGHTGRAY);
	outtextxy(540, 94, (char *)"LAST ROLL");
	setlinestyle(SOLID_LINE, 1, 2);
	rectangle(480, 110, 680, 230);
	outtextxy(515, 255, (char *)"CURRENT TURN");
	rectangle(480, 275, 680, 300);
	drawButton(ROLL_LEFT, ROLL_TOP, ROLL_RIGHT, ROLL_BOTTOM, LIGHTGREEN, (char *)"ROLL DICE");
	drawButton(QUIT_LEFT, QUIT_TOP, QUIT_RIGHT, QUIT_BOTTOM, LIGHTRED, (char *)"QUIT");
	setcolor(DARKGRAY);
	outtextxy(510, 420, (char *)"ENTER = ROLL");
	outtextxy(518, 438, (char *)"ESC = QUIT");
}

void welcome()
{

	int freq;
	srand((unsigned)time(0));
	for (int i = 0; i < 50; i++)
	{
		freq = (rand() % 6 + 1); // %6 produces numbers between 0 to 5 and plus 1 will give u numbers between 1 to 6
		Beep(octave[freq], 150);
	}
}

void displayDice()
{
	switch (dice)
	{
	case 1:
		putimage(535, 165, dot, COPY_PUT);
		break;
	case 2:
		putimage(515, 145, dot, COPY_PUT);
		putimage(555, 185, dot, COPY_PUT);
		break;
	case 3:
		putimage(515, 145, dot, COPY_PUT);
		putimage(535, 165, dot, COPY_PUT);
		putimage(555, 185, dot, COPY_PUT);
		break;
	case 4:
		putimage(515, 145, dot, COPY_PUT);
		putimage(555, 145, dot, COPY_PUT);
		putimage(515, 185, dot, COPY_PUT);
		putimage(555, 185, dot, COPY_PUT);
		break;
	case 5:
		putimage(515, 145, dot, COPY_PUT);
		putimage(555, 145, dot, COPY_PUT);
		putimage(535, 165, dot, COPY_PUT);
		putimage(515, 185, dot, COPY_PUT);
		putimage(555, 185, dot, COPY_PUT);
		break;
	case 6:
		putimage(515, 145, dot, COPY_PUT);
		putimage(515, 165, dot, COPY_PUT);
		putimage(515, 185, dot, COPY_PUT);
		putimage(555, 145, dot, COPY_PUT);
		putimage(555, 165, dot, COPY_PUT);
		putimage(555, 185, dot, COPY_PUT);
		break;
	}
}

void getdice()
{
	srand((unsigned)time(0)); // srand -  gives the random function:  time(0) gives the time in seconds
	dice = (rand() % 6 + 1);  // assigned dice
	displayDice();
}

void play()
{
	getimage(x1, y1, x1 + TOKEN_SIZE, y1 + TOKEN_SIZE, o1);
	getimage(x2, y2, x2 + TOKEN_SIZE, y2 + TOKEN_SIZE, o2);
	drawPawn(x1, y1, GREEN);
	drawPawn(x2, y2, LIGHTMAGENTA);

	while (1)
	{
		if (user == 0)
		{
			putimage(487, 282, turn, COPY_PUT);
			setcolor(GREEN);
			outtextxy(490, 285, (char *)"Player 1");

			if (waitForAction())
				getdice();
			else
				exit(0);
			setcolor(YELLOW);

			if (cnt1 == 96 && dice >= 4)
			{
				delay(1000);
				goto invalid1;
				user = 1;
			}
			else if (cnt1 == 97 && dice >= 3)
			{
				delay(1000);
				goto invalid1;
				user = 1;
			}
			else if (cnt1 == 98 && dice >= 2)
			{
				delay(1000);
				goto invalid1;
				user = 1;
			}
			else if (cnt1 == 99 && dice >= 1)
			{
				delay(1000);
				goto invalid1;
				user = 1;
			}
			for (i = 1; i <= dice; i++, cnt1++)
			{
				putimage(x1, y1, o1, COPY_PUT);
				Beep(octave[1], 150);
				if (dir1 == 0)
				{
					getimage(x1, y1, x1 + TOKEN_SIZE, y1 + TOKEN_SIZE, o1);
					x1 += 40;
					if (x1 > 410)
						x1 -= 40, y1 -= 40, dir1 = 1;
					getimage(x1, y1, x1 + TOKEN_SIZE, y1 + TOKEN_SIZE, o1);
					drawPawn(x1, y1, GREEN);
					delay(1000);
					goto ch1;
				}
				else
				{
					size = imagesize(x1, y1, x1 + TOKEN_SIZE, y1 + TOKEN_SIZE);
					getimage(x1, y1, x1 + TOKEN_SIZE, y1 + TOKEN_SIZE, o1);
					x1 -= 40;
					if (x1 < 50)
						x1 += 40, y1 -= 40, dir1 = 0;
					getimage(x1, y1, x1 + TOKEN_SIZE, y1 + TOKEN_SIZE, o1);
					drawPawn(x1, y1, GREEN);
					delay(1000);
					goto ch1;
				}
			ch1:
				if (cnt1 == 99)
					goto over;
			}
			if (cnt1 == 12 || cnt1 == 72 || cnt1 == 78)
			{
				putimage(x1, y1, o1, COPY_PUT);
				x1 -= 80;
				y1 -= 80;
				getimage(x1, y1, x1 + TOKEN_SIZE, y1 + TOKEN_SIZE, o1);
				drawPawn(x1, y1, GREEN);
				if (cnt1 == 12)
					cnt1 = 34;
				else if (cnt1 == 72)
					cnt1 = 94;
				else if (cnt1 == 78)
				{
					cnt1 = 100;
					goto over;
				}
			}
			else if (cnt1 == 22 || cnt1 == 46)
			{
				putimage(x1, y1, o1, COPY_PUT);
				x1 += 40;
				y1 -= 40;
				getimage(x1, y1, x1 + TOKEN_SIZE, y1 + TOKEN_SIZE, o1);
				drawPawn(x1, y1, GREEN);
				if (cnt1 == 22)
					cnt1 = 38;
				else if (cnt1 == 46)
					cnt1 = 54;
				dir1 = 1;
			}
			else if (cnt1 == 36 || cnt1 == 99)
			{
				putimage(x1, y1, o1, COPY_PUT);
				x1 += 160;
				y1 += 120;
				getimage(x1, y1, x1 + TOKEN_SIZE, y1 + TOKEN_SIZE, o1);
				drawPawn(x1, y1, GREEN);
				if (cnt1 == 36)
					cnt1 = 9;
				else if (cnt1 == 99)
					cnt1 = 66;
				dir1 = 0;
			}
			else if (cnt1 == 62)
			{
				putimage(x1, y1, o1, COPY_PUT);
				y1 += 240;
				getimage(x1, y1, x1 + TOKEN_SIZE, y1 + TOKEN_SIZE, o1);
				drawPawn(x1, y1, GREEN);
				cnt1 = 2;
			}
			else if (cnt1 == 90)
			{
				putimage(x1, y1, o1, COPY_PUT);
				x1 -= 80;
				y1 += 160;
				getimage(x1, y1, x1 + TOKEN_SIZE, y1 + TOKEN_SIZE, o1);
				drawPawn(x1, y1, GREEN);
				cnt1 = 48;
			}

			// if (dice==5 || dice==6) user=0; else user=1;
			if (dice == 6)
				user = 0;
			else
				user = 1;

		invalid1:
			putimage(500, 130, back, COPY_PUT);
		}
		else
		{
			putimage(487, 282, turn, COPY_PUT);
			setcolor(LIGHTMAGENTA);
			outtextxy(490, 285, (char *)"Player 2");
			setcolor(YELLOW);
			if (waitForAction())
				getdice();
			else
				exit(0);
			if (cnt2 == 96 && dice != 4)
			{
				delay(1000);
				goto invalid2;
				user = 0;
			}
			else if (cnt2 == 97 && dice != 3)
			{
				delay(1000);
				goto invalid2;
				user = 0;
			}
			else if (cnt2 == 98 && dice != 2)
			{
				delay(1000);
				goto invalid2;
				user = 0;
			}
			else if (cnt2 == 99 && dice != 1)
			{
				delay(1000);
				goto invalid2;
				user = 0;
			}
			for (i = 1; i <= dice; i++, cnt2++)
			{
				putimage(x2, y2, o2, COPY_PUT);
				Beep(octave[4], 150);
				if (dir2 == 0)
				{
					getimage(x2, y2, x2 + TOKEN_SIZE, y2 + TOKEN_SIZE, o2);
					x2 += 40;
					if (x2 > 440)
						x2 -= 40, y2 -= 40, dir2 = 1;
					getimage(x2, y2, x2 + TOKEN_SIZE, y2 + TOKEN_SIZE, o2);
					drawPawn(x2, y2, LIGHTMAGENTA);
					delay(1000);
					goto ch2;
				}
				else
				{
					getimage(x2, y2, x2 + TOKEN_SIZE, y2 + TOKEN_SIZE, o2);
					x2 -= 40;
					if (x2 < 50)
						x2 += 40, y2 -= 40, dir2 = 0;
					getimage(x2, y2, x2 + TOKEN_SIZE, y2 + TOKEN_SIZE, o2);
					drawPawn(x2, y2, LIGHTMAGENTA);
					delay(1000);
					goto ch2;
				}
			ch2:
				if (cnt2 == 99)
					goto over;
			}
			if (cnt2 == 12 || cnt2 == 72 || cnt2 == 78)
			{
				putimage(x2, y2, o2, COPY_PUT);
				x2 -= 80;
				y2 -= 80;
				getimage(x2, y2, x2 + TOKEN_SIZE, y2 + TOKEN_SIZE, o2);
				drawPawn(x2, y2, LIGHTMAGENTA);
				if (cnt2 == 12)
					cnt2 = 34;
				else if (cnt2 == 72)
					cnt2 = 94;
				else if (cnt2 == 78)
				{
					cnt2 = 100;
					goto over;
				}
			}
			else if (cnt2 == 22 || cnt2 == 46)
			{
				putimage(x2, y2, o2, COPY_PUT);
				x2 += 40;
				y2 -= 40;
				getimage(x2, y2, x2 + TOKEN_SIZE, y2 + TOKEN_SIZE, o2);
				drawPawn(x2, y2, LIGHTMAGENTA);
				if (cnt2 == 22)
					cnt2 = 38;
				else if (cnt2 == 46)
					cnt2 = 54;
				dir2 = 1;
			}
			else if (cnt2 == 36 || cnt2 == 99)
			{
				putimage(x2, y2, o2, COPY_PUT);
				x2 += 160;
				y2 += 120;
				getimage(x2, y2, x2 + TOKEN_SIZE, y2 + TOKEN_SIZE, o2);
				drawPawn(x2, y2, LIGHTMAGENTA);
				if (cnt2 == 36)
					cnt2 = 9;
				else if (cnt2 == 99)
					cnt2 = 66;
				dir2 = 0;
			}
			else if (cnt2 == 62)
			{
				putimage(x2, y2, o2, COPY_PUT);
				y2 += 240;
				getimage(x2, y2, x2 + TOKEN_SIZE, y2 + TOKEN_SIZE, o2);
				drawPawn(x2, y2, LIGHTMAGENTA);
				cnt2 = 2;
			}
			else if (cnt2 == 90)
			{
				putimage(x2, y2, o2, COPY_PUT);
				x2 -= 80;
				y2 += 160;
				getimage(x2, y2, x2 + TOKEN_SIZE, y2 + TOKEN_SIZE, o2);
				drawPawn(x2, y2, LIGHTMAGENTA);
				cnt2 = 48;
			}
			if (dice == 5 || dice == 6)
				user = 1;
			else
				user = 0;
		invalid2:
			putimage(500, 130, back, COPY_PUT);
			delay(1000);
		}
	}
over:;
}

const int PLAYER_COUNT = 5;
int playerSquares[PLAYER_COUNT] = {1, 1, 1, 1, 1};
int playerColors[PLAYER_COUNT] = {GREEN, LIGHTMAGENTA, YELLOW, LIGHTCYAN, LIGHTRED};
int gameWinner = -1;
int activePlayerCount = 2;

void drawPlayerSelection(int selectedPlayers)
{
	cleardevice();
	setbkcolor(BLACK);
	settextstyle(BOLD_FONT, HORIZ_DIR, 3);
	setcolor(YELLOW);
	outtextxy(190, 65, (char *)"SNAKES & LADDERS");
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setcolor(LIGHTCYAN);
	outtextxy(225, 125, (char *)"HOW MANY PLAYERS?");

	for (int option = 0; option < 4; option++)
	{
		int left = 125 + option * 125;
		int color = playerColors[option + 1];
		char label[12];
		sprintf(label, "%d PLAYERS", option + 2);
		drawButton(left, 180, left + 105, 230, color, label);
		if (selectedPlayers == option + 2)
		{
			setcolor(WHITE);
			setlinestyle(SOLID_LINE, 0, 3);
			rectangle(left - 4, 176, left + 109, 234);
			setlinestyle(SOLID_LINE, 0, 1);
		}
	}

	char selectedText[24];
	settextstyle(BOLD_FONT, HORIZ_DIR, 1);
	setcolor(WHITE);
	sprintf(selectedText, "SELECTED: %d PLAYERS", selectedPlayers);
	outtextxy(278, 250, selectedText);
	drawButton(250, 275, 470, 325, LIGHTGREEN, (char *)"START GAME");

	for (int player = 0; player < PLAYER_COUNT; player++)
		drawPawn(265 + player * 38, 350, playerColors[player]);

	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	setcolor(LIGHTGRAY);
	outtextxy(218, 395, (char *)"CHOOSE PLAYERS, THEN PRESS START");
	outtextxy(235, 420, (char *)"KEYS 2-5  ENTER=START  ESC=QUIT");
}

int selectPlayerCount()
{
	int selectedPlayers = 2;
	drawPlayerSelection(selectedPlayers);
	while (1)
	{
		if (kbhit())
		{
			int key = getch();
			if (key >= '2' && key <= '5')
			{
				selectedPlayers = key - '0';
				drawPlayerSelection(selectedPlayers);
			}
			if (key == 13)
				return selectedPlayers;
			if (key == 27)
				exit(0);
		}

		if (ismouseclick(WM_LBUTTONDOWN))
		{
			int mouseX, mouseY;
			getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
			if (mouseY >= 180 && mouseY <= 230)
			{
				for (int option = 0; option < 4; option++)
				{
					int left = 125 + option * 125;
					if (mouseX >= left && mouseX <= left + 105)
					{
						selectedPlayers = option + 2;
						drawPlayerSelection(selectedPlayers);
					}
				}
			}
			if (mouseX >= 250 && mouseX <= 470 &&
				mouseY >= 275 && mouseY <= 325)
				return selectedPlayers;
		}
		delay(20);
	}
}

void getTokenPosition(int square, int playerIndex, int &tokenX, int &tokenY)
{
	int row = (square - 1) / 10;
	int indexInRow = (square - 1) % 10;
	int column = (row % 2 == 0) ? indexInRow : 9 - indexInRow;
	int offsetX[PLAYER_COUNT] = {1, 12, 23, 6, 20};
	int offsetY[PLAYER_COUNT] = {22, 22, 22, 5, 5};

	tokenX = 45 + column * 40 + offsetX[playerIndex];
	tokenY = 20 + (9 - row) * 40 + offsetY[playerIndex];
}

void drawFivePlayers()
{
	for (int player = 0; player < activePlayerCount; player++)
	{
		int tokenX, tokenY;
		getTokenPosition(playerSquares[player], player, tokenX, tokenY);
		drawPawn(tokenX, tokenY, playerColors[player]);
	}
}

void drawCurrentPlayer(int player)
{
	char turnText[24];
	setfillstyle(SOLID_FILL, BLACK);
	bar(482, 277, 678, 298);
	setcolor(playerColors[player]);
	setbkcolor(BLACK);
	settextstyle(BOLD_FONT, HORIZ_DIR, 1);
	sprintf(turnText, "PLAYER %d OF %d", player + 1, activePlayerCount);
	outtextxy(520, 283, turnText);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
}

void drawGameScreen(int currentPlayer)
{
	cleardevice();
	numbering();
	setupLadder1();
	setupLadder2();
	snake1();
	snake2();
	status();

	setcolor(WHITE);
	setfillstyle(SOLID_FILL, WHITE);
	bar(500, 130, 580, 210);
	rectangle(500, 130, 580, 210);
	if (dice > 0)
		displayDice();

	drawFivePlayers();
	drawCurrentPlayer(currentPlayer);
}

int transportedSquare(int square)
{
	if (square == 12) return 34;
	if (square == 22) return 38;
	if (square == 46) return 54;
	if (square == 72) return 94;
	if (square == 78) return 100;
	if (square == 36) return 9;
	if (square == 62) return 2;
	if (square == 90) return 48;
	if (square == 99) return 66;
	return square;
}

void playFivePlayerGame()
{
	int currentPlayer = 0;
	dice = 0;
	drawGameScreen(currentPlayer);

	while (gameWinner < 0)
	{
		if (!waitForAction())
			exit(0);

		getdice();
		int destination = playerSquares[currentPlayer] + dice;
		if (destination <= 100)
		{
			// Update once per roll so the board never flashes during movement.
			if (destination <= 100)
				playerSquares[currentPlayer] = destination;
			drawGameScreen(currentPlayer);
			Beep(octave[currentPlayer % 7], 120);

			int transported = transportedSquare(playerSquares[currentPlayer]);
			if (transported != playerSquares[currentPlayer])
			{
				delay(350);
				playerSquares[currentPlayer] = transported;
				drawGameScreen(currentPlayer);
			}
		}

		if (playerSquares[currentPlayer] == 100)
		{
			gameWinner = currentPlayer;
			break;
		}

		if (dice != 6)
			currentPlayer = (currentPlayer + 1) % activePlayerCount;
		drawGameScreen(currentPlayer);
	}
}

int main(int argc, char *argv[])
{
	initwindow(720, 480, (char *)"Snakes & Ladders");

	size = imagesize(487, 282, 593, 293);
	turn = malloc(size);
	getimage(487, 282, 593, 293, turn);

	// Player 1 pawn: round head, flared body, white outline.
	int pawnBody[] = {104, 108, 112, 108, 115, 115, 101, 115};
	setcolor(WHITE);
	setfillstyle(SOLID_FILL, GREEN);
	fillellipse(108, 104, 4, 4);
	fillpoly(4, pawnBody);
	rectangle(101, 115, 115, 116);
	setfillstyle(SOLID_FILL, WHITE);
	fillellipse(108, 104, 1, 1);
	size = imagesize(100, 100, 100 + TOKEN_SIZE, 100 + TOKEN_SIZE);
	obj1 = malloc(size);
	getimage(100, 100, 100 + TOKEN_SIZE, 100 + TOKEN_SIZE, obj1);
	cleardevice();

	// Player 2 pawn uses the same readable silhouette in a different color.
	setcolor(WHITE);
	setfillstyle(SOLID_FILL, LIGHTMAGENTA);
	fillellipse(108, 104, 4, 4);
	fillpoly(4, pawnBody);
	rectangle(101, 115, 115, 116);
	setfillstyle(SOLID_FILL, WHITE);
	fillellipse(108, 104, 1, 1);
	size = imagesize(100, 100, 100 + TOKEN_SIZE, 100 + TOKEN_SIZE);
	obj2 = malloc(size);
	getimage(100, 100, 100 + TOKEN_SIZE, 100 + TOKEN_SIZE, obj2);
	cleardevice();

	o1 = malloc(size);
	o2 = malloc(size);

	// create dice placeholder and put into memory via back and dot pointer
	setcolor(WHITE);
	setfillstyle(SOLID_FILL, WHITE);
	rectangle(500, 130, 580, 210);
	floodfill(510, 140, 15);

	size = imagesize(500, 130, 580, 210);
	back = malloc(size);
	getimage(500, 130, 580, 210, back);
	setcolor(0);
	setfillstyle(1, BLACK);
	rectangle(535, 165, 545, 175);
	floodfill(540, 170, 0);
	size = imagesize(535, 165, 545, 175);
	dot = malloc(size);
	getimage(535, 165, 545, 175, dot);
	cleardevice();

	activePlayerCount = selectPlayerCount();
	welcome();
	playFivePlayerGame();
	setfillstyle(SOLID_FILL, BLACK);
	bar(465, 315, 620, 435);
	settextstyle(BOLD_FONT, HORIZ_DIR, 1);
	setcolor(YELLOW);
	char winnerText[24];
	sprintf(winnerText, "PLAYER %d WINS!", gameWinner + 1);
	setcolor(playerColors[gameWinner]);
	outtextxy(485, 345, winnerText);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	setcolor(LIGHTGRAY);
	outtextxy(475, 385, (char *)"Press any key to close");
	getch();
}
