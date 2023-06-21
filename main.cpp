#include "stdio.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "sdl_general.h"

#include "menu_parameters.h"

#include "usr_tile_parameters.h"

extern usr_tile_parameters UsrTile;

#include "map_parameters.h"
#include "ball_parameters.h"
#include "keyboard_parameters.h"

extern ball_parameters Ball;

map_parameters Map; 

SDL_Texture *load_texture_from_file(int x, int y, const char *filename, SDL_Rect* rect) {

	SDL_Surface *surface = IMG_Load(filename);
	if (surface == NULL) {
		printf("Couldn't load image %s!\n", filename);
		DeInit();
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
	*rect = {x, y, surface->w, surface->h};
	SDL_FreeSurface(surface);

	return texture;

}

void showActivatedBonuses(SDL_Renderer* ren, bool *isTakedBonus);
 
int main() {

	create_necessary_files();

	Init();	
	start_menu(ren);
	DeInit();
}

void game_cycle(SDL_Renderer* ren, int levelNumber) {

	SDL_Rect coreRect;
	SDL_Rect fireballRect;
	SDL_Rect doubleTileRect;
	SDL_Rect resizeRect;
	SDL_Rect magnetRect;

	int lasttime = SDL_GetTicks();
	int newtime=0;
	int dt = 0;
	float dx = 1, dy = -1;
	float alpha=1;

	bool isBallMove = false;
	bool isRunning = true;	
	bool isBallLaunched = false;
	bool isFirstLaunch = true;

	char stringScore[23];
	
	char stringLevelTime[10];
	int levelTime;

	SDL_Event ev;

	SDL_PollEvent(&ev);

	bool isKeyPressed[] = {false, false, false, false};
	bool isTakedBonus[] = {false, false, false, false, false};

	TTF_Font* font = TTF_OpenFont("fonts/CherryBombOne-Regular.ttf", 50);

	while (isRunning) {
	
		sprintf(stringLevelTime, "%02d:%02d", levelTime/1000/60, levelTime/1000%60);
		SDL_Surface* stringLevelTimeSurface = TTF_RenderText_Blended(font, stringLevelTime, {215, 192, 174});
		SDL_Rect stringLevelTimeRect = {470, -20, stringLevelTimeSurface->w, stringLevelTimeSurface->h};
		SDL_Texture* stringLevelTimeTexture = SDL_CreateTextureFromSurface(ren, stringLevelTimeSurface);

		SDL_FreeSurface(stringLevelTimeSurface);

		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderClear(ren);

		sprintf(stringScore, "%d", UsrTile.score);
		SDL_Surface* stringScoreSurface = TTF_RenderText_Blended(font, stringScore, {215, 192, 174});
		SDL_Rect stringScoreRect = {1, -20, stringScoreSurface->w, stringScoreSurface->h};
		SDL_Texture* stringScoreTexture = SDL_CreateTextureFromSurface(ren, stringScoreSurface);

		SDL_FreeSurface(stringScoreSurface);

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
					case SDL_SCANCODE_RETURN: isBallLaunched = true; break;
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
		if (dt < 16) {
			SDL_Delay(16-dt);
			newtime = SDL_GetTicks();
			dt = newtime - lasttime;
		}
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
			//printf("SCORE: %d\n", UsrTile.score);
			score_screen(ren, UsrTile.score);
			Ball.x = DEFAULT_BALL_X;
			Ball.y = DEFAULT_BALL_Y;
			UsrTile.x = 400;
			UsrTile.y = 800;
			UsrTile.width = 150; 
			UsrTile.score = 0;
			TTF_CloseFont(font);
			save_level_progress(0);
		}

		usr_tile_movements(ren);		
		
		if (isBallMove) {
			levelTime += dt;
			ball_movements(ren, UsrTile, Map, dt, dx, dy, WIDTH, isBallLaunched, isFirstLaunch, isTakedBonus);
		}

		level(ren);

		SDL_RenderCopy(ren, stringScoreTexture, NULL, &stringScoreRect);
		SDL_RenderCopy(ren, stringLevelTimeTexture, NULL, &stringLevelTimeRect);

		SDL_RenderPresent(ren);	

		if (Map.createdRectsCount == 0) {
			isRunning = false;
			Ball.x = DEFAULT_BALL_X;
			Ball.y = DEFAULT_BALL_Y;
			UsrTile.x = 400;
			UsrTile.y = 800;
			UsrTile.width = 150; 
			if (levelNumber != 0) save_level_progress(levelNumber);
			if (levelNumber == 0) score_screen(ren, UsrTile.score);
			TTF_CloseFont(font);
		}
		isBallMove = true;
		SDL_DestroyTexture(stringScoreTexture);
		SDL_DestroyTexture(stringLevelTimeTexture);
	}

}

void showActivatedBonuses(SDL_Renderer* ren, bool *isTakedBonus) {



}
