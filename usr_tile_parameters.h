struct usr_tile_parameters {

	float x=100, y=800;

	float width=150, height=20;

	char usrTileBuffsId;

};

extern usr_tile_parameters usrTile;

void usr_tile_movements(SDL_Renderer* ren, int width, int height);
