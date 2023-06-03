#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "menu_parameters.h"

void start_menu(SDL_Renderer* ren) {

	SDL_Event ev;

	SDL_PollEvent(&ev);

	TTF_Font* font = TTF_OpenFont("fonts/BlackOpsOne-Regular.ttf", 75);
	char str[100] = "Hello, World!";

	SDL_Surface* str_surf = TTF_RenderText_Blended(font, str, {215, 192, 174});
	SDL_Rect str_rect = {10, 10, str_surf->w, str_surf->h};
	SDL_Texture* str_text = SDL_CreateTextureFromSurface(ren, str_surf);

	bool isKeyPressed[] = {false, false, false, false};

	bool isRunning = true;	
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
					case SDL_SCANCODE_UP: isKeyPressed[UP]=true; break;
					case SDL_SCANCODE_W: isKeyPressed[W]=true; break;
					case SDL_SCANCODE_DOWN: isKeyPressed[DOWN]=true; break;
					case SDL_SCANCODE_S: isKeyPressed[S]=true; break;
					case SDL_SCANCODE_ESCAPE: isRunning = false; break;
					//case SDL_SCANCODE_TAB: character_leveling();
					}
					break;
				case SDL_KEYUP:
					switch (ev.key.keysym.scancode) {
					case SDL_SCANCODE_UP: isKeyPressed[UP]=false; break;
					case SDL_SCANCODE_W: isKeyPressed[W]=false; break;
					case SDL_SCANCODE_DOWN: isKeyPressed[DOWN]=false; break;
					case SDL_SCANCODE_S: isKeyPressed[S]=false; break;
					//case SDL_SCANCODE_TAB: character_leveling();
					}
					break;

				

			}
		}	

		if ((isKeyPressed[UP]||isKeyPressed[W]) && 
				!(isKeyPressed[DOWN]||isKeyPressed[S])) {
		}

		if ((isKeyPressed[UP]||isKeyPressed[W]) && 
				!(isKeyPressed[DOWN]||isKeyPressed[S])) {
		}

		SDL_RenderCopy(ren, str_text, NULL, &str_rect);

		SDL_RenderPresent(ren);	

	}

	TTF_CloseFont(font);
}
