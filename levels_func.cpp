#include <stdio.h>
#include <SDL2/SDL.h>
#include "map_parameters.h"
#include "menu_parameters.h"

extern map_parameters Map;

void draw_map(SDL_Renderer* ren, int *level) {

	int rectCount = 0;
	int maskIndex = 0;

	for (int j = 0; j < RECTS_ROWS; j++) {
		for (int i = 0; i < RECTS_COLS; i++) {
			Map.rects[rectCount].x = -95;
			Map.rects[rectCount].y = -30;
			rectCount++;
		}
	}

	rectCount = 0;

	for(int j = 0; j < RECTS_ROWS; j++) {
		for (int i = 0; i < RECTS_COLS; i++) {
			if (level[maskIndex] != 0) {
				Map.rects[rectCount].x=10+105*i;
				Map.rects[rectCount].y=10+55*j;
				Map.rects[rectCount].w=95;
				Map.rects[rectCount].h=30;
			}	
			rectCount++;	
			maskIndex++;
		}
		
	}


}

void level1_map_mask(SDL_Renderer* ren) {

	int level[RECTS_AMOUNT]{0, 1, 1, 1, 1, 1, 1, 1, 1,
							1, 1, 1, 1, 1, 1, 1, 1, 1,
							1, 1, 1, 1, 1, 1, 1, 1, 1,
							1, 1, 1, 1, 1, 1, 1, 1, 1,
							1, 1, 1, 1, 1, 1, 1, 1, 0
							};

	draw_map(ren, level);

}

void level2_map_mask(SDL_Renderer* ren) {

	int level[RECTS_AMOUNT]{0, 0, 0, 0, 0, 0, 0, 0, 0,
							0, 1, 1, 1, 1, 1, 1, 1, 0,
							0, 0, 1, 1, 1, 1, 1, 0, 0,
							0, 0, 0, 1, 1, 1, 0, 0, 0,
							0, 0, 0, 0, 1, 0, 0, 0, 0
							};

	draw_map(ren, level);

}

void level3_map_mask(SDL_Renderer* ren) {

	int level[RECTS_AMOUNT]{0, 0, 0, 0, 0, 0, 0, 0, 1,
							0, 0, 0, 0, 0, 0, 0, 1, 1,
							0, 0, 0, 0, 0, 0, 1, 1, 1,
							0, 0, 0, 0, 0, 1, 1, 1, 1,
							0, 0, 0, 0, 1, 1, 1, 1, 1
							};

	draw_map(ren, level);

}

void creat_custom_level() {

	int level[RECTS_AMOUNT];

	int maskCount = 0;
	for (int j = 0; j < RECTS_ROWS; j++) {
		printf("ROW %d: ", j);
		for (int i = 0; i < RECTS_COLS; i++) {
			scanf("%d", &level[maskCount]);	
			maskCount++;
		}
	}

	FILE *ft;
	ft = fopen("custom_level.txt", "wt");

	maskCount = 0;
	for (int j = 0; j < RECTS_ROWS; j++) {
		for (int i = 0; i < RECTS_COLS; i++) {
			fprintf(ft, "%d ", level[maskCount]);	
			maskCount++;
		}
		fprintf(ft, "\n");
	}
	fclose(ft);

}

void play_custom_level(SDL_Renderer *ren) {

	int level[RECTS_AMOUNT];

	FILE *ft;
	ft = fopen("custom_level.txt", "rt");

	for (int i = 0; i < RECTS_AMOUNT; i++) {
		fscanf(ft, "%d", &level[i]);	
	}

	draw_map(ren, level);

	game_cycle(ren);

}

void level(SDL_Renderer* ren) {

	SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
	SDL_RenderFillRects(ren, Map.rects, RECTS_AMOUNT);

	//draw_map();

}

