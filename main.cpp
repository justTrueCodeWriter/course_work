#include "stdio.h"
#include <SDL2/SDL.h>
#include "sdl_general.h"
#include "usr_tile_parameters.h"

int main() {

	bool isRunning = true;	

	SDL_Event ev;

	Init();	

	while (usrTile.x++ <= 1000) {
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderClear(ren);

		SDL_PollEvent(&ev);

		switch (ev.type) {
			isRunning = false;
			break;
		}
		
		usr_tile_movements(ren, WIDTH, HEIGHT);			

		usrTile.x++;
		usrTile.y--;

		SDL_RenderPresent(ren);	

		SDL_Delay(16);

			
	}	

	DeInit();

}
