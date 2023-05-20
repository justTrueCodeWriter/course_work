#define RECTS_SIZE 40

#define RECTS_ROWS 4
#define RECTS_COLS 5

struct map_parameters {

	SDL_Rect rects[RECTS_SIZE];

	int *colorMask;

};

void draw_map(SDL_Renderer* ren);

void level1(SDL_Renderer* ren);
void level2();
void level3();
