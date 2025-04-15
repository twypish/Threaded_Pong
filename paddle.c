// ***********************************************************************************************
// * Project     : Final project 
// * File        : paddle.c
// * Purpose     : Implements the methods for the paddle
// * Contributor : Robert Myers Jr. and Troy W.
// ***********************************************************************************************
#include <ncurses.h>
#include "paddle.h"

void draw_paddle(paddle_t *paddle)
{
	int color_index = paddle->is_left + 1;
	start_color();
	init_pair(color_index, paddle->color, COLOR_BLACK);
	attron(COLOR_PAIR(color_index));
	mvaddch(paddle->y, paddle->x, '#');
	mvaddch(paddle->y + 1, paddle->x, '#');
	mvaddch(paddle->y - 1, paddle->x, '#');
	attroff(COLOR_PAIR(color_index));
}

void setup_paddle(paddle_t *paddle, field_t *field, int is_left, int color)
{
	paddle->y = field->y + field->height/2;
	if (is_left) 
	{
		paddle->x = field->x + 2;
	}
	else 
	{
		paddle->x = field->width - 3;
	}
	paddle->is_left = is_left;
	paddle->y_upper = field->y+2;
	paddle->y_lower = field->y+field->height-3;
	paddle->color = color;
	paddle->ralley = 0;
	draw_paddle(paddle);
}

void move_paddle_up(paddle_t *paddle)
{
	if(paddle->y > paddle->y_upper) 
	{ 
		mvaddch(paddle->y+1, paddle->x, ' ');
		paddle->y--;
		draw_paddle(paddle);
	} 
}

void move_paddle_down(paddle_t *paddle)
{
	if(paddle->y < paddle->y_lower) 
	{
		mvaddch(paddle->y-1, paddle->x, ' ');
		paddle->y++;
		draw_paddle(paddle);
	} 
}
