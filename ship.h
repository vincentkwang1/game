#pragma once
#ifndef ship_h_
#define ship_h_
#include <SDL.h>
class ship {
public:
	static const int ship_height = 494;
	static const int ship_width = 710;
	static const int paddle_spd = 6;
	static const int rotSpd = 2;
	ship();
	void handleEvent(SDL_Event& e, int selected);
	void move();
	void render(int selected);
	void renderBeam();
	SDL_Rect getLCollider();
	SDL_Rect getSCollider();
private:
	int pPosX, pPosY;
	SDL_Rect lCollider;
	SDL_Rect sCollider;
	int pVelX, pVelY;
	int angle = 0;
	int rotVel = 0;
};
#endif // !ship_h_
