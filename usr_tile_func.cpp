#include <SDL2/SDL.h>
#include "usr_tile_parameters.h"

usr_tile_parameters UsrTile;

void usr_tile_movements(SDL_Renderer* ren) {

	SDL_FRect tile = {UsrTile.x, UsrTile.y, UsrTile.width, UsrTile.height};

	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderFillRectF(ren, &tile);

}
