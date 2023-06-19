#define DEFAULT_BALL_X 75
#define DEFAULT_BALL_Y 780

struct ball_parameters {

	float x=DEFAULT_BALL_X, y=DEFAULT_BALL_Y;
	int bonusCount = 1;
	float speed = 0.5;
	float radius = 30;

};

void ball_movements(SDL_Renderer* ren, usr_tile_parameters& UsrTile, map_parameters& Map, int *colorMaskLink, int dt, float &dx, float &dy, int width);
