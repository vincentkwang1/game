#pragma once
#include "global.h"
class node {
public:
	static const int node_height = 100;
	static const int node_width = 100;
	static const int rotSpd = 2;
	node();
	void move();
	void setPosition(int position);
	void render(int selected);
	void handleEvent(SDL_Event& e, int selected);
	SDL_Rect getCollider();
	int getAngle();
	void setAngle(int angle);
	double findAngle(SDL_Point* center);
	bool getFiring();
	bool getReloading();
	SDL_Point getPoint();
private:
	int reloadSpd = 5;
	int reloadProgress = 0;
	bool firing = false;
	bool reloading = true;
	int nPosX, nPosY;
	SDL_Rect nCollider;
	int type = 1;
	int pPosition = 0;
	int angle = 0;
	int rotVel = 0;
};