// ***********************************************************************************************
// * Project     : Final project 
// * File        : field.c
// * Purpose     : Implements the methods for the field
// * Contributor : Robert Myers Jr.
// ***********************************************************************************************
#include "field.h"
#include <curses.h>

field_t init_field(scoreboard_t *scoreboard, int height)
{
	field_t field;
	// Add offsets to the cordinates
	field.x = scoreboard->x;
	field.y = scoreboard->y + scoreboard->height;
	field.width = scoreboard->width;
	field.height = height;
	field.field_window = newwin(field.height, field.width, field.y, field.x);
	box(field.field_window, ACS_VLINE, ACS_HLINE);
	wrefresh(field.field_window);
	return field;
}
void destroy_field(field_t *field)
{
	wclear(field->field_window);
	delwin(field->field_window);

}
