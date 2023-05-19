#include <stdio.h>
#include <SDL2/SDL.h>
#include "map_parameters.h"

#define ELEMENTS 5

map_parameters Map;

void draw_map(SDL_Renderer* ren) {

	int rectCount = 0;
	for (int i = 0; i < 10; i++) {
		for(int j = 0; j < 4; j++) {
			Map.rects[rectCount].x=10+105*i;
			Map.rects[rectCount].y=10+55*j;
			Map.rects[rectCount].w=100;
			Map.rects[rectCount].h=50;

			rectCount++;
		}
	}

	SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
	SDL_RenderFillRects(ren, Map.rects, 40);

}

void level1() {

	int level[ELEMENTS]{1, 1, 1, 1, 1};

	//draw_map();

}

void level2() {

	int level[ELEMENTS]{1, 1, 1, 1, 1};

	//draw_map();

}

void level3() {

	int level[ELEMENTS]{1, 1, 1, 1, 1};

	//draw_map();


}
