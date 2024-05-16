#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "inc/utils.h"
#include "inc/state.h"
#include "inc/game_ui.h"
#include "inc/menu.h"
#include "inc/colors.h"

ui_t menu_ui;

void initialize_menu(void)
{	
		menu_ui.title_text = initialize_3d_text
			(TTF_OpenFont(BMP_FONT, 150),
			 LIGHT_GREEN, 
			 SHADOW_GRAY, 
			 "PONG", 
			 0,
			 0,
			 NONE
			 );
		
		menu_ui.title_text->text_x_pos =  CENTERED(menu_ui.title_text->text_width);
		menu_ui.title_text->text_y_pos = (HEIGHT + menu_ui.title_text->text_height) / 4;

		menu_ui.version_text = initialize_3d_text
			(TTF_OpenFont(BMP_FONT, 50),
			 WHITE, 
			 SHADOW_GRAY, 
			 "V 0.0.2", 
			 menu_ui.title_text->text_x_pos + 435,
			 menu_ui.title_text->text_y_pos + 120,
		         NONE
			 );

		menu_ui.play_text = initialize_3d_text
			(TTF_OpenFont(BMP_FONT, 60),
			 BRIGHT_YELLOW, 
			 SHADOW_GRAY, 
			 "PRESS ANY KEY TO CONTINUE", 
			 0,
			 0,
			 BOBBING
			 );
			
		menu_ui.play_text->text_x_pos = CENTERED(menu_ui.play_text->text_width); 
		menu_ui.play_text->text_y_pos = (HEIGHT + menu_ui.play_text->text_height )/2 + 800;
}

void render_menu(void)
{
	render_3d_text(menu_ui.title_text);
	render_3d_text(menu_ui.version_text);
	render_3d_text(menu_ui.play_text);
}
