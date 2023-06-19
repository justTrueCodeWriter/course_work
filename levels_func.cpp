#include <stdio.h>
#include <SDL2/SDL.h>
#include "map_parameters.h"
#include "menu_parameters.h"

extern map_parameters Map;

void draw_map(SDL_Renderer* ren, int *level, int *colorMask) {

	int rectCount = 0;
	int maskIndex = 0;

	for (int j = 0; j < RECTS_ROWS; j++) {
		for (int i = 0; i < RECTS_COLS; i++) {
			Map.rects[rectCount].x = -95;
			Map.rects[rectCount].y = -30;
			Map.createdRectsCount = 0;
			Map.colorMask[rectCount] = 0;
			rectCount++;
		}
	}

	rectCount = 0;

	for(int j = 0; j < RECTS_ROWS; j++) {
		for (int i = 0; i < RECTS_COLS; i++) {
			if (level[maskIndex] != 0) {
				Map.rects[rectCount].x = 10+97*i;
				Map.rects[rectCount].y = 10+32*j;
				Map.rects[rectCount].w = 95;
				Map.rects[rectCount].h = 30;
				Map.colorMask[rectCount] = colorMask[rectCount];
				if (colorMask[rectCount] != 2) {
					Map.createdRectsCount++;
				}
			}	
			rectCount++;	
			maskIndex++;
		}
		
	}


}

void level1_map_mask(SDL_Renderer* ren) {

	int level[RECTS_AMOUNT]{1, 1, 1, 1, 1, 1, 1, 1, 1,
							1, 1, 1, 1, 1, 1, 1, 1, 1,
							1, 1, 1, 1, 1, 1, 1, 1, 1,
							1, 1, 1, 1, 1, 1, 1, 1, 1,
							1, 1, 1, 1, 1, 1, 1, 1, 1
							};

	int colorMask[RECTS_AMOUNT]{1, 1, 1, 1, 1, 1, 1, 1, 1,
								1, 1, 1, 1, 1, 1, 1, 1, 1,
								1, 1, 1, 1, 1, 1, 1, 1, 1,
								1, 1, 1, 1, 1, 1, 1, 1, 1,
								1, 1, 1, 1, 1, 1, 1, 1, 1	
								};

	draw_map(ren, level, colorMask);

}

void level2_map_mask(SDL_Renderer* ren) {

	int level[RECTS_AMOUNT]{0, 0, 0, 1, 1, 1, 0, 0, 0,
							0, 1, 1, 1, 1, 1, 1, 1, 0,
							0, 0, 1, 1, 1, 1, 1, 0, 0,
							0, 0, 0, 1, 1, 1, 0, 0, 0,
							0, 0, 0, 0, 1, 0, 0, 0, 0
							};
	int colorMask[RECTS_AMOUNT]{0, 0, 0, 1, 2, 1, 0, 0, 0,
								0, 1, 1, 1, 3, 1, 1, 1, 0,
								0, 0, 1, 3, 3, 3, 1, 0, 0,
								0, 0, 0, 1, 1, 1, 0, 0, 0,
								0, 0, 0, 0, 1, 0, 0, 0, 0	
								};

	draw_map(ren, level, colorMask);

}

void level3_map_mask(SDL_Renderer* ren) {

	int level[RECTS_AMOUNT]{0, 0, 0, 0, 0, 0, 0, 0, 1,
							0, 0, 0, 0, 0, 0, 0, 1, 1,
							0, 0, 0, 0, 0, 0, 1, 1, 1,
							0, 0, 0, 0, 0, 1, 1, 1, 1,
							0, 0, 0, 0, 1, 1, 1, 1, 1
							};

	int colorMask[RECTS_AMOUNT]{0, 0, 0, 0, 0, 0, 0, 0, 1,
								0, 0, 0, 0, 0, 0, 0, 1, 1,
								0, 0, 0, 0, 0, 0, 1, 3, 3,
								0, 0, 0, 0, 0, 1, 1, 3, 3,
								0, 0, 0, 0, 1, 2, 2, 2, 2	
								};

	draw_map(ren, level, colorMask);

}

void creat_custom_level() {

	int level[RECTS_AMOUNT];
	int colorMask[RECTS_AMOUNT];

	int maskCount = 0;
	for (int j = 0; j < RECTS_ROWS; j++) {
		printf("ROW %d: ", j);
		for (int i = 0; i < RECTS_COLS; i++) {
			scanf("%d", &level[maskCount]);	
			maskCount++;
		}
	}

	printf("\nTILE TYPE:\n\n");

	maskCount = 0;
	for (int j = 0; j < RECTS_ROWS; j++) {
		printf("ROW %d: ", j);
		for (int i = 0; i < RECTS_COLS; i++) {
			scanf("%d", &colorMask[maskCount]);	
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

	maskCount = 0;
	for (int j = 0; j < RECTS_ROWS; j++) {
		for (int i = 0; i < RECTS_COLS; i++) {
			fprintf(ft, "%d ", colorMask[maskCount]);
			maskCount++;
		}
		fprintf(ft, "\n");
	}
	fclose(ft);

}

void play_custom_level(SDL_Renderer *ren) {

	int level[RECTS_AMOUNT];
	int colorMask[RECTS_AMOUNT];

	FILE *ft;
	ft = fopen("custom_level.txt", "rt");

	for (int i = 0; i < RECTS_AMOUNT; i++) {
		fscanf(ft, "%d", &level[i]);	
	}

	for (int i = 0; i < RECTS_AMOUNT; i++) {
		fscanf(ft, "%d", &colorMask[i]);	
	}

	draw_map(ren, level, colorMask);

	game_cycle(ren);

}

void level(SDL_Renderer* ren) {

	for (int i = 0; i < RECTS_AMOUNT; i++) {
		switch(Map.colorMask[i]) {
			case 1: SDL_SetRenderDrawColor(ren, 133, 163, 137, 255); break;
			case 2: SDL_SetRenderDrawColor(ren, 200, 200, 200, 255); break;  
			case 3: SDL_SetRenderDrawColor(ren, 234, 84, 85, 255); break;
		}
		SDL_RenderFillRect(ren, &Map.rects[i]);
	}
	
}
