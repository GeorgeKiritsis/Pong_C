#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "inc/loading.h"
#include "inc/utils.h"
#include "inc/player_customization.h"
#include "inc/state.h"
#include "inc/colors.h"
#include "inc/game_ui.h"

ui_t1 pc_ui;
ui_t2 loading_ui;

void initialize_player_customization(void)
{
	pc_ui.player_1_text = initialize_3d_text
			(TTF_OpenFont(BMP_FONT, 95),
			 WHITE,
			 SHADOW_GRAY,
			 "PLAYER 1",
			 0,
			 0,
			 NONE
			);
	
	pc_ui.player_1_text->text_x_pos =  CENTERED_LEFT_HALF_X(pc_ui.player_1_text->text_width);
    	pc_ui.player_1_text->text_y_pos = (HEIGHT + pc_ui.player_1_text->text_height) / 2 - 350; 
	pc_ui.player_1_iter = 0;

	pc_ui.play_1_text = initialize_3d_text
			(TTF_OpenFont(BMP_FONT, 60),
			 BRIGHT_YELLOW,
			 SHADOW_GRAY,
			 "PRESS [1] TO PLAY",
			 0,
			 0,
			 BOBBING
			);

	pc_ui.play_1_text->text_x_pos = CENTERED_LEFT_HALF_X(pc_ui.play_1_text->text_width) ;
	pc_ui.play_1_text->text_y_pos += pc_ui.play_1_text->text_height + 1000;

	pc_ui.left_arrow_left = initialize_3d_text
			(TTF_OpenFont(BMP_FONT, 90),
			 WHITE,
			 SHADOW_GRAY,
			 "<",
			 0,
			 0,
			 NONE
			);

	pc_ui.left_arrow_left->text_x_pos = pc_ui.play_1_text->text_x_pos;
	pc_ui.left_arrow_left->text_y_pos = 500;

	pc_ui.left_arrow_right = initialize_3d_text
			(TTF_OpenFont(BMP_FONT, 90),
			 WHITE,
			 SHADOW_GRAY,
			 ">",
			 0,
			 0,
			 NONE
			);


	pc_ui.left_arrow_right->text_x_pos = pc_ui.play_1_text->text_x_pos + pc_ui.play_1_text->text_width - pc_ui.left_arrow_left->text_width;
	pc_ui.left_arrow_right->text_y_pos = 500;

	pc_ui.player_2_text = initialize_3d_text
			(TTF_OpenFont(BMP_FONT, 95),
			 WHITE,
			 SHADOW_GRAY,
			 "PLAYER 2",
			 0,
			 0,
			 NONE
			);

    	pc_ui.player_2_text->text_x_pos = CENTERED_RIGHT_HALF_X(pc_ui.player_2_text->text_width);
	pc_ui.player_2_text->text_y_pos = (HEIGHT + pc_ui.player_2_text->text_height) / 2 - 350;
	pc_ui.player_2_iter = 0;
	
	pc_ui.play_2_text = initialize_3d_text
			(TTF_OpenFont(BMP_FONT, 60),
			 BRIGHT_YELLOW,
			 SHADOW_GRAY,
			 "PRESS [2] TO PLAY",
			 0,
			 0,
			 BOBBING
			);

	pc_ui.play_2_text->text_x_pos = CENTERED_RIGHT_HALF_X(pc_ui.play_2_text->text_width) ;	
	pc_ui.play_2_text->text_y_pos = pc_ui.play_2_text->text_height + 1000 ;
	
	pc_ui.right_arrow_left = initialize_3d_text
			(TTF_OpenFont(BMP_FONT, 90),
			 WHITE,
			 SHADOW_GRAY,
			 "<",
			 0,
			 0,
			 NONE
			 
			);

	pc_ui.right_arrow_left->text_x_pos = pc_ui.play_2_text->text_x_pos ;	
	pc_ui.right_arrow_left->text_y_pos = 500;

	pc_ui.right_arrow_right = initialize_3d_text
			(TTF_OpenFont(BMP_FONT, 90),
			 WHITE,
			 SHADOW_GRAY,
			 ">",
			 0,
			 0,
			 NONE
			);

	pc_ui.right_arrow_right->text_x_pos = pc_ui.play_2_text->text_x_pos + pc_ui.play_2_text->text_width - pc_ui.right_arrow_right->text_width ;
	pc_ui.right_arrow_right->text_y_pos = 500;
	
	pc_ui.player_1_paddle = initialize_paddle(
				WHITE,
				SHADOW_GRAY,
				100,
				600,
				1000,
				300	
				);

	pc_ui.player_1_paddle->paddle_x_pos = CENTERED_LEFT_HALF_X(pc_ui.player_1_paddle->paddle_width);

	pc_ui.player_2_paddle = initialize_paddle(		
			    	WHITE,
				SHADOW_GRAY,
				100,
				600,
				1000,
				300
				);
	
	pc_ui.player_2_paddle->paddle_x_pos = CENTERED_RIGHT_HALF_X(pc_ui.player_2_paddle->paddle_width) - pc_ui.player_2_paddle->paddle_width / 12;
	
}



void render_player_customization(void)
{
	render_3d_text(pc_ui.player_1_text);
	render_3d_text(pc_ui.player_2_text);
	render_3d_text(pc_ui.play_1_text);
	render_3d_text(pc_ui.play_2_text);

	render_hoverable_button(pc_ui.left_arrow_left, state.mouse_x_pos, state.mouse_y_pos);
	render_hoverable_button(pc_ui.left_arrow_right, state.mouse_x_pos, state.mouse_y_pos);
	render_hoverable_button(pc_ui.right_arrow_left, state.mouse_x_pos, state.mouse_y_pos);
	render_hoverable_button(pc_ui.right_arrow_right, state.mouse_x_pos, state.mouse_y_pos);

	render_demonstration_paddle(pc_ui.player_1_paddle, pc_ui.player_1_iter);
	render_demonstration_paddle(pc_ui.player_2_paddle, pc_ui.player_2_iter);
}

