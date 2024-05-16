#ifndef ECS_H 
#define ECS_H

typedef struct entity
{
	float x;
	float y;
	float width;
	float heigt;
	float vel_x;
	float vel_y;
}
game_object;

extern game_object player;

#endif

