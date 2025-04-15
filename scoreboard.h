// ***********************************************************************************************
// * Project     : Final project 
// * File        : scoreboard.c
// * Purpose     : Function prototypes and struct for scoreboard
// * Contributor : Robert Myers Jr.
// ***********************************************************************************************
#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <ncurses.h>
typedef struct 
{
	int x;
	int y;
	int width;
	int height;
	int left_score;
	int right_score;
	WINDOW *scoreboard_window;
} scoreboard_t;

// ***********************************************************************************************
// * Creates a score_board and it's window
// *
// * param x            : The x cordinate for the window
// * param y            : The y cordinate for the window
// * param height       : The height for the window
// * param width        : The width for the window
// * return score_board : The newly created score board
// ***********************************************************************************************
scoreboard_t init_scoreboard(int x, int y, int width, int height);

// ***********************************************************************************************
// * Destorys the score board and frees the window assicoated with it.
// *
// * param score_board : The score_board being cleaned
// ***********************************************************************************************
void destroy_scoreboard(scoreboard_t *score_board);


// ***********************************************************************************************
// * Add a point
// *
// * param is_left : boolean value for termining which side gets the point
// ***********************************************************************************************
void add_point(int is_left, scoreboard_t *score_board);
#endif // SCOREBOARD_H
