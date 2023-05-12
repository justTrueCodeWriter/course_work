#include <SDL2/SDL.h>
#include "ball_parameters.h"

ball_parameters Ball;

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

void ball_movements(SDL_Renderer* ren) {

	draw_ball(ren);	

}
