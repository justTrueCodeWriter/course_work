struct ball_parameters {

	float x=75, y=780;
	int bonusCount = 1;
	float speed = 0.5;
	float radius = 10;

};

void ball_movements(SDL_Renderer* ren, usr_tile_parameters& UsrTile, int dt, int &dx, int &dy, int width);
