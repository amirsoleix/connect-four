#include "graphical.h"

#define DES 50
#define R 40
#define BDR 20

int IWIDTH = 250;
int IHEIGHT = 80;
extern char screen[2000000]= {};

extern int level = 0;
extern int state = 1;
extern int turn = 1;
extern int pturn = 1;
extern int row = 6, col = 7;
extern int gameboard[10][10]={};
extern int moves[42]={};
extern int pclr[2][3]= {232, 28, 43, 69, 159, 227};
extern char username1[100] = {}, username2[100] = {};

/*
    state == 1  Main Menu
    state == 2  Difficulty page
    state == 3  Options
    state == 4  How to Play
    state == 5  The game

    state == 0  Exit
*/

extern int color[10][3] = {232, 28, 43,
                           234, 137, 30,
                           234, 206, 42,
                           10, 163, 79,
                           69, 159, 227,
                           216, 11, 143,
                           106, 52, 153,
                           109, 52, 13,
                           15, 17, 19,
                           255, 255, 255,
                          };

/*  Colors
    Red, Orange, Yellow ,Green ,Blue ,Pink ,Purple ,Brown ,Black ,White
*/

int clr[9] = {};

int mainmenu()
{
    background(clr);
    char help[100];
    row = 6;
    col = 7;

    setbkcolor(COLOR(clr[0],clr[1],clr[2]));
    setcolor(COLOR(clr[3], clr[4], clr[5]));
    settextstyle(3, 0, 5);
    outtextxy(LMARGIN, 25, "WELCOME TO CONNECT FOUR");
    icon(LMARGIN + DES, UMARGIN + DES, LMARGIN + DES + IWIDTH, UMARGIN + DES + IHEIGHT
         , clr[0], clr[1], clr[2], clr[3], clr[4], clr[5], "Player Vs. Computer");
    icon(LMARGIN + DES, UMARGIN + 2 * DES + IHEIGHT, LMARGIN + DES + IWIDTH, UMARGIN + 2 * DES + 2 * IHEIGHT
         , clr[0], clr[1], clr[2], clr[3], clr[4], clr[5], "Player Vs. Player");
    icon(LMARGIN + DES, UMARGIN + 3 * DES + 2 * IHEIGHT, LMARGIN + DES + IWIDTH, UMARGIN + 3 * DES + 3 * IHEIGHT
         , clr[0], clr[1], clr[2], clr[3], clr[4], clr[5], "High Scores");

    icon(WIDTH - DES - IWIDTH/2, HEIGHT - DES - IHEIGHT, WIDTH - DES, HEIGHT - DES
         , clr[0], clr[1], clr[2], clr[3], clr[4], clr[5], "EXIT");

    text(5,LMARGIN + DES + 20, UMARGIN + 5 * IHEIGHT,clr[6],clr[7],clr[8],clr[0],clr[1],clr[2],itoa(row,help,10));
    text(5,LMARGIN + DES * 4 + 20, UMARGIN + 5 * IHEIGHT,clr[6],clr[7],clr[8],clr[0],clr[1],clr[2],itoa(col,help,10));
    colorp(LMARGIN + DES + 30, UMARGIN + 5 * DES + 3 * IHEIGHT, 30, clr[0], clr[1], clr[2]);
    colorp(LMARGIN + DES * 4 + 30, UMARGIN + 5 * DES + 3 * IHEIGHT, 30, clr[0], clr[1], clr[2]);
    text(3,LMARGIN + DES, UMARGIN + 6 * DES + 3 * IHEIGHT,clr[6],clr[7],clr[8],clr[0],clr[1],clr[2],"Rows");
    text(3,LMARGIN + DES * 4, UMARGIN + 6 * DES + 3 * IHEIGHT,clr[6],clr[7],clr[8],clr[0],clr[1],clr[2],"Columns");

    char exitkey = 0;
    int xmouse, ymouse;

    while(exitkey != 27) {
        while(!kbhit())
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                xmouse = mousex();
                ymouse = mousey();

                if(xmouse >= LMARGIN + DES && ymouse >= UMARGIN + DES && xmouse <= LMARGIN + DES + IWIDTH && ymouse <= UMARGIN + DES + IHEIGHT) {
                    return 2;
                }
                if(xmouse >= LMARGIN + DES && ymouse >= UMARGIN + 2 * DES + IHEIGHT && xmouse <= LMARGIN + DES + IWIDTH && ymouse <= UMARGIN + 2 * DES + 2 * IHEIGHT) {
                    level = 0;
                    return 3;
                }
                if(xmouse >= LMARGIN + DES && ymouse >= UMARGIN + 3 * DES + 2 * IHEIGHT && xmouse <= LMARGIN + DES + IWIDTH && ymouse <= UMARGIN + 3 * DES + 3 * IHEIGHT) {
                    return 4;
                }
                if(xmouse >= WIDTH - DES - IWIDTH/2 && ymouse >=  HEIGHT - DES - IHEIGHT && xmouse <= WIDTH - DES && ymouse <= HEIGHT - DES) {
                    return 0;
                }
                if((LMARGIN + DES + 30 - xmouse) * (LMARGIN + DES + 30 - xmouse) + (UMARGIN + 5 * DES + 3 * IHEIGHT - ymouse) * (UMARGIN + 5 * DES + 3 * IHEIGHT - ymouse) <= 900){
                    row++;
                    if(row>9){
                        row = 6;
                    }
                    text(5,LMARGIN + DES + 20, UMARGIN + 5 * IHEIGHT,clr[6],clr[7],clr[8],clr[0],clr[1],clr[2],itoa(row,help,10));
                }
                if((LMARGIN + DES * 4 + 30 - xmouse) * (LMARGIN + DES * 4 + 30 - xmouse) + (UMARGIN + 5 * DES + 3 * IHEIGHT - ymouse) * (UMARGIN + 5 * DES + 3 * IHEIGHT - ymouse) <= 900){
                    col++;
                    if(col>9){
                        col = 6;
                    }
                    text(5,LMARGIN + DES * 4 + 20, UMARGIN + 5 * IHEIGHT,clr[6],clr[7],clr[8],clr[0],clr[1],clr[2],itoa(col,help,10));
                }
            }
            delay(50);
        }
        exitkey = getch();

        if(exitkey == 27) {
            return 0;
        }
    }
}

int difficulty()
{
    background(clr);
    IWIDTH = 350;

    setbkcolor(COLOR(clr[0],clr[1],clr[2]));
    setcolor(COLOR(clr[3], clr[4], clr[5]));
    settextstyle(3, 0, 5);
    outtextxy(LMARGIN, 25, "Choose the Difficulty");
    icon(LMARGIN + DES, UMARGIN + DES, LMARGIN + DES + IWIDTH, UMARGIN + DES + IHEIGHT
         , clr[0], clr[1], clr[2], clr[3], clr[4], clr[5], "Easy | Random");
    icon(LMARGIN + DES, UMARGIN + 2 * DES + IHEIGHT, LMARGIN + DES + IWIDTH, UMARGIN + 2 * DES + 2 * IHEIGHT
         , clr[0], clr[1], clr[2], clr[3], clr[4], clr[5], "Medium | Some logic");
    icon(LMARGIN + DES, UMARGIN + 3 * DES + 2 * IHEIGHT, LMARGIN + DES + IWIDTH, UMARGIN + 3 * DES + 3 * IHEIGHT
         , clr[0], clr[1], clr[2], clr[3], clr[4], clr[5], "Hard | A real Challenge");
    IWIDTH = 250;
    icon(WIDTH - DES - IWIDTH/2, HEIGHT - DES - IHEIGHT, WIDTH - DES, HEIGHT - DES
         , clr[0], clr[1], clr[2], clr[3], clr[4], clr[5], "RETURN");
    IWIDTH = 350;
    char exitkey = 0;
    int xmouse, ymouse;

    while(exitkey != 27 && exitkey != 8) {
        while(!kbhit())
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                xmouse = mousex();
                ymouse = mousey();

                if(xmouse >= LMARGIN + DES && ymouse >= UMARGIN + DES && xmouse <= LMARGIN + DES + IWIDTH && ymouse <= UMARGIN + DES + IHEIGHT) {
                    IWIDTH = 250;
                    level = 1;
                    return 3;
                }
                if(xmouse >= LMARGIN + DES && ymouse >= UMARGIN + 2 * DES + IHEIGHT && xmouse <= LMARGIN + DES + IWIDTH && ymouse <= UMARGIN + 2 * DES + 2 * IHEIGHT) {
                    IWIDTH = 250;
                    level = 2;
                    return 3;
                }
                if(xmouse >= LMARGIN + DES && ymouse >= UMARGIN + 3 * DES + 2 * IHEIGHT && xmouse <= LMARGIN + DES + IWIDTH && ymouse <= UMARGIN + 3 * DES + 3 * IHEIGHT) {
                    IWIDTH = 250;
                    level = 3;
                    return 3;
                }
                if(xmouse >= WIDTH - DES - IWIDTH/2 && ymouse >=  HEIGHT - DES - IHEIGHT && xmouse <= WIDTH - DES && ymouse <= HEIGHT - DES) {
                    IWIDTH = 250;
                    return 1;
                }
            }
            delay(50);
        }
        exitkey = getch();

        if(exitkey == 27 || exitkey == 8) {
            IWIDTH = 250;
            return 1;
        }
    }
}

int options()
{
    int D2 = LMARGIN + IWIDTH * 1.5 - 10;
    turn = 1;
    pturn = 1;
    background(clr);

    for(int i = 0; i < 3; i++) {
        pclr[0][i] = color[0][i];
        pclr[1][i] = color[4][i];
    }

    setbkcolor(COLOR(clr[0],clr[1],clr[2]));
    setcolor(COLOR(clr[3], clr[4], clr[5]));
    settextstyle(3, 0, 5);
    outtextxy(LMARGIN, 25, "Choose colors and starting player");
    if(level == 0) {
        text(4,LMARGIN + DES, UMARGIN + DES, clr[6], clr[7], clr[8], pclr[0][0], pclr[0][1], pclr[0][2], "Player 1");
        text(4, D2 + DES, UMARGIN + DES, clr[6], clr[7], clr[8], pclr[1][0], pclr[1][1], pclr[1][2], "Player 2");
    }
    else {
        text(4, LMARGIN + DES, UMARGIN + DES, clr[6], clr[7], clr[8], pclr[0][0], pclr[0][1], pclr[0][2], "Player");
        text(4, D2 + DES, UMARGIN + DES, clr[6], clr[7], clr[8], pclr[1][0], pclr[1][1], pclr[1][2], "Computer");
    }

    colorp(LMARGIN + DES * 4.5, UMARGIN + DES + 20, 25, 255, 255, 255);
    colorp(D2 + DES * 4.5, UMARGIN + DES + 20, 25, 255, 255, 255);
    if(turn == 1) {
        colorp(LMARGIN + DES * 4.5, UMARGIN + DES + 20, 10, color[8][0], color[8][1], color[8][2]);
    }
    else {
        colorp(D2 + DES * 4.5, UMARGIN + DES + 20, 10, color[8][0], color[8][1], color[8][2]);
    }

    colorp(LMARGIN + DES + R, UMARGIN + 2 * DES + 1.5 * R, R, color[0][0], color[0][1], color[0][2]);
    colorp(LMARGIN + 5 * R - 15, UMARGIN + 2 * DES + 1.5 * R, R, color[1][0], color[1][1], color[1][2]);
    colorp(LMARGIN + 7 * R, UMARGIN + 2 * DES + 1.5 * R, R, color[2][0], color[2][1], color[2][2]);
    colorp(LMARGIN + DES + R, UMARGIN + 6.5 * R, R, color[3][0], color[3][1], color[3][2]);
    colorp(LMARGIN + 5 * R - 15, UMARGIN + 6.5 * R, R, color[4][0], color[4][1], color[4][2]);
    colorp(LMARGIN + 7 * R, UMARGIN + 6.5 * R, R, color[5][0], color[5][1], color[5][2]);
    colorp(LMARGIN + DES + R, UMARGIN + 9 * R, R, color[6][0], color[6][1], color[6][2]);
    colorp(LMARGIN + 5 * R - 15, UMARGIN + 9 * R, R, color[7][0], color[7][1], color[7][2]);
    colorp(LMARGIN + 7 * R, UMARGIN + 9 * R, R, color[9][0], color[9][1], color[9][2]);

    colorp(D2 + DES + R, UMARGIN + 2 * DES + 1.5 * R, R, color[0][0], color[0][1], color[0][2]);
    colorp(D2 + 5 * R - 15, UMARGIN + 2 * DES + 1.5 * R, R, color[1][0], color[1][1], color[1][2]);
    colorp(D2 + 7 * R, UMARGIN + 2 * DES + 1.5 * R, R, color[2][0], color[2][1], color[2][2]);
    colorp(D2 + DES + R, UMARGIN + 6.5 * R, R, color[3][0], color[3][1], color[3][2]);
    colorp(D2 + 5 * R - 15, UMARGIN + 6.5 * R, R, color[4][0], color[4][1], color[4][2]);
    colorp(D2 + 7 * R, UMARGIN + 6.5 * R, R, color[5][0], color[5][1], color[5][2]);
    colorp(D2 + DES + R, UMARGIN + 9 * R, R, color[6][0], color[6][1], color[6][2]);
    colorp(D2 + 5 * R - 15, UMARGIN + 9 * R, R, color[7][0], color[7][1], color[7][2]);
    colorp(D2 + 7 * R, UMARGIN + 9 * R, R, color[9][0], color[9][1], color[9][2]);

    icon(WIDTH - DES - IWIDTH/2, HEIGHT - DES - IHEIGHT, WIDTH - DES, HEIGHT - DES
         , clr[0], clr[1], clr[2], clr[3], clr[4], clr[5], "START");
    icon(LMARGIN + DES, HEIGHT - DES - IHEIGHT, LMARGIN + DES + IWIDTH/2, HEIGHT - DES
         , clr[0], clr[1], clr[2], clr[3], clr[4], clr[5], "RETURN");

    char exitkey = 0;
    int xmouse, ymouse;

    while(exitkey != 27 && exitkey != 8) {
        while(!kbhit())
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                xmouse = mousex();
                ymouse = mousey();

                if((LMARGIN + DES + R - xmouse) * (LMARGIN + DES + R - xmouse) + (UMARGIN + 2 * DES + 1.5 * R- ymouse) * (UMARGIN + 2 * DES + 1.5 * R- ymouse) <= R * R) {
                    for(int i = 0; i < 3; i++) {
                        pclr[0][i] = color[0][i];
                    }
                }
                if((LMARGIN + 5 * R - 15 - xmouse) * (LMARGIN + 5 * R - 15 - xmouse) + (UMARGIN + 2 * DES + 1.5 * R- ymouse) * (UMARGIN + 2 * DES + 1.5 * R- ymouse) <= R * R) {
                    for(int i = 0; i < 3; i++) {
                        pclr[0][i] = color[1][i];
                    }
                }
                if((LMARGIN + 7 * R - xmouse) * (LMARGIN + 7 * R - xmouse) + (UMARGIN + 2 * DES + 1.5 * R- ymouse) * (UMARGIN + 2 * DES + 1.5 * R- ymouse) <= R * R) {
                    for(int i = 0; i < 3; i++) {
                        pclr[0][i] = color[2][i];
                    }
                }
                if((LMARGIN + DES + R - xmouse) * (LMARGIN + DES + R - xmouse) + (UMARGIN + 6.5 * R- ymouse) * (UMARGIN + 6.5 * R- ymouse) <= R * R) {
                    for(int i = 0; i < 3; i++) {
                        pclr[0][i] = color[3][i];
                    }
                }
                if((LMARGIN + 5 * R - 15 - xmouse) * (LMARGIN + 5 * R - 15 - xmouse) + (UMARGIN + 6.5 * R- ymouse) * (UMARGIN + 6.5 * R- ymouse) <= R * R) {
                    for(int i = 0; i < 3; i++) {
                        pclr[0][i] = color[4][i];
                    }
                }
                if((LMARGIN + 7 * R - xmouse) * (LMARGIN + 7 * R - xmouse) + (UMARGIN + 6.5 * R- ymouse) * (UMARGIN + 6.5 * R- ymouse) <= R * R) {
                    for(int i = 0; i < 3; i++) {
                        pclr[0][i] = color[5][i];
                    }
                }
                if((LMARGIN + DES + R - xmouse) * (LMARGIN + DES + R - xmouse) + (UMARGIN + 9 * R- ymouse) * (UMARGIN + 9 * R- ymouse) <= R * R) {
                    for(int i = 0; i < 3; i++) {
                        pclr[0][i] = color[6][i];
                    }
                }
                if((LMARGIN + 5 * R - 15 - xmouse) * (LMARGIN + 5 * R - 15 - xmouse) + (UMARGIN + 9 * R- ymouse) * (UMARGIN + 9 * R- ymouse) <= R * R) {
                    for(int i = 0; i < 3; i++) {
                        pclr[0][i] = color[7][i];
                    }
                }
                if((LMARGIN + 7 * R - xmouse) * (LMARGIN + 7 * R - xmouse) + (UMARGIN + 9 * R- ymouse) * (UMARGIN + 9 * R- ymouse) <= R * R) {
                    for(int i = 0; i < 3; i++) {
                        pclr[0][i] = color[9][i];
                    }
                }

                if((D2 + DES + R - xmouse) * (D2 + DES + R - xmouse) + (UMARGIN + 2 * DES + 1.5 * R- ymouse) * (UMARGIN + 2 * DES + 1.5 * R- ymouse) <= R * R) {
                    for(int i = 0; i < 3; i++) {
                        pclr[1][i] = color[0][i];
                    }
                }
                if((D2 + 5 * R - 15 - xmouse) * (D2 + 5 * R - 15 - xmouse) + (UMARGIN + 2 * DES + 1.5 * R- ymouse) * (UMARGIN + 2 * DES + 1.5 * R- ymouse) <= R * R) {
                    for(int i = 0; i < 3; i++) {
                        pclr[1][i] = color[1][i];
                    }
                }
                if((D2 + 7 * R - xmouse) * (D2 + 7 * R - xmouse) + (UMARGIN + 2 * DES + 1.5 * R- ymouse) * (UMARGIN + 2 * DES + 1.5 * R- ymouse) <= R * R) {
                    for(int i = 0; i < 3; i++) {
                        pclr[1][i] = color[2][i];
                    }
                }

                if((D2 + DES + R - xmouse) * (D2 + DES + R - xmouse) + (UMARGIN + 6.5 * R- ymouse) * (UMARGIN + 6.5 * R- ymouse) <= R * R) {
                    for(int i = 0; i < 3; i++) {
                        pclr[1][i] = color[3][i];
                    }
                }
                if((D2 + 5 * R - 15 - xmouse) * (D2 + 5 * R - 15 - xmouse) + (UMARGIN + 6.5 * R- ymouse) * (UMARGIN + 6.5 * R- ymouse) <= R * R) {
                    for(int i = 0; i < 3; i++) {
                        pclr[1][i] = color[4][i];
                    }
                }
                if((D2 + 7 * R - xmouse) * (D2 + 7 * R - xmouse) + (UMARGIN + 6.5 * R- ymouse) * (UMARGIN + 6.5 * R- ymouse) <= R * R) {
                    for(int i = 0; i < 3; i++) {
                        pclr[1][i] = color[5][i];
                    }
                }

                if((D2 + DES + R - xmouse) * (D2 + DES + R - xmouse) + (UMARGIN + 9 * R- ymouse) * (UMARGIN + 9 * R- ymouse) <= R * R) {
                    for(int i = 0; i < 3; i++) {
                        pclr[1][i] = color[6][i];
                    }
                }
                if((D2 + 5 * R - 15 - xmouse) * (D2 + 5 * R - 15 - xmouse) + (UMARGIN + 9 * R- ymouse) * (UMARGIN + 9 * R- ymouse) <= R * R) {
                    for(int i = 0; i < 3; i++) {
                        pclr[1][i] = color[7][i];
                    }
                }
                if((D2 + 7 * R - xmouse) * (D2 + 7 * R - xmouse) + (UMARGIN + 9 * R- ymouse) * (UMARGIN + 9 * R- ymouse) <= R * R) {
                    for(int i = 0; i < 3; i++) {
                        pclr[1][i] = color[9][i];
                    }
                }

                if((LMARGIN + DES * 4.5 - xmouse) * (LMARGIN + DES * 4.5 - xmouse) + (UMARGIN + DES + 25 - ymouse) * (UMARGIN + DES + 25 - ymouse) <= 25 * 25) {
                    if(turn == 2) {
                        turn = 1;
                        pturn = 1;
                        colorp(D2 + DES * 4.5, UMARGIN + DES + 20, 25, 255, 255, 255);
                        colorp(LMARGIN + DES * 4.5, UMARGIN + DES + 20, 10, color[8][0], color[8][1], color[8][2]);
                    }
                }
                if((D2 + DES * 4.5 - xmouse) * (D2 + DES * 4.5 - xmouse) + (UMARGIN + DES + 25 - ymouse) * (UMARGIN + DES + 25 - ymouse) <= 25 * 25) {
                     if(turn == 1) {
                        turn = 2;
                        pturn = 2;
                        colorp(LMARGIN + DES * 4.5, UMARGIN + DES + 20, 25, 255, 255, 255);
                        colorp(D2 + DES * 4.5, UMARGIN + DES + 20, 10, color[8][0], color[8][1], color[8][2]);
                    }
                }


                if(level == 0) {
                    text(4,LMARGIN + DES, UMARGIN + DES, clr[6], clr[7], clr[8], pclr[0][0], pclr[0][1], pclr[0][2], "Player 1");
                    text(4, D2 + DES, UMARGIN + DES, clr[6], clr[7], clr[8], pclr[1][0], pclr[1][1], pclr[1][2], "Player 2");
                }
                else {
                    text(4, LMARGIN + DES, UMARGIN + DES, clr[6], clr[7], clr[8], pclr[0][0], pclr[0][1], pclr[0][2], "Player");
                    text(4, D2 + DES, UMARGIN + DES, clr[6], clr[7], clr[8], pclr[1][0], pclr[1][1], pclr[1][2], "Computer");
                }


                if(xmouse >= LMARGIN + DES && ymouse >=  HEIGHT - DES - IHEIGHT && xmouse <= LMARGIN + DES + IWIDTH/2 && ymouse <= HEIGHT - DES) {
                    IWIDTH = 250;
                    if(level == 0) {
                        return 1;
                    }
                    else {
                        return 2;
                    }
                }
                if(xmouse >= WIDTH - DES - IWIDTH/2 && ymouse >=  HEIGHT - DES - IHEIGHT && xmouse <= WIDTH - DES && ymouse <= HEIGHT - DES) {
                    IWIDTH = 250;
                    if(pclr[0][1] == pclr [1][1] && pclr[0][0] == pclr [1][0] && pclr[0][2] == pclr [1][2]) {
                        getimage(200,350,600,450,screen);
                        setfillstyle(1, COLOR(255,255,255));
                        setcolor(COLOR(clr[3],clr[4],clr[5]));
                        setbkcolor(COLOR(255, 255, 255));
                        settextstyle(3, 0, 4);
                        bar(200,350,600,450);
                        outtextxy(200 + 25,375,"Choose different Colors!!");
                        delay(2000);
                        putimage(200,350,screen,0);
                        setcolor(COLOR(clr[3],clr[4],clr[5]));
                        setfillstyle(1, COLOR(clr[6],clr[7],clr[8]));
                        settextstyle(3, 0, 3);
                        setbkcolor(COLOR(clr[6],clr[7],clr[8]));
                    }
                    else {
                        return 5;
                    }
                }
            }
            delay(50);
        }
        exitkey = getch();

        if(exitkey == 27 || exitkey == 8) {
            IWIDTH = 250;
            if(level == 0) {
                return 1;
            }
            else {
                return 2;
            }
        }
    }
}

int highscore()
{
    background(clr);
    IWIDTH = 350;
    char score[100];
    int high;

    setbkcolor(COLOR(clr[0],clr[1],clr[2]));
    setcolor(COLOR(clr[3], clr[4], clr[5]));
    settextstyle(3, 0, 5);
    outtextxy(LMARGIN, 25, "High Scores");

    FILE * filePointer;
    filePointer = fopen("high.txt","r");
    if(filePointer != NULL){
    fscanf(filePointer,"%s",&score);
    fscanf(filePointer,"%d", &high);
    text(4, LMARGIN + BDR, UMARGIN + DES, clr[6], clr[7], clr[8], clr[0], clr[1], clr[2], score);
    text(4, LMARGIN + BDR + IWIDTH, UMARGIN + DES, clr[6], clr[7], clr[8], clr[0], clr[1], clr[2], itoa(high, score, 10));
    fscanf(filePointer,"%s",&score);
    fscanf(filePointer,"%d", &high);
    text(4, LMARGIN + BDR, UMARGIN + 3 * DES, clr[6], clr[7], clr[8], clr[0], clr[1], clr[2], score);
    text(4, LMARGIN + BDR + IWIDTH, UMARGIN + 3 * DES, clr[6], clr[7], clr[8], clr[0], clr[1], clr[2], itoa(high, score, 10));
    fscanf(filePointer,"%s",&score);
    fscanf(filePointer,"%d", &high);
    text(4, LMARGIN + BDR, UMARGIN + 5 * DES, clr[6], clr[7], clr[8], clr[0], clr[1], clr[2], score);
    text(4, LMARGIN + BDR + IWIDTH, UMARGIN + 5 * DES, clr[6], clr[7], clr[8], clr[0], clr[1], clr[2], itoa(high, score, 10));
    fclose(filePointer);
    }
    icon(WIDTH - DES - IWIDTH/2, HEIGHT - DES - IHEIGHT, WIDTH - DES, HEIGHT - DES
         , clr[0], clr[1], clr[2], clr[3], clr[4], clr[5], "RETURN");
    IWIDTH = 350;
    char exitkey = 0;
    int xmouse, ymouse;

    while(exitkey != 27 && exitkey != 8) {
        while(!kbhit())
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                xmouse = mousex();
                ymouse = mousey();
                if(xmouse >= WIDTH - DES - IWIDTH/2 && ymouse >=  HEIGHT - DES - IHEIGHT && xmouse <= WIDTH - DES && ymouse <= HEIGHT - DES) {
                    IWIDTH = 250;
                    return 1;
                }
            }
            delay(50);
        }
        exitkey = getch();

        if(exitkey == 27 || exitkey == 8) {
            IWIDTH = 250;
            return 1;
        }
    }
}
