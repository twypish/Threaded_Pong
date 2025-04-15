#ifndef GAME_H
#define GAME_H
#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>
#include "field.h"
#include "paddle.h"
#include "scoreboard.h"
#include "field.h"
#include "ball.h"
#include "menu.h"

typedef struct
{
	int ball_speed;
	int winning_num;
	int *game_state;
	paddle_t *left_paddle;
	paddle_t *right_paddle;
	field_t *field;
	scoreboard_t *scoreboard;
} game_info_t;

// ************************************************************************************************
// * Starts the game
// ************************************************************************************************
void start_game(gameConfig_t *gameConfig);
#endif // GAME_H
