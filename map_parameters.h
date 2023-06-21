#define RECTS_ROWS 5
#define RECTS_COLS 9
#define RECTS_AMOUNT 45

#define BONUS_AMOUNT 5

struct map_parameters {

	int createdRectsCount=0;

	SDL_Rect rects[RECTS_AMOUNT];

	int colorMask[RECTS_AMOUNT];

	int bonusMask[RECTS_AMOUNT];

};

void draw_map(SDL_Renderer* ren, int *colorMask, int *bonusMask);

int level1_map_mask(SDL_Renderer* ren);
int level2_map_mask(SDL_Renderer* ren);
int level3_map_mask(SDL_Renderer* ren);

void create_custom_level();
void play_custom_level(SDL_Renderer* ren);

void level(SDL_Renderer* ren);
