/**
 * CPE 2600
 * Robert M. and Troy W.-P.
 * Final lab
 * This holds all the prototypes for menu.c and the 
 * struct for the settings
 * 
*/
#ifndef MENU_H
#define MENU_H

#include <ncurses.h>

typedef struct{
    int ballSpeed;
    int numPlayers;
    int winningNum;
    int player1Color;
    int player2Color;
    int choice;
} gameConfig_t;

gameConfig_t mainMenu();
void settingsScreen();
void helpScreen();
int pauseMenu();
gameConfig_t endScreen(int winningPlayer);

#endif //MENU_H

