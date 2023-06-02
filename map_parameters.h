#define RECTS_SIZE 24

#define RECTS_ROWS 2 
#define RECTS_COLS 7

struct map_parameters {

	SDL_Rect rects[RECTS_SIZE];

	int *colorMask;

};

void draw_map(SDL_Renderer* ren);

void level1_map_mask(SDL_Renderer* ren);
void level2_map_mask(SDL_Renderer* ren);
void level3_map_mask(SDL_Renderer* ren);

void level(SDL_Renderer* ren);
