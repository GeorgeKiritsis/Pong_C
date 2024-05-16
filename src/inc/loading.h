#ifndef LOADING_H
#define LOADING_H

#include "game_ui.h"

typedef struct 
{
	text_t* loading_text;
	text_t* dot_1;
	text_t* dot_2;
	text_t* dot_3;

	text_t* tip_1;
	text_t* tip_2;
	text_t* tip_3;
	text_t* tip_4;

	int loading_iter;
}
ui_t2;

void initialize_loading(void);

void render_loading_effect(int dot_visible[], int index);

void render_loading(void);

extern ui_t2 loading_ui;

#endif
