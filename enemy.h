#pragma once
#include "global.h"
class enemy {
public:
	enemy() {};
	enemy(int xpos, int ypos);
	void move(SDL_Rect* a);
	void render();
	bool checkCollision(SDL_Rect* a);
	bool getAlive();
	SDL_Point getCenter();
private:
	int health;
	bool alive = true;
	int ePosX, ePosY;
	int eVelX, eVelY;
	SDL_Rect eCollider;
};