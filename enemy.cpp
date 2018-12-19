#include "enemy.h"
#include "global.h"
enemy::enemy(int xpos, int ypos) {
	ePosX = xpos;
	ePosY = ypos;
	eVelX = 1;
	eVelY = 1;
	eCollider.x = ePosX;
	eCollider.y = ePosY;
	eCollider.w = 200;
	eCollider.h = 200;
	health = 20;
}
SDL_Point enemy::getCenter() {
	SDL_Point a = { ePosX + 100, ePosY + 100 };
	return a;
}
void enemy::move(SDL_Rect* a) {
	if (ePosX < 0 || ePosX + 200 >1920){
		eVelX = -eVelX;
	}
	if (ePosY < 0 || ePosY + 200> 1080) {
		eVelY = -eVelY;
	}
	if (ePosX + 200 > a->x && ePosX < a->x + a->w) {
		if (!(ePosY + 200 < a->y || ePosY > a->y + a->h)) {
			eVelY = -eVelY;
		}
	}
	if (ePosY + 200 > a->y && ePosY < a->y + a->h) {
		if (!(ePosX + 200 < a->x || ePosX > a->x + a->w)) {
			eVelX = -eVelX;
		}
	}
	ePosX += eVelX;
	ePosY += eVelY;
	eCollider.x = ePosX;
	eCollider.y = ePosY;
}
void enemy::render() {
	if (health > 0) {
		gEnemyTexture.render(ePosX, ePosY);
	}
	else {
		alive = false;
	}
}
bool enemy::getAlive() {
	return alive;
}
bool enemy::checkCollision(SDL_Rect* a) {
	int leftB, rightB, topB, bottomB;
	int leftA = eCollider.x;
	int rightA = ePosX + eCollider.w;
	int topA = eCollider.y;
	int bottomA = eCollider.y + eCollider.h;
	leftB = a->x;
	rightB = a->x + a->w;
	topB = a->y;
	bottomB = a->y + a->h;
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
	health--;
	return true;
}