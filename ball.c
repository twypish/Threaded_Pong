// ***********************************************************************************************
// * Project     : Final project 
// * File        : ball.c
// * Purpose     : Implements the functions for the ball
// * Contributor : Robert Myers Jr.
// ***********************************************************************************************
#include <stdlib.h>
#include <ncurses.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include "ball.h"
#include "field.h"
#include "scoreboard.h"

ball_t setup_ball(field_t *field)
{
	ball_t ball;
	// center ball
	ball.y = field->height/2 + field->y;
	ball.x = field->width/2;
	ball.direction = 1;
	ball.magintude = 1;
	mvaddch(ball.y, ball.x, '*');
	return ball;
}

void adjust_ball(ball_t *ball, paddle_t *paddle)
{
	srand(time(NULL));
	int angle = (rand()%2)+1;
	ball->direction = angle;
	ball->magintude *= -1;
	ball->x = paddle->is_left ? ball->x + 2 : ball->x - 2;
	paddle->ralley = 1;
}

void reset_ball(ball_t *ball, field_t *field)
{
	ball->y = field->height/2 + field->y;
	ball->x = field->width/2;
}

// ***********************************************************************************************
// * Checks up the collison
// *
// * param ball : The ball that the ball will check
// ***********************************************************************************************
int check_collision(ball_t *ball, paddle_t *paddle, field_t *field)
{
	int xcord = (int)ball->x;
	int ycord = (int)ball->y;
	// Check if a collision needs to be checked with paddle
	if (paddle->x == xcord)
	{
		int distance_from_paddle_center = paddle->y - ycord;
		// Ball hit the paddle
		if (distance_from_paddle_center <= 1 && -1 <= distance_from_paddle_center) 
		{
			adjust_ball(ball, paddle);
		}
	}
	// Check if the north wall is hit
	if (ycord == field->y + 1 || ycord == field->height + field->y - 2) 
	{
		// The direction state has it's ups and downs 2 apart
		ball->direction *= -1;
	}
	else if (xcord == field->width + field->x - 1) 
	{
		return 1;	
	}
	else if (xcord == field->x) 
	{
		return -1;	
	}
	return 0;
}
void remove_space_around_ball(ball_t *ball, field_t *field, paddle_t *left_paddle, paddle_t *right_paddle)
{
	int ycord = (int)ball->y;
	int xcord = (int)ball->x;

	for (int row = -1; row<2; row++) {
		if ((ycord + row != field->y) && (ycord + row != field->y+field->height-1))
		{
			for (int col = -1; col<2; col++) 
			{
				if (xcord + col > left_paddle->x && xcord+col < right_paddle->x)
				{
					mvaddch(ycord + row, xcord + col, ' ');
				}
			}
		}

	}
}

int progress_ball(ball_t *ball, paddle_t *left_paddle, paddle_t *right_paddle, field_t *field, scoreboard_t *score_board)
{
	mvaddch(ball->y, ball->x, ' ');
	remove_space_around_ball(ball, field, left_paddle, right_paddle);
	paddle_t *receiving_paddle;
	receiving_paddle = ball->magintude < 0 ? left_paddle : right_paddle;

	double angle = 0;
	switch(ball->direction)
	{
		case 1:
			angle = -30;
			break;
		case 2:
			angle = -45;
			break;
		case -1:
			angle = 30;
			break;
		case -2:
			angle = 45;
			break;
	}
	double angle_in_radians = (angle)*(M_PI/180);

	ball->x = ball->x + (ball->magintude*cos(angle_in_radians));
	ball->y = ball->y + (ball->magintude*sin(angle_in_radians));

	int goal = check_collision(ball, receiving_paddle, field);
	if (goal != 0)
	{
		reset_ball(ball, field);
		add_point(goal == 1, score_board);		
	}
	mvaddch((int)ball->y, (int)ball->x, '*');
	return goal;
}

