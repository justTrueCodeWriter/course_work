#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "menu_parameters.h"

void start_menu(SDL_Renderer* ren) {

	SDL_Event ev;

	SDL_PollEvent(&ev);

	TTF_Font* fontGameName = TTF_OpenFont("fonts/BlackOpsOne-Regular.ttf", 90);
	TTF_Font* font = TTF_OpenFont("fonts/CherryBombOne-Regular.ttf", 70);
	const char *gameName = "ARKANOIX";
	const char *menuPointer = "-->";
	const char *buttonStart = "START";
	const char *buttonCreateLevel = "CREATE LVL";
	const char *buttonAbout = "ABOUT";
	const char *buttonExit = "EXIT";

	SDL_Surface* gameNameSurface = TTF_RenderText_Blended(fontGameName, gameName, {215, 192, 174});
	SDL_Rect gameNameRect = {230, 160, gameNameSurface->w, gameNameSurface->h};
	SDL_Texture* gameNameTexture = SDL_CreateTextureFromSurface(ren, gameNameSurface);

	SDL_Surface* menuPointerSurface = TTF_RenderText_Blended(fontGameName, menuPointer, {92, 137, 132});
	SDL_Rect menuPointerRect = {100, 370, menuPointerSurface->w, menuPointerSurface->h};
	SDL_Texture* menuPointerTexture = SDL_CreateTextureFromSurface(ren, menuPointerSurface);

	SDL_Surface* buttonStartSurface = TTF_RenderText_Blended(font, buttonStart, {215, 192, 174});
	SDL_Rect buttonStartRect = {350, 370, buttonStartSurface->w, buttonStartSurface->h};
	SDL_Texture* buttonStartTexture = SDL_CreateTextureFromSurface(ren, buttonStartSurface);

	SDL_Surface* buttonCreateLevelSurface = TTF_RenderText_Blended(font, buttonCreateLevel, {215, 192, 174});
	SDL_Rect buttonCreateLevelRect = {300, 440, buttonCreateLevelSurface->w, buttonCreateLevelSurface->h};
	SDL_Texture* buttonCreateLevelTexture = SDL_CreateTextureFromSurface(ren, buttonCreateLevelSurface);

	SDL_Surface* buttonAboutSurface = TTF_RenderText_Blended(font, buttonAbout, {215, 192, 174});
	SDL_Rect buttonAboutRect = {350, 510, buttonAboutSurface->w, buttonAboutSurface->h};
	SDL_Texture* buttonAboutTexture = SDL_CreateTextureFromSurface(ren, buttonAboutSurface);

	SDL_Surface* buttonExitSurface = TTF_RenderText_Blended(font, buttonExit, {215, 192, 174});
	SDL_Rect buttonExitRect = {380, 580, buttonExitSurface->w, buttonExitSurface->h};
	SDL_Texture* buttonExitTexture = SDL_CreateTextureFromSurface(ren, buttonExitSurface);

	bool isRunning = true;	
	int menuChoice = 1;
	while (isRunning) {

		bool isEnter = false;

		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderClear(ren);
		

		while(SDL_PollEvent(&ev) != 0){
			switch (ev.type) {
				case SDL_QUIT:
					isRunning = false;
					break;

				case SDL_KEYDOWN:
					switch (ev.key.keysym.scancode) {
					case SDL_SCANCODE_UP: if (menuPointerRect.y-70>=370) { menuPointerRect.y-=70; menuChoice--; } break;
					case SDL_SCANCODE_W: if (menuPointerRect.y-70>=370) { menuPointerRect.y-=70; menuChoice--; } break;
					case SDL_SCANCODE_DOWN: if (menuPointerRect.y+70<=580) { menuPointerRect.y+=70; menuChoice++; } break;
					case SDL_SCANCODE_S: if (menuPointerRect.y+70<=580) { menuPointerRect.y+=70; menuChoice++; } break;
					case SDL_SCANCODE_ESCAPE: isRunning = false; break;
					case SDL_SCANCODE_RETURN: isEnter = true; break;
					//case SDL_SCANCODE_TAB: character_leveling();
					}
					break;
			}
		}	


		if (isEnter) {
			switch (menuChoice) {
				case 1: break;
				case 2: break;
				case 3: system("xdg-open https://github.com/justTrueCodeWriter/course_work"); break;
				case 4: exit(1); break;
			}
		}
		
		SDL_RenderCopy(ren, gameNameTexture, NULL, &gameNameRect);
		SDL_RenderCopy(ren, menuPointerTexture, NULL, &menuPointerRect);
		SDL_RenderCopy(ren, buttonStartTexture, NULL, &buttonStartRect);
		SDL_RenderCopy(ren, buttonCreateLevelTexture, NULL, &buttonCreateLevelRect);
		SDL_RenderCopy(ren, buttonAboutTexture, NULL, &buttonAboutRect);
		SDL_RenderCopy(ren, buttonExitTexture, NULL, &buttonExitRect);

		SDL_RenderPresent(ren);	

	}

	TTF_CloseFont(font);
}
