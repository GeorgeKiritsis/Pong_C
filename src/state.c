#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "inc/state.h"
#include "inc/utils.h"
#include "inc/state_machine.h"
#include "inc/loading.h"
#include "inc/game_over.h"
#include "inc/game_ui.h"
#include "inc/game_settings.h"
#include "inc/player_customization.h"
#include "inc/ecs.h"
#include "inc/menu.h"
#include "inc/colors.h"
#include "inc/game.h"

state_t state;
state_e game_state;

int initialize(void)
{
	ASSERT(
		!SDL_Init(SDL_INIT_EVERYTHING),
		"Error Initializng SDL: %s.\n",
		SDL_GetError()
		);

	state.window = SDL_CreateWindow(
		"PONG V 0.0.2",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_ALLOW_HIGHDPI
		);
	
	ASSERT(
		state.window,
		"Error Creating Window: %s.\n",
		SDL_GetError()
		);
	
	state.renderer = SDL_CreateRenderer(
		state.window,
		-1,
		SDL_RENDERER_ACCELERATED|
		SDL_RENDERER_PRESENTVSYNC
		);

	ASSERT(
		state.renderer,
		"Error Creating Renderer: %s.\n",
		SDL_GetError()
		);
	
	ASSERT(
		!TTF_Init(),
		"Error Initializng SDL_TTF: %s.\n",
		TTF_GetError()
		);

	game_state = MENU;
	switch (game_state) 
	{
		case MENU:
		     	initialize_menu();
		      	break;
		case PLAYER_CUSTOMIZATION:
			cleanup_3d_text(menu_ui.title_text);	
			initialize_player_customization();
			break;
		case LOADING:
			initialize_loading();
			break;
		case GAME:
			initialize_game();
			break;
	}

	return 1;
}

void input(void)
{
	state.mouse_state = SDL_GetMouseState(&state.mouse_x_pos, &state.mouse_y_pos);
	if(game_state == LOADING && loading_ui.loading_iter >= 1.5) //TODO: CHANGE TO 4
	{
		game_state = GAME;
	}


	while(SDL_PollEvent(&state.event))
	{
		switch(state.event.type)
		{
			case SDL_QUIT:
				state.isRunning = 0;
				shutdown();
				break;
			case SDL_KEYDOWN:
				if(game_state == MENU)
				{
					game_state = PLAYER_CUSTOMIZATION;
					initialize_player_customization();
				}
				else if(game_state == PLAYER_CUSTOMIZATION)
				{

					if(state.event.key.keysym.sym == SDLK_1)
					{
						pc_ui.play_1_text->text_effects_e = SELECTED;
						pc_ui.player_1_is_ready = 1;
					}
					if(state.event.key.keysym.sym == SDLK_2)
					{
						pc_ui.play_2_text->text_effects_e = SELECTED;
						pc_ui.player_2_is_ready = 1;
					}
					if(pc_ui.player_1_is_ready && pc_ui.player_2_is_ready)
					{
						printf("Both Players Are Ready\n");
						game_state = LOADING;
					}
				}
				if(state.event.key.keysym.sym == SDLK_ESCAPE)
				{
					state.isRunning = 0;
					shutdown();
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(game_state == PLAYER_CUSTOMIZATION)
				{
					if(!pc_ui.player_1_is_ready)
					{
						if (state.event.button.button == SDL_BUTTON_LEFT && is_over_button(pc_ui.left_arrow_left, state.mouse_x_pos, state.mouse_y_pos))					
						{
							if(pc_ui.player_1_iter != 0)
							{
								pc_ui.player_1_iter--;
							}
							else 
							{
								pc_ui.player_1_iter = 8;
							}

							printf("1 Iter : %d\n", pc_ui.player_1_iter);
							apply_selected_color(pc_ui.player_1_paddle,pc_ui.player_1_iter);
						}
						if(state.event.button.button == SDL_BUTTON_LEFT && is_over_button(pc_ui.left_arrow_right, state.mouse_x_pos, state.mouse_y_pos))
						{
							if(pc_ui.player_1_iter != 8)
							{
								pc_ui.player_1_iter++;
							}
							else 
							{
								pc_ui.player_1_iter = 0;
							}

							printf("1 Iter : %d\n", pc_ui.player_1_iter);
							apply_selected_color(pc_ui.player_1_paddle, pc_ui.player_1_iter);
							
						}

					}
					if(!pc_ui.player_2_is_ready)
					{
						if(state.event.button.button == SDL_BUTTON_LEFT && is_over_button(pc_ui.right_arrow_left, state.mouse_x_pos, state.mouse_y_pos))
						{
							if(pc_ui.player_2_iter != 0)
							{
								pc_ui.player_2_iter--;
							}
							else 
							{
								pc_ui.player_2_iter = 5;
							}
							printf("2 Iter : %d\n", pc_ui.player_2_iter);
							apply_selected_color(pc_ui.player_2_paddle, pc_ui.player_2_iter);
							
						}
						if(state.event.button.button == SDL_BUTTON_LEFT && is_over_button(pc_ui.right_arrow_right, state.mouse_x_pos, state.mouse_y_pos))				
						{
							
							if(pc_ui.player_2_iter != 5)
							{
								pc_ui.player_2_iter++;
							}
							else 
							{
								pc_ui.player_2_iter = 0;
							}
							printf("2 Iter : %d\n", pc_ui.player_2_iter);
							apply_selected_color(pc_ui.player_2_paddle, pc_ui.player_2_iter);

						}

					}
				}
				break;
			}
	}
}

void setup(void)
{
	pc_ui.player_1_is_ready = 0;
	pc_ui.player_2_is_ready = 0;
	loading_ui.loading_iter = 0;
	//playeers start pos
	//ball start pos
	//ball is served
	//player score
	
	char score_1 = 0;
	char score_2 = 0;
}



void update(void)
{
	float deltaTime = (SDL_GetTicks() - state.lastFrameTime) / 1000.0;
	state.lastFrameTime = SDL_GetTicks();

}

void render(void)
{
    	SDL_SetRenderDrawColor(state.renderer, 30, 30, 30, 255);
    	SDL_RenderClear(state.renderer);

	switch (game_state)
	{
		case MENU:
			render_menu();
			break;
		case PLAYER_CUSTOMIZATION:
			render_player_customization();
			break;
		case LOADING:
			render_loading();
			break;
		case GAME:
			render_game();
			break;
	}
    	
	  
    	SDL_RenderPresent(state.renderer);
}


void shutdown(void)
{
	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
}
