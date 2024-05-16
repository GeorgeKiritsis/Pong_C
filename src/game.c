#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>
#include "inc/game_ui.h"
#include "inc/player_customization.h"
#include "inc/utils.h"
#include "inc/game.h"
#include "inc/colors.h"

ui_t3 game_ui;

void initialize_game(void)
{
		game_ui.player_1_score = initialize_3d_text(
			TTF_OpenFont(BMP_FONT, 120),
			WHITE,
			SHADOW_GRAY,
			"0",
			0,
			50,
			NONE
		);

		game_ui.player_1_score->text_x_pos = CENTERED_LEFT_HALF_X(game_ui.player_1_score->text_width);

		game_ui.player_2_score = initialize_3d_text(
			TTF_OpenFont(BMP_FONT, 120),
			WHITE,
			SHADOW_GRAY,
			"0",
			0,
			50,
			NONE
		);
		
		game_ui.player_2_score->text_x_pos = CENTERED_RIGHT_HALF_X(game_ui.player_2_score->text_width);
		
		game_ui.player_1 = initialize_paddle(
				WHITE,
				SHADOW_GRAY,
				50,
				500,
				200,
				400
				);

		game_ui.player_1->paddle_x_pos = CENTERED_LEFT_HALF_X(game_ui.player_1->paddle_width) - 550;
		game_ui.player_1->paddle_y_pos = CENTERED_VERTICALLY(game_ui.player_1->paddle_height);


		game_ui.player_2 = initialize_paddle(
				WHITE,
				SHADOW_GRAY,
				50,
				500,
				200,
				400
				);
		game_ui.player_2->paddle_x_pos = CENTERED_RIGHT_HALF_X(game_ui.player_2->paddle_width) + 550;
		game_ui.player_2->paddle_y_pos = CENTERED_VERTICALLY(game_ui.player_2->paddle_height);

		
		game_ui.game_ball = initialize_paddle(
				WHITE,
				SHADOW_GRAY,
				30,
				30,
				0,
				0
				);
		game_ui.game_ball->paddle_x_pos = CENTERED(game_ui.game_ball->paddle_width);
		game_ui.game_ball->paddle_y_pos = CENTERED_VERTICALLY(game_ui.game_ball->paddle_height);
				


}


void render_game(void)
{
	if(!game_ui.player_1_score)
	{
		initialize_game();
	}
	
	render_3d_text(game_ui.player_1_score);
	render_3d_text(game_ui.player_2_score);

	render_demonstration_paddle(game_ui.player_1, pc_ui.player_1_iter);
	render_demonstration_paddle(game_ui.player_2, pc_ui.player_2_iter);
	render_demonstration_paddle(game_ui.game_ball, 0);
}
