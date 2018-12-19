#pragma once
#include "global.h"
#ifndef bullet_h_
#define bullet_h
class bullet {
public:
	static const int bullet_height = 6;
	static const int bullet_width = 15;
	bullet() {};
	bullet(SDL_Point* point, int angle);
	void move();
	void render();
	bool getAlive();
	void setAlive(bool newAlive);
	SDL_Rect getCollider();
	bool checkCollision(SDL_Rect* a, SDL_Rect* b);
private:
	int pAngle;
	bool alive = true;
	int bPosX1, bPosY1, bPosX2, bPosY2;
	int bVelX, bVelY;
	SDL_Rect bCollider;
};
#endif 
