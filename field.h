// ***********************************************************************************************
// * Project     : Final project 
// * File        : field.h
// * Purpose     : Declares the methods and struct for the field
// * Contributor : Robert Myers Jr.
// ***********************************************************************************************
#ifndef FIELD_H
#define FIELD_H
#include <ncurses.h>
#include "scoreboard.h"
typedef struct 
{
	int x;
	int y;
	int width;
	int height;
	WINDOW *field_window;
} field_t;

// ***********************************************************************************************
// * Creates a field and it's window
// *
// * param score_board  : The scoreboard that is used to setup the field
// * return field       : The newly created field
// ***********************************************************************************************
field_t init_field(scoreboard_t *scoreboard, int height);

// ***********************************************************************************************
// * Destorys the score board and frees the window assicoated with it.
// *
// * param field : The field being cleaned
// ***********************************************************************************************
void destroy_field(field_t *field);


#endif // FIELD_H
