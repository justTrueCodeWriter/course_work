#include "stdio.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "sdl_general.h"

#include "menu_parameters.h"

#include "usr_tile_parameters.h"

extern usr_tile_parameters UsrTile;

#include "map_parameters.h"
#include "ball_parameters.h"
#include "keyboard_parameters.h"

extern ball_parameters Ball;

map_parameters Map; 

int main() {

	Init();	
	start_menu(ren);
	DeInit();
}

void game_cycle(SDL_Renderer* ren) {

	int lasttime = SDL_GetTicks();
	int newtime;
	int dt = 0;
	int dx = 1, dy = -1;
	float alpha=1;

	bool isBallMove = true;
	bool isRunning = true;	

	SDL_Event ev;

	SDL_PollEvent(&ev);

	bool isKeyPressed[] = {false, false, false, false};

	
	//draw_map(ren);

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
					case SDL_SCANCODE_ESCAPE: if (!escape_menu(ren)) return; isBallMove = false; break;
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

		newtime = SDL_GetTicks();
		dt = newtime-lasttime;
		/*if (dt < 16) {
			SDL_Delay(16-dt);
			newtime = SDL_GetTicks();
			dt = newtime - lasttime;
		}*/
		lasttime = newtime;
		
		if ((isKeyPressed[LEFT]||isKeyPressed[A]) && 
				!(isKeyPressed[RIGHT]||isKeyPressed[D])) {
			if (UsrTile.x > 0)
				UsrTile.x-=1.5*dt;
		}
		if ((isKeyPressed[RIGHT]||isKeyPressed[D]) && 
				!(isKeyPressed[LEFT]||isKeyPressed[A])) {
			if (UsrTile.x < WIDTH-UsrTile.width)
				UsrTile.x+=1.5*dt;
		}
		
		if (Ball.y>=HEIGHT) {
			isRunning=false;
			printf("SCORE: %d\n", UsrTile.score);
			Ball.x = DEFAULT_BALL_X;
			Ball.y = DEFAULT_BALL_Y;
		}


		usr_tile_movements(ren);		
		if (isBallMove)
			ball_movements(ren, UsrTile, Map, dt, dx, dy, WIDTH);

		level(ren);

		SDL_RenderPresent(ren);	

		isBallMove = true;

	}

}
