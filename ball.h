// ***********************************************************************************************
// * Project     : Final project 
// * File        : ball.h
// * Purpose     : declares the ball struct and functions
// * Contributor : Robert Myers Jr.
// ***********************************************************************************************

#ifndef BALL_H
#define BALL_H
#define DEGREES30 30
#define DEGREES45 45
#define DEGREES60 60
#include "field.h"
#include "paddle.h"
#include "scoreboard.h"
typedef struct 
{
	double x;
	double y;
	int magintude;
	int direction;
} ball_t;

// ***********************************************************************************************
// * Setups up the ball
// *
// * param field : The field that the ball will start up at
// ***********************************************************************************************
ball_t setup_ball(field_t *field);

// ***********************************************************************************************
// * Reset the ball
// *
// * param ball  : The ball that is being reset
// * param field : The field that the ball will start up at
// ***********************************************************************************************
void reset_ball(ball_t *ball, field_t *field);

// ***********************************************************************************************
// * Progresses the ball one unit
// *
// * param ball         : The ball that is being moved
// * param left_paddle  : The left paddle
// * param right_paddle : The left paddle
// * param field        : The field
// ***********************************************************************************************
int progress_ball(ball_t *ball, paddle_t *left_paddle, paddle_t *right_paddle, 
		field_t *field, scoreboard_t *scoreboad);
#endif //BALL_H
