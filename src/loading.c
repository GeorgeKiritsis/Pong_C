#include "inc/loading.h"
#include "inc/game_ui.h"
#include "inc/colors.h"
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include "inc/utils.h"
#include <stdio.h>

ui_t2 loading_ui;

void initialize_loading(void)
{
	loading_ui.loading_text = initialize_3d_text(
		TTF_OpenFont(BMP_FONT, 150),
		LIGHT_GREEN,
		SHADOW_GRAY,
		"LOADING",
		0,
		0,
		NONE
		);

	loading_ui.loading_text->text_x_pos = CENTERED(loading_ui.loading_text->text_width);
	loading_ui.loading_text->text_y_pos = (HEIGHT + loading_ui.loading_text->text_height) / 4;
	printf("finished loading text initialization\n");
	
    	loading_ui.dot_1 = initialize_3d_text(
		TTF_OpenFont(BMP_FONT, 150),
		LIGHT_GREEN,
		SHADOW_GRAY,
		".",
		loading_ui.loading_text->text_x_pos + loading_ui.loading_text->text_width,
		loading_ui.loading_text->text_y_pos,
		NONE
		);

	loading_ui.dot_2 = initialize_3d_text(
		TTF_OpenFont(BMP_FONT, 150),
		LIGHT_GREEN,
		SHADOW_GRAY,
		".",
		loading_ui.loading_text->text_x_pos + loading_ui.loading_text->text_width + loading_ui.dot_1->text_width /2 ,
		loading_ui.loading_text->text_y_pos,
		NONE
		);
	
	loading_ui.dot_3 = initialize_3d_text(
		TTF_OpenFont(BMP_FONT, 150),
		LIGHT_GREEN,
		SHADOW_GRAY,
		".",
		loading_ui.dot_2->text_x_pos + loading_ui.dot_2->text_width /2 ,
		loading_ui.loading_text->text_y_pos,
		NONE
		);

	loading_ui.tip_1 = initialize_3d_text(
		TTF_OpenFont(BMP_FONT, 50),
		WHITE,
		SHADOW_GRAY,
		"> PLAYER 1 CONTROLS: W  /\\ S    \\/",
		0,
		500,
		NONE
		);

	loading_ui.tip_1->text_x_pos = CENTERED(loading_ui.tip_1->text_width);
	
	loading_ui.tip_2 = initialize_3d_text(
		TTF_OpenFont(BMP_FONT, 50),
		WHITE,
		SHADOW_GRAY,
		"> PLAYER 2 CONTROLS: UP /\\ DOWN \\/",
		0,
		0,
		NONE
		);

	loading_ui.tip_2->text_x_pos = CENTERED(loading_ui.tip_1->text_width);
	loading_ui.tip_2->text_y_pos = loading_ui.tip_1->text_y_pos + 2 * loading_ui.tip_1->text_height;

	loading_ui.tip_3 = initialize_3d_text(
		TTF_OpenFont(BMP_FONT, 50),
		WHITE,
		SHADOW_GRAY,
		"> BALL CONTROLS:     SERVE [SPACE]",
		0,
		0,
		NONE
		);

	loading_ui.tip_3->text_x_pos = CENTERED(loading_ui.tip_1->text_width);
	loading_ui.tip_3->text_y_pos = loading_ui.tip_1->text_y_pos + 4 * loading_ui.tip_1->text_height;

	loading_ui.tip_4 = initialize_3d_text(
		TTF_OpenFont(BMP_FONT, 50),
		WHITE,
		SHADOW_GRAY,
		"> TARGET:  FIRST TO 10 POINTS WINS ",
		0,
		0,
		NONE
		);

	loading_ui.tip_4->text_x_pos = CENTERED(loading_ui.tip_1->text_width);
	loading_ui.tip_4->text_y_pos = loading_ui.tip_1->text_y_pos + 6 * loading_ui.tip_1->text_height;


}

void render_loading_effect(int dot_visible[], int index)
{
	if(dot_visible[0])
	{
		render_3d_text(loading_ui.dot_1);
	}
	if(dot_visible[1])
	{
	    	render_3d_text(loading_ui.dot_2);
	}
	if(dot_visible[2])
	{
    		render_3d_text(loading_ui.dot_3);
	}
}
void render_loading(void)
{
    if (!loading_ui.loading_text) 
    {
        initialize_loading();
    }

    static u32 last_time = 0;
    static int dot_index = 0;
    static int dot_visible[3] = {0};

    u32 current_time = SDL_GetTicks();
    u32 elapsed_time = current_time - last_time;

    if (dot_index == 0 && elapsed_time >= 2000) // Show first dot after 2 seconds
    {
        dot_visible[0] = 1;
        dot_index++;
    }
    else if (dot_index == 1 && elapsed_time >= 3000) // Show second dot after 3 seconds
    {
        dot_visible[1] = 1;
        dot_index++;
    }
    else if (dot_index == 2 && elapsed_time >= 4000) // Show third dot after 4 seconds
    {
        dot_visible[2] = 1;
        dot_index++;
    }

    render_3d_text(loading_ui.loading_text);
    render_loading_effect(dot_visible, dot_index);

    if (dot_index > 2 && elapsed_time >= 5000) // Display all dots together for 1 second
    {
	loading_ui.loading_iter++;
        SDL_Delay(500); // Delay for 1 second before resetting
        dot_index = 0;
        memset(dot_visible, 0, sizeof(dot_visible)); // Reset dot visibility
        last_time = current_time; // Update last time after reset
    }

    render_3d_text(loading_ui.tip_1);
    render_3d_text(loading_ui.tip_2);
    render_3d_text(loading_ui.tip_3);
    render_3d_text(loading_ui.tip_4);
}

