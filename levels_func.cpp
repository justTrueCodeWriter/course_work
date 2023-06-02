#include <stdio.h>
#include <SDL2/SDL.h>
#include "map_parameters.h"

#define ELEMENTS 5

map_parameters Map;

void draw_map(SDL_Renderer* ren, int *level) {

	int rectCount = 0;
	int maskIndex = 0;
	for (int i = 0; i < RECTS_COLS; i++) {
		for(int j = 0; j < RECTS_ROWS; j++) {
			if (level[maskIndex] != 0) {
				Map.rects[rectCount].x=10+105*i;
				Map.rects[rectCount].y=10+55*j;
				Map.rects[rectCount].w=100;
				Map.rects[rectCount].h=50;

				rectCount++;
			}	
			maskIndex++;
		}
	}


}

void level1_map_mask(SDL_Renderer* ren) {

	int level[14]{1, 1, 1, 1, 1, 0, 0,
				1, 1, 1, 0, 1, 0, 1};

	draw_map(ren, level);

}

void level2_map_mask(SDL_Renderer* ren) {

	int level[14]{0, 1, 0, 0, 1, 0, 0,
				1, 0, 1, 0, 1, 0, 1};

	draw_map(ren, level);

}

void level3_map_mask(SDL_Renderer* ren) {

	int level[14]{1, 1, 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1, 1, 1};

	draw_map(ren, level);

}

void level(SDL_Renderer* ren) {

	SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
	SDL_RenderFillRects(ren, Map.rects, 40);

	//draw_map();

}


