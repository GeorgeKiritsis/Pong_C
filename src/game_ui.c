#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include  "inc/player_customization.h"
#include <stdio.h>
#include <stdlib.h>
#include "inc/game_ui.h"
#include "inc/state.h"
#include "inc/utils.h"
#include "inc/colors.h"

text_t* initialize_3d_text(TTF_Font* font, SDL_Color text_color, SDL_Color shadow_color, char* content, int x_pos, int y_pos,enum Effects text_effect)
{
	text_t* text = malloc(sizeof(text_t));

	ASSERT(
		text,
		"Error: Failed to allocate memory for text\n"
		);

	ASSERT(
		text->font = font ,
		"Error: Failed to load font -> %s",
		TTF_GetError()
		);
	
	text->text_color = text_color;
	text->shadow_color = shadow_color;
	text->content = content;
	
	ASSERT(

		text->text_surface = TTF_RenderText_Solid(text->font, content, text->text_color),
		"Error: Failed to create text_surface -> %s",
		TTF_GetError()
		);

	if(!text->text_surface)
	{
		SDL_FreeSurface(text->text_surface);
		free(text);

		return NULL;
	}

	text->shadow_surface = TTF_RenderText_Solid(text->font, content, text->shadow_color);
	ASSERT(
		text->shadow_surface = TTF_RenderText_Solid(text->font, content, text->shadow_color),
		"Error: Failed to create shadow_surface ->  %s",
		TTF_GetError()
		);
	if(!text->shadow_surface)
	{
		SDL_FreeSurface(text->shadow_surface);
		free(text);

		return NULL;
	}

	ASSERT(
		text->text_texture = SDL_CreateTextureFromSurface(state.renderer, text->text_surface),
		"Error: Failed to create text_texture -> %s",
		SDL_GetError()
		);

	if(!text->text_texture)
	{
		SDL_DestroyTexture(text->text_texture);
		free(text);

		return NULL;
	}

	text->shadow_texture = SDL_CreateTextureFromSurface(state.renderer, text->shadow_surface);
	ASSERT(
		text->shadow_texture = SDL_CreateTextureFromSurface(state.renderer, text->shadow_surface),
		"Error: Failed to create shadow_texture -> %s",
		SDL_GetError()
		);

	if(!text->shadow_texture)
	{
		SDL_DestroyTexture(text->shadow_texture);
		free(text);

		return NULL;
	}

	text->text_width = 0;
	text->text_height = 0;
	text->text_x_pos = x_pos;
	text->text_y_pos = y_pos;

	SDL_QueryTexture(text->text_texture, NULL, NULL, &text->text_width, &text->text_height);
	SDL_QueryTexture(text->shadow_texture, NULL, NULL, &text->text_width, &text->text_height);
	
	text->text_effects_e = text_effect;
	return text;
}

SDL_Color apply_selected_color(paddle_t* paddle, int player_iter)
{
    switch (player_iter)
    {
        case 0:
            paddle->main_color = WHITE; 
            break;
        case 1:
            paddle->main_color = COLOR_1; 
            break;
        case 2:
            paddle->main_color = COLOR_2;  
	    break;
        case 3:
            paddle->main_color = COLOR_3;  
            break;
        case 4:
            paddle->main_color = COLOR_4;   
	    break;
        case 5:
            paddle->main_color = COLOR_5;  
	    break;
	case 6:
	    paddle->main_color = COLOR_6;
	    break;
	case 7:
	    paddle->main_color = COLOR_7;
	    break;
	case 8:
	    paddle->main_color = COLOR_8;
        }

    return paddle->main_color;
}

paddle_t* initialize_paddle(SDL_Color main_color, SDL_Color shadow_color, int paddle_width, int paddle_height, int paddle_x_pos, int paddle_y_pos)
{
	paddle_t* paddle = malloc(sizeof(paddle_t));
	
	ASSERT(
		paddle,
		"Failed to allocate memory for paddle\n"
	      );
	paddle->main_color = main_color;
	paddle->shadow_color = shadow_color;

	paddle->paddle_width = paddle_width;
	paddle->paddle_height = paddle_height;
	paddle->paddle_x_pos = paddle_x_pos;
	paddle->paddle_y_pos = paddle_y_pos;
	
	return paddle;
}

void render_3d_text(text_t* text)
{
	text->shadow_rect = (SDL_Rect){text->text_x_pos + 8,
				       text->text_y_pos + 8,
				       text->text_width,
				       text->text_height
			};
	text->text_rect = (SDL_Rect){text->text_x_pos,
				     text->text_y_pos,
				     text->text_width,
				     text->text_height
			};

	switch (text->text_effects_e) 
	{
		case NONE:
			break;
		case BOBBING:
			if (((SDL_GetTicks() / 1000) % 2 == 0))
			{
				text->text_rect = (SDL_Rect){text->text_x_pos - 2.5,
							     text->text_y_pos - 2.5,
							     text->text_width,
							     text->text_height
						            };
			}
			
			break;
		case SELECTED:
			if(pc_ui.play_1_text->text_effects_e == SELECTED)
			{
				pc_ui.play_1_text->text_surface = TTF_RenderText_Solid(pc_ui.play_1_text->font, "PRESS [1] TO PLAY", BRIGHT_ORANGE);
				pc_ui.play_1_text->text_texture = SDL_CreateTextureFromSurface(state.renderer, pc_ui.play_1_text->text_surface);
	}
			if(pc_ui.play_2_text->text_effects_e == SELECTED)
			{

				pc_ui.play_2_text->text_surface = TTF_RenderText_Solid(pc_ui.play_2_text->font, "PRESS [2] TO PLAY", BRIGHT_ORANGE);
				pc_ui.play_2_text->text_texture = SDL_CreateTextureFromSurface(state.renderer, pc_ui.play_2_text->text_surface);
	}	

				
			break;
		case HOVERED:
								break;
	}
	SDL_RenderCopy(state.renderer,
		       text->shadow_texture,
		       NULL,
		       &text->shadow_rect
		      );

	SDL_RenderCopy(state.renderer,
		       text->text_texture,
		       NULL,
		       &text->text_rect
		      );
		
}
void render_hoverable_button(text_t *button, int mouse_x_pos, int mouse_y_pos)
{
	if (is_over_button(button, mouse_x_pos, mouse_y_pos)) 
	{
		button->text_width += 12;
		button->text_height += 12;
		button->text_effects_e = HOVERED;
    	} 	
	else 
	{
        	button->text_effects_e = NONE;
   	}

    	render_3d_text(button);

    	if (button->text_effects_e == HOVERED) 
	{
       		button->text_width -= 12;
        	button->text_height -= 12;
    	}
}

void render_demonstration_paddle(paddle_t* paddle, int player_iter)
{
	paddle->shadow_rect = (SDL_Rect){paddle->paddle_x_pos + 12,
					 paddle->paddle_y_pos + 12,
					 paddle->paddle_width,
					 paddle->paddle_height
				         };

	paddle->main_rect = (SDL_Rect){paddle->paddle_x_pos,
				       paddle->paddle_y_pos,
				       paddle->paddle_width,
				       paddle->paddle_height 
				       };
	//TODO: Implement paddle changing color according to user
	//
	SDL_Color new_main_color = apply_selected_color(paddle, player_iter);
        SDL_SetRenderDrawColor(state.renderer, 100, 100, 100, 255);
	SDL_RenderFillRect(state.renderer, &paddle->shadow_rect);
	SDL_SetRenderDrawColor(state.renderer, new_main_color.r, new_main_color.g, new_main_color.b, 255);
	SDL_RenderFillRect(state.renderer, &paddle->main_rect);
}


void cleanup_3d_text(text_t* text)
{
	SDL_FreeSurface(text->shadow_surface);
	SDL_FreeSurface(text->text_surface);
	SDL_DestroyTexture(text->shadow_texture);
	SDL_DestroyTexture(text->text_texture);
}


int is_over_button(text_t *button, int mouse_x_pos, int mouse_y_pos) {
    return (mouse_x_pos >= button->text_x_pos/2 &&
            mouse_x_pos <= button->text_x_pos/2 + button->text_width/2 &&
            mouse_y_pos >= button->text_y_pos/2 &&
            mouse_y_pos <= button->text_y_pos/2 + button->text_height/2);
}

