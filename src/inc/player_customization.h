#ifndef PLAYER_CUSTOMIZATION_H
#define PLAYER_CUSTOMIZATION_H

#include "game_ui.h"

typedef struct 
{
	text_t* player_1_text;
	text_t* player_2_text;
	text_t* play_1_text;
	text_t* play_2_text;
	text_t* left_arrow_left;
	text_t* left_arrow_right;
	text_t* right_arrow_left;
	text_t* right_arrow_right;
	paddle_t* player_1_paddle;
	paddle_t* player_2_paddle;

	int player_1_iter;
	int player_2_iter;

	int player_1_is_ready;
	int player_2_is_ready;

	text_t* loading_txt;
}
ui_t1;

void initialize_player_customization(void);

void initialize_demonstration_paddles(void);

void render_player_customization(void);

void render_demonstration_paddle(paddle_t* paddle, int player_iter);

extern ui_t1 pc_ui;
#endif
