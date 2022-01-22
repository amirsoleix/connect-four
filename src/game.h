#include "pages.h"

int settings();
int rbead;
int p1win, p2win, p1state, p2state;
int movesplayed = 0;
void movement(int cl);
void wincheck();
int endgame();
int time1, time2;
int easy();
int medium();
int hard();
int win = 0;
int current_time, settings_time2;

void column(int x, int y, int row, int col, int r, int g, int b)
{
    int bsize = (HEIGHT - y - BDR) / row;
    int csize = (WIDTH - x - BDR) / col;
    setfillstyle(1, COLOR(clr[0], clr[1], clr[2]));
    setlinestyle(1, 0, 3);
    bar(x, y, x + csize, HEIGHT);
    rbead = min(bsize,csize)/2 - 5;
    for(int i = 0; i < row; i++) {
        setfillstyle(1, COLOR(clr[6], clr[7], clr[8]));
        setcolor(COLOR(clr[0], clr[1], clr[2]));
        fillellipse(x + csize/2, y + bsize * (i+.5), rbead, rbead);
    }
}

int game()
{
    turn = pturn;
    win = 0;
    time1 = 0;
    time2 = 0;
    p1win = 0;
    p2win = 0;

    time_t seconds;
    seconds = time(NULL);
    char time_str[100];
    current_time = time(NULL);
    settings_time2 = 0;
    int settings_time1;

    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            gameboard[i][j] = 0;
        }
    }
    movesplayed = 0;
    for(int i = 0; i < 42; i++) {
        moves[i] = -1;
    }

    background(clr);
    setbkcolor(COLOR(clr[0],clr[1],clr[2]));
    setcolor(COLOR(clr[3], clr[4], clr[5]));

    for(int i = 0; i < col; i++) {
        column(LMARGIN + BDR + i * ((WIDTH - LMARGIN - 2 * BDR) / col),UMARGIN + 5* BDR,row, col - i, clr[0],clr[1],clr[2]);
    }

    icon(WIDTH - DES - IWIDTH/2, 20, WIDTH - DES, 80
         , clr[6], clr[7], clr[8], clr[0], clr[1], clr[2], "Settings");


    char exitkey = 0;
    int xmouse, ymouse;
    int rsize = (WIDTH - LMARGIN - 2 * BDR) / col;
    time1 = 0;
    while(exitkey!= 27) {
        while(!kbhit())
        {
            current_time = time(NULL) - seconds;
            if(current_time - time1 > 10) {
                getimage(300, 350, 500, 450, screen);
                setfillstyle(1, COLOR(255, 255, 255));
                bar(300, 350, 500, 450);
                icon(310, 360, 490, 440, clr[0], clr[1], clr[2], clr[6], clr[7], clr[8], "Out of time!");
                icon(310, 360, 490, 440, clr[0], clr[1], clr[2], clr[6], clr[7], clr[8], "Out of time!");
                delay(500);
                putimage(300, 350, screen, 0);
                turn++;
                if(turn == 3){
                    turn = 1;
                }
                time1 = current_time;
            }
            int tool = (current_time - settings_time2)/ 60;
            itoa(tool,time_str,10);

            if(tool > 9) {
                text(4, 42, 30, clr[0],clr[1],clr[2],clr[3],clr[4],clr[5],time_str);
            }
            else {
                text(4, 42, 30, clr[0],clr[1],clr[2],clr[3],clr[4],clr[5],"0");
                text(4, 58, 30, clr[0],clr[1],clr[2],clr[3],clr[4],clr[5],time_str);
            }
            tool = (current_time - settings_time2)% 60;
            text(4, 75, 30, clr[0],clr[1],clr[2],clr[3],clr[4],clr[5],":");
            itoa(tool,time_str,10);
            if(tool == 0) {
                icon(103,30,120,80,clr[0],clr[1],clr[2],clr[0],clr[1],clr[2],"");
                delay(50);
            }
            text(4, 85, 30, clr[0],clr[1],clr[2],clr[3],clr[4],clr[5],time_str);

            if(level == 0 || (level != 0 && turn == 1)) {
                if(ismouseclick(WM_MOUSEMOVE)) {
                    clearmouseclick(WM_MOUSEMOVE);
                    xmouse = mousex();
                    ymouse = mousey();
                    for(int i = 0; i < col; i++) {
                        if(xmouse >= LMARGIN + BDR + rsize * i && xmouse <= LMARGIN + BDR + rsize * (i+1) && ymouse >= UMARGIN) {

                            setfillstyle(1, COLOR(clr[6],clr[7],clr[8]));
                            bar(LMARGIN, UMARGIN, WIDTH, UMARGIN + 5 * BDR);
                            colorp(LMARGIN + BDR + rsize * (i+.5), UMARGIN + 2.5 * BDR, rbead, pclr[turn-1][0], pclr[turn-1][1], pclr[turn-1][2]);
                        }
                    }
                }
                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    xmouse = mousex();
                    ymouse = mousey();
                    int bsize = (HEIGHT - UMARGIN - 5 * BDR) / row;
                    int csize = (WIDTH - LMARGIN - 2 * BDR) / col;
                    for(int i = 0 ; i < col; i++) {
                        if(xmouse >= LMARGIN + BDR + rsize * i && xmouse <= LMARGIN + BDR + rsize * (i+1) && ymouse >= UMARGIN) {
                            movement(i);
                            time1 = current_time;
                            if(p1state>p1win) {
                                win = 1;
                            }
                            else if(p2state > p2win) {
                                win = 2;
                            }
                            if(win != 0) {
                                int scores[3];
                        char names[3][100];
                        FILE *filePointer;
                        filePointer = fopen("high.txt", "r");
                        if(filePointer != NULL){
                        fscanf(filePointer,"%s %d %s %d %s %d", &names[0], &scores[0], &names[1], &scores[1], &names[2], &scores[2]);
                        fclose(filePointer);
                        filePointer = fopen("high.txt", "w");
                        if(filePointer != NULL){
                        if( movesplayed < scores[0]) {
                            if(win == 1)
                                fprintf(filePointer,"%s %d\n %s %d\n%s %d\n", username1, movesplayed, names[0], scores[0], names[1], scores[1]);
                            if(win == 2 && level == 0)
                                fprintf(filePointer,"%s %d\n %s %d\n%s %d\n", username2, movesplayed, names[0], scores[0], names[1], scores[1]);
                        }
                        else if( movesplayed < scores[1]) {
                            if(win == 1)
                                fprintf(filePointer,"%s %d\n %s %d\n%s %d\n",  names[0], scores[0],username1, movesplayed, names[1], scores[1]);
                            if(win == 2 && level == 0)
                                fprintf(filePointer,"%s %d\n %s %d\n%s %d\n",  names[0], scores[0],username2, movesplayed, names[1], scores[1]);
                        }
                        else if( movesplayed < scores[2]) {
                            if(win == 1)
                                fprintf(filePointer,"%s %d\n %s %d\n%s %d\n",  names[0], scores[0], names[1], scores[1],username1, movesplayed);
                            if(win == 2 && level == 0)
                                fprintf(filePointer,"%s %d\n %s %d\n%s %d\n",  names[0], scores[0], names[1], scores[1],username2, movesplayed);
                        }
                        fclose(filePointer);
                        }
                        }
                                int response = -1;
                                settings_time1 = time(NULL);
                                response = endgame();
                                if(response == 1) {
                                    return 1;
                                }
                                else if(response == 5) {
                                    return 5;
                                }
                                settings_time2 += time(NULL) - settings_time1;

                            }
                        }
                    }
                    if(xmouse >= WIDTH - DES - IWIDTH/2 && xmouse <= WIDTH - DES && ymouse >= 20 && ymouse <= 80) {
                        settings_time1 = time(NULL);
                        int astate;
                        astate = settings();
                        if(astate == 1) {
                            return 1;
                        }
                        else if(astate == 5) {
                            return 5;
                        }
                        settings_time2 += time(NULL) - settings_time1;
                        time1 = current_time;
                    }
                    delay(50);
                }
            }
            else {
                if(level == 1) {
                    movement(easy());
                    time1 = current_time;
                }
                else if(level == 2) {
                    movement(medium());
                    time1 = current_time;
                }
                else if(level == 3) {
                    movement(hard());
                    time1 = current_time;
                }

                if(p1state>p1win) {
                    win = 1;
                }
                else if(p2state > p2win) {
                    win = 2;
                }
                if(win != 0) {
                    int scores[3];
                        char names[3][100];
                        FILE *filePointer;
                        filePointer = fopen("high.txt", "r");
                        if(filePointer != NULL){
                        fscanf(filePointer,"%s %d %s %d %s %d", &names[0], &scores[0], &names[1], &scores[1], &names[2], &scores[2]);
                        fclose(filePointer);
                        filePointer = fopen("high.txt", "w");
                        if(filePointer != NULL){
                        if( movesplayed < scores[0]) {
                            if(win == 1)
                                fprintf(filePointer,"%s %d\n %s %d\n%s %d\n", username1, movesplayed, names[0], scores[0], names[1], scores[1]);
                            if(win == 2 && level == 0)
                                fprintf(filePointer,"%s %d\n %s %d\n%s %d\n", username2, movesplayed, names[0], scores[0], names[1], scores[1]);
                        }
                        else if( movesplayed < scores[1]) {
                            if(win == 1)
                                fprintf(filePointer,"%s %d\n %s %d\n%s %d\n",  names[0], scores[0],username1, movesplayed, names[1], scores[1]);
                            if(win == 2 && level == 0)
                                fprintf(filePointer,"%s %d\n %s %d\n%s %d\n",  names[0], scores[0],username2, movesplayed, names[1], scores[1]);
                        }
                        else if( movesplayed < scores[2]) {
                            if(win == 1)
                                fprintf(filePointer,"%s %d\n %s %d\n%s %d\n",  names[0], scores[0], names[1], scores[1],username1, movesplayed);
                            if(win == 2 && level == 0)
                                fprintf(filePointer,"%s %d\n %s %d\n%s %d\n",  names[0], scores[0], names[1], scores[1],username2, movesplayed);
                        }
                        fclose(filePointer);
                        }
                        }
                    int response = -1;
                    settings_time1 = time(NULL);
                    response = endgame();
                    if(response == 1) {
                        return 1;
                    }
                    else if(response == 5) {
                        return 5;
                    }
                    settings_time2 += time(NULL) - settings_time1;
                    time1 = current_time;

                }
            }
        }
        exitkey = getch();
        if(exitkey== 27 || exitkey == 82 || exitkey == 114) {
            settings_time1 = time(NULL);
            int astate;
            astate = settings();
            if(astate == 1) {
                return 1;
            }
            else if(astate == 5) {
                return 5;
            }
            settings_time2 += time(NULL) - settings_time1;
            time1 = current_time;

        }
        else if(exitkey == 26) {

            if(level == 0 && movesplayed > 0) {
                int counter = 0, i = 0;
            int bsize = (HEIGHT - UMARGIN - 6 * BDR) / row;
            int rsize = (WIDTH - LMARGIN - 2 * BDR) / col;
                int backer;
                backer = moves[movesplayed-1];
                int done = 0;
                for(i = row- 1; i >=0 && !done; i--) {
                    if(gameboard[backer][i] != 0) {
                        gameboard[backer][i] = 0;
                        done = 1;
                    }
                }
                i++;
                moves[movesplayed-1] = -1;
                movesplayed--;
                int xcircle = LMARGIN + BDR + (backer + .5) * rsize;
                int yend = HEIGHT - BDR - 2 - bsize * (i + .5);
                colorp(xcircle, yend, rbead - 2, clr[6], clr[7], clr[8]);
                turn--;
                if(turn==0) {
                    turn = 2;
                }
            }
            else if(turn == 1 && movesplayed > 1) {
                int backer, done;
                for(int k = 0 ; k < 2; k++) {
                    int counter = 0, i = 0;
                    int bsize = (HEIGHT - UMARGIN - 6 * BDR) / row;
                    int rsize = (WIDTH - LMARGIN - 2 * BDR) / col;
                    backer = moves[movesplayed-1];
                    done = 0;
                    for(i = row- 1; i >=0 && !done; i--) {
                        if(gameboard[backer][i] != 0) {
                            gameboard[backer][i] = 0;
                            done = 1;
                        }
                    }
                    i++;
                    moves[movesplayed-1] = -1;
                    movesplayed--;
                    int xcircle = LMARGIN + BDR + (backer + .5) * rsize;
                    int yend = HEIGHT - BDR - 2 - bsize * (i + .5);
                    colorp(xcircle, yend, rbead - 2, clr[6], clr[7], clr[8]);
                }
            }
        }
        else if(exitkey == 68 || exitkey == 100) {
            xmouse += rsize;
            if(xmouse > LMARGIN + BDR + rsize * (col)) {
                xmouse -= rsize * col;
            }
            for(int i = 0; i < col; i++) {
                if(xmouse >= LMARGIN + BDR + rsize * i && xmouse <= LMARGIN + BDR + rsize * (i+1) && ymouse >= UMARGIN) {

                    setfillstyle(1, COLOR(clr[6],clr[7],clr[8]));
                    bar(LMARGIN, UMARGIN, WIDTH, UMARGIN + 5 * BDR);
                    colorp(LMARGIN + BDR + rsize * (i+.5), UMARGIN + 2.5 * BDR, rbead, pclr[turn-1][0], pclr[turn-1][1], pclr[turn-1][2]);
                }
            }
        }
        else if(exitkey == 65 || exitkey == 97) {
            xmouse -= rsize;
            if(xmouse < LMARGIN + BDR) {
                xmouse += rsize * col;
            }
            for(int i = 0; i < col; i++) {
                if(xmouse >= LMARGIN + BDR + rsize * i && xmouse <= LMARGIN + BDR + rsize * (i+1) && ymouse >= UMARGIN) {

                    setfillstyle(1, COLOR(clr[6],clr[7],clr[8]));
                    bar(LMARGIN, UMARGIN, WIDTH, UMARGIN + 5 * BDR);
                    colorp(LMARGIN + BDR + rsize * (i+.5), UMARGIN + 2.5 * BDR, rbead, pclr[turn-1][0], pclr[turn-1][1], pclr[turn-1][2]);
                }
            }
        }
        else if(exitkey == 13) {
            int bsize = (HEIGHT - UMARGIN - 5 * BDR) / row;
            int csize = (WIDTH - LMARGIN - 2 * BDR) / col;
            for(int i = 0 ; i < col; i++) {
                if(xmouse >= LMARGIN + BDR + rsize * i && xmouse <= LMARGIN + BDR + rsize * (i+1) && ymouse >= UMARGIN) {
                    movement(i);
                    time1 = current_time;
                    if(p1state>p1win) {
                        win = 1;
                    }
                    else if(p2state > p2win) {
                        win = 2;
                    }
                    if(win != 0) {
                        int response = -1;
                        int scores[3];
                        char names[3][100];
                        FILE *filePointer;
                        filePointer = fopen("high.txt", "r");
                        if(filePointer != NULL){
                        fscanf(filePointer,"%s %d %s %d %s %d", &names[0], &scores[0], &names[1], &scores[1], &names[2], &scores[2]);
                        fclose(filePointer);
                        filePointer = fopen("high.txt", "w");
                        if(filePointer != NULL){
                        if( movesplayed < scores[0]) {
                            if(win == 1)
                                fprintf(filePointer,"%s %d\n %s %d\n%s %d\n", username1, movesplayed, names[0], scores[0], names[1], scores[1]);
                            if(win == 2 && level == 0)
                                fprintf(filePointer,"%s %d\n %s %d\n%s %d\n", username2, movesplayed, names[0], scores[0], names[1], scores[1]);
                        }
                        else if( movesplayed < scores[1]) {
                            if(win == 1)
                                fprintf(filePointer,"%s %d\n %s %d\n%s %d\n",  names[0], scores[0],username1, movesplayed, names[1], scores[1]);
                            if(win == 2 && level == 0)
                                fprintf(filePointer,"%s %d\n %s %d\n%s %d\n",  names[0], scores[0],username2, movesplayed, names[1], scores[1]);
                        }
                        else if( movesplayed < scores[2]) {
                            if(win == 1)
                                fprintf(filePointer,"%s %d\n %s %d\n%s %d\n",  names[0], scores[0], names[1], scores[1],username1, movesplayed);
                            if(win == 2 && level == 0)
                                fprintf(filePointer,"%s %d\n %s %d\n%s %d\n",  names[0], scores[0], names[1], scores[1],username2, movesplayed);
                        }
                        fclose(filePointer);
                        }
                        }
                        settings_time1 = time(NULL);
                        response = endgame();
                        if(response == 1) {
                            return 1;
                        }
                        else if(response == 5) {
                            return 5;
                        }
                        settings_time2 += time(NULL) - settings_time1;
                        time1 = current_time;

                    }
                }
            }
        }
        exitkey = 0;
    }
}

int settings()
{
    getimage(300, 200, 500, 600, screen);
    setfillstyle(1, COLOR(255, 255, 255));
    bar(300, 200, 500, 600);
    icon(325, 220, 475, 295, clr[0], clr[1], clr[2], clr[6], clr[7], clr[8], "Resume");
    icon(325, 315, 475, 390, clr[0], clr[1], clr[2], clr[6], clr[7], clr[8], "Restart");
    icon(325, 410, 475, 485, clr[0], clr[1], clr[2], clr[6], clr[7], clr[8], "Cheat");
    icon(325, 505, 475, 580, clr[0], clr[1], clr[2], clr[6], clr[7], clr[8], "Exit");

    char exitkey = 0;
    int xmouse, ymouse;

    while(exitkey!= 8) {
        while(!kbhit())
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                xmouse = mousex();
                ymouse = mousey();

                if(xmouse >= 325 && ymouse >= 220 && xmouse <= 475 && ymouse <= 295) {
                    putimage(300, 200, screen, 0);
                    return -1;
                }
                if(xmouse >= 325 && ymouse >= 315 && xmouse <= 475 && ymouse <= 390) {
                    return 5;
                }
                if(xmouse >= 325 && ymouse >= 410 && xmouse <= 475 && ymouse <= 485) {
                    time_t duration = time(NULL);
                    int index = 0;
                    char c;
                    while(time(NULL) - duration <= 3) {
                        char code[]="helpme";
                        while(!kbhit()) {
                            if(time(NULL) - duration > 3) {
                                putimage(300, 200, screen, 0);
                                return -1;
                            }
                        }
                        c = getch();
                        if(c == code[index]) {
                            index++;
                        }
                        if(index == 6) {
                            win = turn;
                            putimage(300, 200, screen, 0);
                            return -1;
                        }

                    }
                }
                if(xmouse >= 325 && ymouse >= 505 && xmouse <= 475 && ymouse <= 580) {
                    return 1;
                }

            }
        }
        exitkey = getch();
        if(exitkey == 8) {
            putimage(300, 200, screen, 0);
            return -1;
        }
    }
}

void movement(int cl)
{

    int bsize = (HEIGHT - UMARGIN - 6 * BDR) / row;
    int rsize = (WIDTH - LMARGIN - 2 * BDR) / col;


    int xcircle = LMARGIN + BDR + (cl + .5) * rsize;
    int ycircle = UMARGIN + 2.5 * BDR;
    int yend = -1;

    for(int j = 0; j < row && yend == -1; j++) {
        if(gameboard[cl][j] == 0) {
            yend = j;
            gameboard[cl][j] = turn;
            moves[movesplayed] = cl;
            movesplayed++;
        }
    }
    if(yend != -1) {
        yend = HEIGHT - BDR - 2 - bsize * (yend + .5);
        int ystart = HEIGHT - BDR - 2 - bsize * (row+.5);

        setfillstyle(1, COLOR(clr[6],clr[7],clr[8]));
        bar(LMARGIN, UMARGIN, WIDTH, UMARGIN + 5 * BDR);
        colorp(xcircle, ystart, rbead, pclr[turn-1][0], pclr[turn-1][1], pclr[turn-1][2]);
        colorp(xcircle, ystart, rbead, clr[6], clr[7], clr[8]);
        for(int i = ystart + bsize; i <= yend; i+= bsize) {
            colorp(xcircle, i - bsize, rbead - 2, clr[6], clr[7], clr[8]);
            colorp(xcircle, i, rbead - 2, pclr[turn-1][0],pclr[turn-1][1],pclr[turn-1][2]);
            delay(50 - ((yend - i)/bsize) * 5);
        }
        if(yend >= ystart + 2 * bsize) {
            delay(50);
            colorp(xcircle, yend, rbead - 2, clr[6], clr[7], clr[8]);
            colorp(xcircle, yend - bsize, rbead - 2, pclr[turn-1][0],pclr[turn-1][1],pclr[turn-1][2]);
            delay(50);
            colorp(xcircle, yend - bsize, rbead - 2, clr[6], clr[7], clr[8]);
            colorp(xcircle, yend - 2 * bsize, rbead - 2, pclr[turn-1][0],pclr[turn-1][1],pclr[turn-1][2]);
            delay(125);
            colorp(xcircle, yend - 2 * bsize, rbead - 2, clr[6], clr[7], clr[8]);
            colorp(xcircle, yend - bsize, rbead - 2, pclr[turn-1][0],pclr[turn-1][1],pclr[turn-1][2]);
            delay(75);
            colorp(xcircle, yend - bsize, rbead - 2, clr[6], clr[7], clr[8]);
            colorp(xcircle, yend, rbead - 2, pclr[turn-1][0],pclr[turn-1][1],pclr[turn-1][2]);
            delay(50);
            colorp(xcircle, yend, rbead - 2, clr[6], clr[7], clr[8]);
            colorp(xcircle, yend - bsize, rbead - 2, pclr[turn-1][0],pclr[turn-1][1],pclr[turn-1][2]);
            delay(100);
            colorp(xcircle, yend - bsize, rbead - 2, clr[6], clr[7], clr[8]);
            colorp(xcircle, yend, rbead - 2, pclr[turn-1][0],pclr[turn-1][1],pclr[turn-1][2]);
            delay(50);
        }
        turn++;
        if(turn == 3) {
            turn = 1;
        }
        wincheck();
    }
    else {
        if(level == 0 || (level != 0) && (turn ==1)) {
            getimage(300, 350, 500, 450, screen);
            setfillstyle(1, COLOR(255, 255, 255));
            bar(300, 350, 500, 450);
            icon(310, 360, 490, 440, clr[0], clr[1], clr[2], clr[6], clr[7], clr[8], "Full Column!!");
            icon(310, 360, 490, 440, clr[0], clr[1], clr[2], clr[6], clr[7], clr[8], "Full Column!!");
            delay(500);
            putimage(300, 350, screen, 0);
        }

    }
}

void wincheck()
{
    p1state = 0;
    p2state = 0;
    for(int i = 0; i <= row - 4; i++) {
        for(int j = 0; j < col; j++) {
            if(gameboard[j][i] == gameboard [j][i+1] && gameboard[j][i+1] == gameboard[j][i+2] && gameboard[j][i+2] == gameboard[j][i+3] && gameboard[j][i+3] == 1) {
                p1state++;
            }
            else if(gameboard[j][i] == gameboard [j][i+1] && gameboard[j][i+1] == gameboard[j][i+2] && gameboard[j][i+2] == gameboard[j][i+3] && gameboard[j][i+3] == 2) {
                p2state++;
            }
        }
    }

    for(int i = 0; i <= col - 4; i++) {
        for(int j = 0; j < row; j++) {
            if(gameboard[i][j] == gameboard [i+1][j] && gameboard[i+1][j] == gameboard[i+2][j] && gameboard[i+2][j] == gameboard[i+3][j] && gameboard[i+3][j] == 1) {
                p1state++;
            }
            else if(gameboard[i][j] == gameboard [i+1][j] && gameboard[i+1][j] == gameboard[i+2][j] && gameboard[i+2][j] == gameboard[i+3][j] && gameboard[i+3][j] == 2) {
                p2state++;
            }
        }
    }

    for(int i = 0; i <= col - 4; i++) {
        for(int j = 0; j <= row - 4; j++) {
            if(gameboard[i][j] == gameboard [i+1][j+1] && gameboard[i+1][j+1] == gameboard[i+2][j+2] && gameboard[i+2][j+2] == gameboard[i+3][j+3] && gameboard[i+3][j+3] == 1) {
                p1state++;
            }
            else if(gameboard[i][j] == gameboard [i+1][j+1] && gameboard[i+1][j+1] == gameboard[i+2][j+2] && gameboard[i+2][j+2] == gameboard[i+3][j+3] && gameboard[i+3][j+3] == 2) {
                p2state++;
            }
        }
    }

    for(int i = 0; i <= col - 4; i++) {
        for(int j = 0; j <= row - 4; j++) {
            if(gameboard[i][j+3] == gameboard[i+1][j+2] && gameboard[i+1][j+2] == gameboard[i+2][j+1] && gameboard[i+2][j+1] == gameboard[i+3][j] && gameboard[i+3][j] == 1) {
                p1state++;
            }
            if(gameboard[i][j+3] == gameboard[i+1][j+2] && gameboard[i+1][j+2] == gameboard[i+2][j+1] && gameboard[i+2][j+1] == gameboard[i+3][j] && gameboard[i+3][j] == 2) {
                p2state++;
            }
        }
    }
}


int endgame()
{
    delay(500);
    setfillstyle(1, COLOR(255, 255, 255));
    bar(300, 260, 500, 600);
    if(win == 1) {
        if(level == 0) {
            text(3, 320, 300, 255,255,255, clr[0],clr[1],clr[2],"Player 1 Wins!!");
            text(3, 320, 300, 255,255,255, clr[0],clr[1],clr[2],"Player 1 Wins!!");
        }
        else {
            text(3, 320, 300, 255,255,255, clr[0],clr[1],clr[2],"Player Wins :)");
            text(3, 320, 300, 255,255,255, clr[0],clr[1],clr[2],"Player Wins :)");
        }
    }
    else if(win == 2) {
        if(level == 0) {
            text(3, 320, 300, 255,255,255, clr[0],clr[1],clr[2],"Player 2 Wins!!");
            text(3, 320, 300, 255,255,255, clr[0],clr[1],clr[2],"Player 2 Wins!!");
        }
        else {
            text(3, 305, 300, 255,255,255, clr[0],clr[1],clr[2],"Computer Wins :(");
            text(3, 305, 300, 255,255,255, clr[0],clr[1],clr[2],"Computer Wins :(");
        }
    }
    char helper[100];
    text(3, 325, 350, 255,255,255, clr[0],clr[1],clr[2],itoa(current_time - settings_time2,helper,10));
    text(3, 375, 350, 255,255,255, clr[0],clr[1],clr[2],"Seconds");
    icon(325, 410, 475, 485, clr[0], clr[1], clr[2], clr[6], clr[7], clr[8], "Restart");
    icon(325, 505, 475, 580, clr[0], clr[1], clr[2], clr[6], clr[7], clr[8], "Exit to Menu");

    char exitkey = 0;
    int xmouse, ymouse;

    while(exitkey != 82 && exitkey != 114) {
        while(!kbhit())
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                xmouse = mousex();
                ymouse = mousey();
                if(xmouse >= 325 && ymouse >= 410 && xmouse <= 475 && ymouse <= 485) {
                    return 5;
                }
                if(xmouse >= 325 && ymouse >= 505 && xmouse <= 475 && ymouse <= 580) {
                    return 1;
                }

            }
        }
        exitkey = getch();
        if(exitkey == 82 || exitkey == 114) {
            return 5;
        }
    }
}

int easy()
{
    return rand() % col;
}

int medium()
{
    return rand() % col;
}

int hard()
{
    return rand() % col;
}
