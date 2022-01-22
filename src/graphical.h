#include <stdio.h>
#include <graphics.h>
#include <time.h>
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>

#define HEIGHT 800
#define WIDTH 800

#define LMARGIN 65
#define UMARGIN 130

void background(int clr[])
{
    srand(time(0));
    int colorchoice, h;
    int color[90] =   {15, 32, 67, 122, 207, 221, 213, 164, 88,
                       86, 18, 16, 240, 146, 34, 246, 236, 32,
                       59, 20, 18, 238, 45, 123, 190, 147, 117,
                       63, 43, 44, 237, 48, 71, 173, 162, 135,
                       239, 104, 43, 68, 68, 68, 187, 189, 189,
                       112, 80, 80, 240, 169, 121, 250, 241, 175,
                       24, 27, 28, 73, 135, 62, 176, 192, 220,
                       89, 10, 49, 145, 171, 60, 239, 198, 138,
                       41, 27, 79, 156, 234, 230, 253, 213, 44,
                       32, 27, 80, 200, 33, 40, 179, 180, 180};
    colorchoice = rand() % 9;
    h = colorchoice * 9;
    setfillstyle(1, COLOR(color[h], color[h+1], color[h+2]));
    bar(0, 0, WIDTH, 100);
    setfillstyle(1, COLOR(color[h+3], color[h+4], color[h+5]));
    bar(0,100,LMARGIN, HEIGHT);
    bar(0,100,WIDTH, UMARGIN);
    setfillstyle(1, COLOR(color[h+6], color[h+7], color[h+8]));
    bar(LMARGIN,UMARGIN,WIDTH, HEIGHT);
    setfillstyle(1, BLACK);
    for(int i = 0; i < 9; i++){
        clr[i] = color[h + i];
    }
    setbkcolor(COLOR(clr[3],clr[4],clr[5]));
    setcolor(WHITE);
    settextstyle(3, 0, 2);
    outtextxy(515,100,"Developed by Amir Soleimani");
}

void icon(int x1, int y1, int x2, int y2, int R, int G, int B, int tR, int tG, int tB, char text[])
{
    setfillstyle(1, COLOR(R, G, B));
    setbkcolor(COLOR(R, G, B));
    bar(x1, y1, x2, y2);
    setcolor(COLOR(tR, tG, tB));
    settextstyle(3, 0, 3);
    outtextxy(x1+15, (y1+y2)/2 - 15, text);
}

void text(int tsize, int x, int y, int R, int G, int B, int tR, int tG, int tB, char text[])
{
    settextstyle(3, 0, tsize);
    setcolor(COLOR(tR, tG, tB));
    setbkcolor(COLOR(R, G, B));
    outtextxy(x, y, text);
}

void colorp(int x, int y, int r, int R, int G, int B)
{
    setfillstyle(1, COLOR(R, G, B));
    setlinestyle(1, 0, 3);
    setcolor(COLOR(R, G, B));
    fillellipse(x, y, r, r);
}
