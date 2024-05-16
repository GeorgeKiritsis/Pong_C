#include <stdlib.h>
#include "inc/state.h"

int main(int argc, char* argv[])
{
	state.isRunning = initialize();

	setup();

	while(state.isRunning)
	{
		input();
		update();
		render();
	}

	atexit(shutdown);
		
	return 0;	
}
