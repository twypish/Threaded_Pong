#include "menu.h"
#include "game.h"
#include <curses.h>
#include <ncurses.h>
void setup_ncurses()
{
	initscr();
	refresh();
	// diable cursor
	curs_set(0);
	// diable printing key presses
	noecho();
	// Enable the arrow keys
	keypad(stdscr, true);
	// Don't wait for key presses
	nodelay(stdscr, true);
	// Start color
	start_color();
	refresh();
}

int main()
{
	setup_ncurses();
	gameConfig_t gameConfig = mainMenu();

	while(gameConfig.choice != 3)
	{
		start_game(&gameConfig);
		refresh();
		gameConfig = mainMenu();
	}
	if(gameConfig.choice == 3){
	    endwin();
	    printf("Thank you for playing our game\n");
	    return 0;
	}
}
