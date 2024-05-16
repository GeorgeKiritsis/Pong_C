#ifndef MENU_H
#define MENU_H

#include "game_ui.h"

typedef struct  
{
	text_t* title_text;
	text_t* version_text;
	text_t* play_text;
}
ui_t;

void initialize_menu(void);

void render_menu(void);

extern ui_t menu_ui;
#endif
