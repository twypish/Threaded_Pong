// ***********************************************************************************************
// * Project     : Final project 
// * File        : paddle.h
// * Purpose     : Declares the struct and helper methods to use with paddles
// * Contributor : Robert Myers Jr.
// ***********************************************************************************************
#ifndef PADDLE_H
#define PADDLE_H
#include "field.h"
typedef struct
{
	int x;
	int y;
	int y_upper;
	int y_lower;
	int is_left;
	int ralley;
	int color;
} paddle_t;

// ***********************************************************************************************
// * Sets up the paddles in the field
// *
// * param paddle  : The paddle that is being setup 
// * param field   : The field that is used to set the bounds of the paddle
// * param height  : The height of the window
// * param width   : The width of the window
// * param is_left : Boolean value for determining which side to set up the paddle
// * param color : Boolean value for determining which side to set up the paddle
// ***********************************************************************************************
void setup_paddle(paddle_t *paddle, field_t *field, int is_left, int color);


// ***********************************************************************************************
// * Moves a paddle up one unit
// *
// * param paddle : The paddle that is being moved up
// ***********************************************************************************************
void move_paddle_up(paddle_t *paddle);


// ***********************************************************************************************
// * Moves a paddle down one unit
// *
// * param paddle : The paddle that is being moved up
// * param height : The height of the window
// ***********************************************************************************************
void move_paddle_down(paddle_t *paddle);

// ***********************************************************************************************
// * Draws the paddle
// *
// * param paddle : The paddle that is being redrawn
// ***********************************************************************************************
void draw_paddle(paddle_t *paddle);
#endif // PADDLE_H
