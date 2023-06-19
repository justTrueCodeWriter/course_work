#include <SDL2/SDL.h>
#include "usr_tile_parameters.h"
#include "map_parameters.h"
#include "ball_parameters.h"

ball_parameters Ball;

bool check_tile_collision(usr_tile_parameters& UsrTile);
void check_map_tiles_collision(SDL_Rect *rect, int &createdRectsCount, float &dx, float &dy, int &rectToDelete);

void draw_ball(SDL_Renderer* ren) {


	SDL_FRect rect={Ball.x, Ball.y, Ball.radius, Ball.radius};

	SDL_RenderFillRectF(ren, &rect);

	/*
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
	}*/

}

void ball_movements(SDL_Renderer* ren, usr_tile_parameters& UsrTile, map_parameters& Map, int *colorMaskLink, int dt, float &dx, float &dy, int WIDTH) {

	draw_ball(ren);	

	Ball.x += Ball.speed*dt*dx;
	Ball.y += Ball.speed*dt*dy;

	if (Ball.x<0)
		dx = abs(dx);
	if(Ball.x+Ball.radius>WIDTH)
		dx = -abs(dx);
	if (Ball.y<0)
		dy = abs(dy);

	if (check_tile_collision(UsrTile) && dy > 0) {
		dy = -dy;
	}

	int rectToDelete=-1;
	check_map_tiles_collision(Map.rects, Map.createdRectsCount, dx, dy, rectToDelete);

	if (rectToDelete!=-1) {
		printf("COLOR MASK: %d\n", colorMaskLink[rectToDelete]);
		switch(colorMaskLink[rectToDelete]) {
			case 1: Map.rects[rectToDelete].x=-WIDTH;
					UsrTile.score+=UsrTile.multiplier+1;
					break;
			case 2: break;
		}
		
	}

}

bool check_tile_collision(usr_tile_parameters& UsrTile)
{
	float leftA, leftB;
	float rightA, rightB;
	float topA, topB;
	float bottomA, bottomB;

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

void check_map_tiles_collision(SDL_Rect *rect, int &createdRectsCount, float &dx, float &dy, int &rectToDelete) {

	for (int i = 0; i < RECTS_AMOUNT; i++) {

		if ((rect[i].y+rect[i].h>=Ball.y) && (rect[i].y+rect[i].h<=Ball.y+Ball.radius) &&
				(Ball.x>=rect[i].x) && (Ball.x<=rect[i].x+rect[i].w)) {
			dy = abs(dy);	
			rectToDelete=i;	
			createdRectsCount--;
			return;
		}

		if ((rect[i].y>=Ball.y) && (rect[i].y<=Ball.y+Ball.radius) &&
				(Ball.x>=rect[i].x) && (Ball.x<=rect[i].x+rect[i].w)) {
			dy = -abs(dy);	
			rectToDelete=i;	
			createdRectsCount--;
			return;
		} 

		if ((rect[i].x+rect[i].w>Ball.x) && (rect[i].x+rect[i].w<=Ball.x+Ball.radius) &&
				(Ball.y>=rect[i].y) && (Ball.y<=rect[i].y+rect[i].h)) {
			dx = abs(dx);
			rectToDelete=i;	
			createdRectsCount--;
			return;
		}

		if ((rect[i].x>=Ball.x) && (rect[i].x<=Ball.x+Ball.radius) &&
				(Ball.y>=rect[i].y) && (Ball.y<=rect[i].y+rect[i].h)) {
			dx = -abs(dx);
			rectToDelete=i;	
			createdRectsCount--;
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
