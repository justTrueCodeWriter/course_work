struct usr_tile_parameters {

	float x=400, y=800;

	float width=150.0, height=20.0;

	char usrTileBuffsId;
	
	int score = 0;

	int multiplier = 0;

	int doubleTile, resizeTile, magnet;

};


void usr_tile_movements(SDL_Renderer* ren);
