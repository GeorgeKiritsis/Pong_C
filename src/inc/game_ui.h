#ifndef GAME_UI_H
#define GAME_UI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "state.h"
#define BMP_FONT "/Users/giorgoskir/Library/Fonts/PressStart2P-Regular.ttf"
 
#define CENTERED_LEFT_HALF_X(_w) (WIDTH - _w) / 2
#define CENTERED_RIGHT_HALF_X(_w) (WIDTH + WIDTH/2 - _w/2)
#define CENTERED(_w) (WIDTH - _w/2)
#define CENTERED_VERTICALLY(_h) (HEIGHT - _h/2)

typedef struct Text
{
	TTF_Font* font;
	SDL_Color text_color;
	SDL_Color shadow_color;

	SDL_Surface* text_surface;
	SDL_Surface* shadow_surface;

	SDL_Texture* text_texture;
	SDL_Texture* shadow_texture;

	SDL_Rect text_rect;
	SDL_Rect shadow_rect;
	
	int text_width;
	int text_height;

	int text_x_pos;
	int text_y_pos;

	char* content;
	
	enum Effects
	{
		NONE,
		BOBBING,
		SELECTED,
		HOVERED
	}
	text_effects_e;

}
text_t;

typedef struct Paddle
{
	SDL_Color main_color;
	SDL_Color shadow_color;
	
	SDL_Rect main_rect;
	SDL_Rect shadow_rect;

	int paddle_width;
	int paddle_height;
	int paddle_x_pos;
	int paddle_y_pos;

	enum Colors
	{
		WHITE,
		BEIGE,
		GRAY,
		ORANGE,
		RED,
		BLUE,
	}
	paddle_colors_e;
}
paddle_t;

text_t* initialize_3d_text(
		TTF_Font* font, 
		SDL_Color text_color, 
		SDL_Color shadow_color, 
		char* content, 
		int text_x_pos, 
		int text_y_pos, 
		enum Effects text_effect 
		);

SDL_Color apply_selected_color(paddle_t* paddle, int player_iter);

paddle_t* initialize_paddle(
		SDL_Color main_color,
		SDL_Color shadow_color,
		int paddle_width,
		int paddle_height,
		int paddle_x_pos,
		int paddle_y_pos
		);

void render_3d_text(text_t* text);

void render_hoverable_button(text_t* button, int mouse_x_pos , int mouse_y_pos);

void render_paddle(paddle_t* paddle, int player_iter);

void cleanup_3d_text(text_t* text);

int is_over_button(text_t* button, int mouse_x_pos, int mouse_y_pos);

#endif
