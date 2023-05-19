#include <SDL2/SDL.h>
#include "usr_tile_parameters.h"
#include "map_parameters.h"
#include "ball_parameters.h"

ball_parameters Ball;

bool check_tile_collision(usr_tile_parameters& UsrTile);
void check_map_tiles_collision(SDL_Rect *rect, int &dx, int &dy);

void draw_ball(SDL_Renderer* ren) {

	for (int w = 0; w < Ball.radius * 2; w++)
	{
		for (int h = 0; h < Ball.radius * 2; h++)
			{
			int dx = Ball.radius - w; 
			int dy = Ball.radius - h; 
			if ((dx*dx + dy*dy) <= (Ball.radius * Ball.radius))
			{
				SDL_RenderDrawPoint(ren, Ball.x + dx, Ball.y + dy);
			}
		}
	}

}

void ball_movements(SDL_Renderer* ren, usr_tile_parameters& UsrTile, map_parameters& Map, int dt, int &dx, int &dy, int WIDTH) {

	draw_ball(ren);	

	Ball.x += Ball.speed*dt*dx;
	Ball.y += Ball.speed*dt*dy;

	if (Ball.x-Ball.radius<=0 || Ball.x+Ball.radius>=WIDTH)
		dx = -dx;
	if (Ball.y-Ball.radius<=0)
		dy = -dy;

	if (check_tile_collision(UsrTile) && dy > 0) {
		dy = -dy;
	}

	// if(check_tile_collision(Map.rects[i]));
	//		dy = -dy;
	//		Map.rects[i].pop();


	check_map_tiles_collision(Map.rects, dx, dy);
}

bool check_tile_collision(usr_tile_parameters& UsrTile)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = UsrTile.x;
	rightA = UsrTile.x + UsrTile.width;
	topA = UsrTile.y;
	bottomA = UsrTile.y + UsrTile.height;

	leftB = Ball.x;
	rightB = Ball.x + Ball.radius;
	topB = Ball.y;
	bottomB = Ball.y + Ball.radius;
	if (bottomA <= topB) {
		return false;
	}
	if (topA >= bottomB) {
		return false;
	}
	if (rightA <= leftB) {
		return false;
	}
	if (leftA >= rightB) {
		return false;
	}

	return true;
}

void check_map_tiles_collision(SDL_Rect *rect, int &dx, int &dy) {

	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	for (int i = 0; i < 40; i++) {
		leftA = rect[i].x;
		rightA = rect[i].x + rect[i].w;
		topA = rect[i].y;
		bottomA = rect[i].y + rect[i].h;

		
		leftB = Ball.x;
		rightB = Ball.x + Ball.radius;
		topB = Ball.y;
		bottomB = Ball.y + Ball.radius;

		printf("%d=%d | %d=%d\n", leftA, leftB, topA, topB);

		if (Ball.y<rect[i].y) {
			dy = -dy;	
		}
		/*if (((rightB>leftA) || (leftB<rightA))) {
			dx = -dx;	
		}*/
	}	

}
