#undef UNICODE
#undef _UNICODE

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <graphics.h>
#pragma comment(lib,"Winmm.lib")

void startup();
void start_time();
void now_time();
void printbeforegame();
void bird();
void print();
void printstone();
void judge();
void gameover();
void printscore(int scoreee,int score_y);
int Readini();
void Writeini();
void mprintscore();

IMAGE bkg, bird1[4], bird2[4], stone1[2], stone2[2], over[2], n1[10],n2[10];
int bird_x, bird_y;
int t;
float ti;
int i, k;
clock_t startTime, endTime;
LOGFONT f;
int stone_x[2];
int ll[2];
int score;
int fall;
TCHAR h_score[20];
int stone_blank;
int isFirst = 1;
MOUSEMSG m;

int main()
{
	startup();
	print();
	getch();
	start_time();
	while (1)
	{
		bird();
		print();
		judge();
	}
}

void bird()
{
	if (ti > 0.05)
		fall = 1;
	char space;
	if (kbhit())
	{
		space = getch();
		if (space == ' ')
		{
			bird_y -= 45;
			fall = 0;
			start_time();
		}
		else if (space == 'u')
		{
			mciSendString("stop music", NULL, 0, NULL);
			mciSendString("close music", NULL, 0, NULL);
		}
		else if (space == 27)
			getch();
	}
	else
	{
		now_time();
		Sleep(40);
		ti = (endTime - startTime) / CLOCKS_PER_SEC;
		bird_y += int( 8 + 20 * pow(ti, 2) + 0.5);
	}
	while (MouseHit())
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			bird_y -= 45;
			fall = 0;
			start_time();
			break;
		case WM_RBUTTONDOWN:
			getch();
			break;
		}
	}
	if (bird_y <= 0)
		bird_y = 0;
}

void print()
{
	putimage(0, 0, &bkg);
	printstone();
	if (fall == 0)
	{
		putimage(bird_x, bird_y, &bird1[i % 3], NOTSRCERASE);
		putimage(bird_x, bird_y, &bird2[i % 3], SRCINVERT);
	}
	else
	{
		putimage(bird_x, bird_y, &bird1[3], NOTSRCERASE);
		putimage(bird_x, bird_y, &bird2[3], SRCINVERT);
	}
	mprintscore();
	if (k % 5 == 0)
		i++;
	k++;
	FlushBatchDraw();
}

void startup()
{
	initgraph(350, 600);
	mciSendString("open \"..\\sounds\\Alin.mp3\" alias music", NULL, 0, NULL);
	mciSendString("play music repeat", NULL, 0, NULL);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "flappy bird");
	if (isFirst == 1)
	{
		printbeforegame();
		getch();
	}
	srand(time(0));
	bird_x = 40;
	bird_y = 150;
	startTime = 0;
	endTime = 0;
	i = 0,k = 0;
	ti = 0;
	fall = 0;
	score = 0;
	stone_blank = 110;
	stone_x[0] = 350;
	stone_x[1] = 350+300;
	ll[0] = 100 + rand() % (401 - stone_blank);
	ll[1] = 100 + rand() % (401 - stone_blank);
	BeginBatchDraw();
	loadimage(&bkg, "..\\resources\\backgroundfd.jpg");
	loadimage(&bird1[0], "..\\resources\\bird1-1.gif");
	loadimage(&bird2[0], "..\\resources\\bird1-2.gif");
	loadimage(&bird1[1], "..\\resources\\bird2-1.gif");
	loadimage(&bird2[1], "..\\resources\\bird2-2.gif");
	loadimage(&bird1[2], "..\\resources\\bird3-1.gif");
	loadimage(&bird2[2], "..\\resources\\bird3-2.gif");
	loadimage(&bird1[3], "..\\resources\\bird4-1.gif");
	loadimage(&bird2[3], "..\\resources\\bird4-2.gif");
	loadimage(&stone1[0], "..\\resources\\stone_up2.gif");
	loadimage(&stone1[1], "..\\resources\\stone_up1.gif");
	loadimage(&stone2[0], "..\\resources\\stone_down2.gif");
	loadimage(&stone2[1], "..\\resources\\stone_down1.gif");
	loadimage(&over[0], "..\\resources\\gameover1.gif");
	loadimage(&over[1], "..\\resources\\gameover2.gif");
	loadimage(&n1[0], "..\\resources\\0_1.jpg");
	loadimage(&n2[0], "..\\resources\\0_2.jpg");
	loadimage(&n1[1], "..\\resources\\1_1.jpg");
	loadimage(&n2[1], "..\\resources\\1_2.jpg");
	loadimage(&n1[2], "..\\resources\\2_1.jpg");
	loadimage(&n2[2], "..\\resources\\2_2.jpg");
	loadimage(&n1[3], "..\\resources\\3_1.jpg");
	loadimage(&n2[3], "..\\resources\\3_2.jpg");
	loadimage(&n1[4], "..\\resources\\4_1.jpg");
	loadimage(&n2[4], "..\\resources\\4_2.jpg");
	loadimage(&n1[5], "..\\resources\\5_1.jpg");
	loadimage(&n2[5], "..\\resources\\5_2.jpg");
	loadimage(&n1[6], "..\\resources\\6_1.jpg");
	loadimage(&n2[6], "..\\resources\\6_2.jpg");
	loadimage(&n1[7], "..\\resources\\7_1.jpg");
	loadimage(&n2[7], "..\\resources\\7_2.jpg");
	loadimage(&n1[8], "..\\resources\\8_1.jpg");
	loadimage(&n2[8], "..\\resources\\8_2.jpg");
	loadimage(&n1[9], "..\\resources\\9_1.jpg");
	loadimage(&n2[9], "..\\resources\\9_2.jpg");
}

void printbeforegame()
{
	loadimage(NULL, "..\\resources\\bkg_1.jpg");
	gettextstyle(&f);
	f.lfHeight = 15;
	f.lfItalic = 1;
	_tcscpy_s(f.lfFaceName, "宋体");
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	outtextxy(207, 510, "操作说明:");
	outtextxy(207, 530, "蹦:空格键");
	outtextxy(207, 550, "关闭音乐:u键");
	outtextxy(207, 580, "Author: Simon Joe");
}

void printstone()
{
	putimage(stone_x[0], ll[0]-600, &stone1[0], NOTSRCERASE);
	putimage(stone_x[0], ll[0]-600, &stone1[1], SRCINVERT);
	putimage(stone_x[0], ll[0] + stone_blank, &stone2[0], NOTSRCERASE);
	putimage(stone_x[0], ll[0] + stone_blank, &stone2[1], SRCINVERT);
	putimage(stone_x[1], ll[1] - 600, &stone1[0], NOTSRCERASE);
	putimage(stone_x[1], ll[1] - 600, &stone1[1], SRCINVERT);
	putimage(stone_x[1], ll[1] + stone_blank, &stone2[0], NOTSRCERASE);
	putimage(stone_x[1], ll[1] + stone_blank, &stone2[1], SRCINVERT);
	stone_x[0]--;
	stone_x[1]--;
	if (stone_x[0] < -140)
	{
		stone_x[0] = stone_x[1] + 300;
		ll[0] = 100 + rand() % (401 - stone_blank);
	}
	if (stone_x[1] < -140)
	{
		stone_x[1] = stone_x[0] +300;
		ll[1] = 100 + rand() % (401 - stone_blank);
	}
}

void judge()
{
	for (int j = 0; j < 2; j++)
		if ((stone_x[j] <= (bird_x + 34)) && (stone_x[j] >= (bird_x - 140)))
			if ((bird_y >= ll[j]) && (bird_y <= (ll[j] + stone_blank - 24)))
			{
				if(stone_x[j] == -100)
					score++;
			}
			else
				gameover();
	if (bird_y >= 566)
		gameover();
}

void gameover()
{
	putimage(0, 0, &bkg);
	putimage(76, 280 , &over[0], NOTSRCERASE);
	putimage(76, 280, &over[1], SRCINVERT);
	mprintscore();
	Writeini();
	FlushBatchDraw();
	getch();
	isFirst = 0;
	main();
}

void mprintscore()
{
	f.lfHeight = 25;
	settextstyle(&f);
	outtextxy(180,20, "record:");
	printscore(Readini(), 20);
	outtextxy(180, 70, "current:");
	printscore(score, 70);
	
}

void printscore(int scoree,int score_y)
{
	int nv[10], num = scoree, m = 0;
	if (num == 0)
	{
		putimage(330 - 24, score_y, &n1[0], NOTSRCERASE);
		putimage(330 - 24, score_y, &n2[0], SRCINVERT);
	}
	while (num)
	{
		nv[m+1] = num % 10;
		m++;
		num /= 10;
	}
	for (;m > 0; m--)
	{
		putimage(330 - 24 * m, score_y, &n1[nv[m]], NOTSRCERASE);
		putimage(330 - 24 * m, score_y, &n2[nv[m]], SRCINVERT);
	}
}

int Readini()
{
	int a;
	a = GetPrivateProfileInt("bird", "highest_score", 0, "..\\highestscore.ini");
	return a;
}

void Writeini()
{
	if (score > Readini())
	{
		_stprintf_s(h_score, "%d", score);
		WritePrivateProfileString("bird", "highest_score", h_score, "..\\highestscore.ini");
	}
}

void start_time()
{
	startTime = clock();
}

void now_time()
{
	endTime = clock();
}
