#include <SDL2/SDL.h>
#include "usr_tile_parameters.h"
#include "map_parameters.h"
#include "ball_parameters.h"

ball_parameters Ball;

bool check_tile_collision(usr_tile_parameters& UsrTile);
void check_map_tiles_collision(SDL_Rect *rect, int &dx, int &dy, int &rectToDelete);

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

	int rectToDelete=-1;
	check_map_tiles_collision(Map.rects, dx, dy, rectToDelete);

	if (rectToDelete!=-1)
		Map.rects[rectToDelete].x=-WIDTH;

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

void check_map_tiles_collision(SDL_Rect *rect, int &dx, int &dy, int &rectToDelete) {

	for (int i = 0; i < RECTS_SIZE; i++) {

		if ((Ball.y<=rect[i].y+rect[i].h)&&((Ball.x>=rect[i].x) && 
					(Ball.x<=rect[i].x+rect[i].w))) {
			dy = abs(dy);	
			rectToDelete=i;	
			return;
		}

		if ((Ball.x <=rect[i].x+rect[i].w)&&((Ball.y>=rect[i].y) &&
					(Ball.y<=rect[i].y+rect[i].h))) {
			dx = abs(dx);
			rectToDelete=i;	
			return;
		}

		/*if ((Ball.x >=rect[i].x)&&((Ball.y>=rect[i].y) &&
					(Ball.y<=rect[i].y+rect[i].h))) {
			dx = abs(dx);
			rectToDelete=i;	
			return;
		}*/
		
	}	

}
