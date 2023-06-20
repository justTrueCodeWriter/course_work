#define UP 0
#define W 1
#define DOWN 2
#define S 3

void start_menu(SDL_Renderer* ren);
void create_necessary_files();

int level_menu(SDL_Renderer* ren);
void save_level_progress(int levelNumber);

int custom_level_menu(SDL_Renderer* ren);

void game_cycle(SDL_Renderer* ren, int levelNumber);
void score_screen(SDL_Renderer* ren, int score);

int escape_menu(SDL_Renderer* ren);
