/**
 * CPE 2600
 * Robert M. and Troy W.-P.
 * Final lab
 * This holds all the creation of the menus and 
 * changing of the settings for the game
 * 
*/

#include <ncurses.h>
#include <string.h>
#include "menu.h"

//game config
static gameConfig_t config = {1, 2, 3, 1, 4, -1};

/*
Creates the game menu and returns the 
game config settings struct
*/
gameConfig_t mainMenu(){
	WINDOW * mainMenu = newwin(6, 75, 20, 5);
	box(mainMenu, 0 , 0);
	wrefresh(mainMenu);

	//Alows for keyboard use
	keypad(mainMenu, true);

	char* choices[4] = {"Start", "Settings", "Help", "Quit Game"};
	int key_press = 0;
	int highlight = 0;

	while(config.choice != 0 && config.choice != 3){
		if(config.choice == 2){
			helpScreen();
			box(mainMenu, 0 , 0);
			wrefresh(mainMenu);
			config.choice = -1;
		} else if(config.choice == 1){
			settingsScreen();
			box(mainMenu, 0 , 0);
			refresh();
			wrefresh(mainMenu);
			config.choice = -1;
		}


		for(int i = 0; i < 4; i++){
			if(i == highlight){
				wattron(mainMenu, A_REVERSE);
			}
			mvwprintw(mainMenu, i+1, 1, "%s", choices[i]);
			wattroff(mainMenu, A_REVERSE);}

		key_press = wgetch(mainMenu);
		switch (key_press)
		{
			case KEY_UP:
				highlight--;
				if(highlight == -1){
					highlight = 0;
				}
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight == 4){
					highlight = 3;
				}
				break;
			case 10:
				config.choice = highlight;
				break;
			default:
				break;
		}

	}
	config.choice = highlight;
	werase(mainMenu);
	wrefresh(mainMenu);
	delwin(mainMenu);
	endwin();
	return config;
}

/*
Help screen prints out a screen that explains the way to 
use the simple menus and game
*/
void helpScreen() {
	WINDOW *helpMenu = newwin(12, 85, 20, 5);
	box(helpMenu, 0, 0);
	keypad(helpMenu, true);

	int key_press = 0;
	int window_width = getmaxx(helpMenu);

	mvwprintw(helpMenu, 0, (window_width - 10) / 2, "HELP MENU");
	mvwprintw(helpMenu, 1, 1, "To start play, highlight 'Start' and hit the Enter key.");
	mvwprintw(helpMenu, 2, 1, "To quit the game, highlight 'Quit' and hit the Enter key to leave the game.");
	mvwprintw(helpMenu, 3, 1, "Highlight 'Settings' and hit Enter to open settings.");
	mvwprintw(helpMenu, 4, 1, "In settings, you can change the following:");
	mvwprintw(helpMenu, 5, 3, "- Player colors");
	mvwprintw(helpMenu, 6, 3, "- Winning score");
	mvwprintw(helpMenu, 7, 3, "- Ball starting speed");

	mvwprintw(helpMenu, 10, 1, "Press Enter to exit the Help Menu.");
	wrefresh(helpMenu);

	while (key_press != 10) {
		key_press = wgetch(helpMenu);
	}
	werase(helpMenu);
	wrefresh(helpMenu);
	delwin(helpMenu);
	endwin();
}

/*
Setting screen allows use to change the game
this changed the config struct to allow 
for reuse.
*/
void settingsScreen(){
	WINDOW *settingMenu = newwin(10, 90, 20, 5);
	keypad(settingMenu, true);

	int key_press = 0;
	int choice = -1;
	int highlight = 0;

	char* choices[6] = {"Num Players", "Ball Speed", "Winning Num", "Player one color", "Player two color",
		"Hit Enter key to exit setting screen and arrows keys to change highlighted settings"};

	char* colors[8] = {"Black", "Red", "Green", "Yellow", "Blue", "Magenta", "Cyan", "White"};

	while(choice == -1){
		start_color();
		if(config.player1Color != 7){
			// Init color (name as INT, text color, highlight color)
			init_pair(1, COLOR_WHITE, config.player1Color);
		}else {
			init_pair(1, COLOR_BLACK, config.player1Color);
		}

		if(config.player2Color != 7)
			init_pair(2, COLOR_WHITE, config.player2Color);
		else {
			init_pair(2, COLOR_BLACK, config.player2Color);
		}
		werase(settingMenu);
		wrefresh(settingMenu);
		box(settingMenu, 0, 0);
		int window_width = getmaxx(settingMenu);
		mvwprintw(settingMenu, 0, (window_width - 10) / 2, "Settings MENU");
		for(int i = 0; i < 6; i++){
			if(i == highlight){
				wattron(settingMenu, A_REVERSE);
			}
			if(i == 0){
				mvwprintw(settingMenu, i+1, 1, "%s <%i>", choices[i], config.numPlayers);
				wattroff(settingMenu, A_REVERSE);
			} else if(i == 1){
				mvwprintw(settingMenu, i+1, 1, "%s <%i>", choices[i], config.ballSpeed);
				wattroff(settingMenu, A_REVERSE);
			} else if(i == 2){
				mvwprintw(settingMenu, i+1, 1, "%s <%i>", choices[i], config.winningNum);
				wattroff(settingMenu, A_REVERSE);
			} else if (i == 3) {
				mvwprintw(settingMenu, i+1, 1, "%s", choices[i]);
				wattron(settingMenu, COLOR_PAIR(1));
				mvwprintw(settingMenu, i+1, 18,"<%s>", colors[config.player1Color]);
				wattroff(settingMenu, COLOR_PAIR(1));
				wattroff(settingMenu, A_REVERSE);

			} else if (i == 4) {
				mvwprintw(settingMenu, i+1, 1, "%s", choices[i]);
				wattron(settingMenu, COLOR_PAIR(2));
				mvwprintw(settingMenu, i+1, 18, "<%s>", colors[config.player2Color]);
				wattroff(settingMenu, COLOR_PAIR(2));
				wattroff(settingMenu, A_REVERSE);
			} else {
				mvwprintw(settingMenu, i+1, 1, "%s", choices[i]);
				wattroff(settingMenu, A_REVERSE);
			}
		}

		key_press = wgetch(settingMenu);
		switch (key_press)
		{
			case KEY_UP:
				highlight--;
				if(highlight == -1){
					highlight = 0;
				}
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight == 5){
					highlight = 4;
				}
				break;
			case KEY_LEFT:
				if (highlight == 1){
					config.ballSpeed--;
					if(config.ballSpeed == 0){
						config.ballSpeed = 1;
					}
				}else if (highlight == 2){
					config.winningNum--;
					if(config.winningNum == 0){
						config.winningNum = 1;
					}
				}else if (highlight == 3){
					config.player1Color--;
					if(config.player1Color == -1){
						config.player1Color =0;
					}
				}else if (highlight == 4){
					config.player2Color--;
					if(config.player2Color == -1){
						config.player2Color = 0;
					}
				}
				break;
			case KEY_RIGHT:
				if (highlight == 1){
					config.ballSpeed++;
					if(config.ballSpeed == 11){
						config.ballSpeed = 10;
					}
				}else if (highlight == 2){
					config.winningNum++;
					if(config.winningNum == 11){
						config.winningNum = 10;
					}
				}else if (highlight == 3){
					config.player1Color++;
					if(config.player1Color == 8){
						config.player1Color = 7;
					}
				}else if (highlight == 4){
					config.player2Color++;
					if(config.player2Color == 8){
						config.player2Color = 7;
					}
				}
				break;
			case 10:
				choice = 0;
				break;
			default:
				break;
		}
	}
	werase(settingMenu);
	wrefresh(settingMenu);
	delwin(settingMenu);
	endwin();
}

/*
All set up for the pause menu screen
returns an int with the choice made by the user
*/
int pauseMenu(){
	WINDOW * pauseMenu = newwin(6, 75, 20, 5);
	box(pauseMenu, 0 , 0);
	keypad(pauseMenu, true);

	wrefresh(pauseMenu);
	char* choices[3] = {"Quit to Main Menu", "Continue", "Hit Enter to select Choice"};
	int highlight = 0;
	int key_press = -1;
	int choice = -1;
	while(choice == -1){
		for(int i = 0; i < 3; i++){
			if(i == highlight){
				wattron(pauseMenu, A_REVERSE);
			}
			mvwprintw(pauseMenu, i+1, 1, "%s", choices[i]);
			wattroff(pauseMenu, A_REVERSE);}

		key_press = wgetch(pauseMenu);
		switch (key_press)
		{
			case KEY_UP:
				highlight--;
				if(highlight == -1){
					highlight = 0;
				}
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight == 2){
					highlight = 1;
				}
				break;
			case 10:
				choice = highlight;
				if(highlight == 0){
					config.choice = -1;
				}
				break;
			default:
				break;
		}
	}

	werase(pauseMenu);
	wrefresh(pauseMenu);
	delwin(pauseMenu);
	endwin();

	return choice;
}


gameConfig_t endScreen(int winningPlayer){
	WINDOW * endMenu = newwin(8, 75, 20, 5);
	box(endMenu, 0 , 0);
	wrefresh(endMenu);
	keypad(endMenu, true);
	char* choices[4] = {"Winning Player is Player", "Play Again", "Quit to Main Menu", "Hit Enter to make selection" };
	int highlight = 1;
	int key_press = -1;
	int choice = 1;
	while(choice){
		for(int i = 0; i < 4; i++){
			if(i == highlight){
				wattron(endMenu, A_REVERSE);
			}
			if(i == 0)
			{
				winningPlayer = winningPlayer == 1 ? 1 : 2;
				mvwprintw(endMenu, i+1, 1, "%s %i", choices[i], (winningPlayer));
				wattroff(endMenu, A_REVERSE);
			} else {
				mvwprintw(endMenu, i+1, 1, "%s", choices[i]);
				wattroff(endMenu, A_REVERSE);
			}

		}

		key_press = wgetch(endMenu);
		switch (key_press)
		{
			case KEY_UP:
				highlight--;
				if(highlight == 0){
					highlight = 1;
				}
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight == 3){
					highlight = 2;
				}
				break;
			case 10:
				if(highlight == 1){
					config.choice = 0;
				} else {
					config.choice = -1;
				}
				choice = 0;
				break;
			default:
				break;
		}

	}
	werase(endMenu);
	wrefresh(endMenu);
	delwin(endMenu);
	endwin();
	return config;
}

