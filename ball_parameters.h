#define DEFAULT_BALL_X 465
#define DEFAULT_BALL_Y 750

#define CORE_BONUS 0
#define FIREBALL_BONUS 1
#define DOUBLE_TILE_BONUS 2
#define RESIZE_TILE_BONUS 3
#define MAGNET_TILE_BONUS 4

struct ball_parameters {

	float x=DEFAULT_BALL_X, y=DEFAULT_BALL_Y;
	int bonusCount = 1;
	float speed = 0.5;
	float radius = 20;

};

void ball_movements(SDL_Renderer* ren, usr_tile_parameters& UsrTile, map_parameters& Map, int dt, float &dx, float &dy, int width, bool &isBallLaunched, bool &isFirstLaunch, bool *isTakedBonus);
