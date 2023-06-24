#include <SDL2/SDL.h>
#include "usr_tile_parameters.h"
#include "map_parameters.h"
#include "ball_parameters.h"

ball_parameters Ball;

bool check_tile_collision(usr_tile_parameters& UsrTile);
void check_map_tiles_collision(SDL_Rect *rect, float &dx, float &dy, int &rectToDelete);

void draw_ball(SDL_Renderer* ren) {


	SDL_FRect rect={Ball.x, Ball.y, Ball.radius, Ball.radius};

	SDL_RenderFillRectF(ren, &rect);


}

void fireball_hit(usr_tile_parameters &UsrTile, map_parameters &Map, int rectToDelete, int WIDTH) {

	if (rectToDelete < RECTS_AMOUNT) {
		for (int i = 0; i < 3; i++) {
			if (Map.rects[rectToDelete+i].x != -WIDTH) {
				Map.rects[rectToDelete+i].x = -WIDTH;
				Map.createdRectsCount--;
			}
		}
	}


}

void bonus_activate(usr_tile_parameters &UsrTile, usr_tile_parameters& UsrTileClone, map_parameters &Map, bool *isTakedBonus, int rectToDelete) {

	switch (Map.bonusMask[rectToDelete]) {
		case 1: isTakedBonus[CORE_BONUS] = true; Ball.core = 5; break;
		case 2: isTakedBonus[FIREBALL_BONUS] = true; Ball.fireball = 5; break;
		case 3: isTakedBonus[DOUBLE_TILE_BONUS] = true; UsrTile.doubleTile = 5; UsrTileClone.x = -100; UsrTileClone.y = 50; break;
		case 4: isTakedBonus[RESIZE_TILE_BONUS] = true; UsrTile.width = 300.0; UsrTile.resizeTile = 5; break;
		case 5: isTakedBonus[MAGNET_TILE_BONUS] = true; UsrTile.magnet = 5; break;
	}

}

void bonusTimeDecrease(bool *isTakedBonus, usr_tile_parameters& UsrTile) {

	if (isTakedBonus[FIREBALL_BONUS]) Ball.fireball--;
	if (isTakedBonus[DOUBLE_TILE_BONUS]) UsrTile.doubleTile--;
	if (isTakedBonus[RESIZE_TILE_BONUS]) UsrTile.resizeTile--;

}

void checkBonusDeactivate(bool *isTakedBonus, usr_tile_parameters& UsrTile, usr_tile_parameters& UsrTileClone) {
	int bonusTimesCount[] = {Ball.fireball, UsrTile.doubleTile, UsrTile.resizeTile, UsrTile.magnet};	

	for (int i = 0; i < 4; i++) {
		if (bonusTimesCount[i]<=0)
			isTakedBonus[i+1] = false;
	}

	if (!isTakedBonus[RESIZE_TILE_BONUS])
		UsrTile.width = 150;
	if (!isTakedBonus[DOUBLE_TILE_BONUS])
		UsrTileClone.x = -300;
}


void check_double_tiles_collision(usr_tile_parameters& UsrTile, float &dx, float &dy, float &alpha, bool &isBallLaunched, bool *isTakedBonus, bool isTileClone) {

	if (check_tile_collision(UsrTile)&& isTakedBonus[MAGNET_TILE_BONUS]) {
		if (isBallLaunched) Ball.xPositionOnTile = Ball.x-UsrTile.x;
		isBallLaunched = false;
		if (Ball.x+Ball.radius/2.0 > UsrTile.x+UsrTile.width/2) {
			dx = abs(dx); 
			alpha = Ball.x-(UsrTile.x);
		}
		else if (Ball.x+Ball.radius/2.0 < UsrTile.x+UsrTile.width/2) {
			dx = -abs(dx);
			alpha = (UsrTile.x+UsrTile.width)-(Ball.x+Ball.radius);
		}
		if (isTileClone) dy = abs(dy);
		else dy = -abs(dy);
	}
		

	else if (check_tile_collision(UsrTile)&& dy > 0) {
		if (Ball.x+Ball.radius/2.0 > UsrTile.x+UsrTile.width/2) { 
			dx = abs(dx);
			alpha = Ball.x-(UsrTile.x);
		}
		else if (Ball.x+Ball.radius/2.0 < UsrTile.x+UsrTile.width/2) {
			dx = -abs(dx);
			alpha = (UsrTile.x+UsrTile.width)-(Ball.x+Ball.radius);
		}
		if (isTileClone) dy = abs(dy);
		else dy = -abs(dy);
	}

}

void ball_movements(SDL_Renderer* ren, usr_tile_parameters& UsrTile, usr_tile_parameters& UsrTileClone, map_parameters& Map, int dt, float &dx, float &dy, float &alpha, int WIDTH, bool &isBallLaunched, bool &isFirstLaunch, bool *isTakedBonus) {

	draw_ball(ren);	

	if (isBallLaunched) {
	
		Ball.x += Ball.speed*dt*dx*abs(cos(alpha));
		Ball.y += Ball.speed*dt*dy;
	}
	else if (isTakedBonus[MAGNET_TILE_BONUS] && !isBallLaunched) {
		printf("%lf = %lf\n", Ball.x, Ball.xPositionOnTile);
		Ball.x = UsrTile.x+Ball.xPositionOnTile;
		Ball.y = DEFAULT_BALL_Y;
	}
	else {
		Ball.x = UsrTile.x + UsrTile.width/2-Ball.radius/2;
		Ball.y = DEFAULT_BALL_Y;
	}

	if (Ball.x<0)
		dx = abs(dx);
	if(Ball.x+Ball.radius>WIDTH)
		dx = -abs(dx);
	if (Ball.y<0)
		dy = abs(dy);

	check_double_tiles_collision(UsrTile, dx, dy, alpha, isBallLaunched, isTakedBonus, false);
	check_double_tiles_collision(UsrTileClone, dx, dy, alpha, isBallLaunched, isTakedBonus, true);
	

	int rectToDelete=-1;
	check_map_tiles_collision(Map.rects, dx, dy, rectToDelete);
	if (rectToDelete!=-1) {
		printf("%d\n", Map.createdRectsCount);
		switch(Map.colorMask[rectToDelete]) {
			case 1: UsrTile.score+=UsrTile.multiplier+1;
					bonusTimeDecrease(isTakedBonus, UsrTile);
					if (isTakedBonus[FIREBALL_BONUS]) fireball_hit(UsrTile, Map, rectToDelete, WIDTH);
					else {
						Map.rects[rectToDelete].x=-WIDTH;
						Map.createdRectsCount--;
					}
					break;
			case 2: if (isTakedBonus[CORE_BONUS]) {
						bonusTimeDecrease(isTakedBonus, UsrTile);
						Map.rects[rectToDelete].x=-WIDTH;
						UsrTile.score+=UsrTile.multiplier+5;
					}
					break;
			case 3: UsrTile.score+=UsrTile.multiplier+10;
					bonusTimeDecrease(isTakedBonus, UsrTile);
					if (isTakedBonus[FIREBALL_BONUS]) fireball_hit(UsrTile, Map, rectToDelete, WIDTH);
					else {
						Map.rects[rectToDelete].x=-WIDTH;
						Map.createdRectsCount--;
					}
					break;
		}

		bonus_activate(UsrTile, UsrTileClone, Map, isTakedBonus, rectToDelete);
		
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

void save_custom_level() {



}

void check_map_tiles_collision(SDL_Rect *rect, float &dx, float &dy, int &rectToDelete) {

	for (int i = 0; i < RECTS_AMOUNT; i++) {

		if ((rect[i].y+rect[i].h>=Ball.y) && (rect[i].y+rect[i].h<=Ball.y+Ball.radius) &&
				(Ball.x>=rect[i].x) && (Ball.x<=rect[i].x+rect[i].w)) {
			dy = abs(dy);	
			rectToDelete=i;	
			return;
		}

		if ((rect[i].y>=Ball.y) && (rect[i].y<=Ball.y+Ball.radius) &&
				(Ball.x>=rect[i].x) && (Ball.x<=rect[i].x+rect[i].w)) {
			dy = -abs(dy);	
			rectToDelete=i;	
			return;
		} 

		if ((rect[i].x+rect[i].w>Ball.x) && (rect[i].x+rect[i].w<Ball.x+Ball.radius) &&
				(Ball.y+Ball.radius/2>=rect[i].y) && (Ball.y+Ball.radius/2<=rect[i].y+rect[i].h)) {
			dx = abs(dx);
			rectToDelete=i;	
			return;
		}

		if ((rect[i].x>=Ball.x) && (rect[i].x<=Ball.x+Ball.radius) &&
				(Ball.y+Ball.radius/2>=rect[i].y) && (Ball.y+Ball.radius/2<=rect[i].y+rect[i].h)) {
			dx = -abs(dx);
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
