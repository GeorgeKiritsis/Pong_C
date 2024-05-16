#ifndef GAME_H
#define GAME_H

#include "game_ui.h"

typedef struct 
{
	text_t* player_1_score;
	text_t* player_2_score;

	paddle_t* player_1;
	paddle_t* player_2;
	paddle_t* game_ball;

}
ui_t3;

void initialize_game(void);

void render_game(void);

extern ui_t3 game_ui;
#endif
