#include "game.h"

int main()
{
    printf("Please enter the name of the players:\n");
    printf("(Press two enters if there is only one player!)\n");
    gets(username1);
    gets(username2);
    initwindow(WIDTH,HEIGHT);
    PlaySound("theme.wav", NULL, SND_ASYNC);
    char s[100];
    int clr[9] = {};
    while(true) {
        if(state == 1) {
            state = mainmenu();
        }
        else if(state == 2) {
            state = difficulty();
        }
        else if(state == 3) {
            state = options();
        }
        else if(state == 4) {
            state = highscore();
        }
        else if(state == 5){
            state = game();
        }
        else if(state == 0) {
            return 0;
        }
    }
    return 0;
}
