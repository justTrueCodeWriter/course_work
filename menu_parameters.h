#define UP 0
#define W 1
#define DOWN 2
#define S 3

void start_menu(SDL_Renderer* ren);

int level_menu(SDL_Renderer* ren);

int custom_level_menu(SDL_Renderer* ren);

void game_cycle(SDL_Renderer* ren);
void score_screen(SDL_Renderer* ren, int score);

int escape_menu(SDL_Renderer* ren);
