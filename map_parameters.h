#define RECTS_ROWS 5
#define RECTS_COLS 9
#define RECTS_AMOUNT 45

struct map_parameters {

	int createdRectsCount=0;

	SDL_Rect rects[RECTS_AMOUNT];

};

void draw_map(SDL_Renderer* ren);

void level1_map_mask(SDL_Renderer* ren, int *&colorMaskLink);
void level2_map_mask(SDL_Renderer* ren, int *&colorMaskLink);
void level3_map_mask(SDL_Renderer* ren, int *colorMaskLink);

void creat_custom_level();
void play_custom_level(SDL_Renderer* ren, int *colorMaskLink);

void level(SDL_Renderer* ren, int *colorMaskLink);
