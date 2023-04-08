struct usr_tile_parameters {

	float x=100, y=1070;

	float width=100, height=40;

	char usrTileBuffsId;

};

extern usr_tile_parameters usrTile;

void usr_tile_movements(SDL_Renderer* ren, int width, int height);
