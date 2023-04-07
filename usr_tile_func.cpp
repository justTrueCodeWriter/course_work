#include <SDL2/SDL.h>
#include "usr_tile_parameters.h"

usr_tile_parameters usrTile;

void usr_tile_movements(SDL_Renderer* ren, int width, int height) {

	SDL_FRect tile = {usrTile.x, usrTile.y, usrTile.width, usrTile.height};

	SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
	SDL_RenderDrawRectF(ren, &tile);

}
