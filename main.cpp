#include "stdio.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "sdl_general.h"

#include "menu_parameters.h"

#include "usr_tile_parameters.h"

extern usr_tile_parameters UsrTile;
extern usr_tile_parameters UsrTileClone;

#include "map_parameters.h"
#include "ball_parameters.h"
#include "keyboard_parameters.h"

extern ball_parameters Ball;

map_parameters Map; 

SDL_Texture *load_texture_from_file(const char *filename, SDL_Rect* rect) {

	SDL_Surface *surface = IMG_Load(filename);
	if (surface == NULL) {
		printf("Couldn't load image %s!\n", filename);
		DeInit();
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
	*rect = {-100, 830, 80, 80};
	SDL_FreeSurface(surface);

	return texture;

}

SDL_Texture *load_ball_texture_from_file(const char *filename, SDL_Rect* rect, int x, int y) {

	SDL_Surface *surface = IMG_Load(filename);
	if (surface == NULL) {
		printf("Couldn't load image %s!\n", filename);
		DeInit();
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
	*rect = {x, y, 30, 30};
	SDL_FreeSurface(surface);

	return texture;

}

void showActivatedBonuses(bool *isTakedBonus, SDL_Rect **bonusImagesRects, SDL_Rect **bonusTimes);
 
int main() {

	create_necessary_files();

	Init();	
	start_menu(ren);
	DeInit();
}

void game_cycle(SDL_Renderer* ren, int levelNumber) {

	TTF_Font* bonusFont = TTF_OpenFont("fonts/CherryBombOne-Regular.ttf", 30);
	char fireballBonus[2];
	char doubleTileBonus[2];
	char resizeTileBonus[2];
	char magnetBonus[2];

	SDL_Rect coreRect;
	SDL_Texture* coreTexture = load_texture_from_file("textures/core.png", &coreRect);
	SDL_Rect fireballRect;
	SDL_Texture* fireballTexture = load_texture_from_file("textures/fireball.png", &fireballRect);
	SDL_Rect doubleTileRect;
	SDL_Texture* doubleTileTexture = load_texture_from_file("textures/double_tile.png", &doubleTileRect);
	SDL_Rect resizeTileRect;
	SDL_Texture* resizeTileTexture = load_texture_from_file("textures/increase_tile_size.png", &resizeTileRect);
	SDL_Rect magnetTileRect;
	SDL_Texture* magnetTileTexture = load_texture_from_file("textures/magnet.png", &magnetTileRect);

	SDL_Rect ballRect;
	SDL_Texture* ballTexture = load_ball_texture_from_file("textures/ball.png", &ballRect, Ball.x-5, Ball.y-5);

	SDL_Rect *bonusImagesRects[] = {&coreRect, &fireballRect, &doubleTileRect, &resizeTileRect, &magnetTileRect};

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

	UsrTile.width = 150;

	UsrTileClone.x = -300;
	UsrTileClone.y = -20;

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

		sprintf(fireballBonus, "%d", Ball.fireball);
		SDL_Surface* fireballBonusSurface = TTF_RenderText_Blended(bonusFont, fireballBonus, {215, 192, 174});
		SDL_Rect fireballBonusRect = {-50, 880, fireballBonusSurface->w, fireballBonusSurface->h};
		SDL_Texture* fireballBonusTexture = SDL_CreateTextureFromSurface(ren, fireballBonusSurface);

		sprintf(doubleTileBonus, "%d", UsrTile.doubleTile);
		SDL_Surface* doubleTileBonusSurface = TTF_RenderText_Blended(bonusFont, doubleTileBonus, {215, 192, 174});
		SDL_Rect doubleTileBonusRect = {-50, 880, doubleTileBonusSurface->w, doubleTileBonusSurface->h};
		SDL_Texture* doubleTileBonusTexture = SDL_CreateTextureFromSurface(ren, doubleTileBonusSurface);

		sprintf(resizeTileBonus, "%d", UsrTile.resizeTile);
		SDL_Surface* resizeTileBonusSurface = TTF_RenderText_Blended(bonusFont, resizeTileBonus, {215, 192, 174});
		SDL_Rect resizeTileBonusRect = {-50, 880, resizeTileBonusSurface->w, resizeTileBonusSurface->h};
		SDL_Texture* resizeTileBonusTexture = SDL_CreateTextureFromSurface(ren, resizeTileBonusSurface);

		sprintf(magnetBonus, "%d", UsrTile.magnet);
		SDL_Surface* magnetBonusSurface = TTF_RenderText_Blended(bonusFont, magnetBonus, {215, 192, 174});
		SDL_Rect magnetBonusRect = {-50, 890, magnetBonusSurface->w, magnetBonusSurface->h};
		SDL_Texture* magnetBonusTexture = SDL_CreateTextureFromSurface(ren, magnetBonusSurface);

		SDL_FreeSurface(fireballBonusSurface);
		SDL_FreeSurface(doubleTileBonusSurface);
		SDL_FreeSurface(resizeTileBonusSurface);
		SDL_FreeSurface(magnetBonusSurface);

		SDL_Rect *bonusTimes[] = {&fireballBonusRect, &doubleTileBonusRect, &resizeTileBonusRect, &magnetBonusRect};

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
					case SDL_SCANCODE_RETURN: isBallLaunched = true; if (isTakedBonus[MAGNET_TILE_BONUS]) UsrTile.magnet--; break;
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

		if (isTakedBonus[DOUBLE_TILE_BONUS])
				UsrTileClone.x = UsrTile.x;

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
			ballRect.x = Ball.x-4;
			ballRect.y = Ball.y-4;
			ball_movements(ren, UsrTile, UsrTileClone, Map, dt, dx, dy, alpha, WIDTH, isBallLaunched, isFirstLaunch, isTakedBonus);
		}

		checkBonusDeactivate(isTakedBonus, UsrTile, UsrTileClone);
		showActivatedBonuses(isTakedBonus, bonusImagesRects, bonusTimes);

		level(ren);

		SDL_RenderCopy(ren, stringScoreTexture, NULL, &stringScoreRect);
		SDL_RenderCopy(ren, stringLevelTimeTexture, NULL, &stringLevelTimeRect);

		SDL_RenderCopy(ren, fireballBonusTexture, NULL, &fireballBonusRect);
		SDL_RenderCopy(ren, doubleTileBonusTexture, NULL, &doubleTileBonusRect);
		SDL_RenderCopy(ren, resizeTileBonusTexture, NULL, &resizeTileBonusRect);
		SDL_RenderCopy(ren, magnetBonusTexture, NULL, &magnetBonusRect);

		SDL_RenderCopy(ren, coreTexture, NULL, &coreRect);
		SDL_RenderCopy(ren, fireballTexture, NULL, &fireballRect);
		SDL_RenderCopy(ren, doubleTileTexture, NULL, &doubleTileRect);
		SDL_RenderCopy(ren, resizeTileTexture, NULL, &resizeTileRect);
		SDL_RenderCopy(ren, magnetTileTexture, NULL, &magnetTileRect);

		SDL_RenderCopy(ren, ballTexture, NULL, &ballRect);

		SDL_RenderPresent(ren);	

		if (Map.createdRectsCount <= 0) {
			isRunning = false;
			Ball.x = DEFAULT_BALL_X;
			Ball.y = DEFAULT_BALL_Y;
			UsrTile.x = 400;
			UsrTile.y = 800;
			UsrTile.width = 150; 
			if (levelNumber != 0) {
				save_level_progress(levelNumber);
				save_level_slot(levelNumber);
			}
			if (levelNumber == 0) score_screen(ren, UsrTile.score);
			TTF_CloseFont(font);
		}
		isBallMove = true;
		SDL_DestroyTexture(stringScoreTexture);
		SDL_DestroyTexture(stringLevelTimeTexture);

		SDL_DestroyTexture(fireballBonusTexture);
		SDL_DestroyTexture(doubleTileBonusTexture);
		SDL_DestroyTexture(resizeTileBonusTexture);
		SDL_DestroyTexture(magnetBonusTexture);
	}

	SDL_DestroyTexture(coreTexture);
	SDL_DestroyTexture(fireballTexture);
	SDL_DestroyTexture(doubleTileTexture);
	SDL_DestroyTexture(resizeTileTexture);
	SDL_DestroyTexture(magnetTileTexture);

	SDL_DestroyTexture(ballTexture);

}

void showActivatedBonuses(bool *isTakedBonus, SDL_Rect **bonusImagesRects, SDL_Rect **bonusTimes) {

	int activeCount = 0;
	for (int i = 0; i < 5; i++) {
		if (isTakedBonus[i]) {
			bonusImagesRects[i]->x = 10;
			bonusImagesRects[i]->x += activeCount*90;
			if (i >= 1) {
				bonusTimes[i-1]->x = bonusImagesRects[i]->x;
			}
			activeCount++;
		}
		if (!isTakedBonus[i]) {
			bonusImagesRects[i]->x = -100;
			if (i >= 1) {
				bonusTimes[i-1]->x = bonusImagesRects[i]->x;
			}
		}
			
	}	

}
