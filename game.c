#include <ncurses.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include "game.h"
#include "menu.h"
#include "paddle.h"
#include "scoreboard.h"

#define WIDTH 75
#define HEIGHT 20

int pause_game = 0;

void * ball_movement(void *game_info_address)
{
	game_info_t game_info = *((game_info_t*)game_info_address);
	// Setup ball
	ball_t ball = setup_ball(game_info.field);
	int *game_state = game_info.game_state;
	int speed_change_interval = 1;
	int ball_speed = game_info.ball_speed;
	int winning_num = game_info.winning_num;
	int ball_reset = 0;
	long is_winner_left = 2;

	paddle_t *right = game_info.right_paddle;
	paddle_t *left = game_info.left_paddle;

	scoreboard_t *scoreboard = game_info.scoreboard;

	while (*game_state) 
	{
		if (!pause_game)
		{
			usleep(300000 - ball_speed * (28000));
			ball_reset = progress_ball(&ball, game_info.left_paddle, game_info.right_paddle, game_info.field,
					scoreboard);
			if (ball_reset)
			{
				// set ball to default speed
				ball_speed = game_info.ball_speed;
				// check for winner
				if (scoreboard->left_score == winning_num) 
				{
					is_winner_left = 1;
					*game_state = 0;
				}
				if (scoreboard->right_score == winning_num) 
				{
					is_winner_left = 0;
					*game_state = 0;
				}
			}
			// Check if a ralley has occured
			if(right->ralley == 1 && right->ralley == left->ralley)
			{
				speed_change_interval--;
				right->ralley = 0;
				left->ralley = 0;
			}
			// increase speed after a number of rallies
			if (ball_speed < 10 && speed_change_interval == 0) 
			{
				ball_speed++;
				speed_change_interval = 1;
			}
		}
	}
	return (void *)is_winner_left;
}

void end_game(scoreboard_t *scoreboard, field_t *field)
{
	destroy_field(field);
	destroy_scoreboard(scoreboard);
}

int pause()
{
	int pause = pauseMenu();
	return pause;
}

void start_game(gameConfig_t *gameConfig) 
{
	int input;
	int game_state = 1;
	void *victor = 0;

	// Setup windows
	scoreboard_t scoreboard = init_scoreboard(0, 0, WIDTH, 5);
	field_t field = init_field(&scoreboard, 20);

	// Setup paddles
	paddle_t left_paddle;
	paddle_t right_paddle;
	setup_paddle(&left_paddle, &field, 1, gameConfig->player1Color);
	setup_paddle(&right_paddle, &field, 0, gameConfig->player2Color);
	refresh();

	// Set up ball thread
	game_info_t game_info = {gameConfig->ballSpeed, gameConfig->winningNum, &game_state, &left_paddle, &right_paddle, &field, &scoreboard};
	pthread_t ball_thread;
	pthread_create(&ball_thread, NULL, &ball_movement, (void *)(&game_info));

	// Main loop
	while (game_state)
	{
		input = getch();
		switch (input)
		{
			case 27:
				pause_game = 1;
				game_state = pause();
				redrawwin(field.field_window);
				draw_paddle(&left_paddle);
				draw_paddle(&right_paddle);
				wrefresh(field.field_window);
				pause_game = 0;
				break;
			case 'w':
				move_paddle_up(&left_paddle);
				break;
			case 's':
				move_paddle_down(&left_paddle);
				break;
			case KEY_UP:
				move_paddle_up(&right_paddle);
				break;
			case KEY_DOWN:
				move_paddle_down(&right_paddle);
				break;
		}
		refresh();
	}
	// Wait for thread and see who has the higher score
	pthread_join(ball_thread, &victor);
	long victor_result = (long)(victor);
	end_game(&scoreboard, &field);
	clear();
	endwin();
	gameConfig->choice = -1;
	if (victor_result != 2)
	{
		gameConfig_t result = endScreen((int)victor_result);
		gameConfig->choice = result.choice;
	}
}
