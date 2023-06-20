#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

#include "menu_parameters.h"
#include "map_parameters.h"

void start_menu(SDL_Renderer* ren) {


	SDL_Event ev;

	SDL_PollEvent(&ev);

	TTF_Font* fontGameName = TTF_OpenFont("fonts/CherryBombOne-Regular.ttf", 90);
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
	SDL_Rect menuPointerRect = {150, 370, menuPointerSurface->w, menuPointerSurface->h};
	SDL_Texture* menuPointerTexture = SDL_CreateTextureFromSurface(ren, menuPointerSurface);

	SDL_Surface* buttonStartSurface = TTF_RenderText_Blended(font, buttonStart, {215, 192, 174});
	SDL_Rect buttonStartRect = {350, 390, buttonStartSurface->w, buttonStartSurface->h};
	SDL_Texture* buttonStartTexture = SDL_CreateTextureFromSurface(ren, buttonStartSurface);

	SDL_Surface* buttonCreateLevelSurface = TTF_RenderText_Blended(font, buttonCreateLevel, {215, 192, 174});
	SDL_Rect buttonCreateLevelRect = {300, 460, buttonCreateLevelSurface->w, buttonCreateLevelSurface->h};
	SDL_Texture* buttonCreateLevelTexture = SDL_CreateTextureFromSurface(ren, buttonCreateLevelSurface);

	SDL_Surface* buttonAboutSurface = TTF_RenderText_Blended(font, buttonAbout, {215, 192, 174});
	SDL_Rect buttonAboutRect = {350, 530, buttonAboutSurface->w, buttonAboutSurface->h};
	SDL_Texture* buttonAboutTexture = SDL_CreateTextureFromSurface(ren, buttonAboutSurface);

	SDL_Surface* buttonExitSurface = TTF_RenderText_Blended(font, buttonExit, {215, 192, 174});
	SDL_Rect buttonExitRect = {380, 600, buttonExitSurface->w, buttonExitSurface->h};
	SDL_Texture* buttonExitTexture = SDL_CreateTextureFromSurface(ren, buttonExitSurface);

	SDL_FreeSurface(gameNameSurface);
	SDL_FreeSurface(menuPointerSurface);
	SDL_FreeSurface(buttonStartSurface);
	SDL_FreeSurface(buttonCreateLevelSurface);
	SDL_FreeSurface(buttonAboutSurface);
	SDL_FreeSurface(buttonExitSurface);

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
				case 1: if(level_menu(ren)) {} break;
				case 2: custom_level_menu(ren); break; 
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

	SDL_DestroyTexture(gameNameTexture);
	SDL_DestroyTexture(menuPointerTexture);
	SDL_DestroyTexture(buttonStartTexture);
	SDL_DestroyTexture(buttonCreateLevelTexture);
	SDL_DestroyTexture(buttonAboutTexture);
	SDL_DestroyTexture(buttonExitTexture);

	TTF_CloseFont(fontGameName);
	TTF_CloseFont(font);
}

void create_necessary_files() {

	FILE *ft;

	ft = fopen("level_progress.bin", "wb");
	fclose(ft);

	ft = fopen("custom_level.txt", "rt");
	fclose(ft);

}

void save_level_progress(int levelNumber) {

	FILE *ft;

	ft = fopen("level_progress.bin", "wb");
	fwrite(&levelNumber, sizeof(int), 1, ft);
	fclose(ft);

}

int check_level_progress() {

	FILE *ft;	

	int levelProgress = 0;

	ft = fopen("level_progress.bin", "rb");
	fread(&levelProgress, sizeof(int), 1, ft);
	fclose(ft);

	return levelProgress;

}

int level_menu(SDL_Renderer* ren) {

	SDL_Event ev;

	SDL_PollEvent(&ev);

	TTF_Font* font = TTF_OpenFont("fonts/CherryBombOne-Regular.ttf", 70);
	const char *menuPointer = "-->";
	const char *buttonLevel1 = "LEVEL 1";
	const char *buttonLevel2 = "LEVEL 2";
	const char *buttonLevel3 = "LEVEL 3";
	const char *buttonExit = "BACK";


	SDL_Surface* menuPointerSurface = TTF_RenderText_Blended(font, menuPointer, {92, 137, 132});
	SDL_Rect menuPointerRect = {200, 440, menuPointerSurface->w, menuPointerSurface->h};
	SDL_Texture* menuPointerTexture = SDL_CreateTextureFromSurface(ren, menuPointerSurface);

	SDL_Surface* buttonExitSurface = TTF_RenderText_Blended(font, buttonExit, {215, 192, 174});
	SDL_Rect buttonExitRect = {380, 370, buttonExitSurface->w, buttonExitSurface->h};
	SDL_Texture* buttonExitTexture = SDL_CreateTextureFromSurface(ren, buttonExitSurface);

	SDL_Surface* buttonLevel1Surface = TTF_RenderText_Blended(font, buttonLevel1, {215, 192, 174});
	SDL_Rect buttonLevel1Rect = {350, 440, buttonLevel1Surface->w, buttonLevel1Surface->h};
	SDL_Texture* buttonLevel1Texture = SDL_CreateTextureFromSurface(ren, buttonLevel1Surface);

	SDL_Surface* buttonLevel2Surface = TTF_RenderText_Blended(font, buttonLevel2, {215, 192, 174});
	SDL_Rect buttonLevel2Rect = {300, 510, buttonLevel2Surface->w, buttonLevel2Surface->h};
	SDL_Texture* buttonLevel2Texture = SDL_CreateTextureFromSurface(ren, buttonLevel2Surface);

	SDL_Surface* buttonLevel3Surface = TTF_RenderText_Blended(font, buttonLevel3, {215, 192, 174});
	SDL_Rect buttonLevel3Rect = {350, 580, buttonLevel3Surface->w, buttonLevel3Surface->h};
	SDL_Texture* buttonLevel3Texture = SDL_CreateTextureFromSurface(ren, buttonLevel3Surface);

	

	SDL_FreeSurface(menuPointerSurface);
	SDL_FreeSurface(buttonLevel1Surface);
	SDL_FreeSurface(buttonLevel2Surface);
	SDL_FreeSurface(buttonLevel3Surface);
	SDL_FreeSurface(buttonExitSurface);

	bool isRunning = true;	
	int menuChoice = 1;
	int levelProgress = check_level_progress();
	int levelNumber = 0;
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
					case SDL_SCANCODE_DOWN: if ((menuPointerRect.y+70<=580)&&(menuChoice<=levelProgress)) { menuPointerRect.y+=70; menuChoice++; } break;
					case SDL_SCANCODE_S: if ((menuPointerRect.y+70<=580)&&(menuChoice<=levelProgress)) { menuPointerRect.y+=70; menuChoice++; } break;
					case SDL_SCANCODE_ESCAPE: isRunning = false; break;
					case SDL_SCANCODE_RETURN: isEnter = true; break;
					//case SDL_SCANCODE_TAB: character_leveling();
					}
					break;
			}
		}	

		if (isEnter) {
			SDL_DestroyTexture(menuPointerTexture);
			SDL_DestroyTexture(buttonLevel1Texture);
			SDL_DestroyTexture(buttonLevel2Texture);
			SDL_DestroyTexture(buttonLevel3Texture);
			SDL_DestroyTexture(buttonExitTexture);

			TTF_CloseFont(font);
			switch (menuChoice) {
				case 0: return 0; break;
				case 1: levelNumber = level1_map_mask(ren); level1_level_bonus(UsrTile); break;
				case 2: levelNumber = level2_map_mask(ren); level2_level_bonus(UsrTile); break;
				case 3: levelNumber = level3_map_mask(ren); level3_level_bonus(UsrTile); break;;
			}
			
			game_cycle(ren, levelNumber);
			return 1;
		}

		SDL_RenderCopy(ren, menuPointerTexture, NULL, &menuPointerRect);
		SDL_RenderCopy(ren, buttonLevel1Texture, NULL, &buttonLevel1Rect);
		SDL_RenderCopy(ren, buttonLevel2Texture, NULL, &buttonLevel2Rect);
		SDL_RenderCopy(ren, buttonLevel3Texture, NULL, &buttonLevel3Rect);
		SDL_RenderCopy(ren, buttonExitTexture, NULL, &buttonExitRect);

		SDL_RenderPresent(ren);	

	}


}

int custom_level_menu(SDL_Renderer* ren) {

	SDL_Event ev;

	SDL_PollEvent(&ev);

	TTF_Font* font = TTF_OpenFont("fonts/CherryBombOne-Regular.ttf", 70);
	const char *menuPointer = "-->";
	const char *buttonCreateLevel = "CREATE LEVEL";
	const char *buttonStartCustomLevel = "START";
	const char *buttonExit = "BACK";


	SDL_Surface* menuPointerSurface = TTF_RenderText_Blended(font, menuPointer, {92, 137, 132});
	SDL_Rect menuPointerRect = {130, 370, menuPointerSurface->w, menuPointerSurface->h};
	SDL_Texture* menuPointerTexture = SDL_CreateTextureFromSurface(ren, menuPointerSurface);

	SDL_Surface* buttonCreateLevelSurface = TTF_RenderText_Blended(font, buttonCreateLevel, {215, 192, 174});
	SDL_Rect buttonCreateLevelRect = {230, 370, buttonCreateLevelSurface->w, buttonCreateLevelSurface->h};
	SDL_Texture* buttonCreateLevelTexture = SDL_CreateTextureFromSurface(ren, buttonCreateLevelSurface);

	SDL_Surface* buttonStartCustomLevelSurface = TTF_RenderText_Blended(font, buttonStartCustomLevel, {215, 192, 174});
	SDL_Rect buttonStartCustomLevelRect = {350, 440, buttonStartCustomLevelSurface->w, buttonStartCustomLevelSurface->h};
	SDL_Texture* buttonStartCustomLevelTexture = SDL_CreateTextureFromSurface(ren, buttonStartCustomLevelSurface);

	SDL_Surface* buttonExitSurface = TTF_RenderText_Blended(font, buttonExit, {215, 192, 174});
	SDL_Rect buttonExitRect = {350, 510, buttonExitSurface->w, buttonExitSurface->h};
	SDL_Texture* buttonExitTexture = SDL_CreateTextureFromSurface(ren, buttonExitSurface);
	
	SDL_FreeSurface(menuPointerSurface);
	SDL_FreeSurface(buttonCreateLevelSurface);
	SDL_FreeSurface(buttonStartCustomLevelSurface);
	SDL_FreeSurface(buttonExitSurface);

	bool isRunning = true;	
	int menuChoice = 1;
	int *colorMaskLink = nullptr;
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
					case SDL_SCANCODE_DOWN: if (menuPointerRect.y+70<=510) { menuPointerRect.y+=70; menuChoice++; } break;
					case SDL_SCANCODE_S: if (menuPointerRect.y+70<=510) { menuPointerRect.y+=70; menuChoice++; } break;
					case SDL_SCANCODE_ESCAPE: isRunning = false; break;
					case SDL_SCANCODE_RETURN: isEnter = true; break;
					//case SDL_SCANCODE_TAB: character_leveling();
					}
					break;
			}
		}	

		if (isEnter) {
			SDL_DestroyTexture(menuPointerTexture);
			SDL_DestroyTexture(buttonCreateLevelTexture);
			SDL_DestroyTexture(buttonStartCustomLevelTexture);
			SDL_DestroyTexture(buttonExitTexture);

			TTF_CloseFont(font);
			switch (menuChoice) {
				case 1: create_custom_level(); break;
				case 2: play_custom_level(ren); break;
				case 3: return 0; break;
			}
			return 1;
		}

		SDL_RenderCopy(ren, menuPointerTexture, NULL, &menuPointerRect);
		SDL_RenderCopy(ren, buttonCreateLevelTexture, NULL, &buttonCreateLevelRect);
		SDL_RenderCopy(ren, buttonStartCustomLevelTexture, NULL, &buttonStartCustomLevelRect);
		SDL_RenderCopy(ren, buttonExitTexture, NULL, &buttonExitRect);

		SDL_RenderPresent(ren);	

	}

}

int escape_menu(SDL_Renderer* ren) {

	SDL_Event ev;

	SDL_PollEvent(&ev);

	TTF_Font* font = TTF_OpenFont("fonts/CherryBombOne-Regular.ttf", 70);
	const char *menuPointer = "-->";
	const char *buttonResume = "RESUME";
	const char *buttonExit = "EXIT";


	SDL_Surface* menuPointerSurface = TTF_RenderText_Blended(font, menuPointer, {92, 137, 132});
	SDL_Rect menuPointerRect = {200, 440, menuPointerSurface->w, menuPointerSurface->h};
	SDL_Texture* menuPointerTexture = SDL_CreateTextureFromSurface(ren, menuPointerSurface);

	SDL_Surface* buttonResumeSurface = TTF_RenderText_Blended(font, buttonResume, {215, 192, 174});
	SDL_Rect buttonResumeRect = {300, 440, buttonResumeSurface->w, buttonResumeSurface->h};
	SDL_Texture* buttonResumeTexture = SDL_CreateTextureFromSurface(ren, buttonResumeSurface);

	SDL_Surface* buttonExitSurface = TTF_RenderText_Blended(font, buttonExit, {215, 192, 174});
	SDL_Rect buttonExitRect = {350, 510, buttonExitSurface->w, buttonExitSurface->h};
	SDL_Texture* buttonExitTexture = SDL_CreateTextureFromSurface(ren, buttonExitSurface);

	SDL_FreeSurface(menuPointerSurface);
	SDL_FreeSurface(buttonResumeSurface);
	SDL_FreeSurface(buttonExitSurface);

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
					case SDL_SCANCODE_DOWN: if (menuPointerRect.y+70<=510) { menuPointerRect.y+=70; menuChoice++; } break;
					case SDL_SCANCODE_S: if (menuPointerRect.y+70<=510) { menuPointerRect.y+=70; menuChoice++; } break;
					case SDL_SCANCODE_ESCAPE: isRunning = false; break;
					case SDL_SCANCODE_RETURN: isEnter = true; break;
					//case SDL_SCANCODE_TAB: character_leveling();
					}
					break;
			}
		}	

		if (isEnter) {
			SDL_DestroyTexture(menuPointerTexture);
			SDL_DestroyTexture(buttonResumeTexture);
			SDL_DestroyTexture(buttonExitTexture);

			TTF_CloseFont(font);
			switch (menuChoice) {
				case 1: return 1; break;
				case 2: return 0; break;
			}
		}

		SDL_RenderCopy(ren, menuPointerTexture, NULL, &menuPointerRect);
		SDL_RenderCopy(ren, buttonResumeTexture, NULL, &buttonResumeRect);
		SDL_RenderCopy(ren, buttonExitTexture, NULL, &buttonExitRect);

		SDL_RenderPresent(ren);	

	}

	

}

void score_screen(SDL_Renderer* ren, int score) {

	SDL_Event ev;

	SDL_PollEvent(&ev);

	TTF_Font* font = TTF_OpenFont("fonts/CherryBombOne-Regular.ttf", 70);
	char scoreTitle[30] = "SCORE: ";
	char stringScore[23];
	sprintf(stringScore, "%d", score);
	strcat(scoreTitle, stringScore);

	SDL_Surface* scoreTitleSurface = TTF_RenderText_Blended(font, scoreTitle, {215, 192, 174});
	SDL_Rect scoreTitleRect = {300, 440, scoreTitleSurface->w, scoreTitleSurface->h};
	SDL_Texture* scoreTitleTexture = SDL_CreateTextureFromSurface(ren, scoreTitleSurface);

	SDL_FreeSurface(scoreTitleSurface);

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
					case SDL_SCANCODE_ESCAPE: isRunning = false; break;
					case SDL_SCANCODE_RETURN: isEnter = true; break;
					//case SDL_SCANCODE_TAB: character_leveling();
					}
					break;
			}
		}	

		if (isEnter) {
			SDL_DestroyTexture(scoreTitleTexture);
			TTF_CloseFont(font);
			return;
		}

		SDL_RenderCopy(ren, scoreTitleTexture, NULL, &scoreTitleRect);

		SDL_RenderPresent(ren);	

	}

}
