#include "stdio.h"
#include <SDL2/SDL.h>
#include "sdl_general.h"
#include "usr_tile_parameters.h"

int main() {

	bool isRunning = true;	

	SDL_Event ev;

	Init();	

<<<<<<< HEAD
	while (usrTile.x++ <= 1000) {
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderClear(ren);
=======
	SDL_PollEvent(&ev);
	while (isRunning) {
>>>>>>> 8ec98e0e44bf32b3a1c8f32de33a715b98bf13fd

		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderClear(ren);

		while(SDL_PollEvent(&ev) != 0){
		switch (ev.type) {
			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode) {
				case SDL_SCANCODE_RIGHT: usrTile.x += 10; break;
				case SDL_SCANCODE_D: usrTile.x += 10; break;
				case SDL_SCANCODE_LEFT: usrTile.x -= 10; break;
				case SDL_SCANCODE_A: usrTile.x -= 10; break;
				case SDL_SCANCODE_ESCAPE: isRunning = false; break;
				//case SDL_SCANCODE_TAB: character_leveling();
				}
				break;
			}
		}	
		usr_tile_movements(ren, WIDTH, HEIGHT);			

		SDL_RenderPresent(ren);	

		SDL_Delay(16);

			
	}	

	DeInit();

}
