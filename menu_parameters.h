#define UP 0
#define W 1
#define DOWN 2
#define S 3

void start_menu(SDL_Renderer* ren);

int level_menu(SDL_Renderer* ren);
void custom_level();

void game_cycle(SDL_Renderer* ren);

int escape_menu(SDL_Renderer* ren);
