#include "stdio.h"
#include <SDL2/SDL.h>
#include "sdl_general.h"
#include "usr_tile_parameters.h"
#include "keyboard_parameters.h"

int main() {

	bool isRunning = true;	

	SDL_Event ev;

	Init();	

	SDL_PollEvent(&ev);

	bool isKeyPressed[] = {false, false, false, false};

	while (isRunning) {

		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderClear(ren);

		while(SDL_PollEvent(&ev) != 0){
			switch (ev.type) {
				case SDL_QUIT:
					isRunning = false;
					break;

				case SDL_KEYDOWN:
					switch (ev.key.keysym.scancode) {
					case SDL_SCANCODE_LEFT: isKeyPressed[LEFT]=true; break;
					case SDL_SCANCODE_A: isKeyPressed[A]=true; break;
					case SDL_SCANCODE_RIGHT: isKeyPressed[RIGHT]=true; break;
					case SDL_SCANCODE_D: isKeyPressed[D]=true; break;
					case SDL_SCANCODE_ESCAPE: isRunning = false; break;
					//case SDL_SCANCODE_TAB: character_leveling();
					}
					break;
				case SDL_KEYUP:
					switch (ev.key.keysym.scancode) {
					case SDL_SCANCODE_LEFT: isKeyPressed[LEFT]=false; break;
					case SDL_SCANCODE_A: isKeyPressed[A]=false; break;
					case SDL_SCANCODE_RIGHT: isKeyPressed[RIGHT]=false; break;
					case SDL_SCANCODE_D: isKeyPressed[D]=false; break;
					//case SDL_SCANCODE_TAB: character_leveling();
					}
					break;

				

			}
		}
		if ((isKeyPressed[LEFT]||isKeyPressed[A]) && 
				!(isKeyPressed[RIGHT]||isKeyPressed[D])) usrTile.x-=30;
		if ((isKeyPressed[RIGHT]||isKeyPressed[D]) && 
				!(isKeyPressed[LEFT]||isKeyPressed[A])) usrTile.x+=30;

		usr_tile_movements(ren, WIDTH, HEIGHT);			

		SDL_RenderPresent(ren);	

		SDL_Delay(16);

			
	}

	DeInit();

}
