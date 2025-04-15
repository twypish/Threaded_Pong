// ***********************************************************************************************
// * Project     : Final project 
// * File        : scoreboard.c
// * Purpose     : Implements the functions for the scoreboard that is displayed
// * Contributor : Robert Myers Jr.
// ***********************************************************************************************
#include <ncurses.h>
#include <stdio.h>
#include "scoreboard.h"

void update_scoreboard(scoreboard_t *scoreboard)
{
	char score_str[scoreboard->width];
	snprintf(score_str, scoreboard->width, "%i - %i", scoreboard->left_score, scoreboard->right_score);
	mvaddstr(scoreboard->y + scoreboard->height/2, scoreboard->x + scoreboard->width/2, score_str);		
	getch();
	wrefresh(scoreboard->scoreboard_window);
}

scoreboard_t init_scoreboard(int x, int y, int width, int height)
{
	scoreboard_t scoreboard = {x, y, width, height, 0, 0, newwin(height, width, y, x)};
	box(scoreboard.scoreboard_window, ACS_VLINE, ACS_HLINE);
	update_scoreboard(&scoreboard);
	return scoreboard;
}

void destroy_scoreboard(scoreboard_t *score_board)
{
	wclear(score_board->scoreboard_window);
	delwin(score_board->scoreboard_window);
}

void add_point(int is_left, scoreboard_t *score_board)
{
	if (is_left)
	{
		score_board->left_score++;
	}
	else
	{
		score_board->right_score++;
	}
	update_scoreboard(score_board);
}
