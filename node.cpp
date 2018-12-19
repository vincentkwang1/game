#include "node.h"
#include "global.h"
const static int SCREEN_WIDTH = 1920;
const static int SCREEN_HEIGHT = 1080;
node::node() {
	nPosX = 500;
	nPosY = 500;
	nCollider.x = 500;
	nCollider.y = 500;
	nCollider.h = 100;
	nCollider.w = 100;
}
void node::setAngle(int a) {
	angle = a;
}
void node::setPosition(int position) {
	pPosition = position;
	switch (position) {
	case 1: angle = -45;  type = 1; nPosX = (SCREEN_WIDTH - 100) / 2 - (350); nPosY = (SCREEN_HEIGHT - 600) / 2; break;//draw in top left
	case 2: angle = 0;    type = 2; reloadSpd = 50; nPosX = (SCREEN_WIDTH - 100) / 2; nPosY = (SCREEN_HEIGHT - 600) / 2; break;//draw in top mid
	case 3: angle = 45;   type = 1; nPosX = (SCREEN_WIDTH - 100) / 2 + (350); nPosY = (SCREEN_HEIGHT - 600) / 2; break;//draw in top right
	case 4: angle = 235;  type = 2; reloadSpd = 50; nPosX = (SCREEN_WIDTH - 100) / 2 - (350); nPosY = (SCREEN_HEIGHT + 400) / 2; break;//draw in bot left
	case 5: angle = 180;  type = 1; nPosX = (SCREEN_WIDTH - 100) / 2; nPosY = (SCREEN_HEIGHT + 400) / 2;; break;//draw in bot mid
	case 6: angle = 135;  type = 2; reloadSpd = 50; nPosX = (SCREEN_WIDTH - 100) / 2 + (350); nPosY = (SCREEN_HEIGHT + 400) / 2; break;//draw in bot right
	}
	nCollider.x = nPosX; nCollider.y = nPosY;
}
void node::move() {
	angle = angle + rotVel;
}
bool node::getReloading() {
	if (firing == true) {
		if (reloadProgress == reloadSpd) {
			reloadProgress = 0;
			reloading = false;
		}
		else {
			reloadProgress++;
			reloading = true;
		}
	}
	return reloading;
}
bool node::getFiring() {	
	return firing;
}
void node::handleEvent(SDL_Event &e, int selected) {
	if (pPosition == selected) {
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
			case SDLK_q: rotVel = rotVel - rotSpd; break;
			case SDLK_e: rotVel = rotVel + rotSpd; break;
			case SDLK_c: firing = !firing; break;
			}
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
			case SDLK_q: rotVel = rotVel + rotSpd; break;
			case SDLK_e: rotVel = rotVel - rotSpd; break;
			}
		}
	}
}
void node::render(int selected) {
	if (pPosition == selected) {
		gSelectedTexture.render(nPosX - 5, nPosY - 5);
	}
	else {
		gNodeTexture.render(nPosX, nPosY);
		rotVel = 0;
	}
	if (type == 1) {
		SDL_Point center = { 20, 60 };
		gTurretTexture.render(nPosX + 30, nPosY - 12, NULL, angle, &center);
	}
	else if (type ==2){
		SDL_Point center = { 20, 60 };
		gTurret2Texture.render(nPosX + 30, nPosY - 12, NULL, angle, &center);
	}
}
double node::findAngle(SDL_Point* center) {
	double targetAngle = 0;
	SDL_Point nCenter = { nPosX + 50, nPosY + 50 };
	double x, y;
	y = (double)(-center->y + nCenter.y);
	x = (double)(center->x - nCenter.x);
	double offset = y/x;
	targetAngle = atan(offset) * 180 / (3.14159265);
	if (x>0 && y<0){
		targetAngle = 90 - targetAngle;
	}
	else if (x > 0 && y > 0) {
		targetAngle = 90 - targetAngle;
	}
	else if (x < 0 && y>0) {
		targetAngle = -targetAngle + 270;
	}
	else if (x < 0 && y < 0) {
		targetAngle = -targetAngle + 270;
	}
	return targetAngle;
}
int node::getAngle() {
	if (angle <= 0) {
		angle = angle + 360;
	}
	int angle1 = angle % 360;
	return angle1;
}
SDL_Rect node::getCollider() {
	return nCollider;
}
SDL_Point node::getPoint() {
	int x = nPosX + 44;
	int y = nPosY + 40;
	SDL_Point point = { x,y };
	return point;
}