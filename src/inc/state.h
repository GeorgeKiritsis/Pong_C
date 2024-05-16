#ifndef STATE_H
#define STATE_H

#include <SDL2/SDL.h>
#include "utils.h"

typedef struct State
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	int isRunning;
	int lastFrameTime;

	int mouse_x_pos;
	int mouse_y_pos;

	u32 mouse_state;
}
state_t;

int initialize(void);

void setup(void);

void input(void);

void update(void);

void render(void);

void shutdown(void);

extern state_t state;
#endif
