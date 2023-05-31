struct ball_parameters {

	float x=75, y=780;
	int bonusCount = 1;
	float speed = 0.5;
	float radius = 30;

};

void ball_movements(SDL_Renderer* ren, usr_tile_parameters& UsrTile, map_parameters& Map, int dt, int &dx, int &dy, int width);
