#include "bullet.h"
bullet::bullet(SDL_Point* point, int angle) {
	alive = true;
	bCollider.w = 6;
	bCollider.h = 15;
	pAngle = angle;
	bVelX = 25 * cos((-90 + angle)*3.14159265 / 180.0);
	bVelY = 25 * sin((-90 + angle)*3.14159265 / 180.0);
	bPosX1 = point->x + bVelX * 2 + bVelY/4;
	bPosY1 = point->y + bVelY * 2 - bVelX/4;
	bPosX2 = point->x + bVelX * 2 - bVelY/4;
	bPosY2 = point->y + bVelY * 2 + bVelX/4;
	bCollider.x = bPosX1 - bVelY/4;
	bCollider.y = bPosY1 + bVelX/4;
}
bool bullet::getAlive() {
	return alive;
}
void bullet::setAlive(bool newAlive) {
	alive = newAlive;
}
void bullet::move() {
	bPosX1 += bVelX;
	bPosY1 += bVelY;
	bPosX2 += bVelX;
	bPosY2 += bVelY;
	bCollider.x = bPosX1;
	bCollider.y = bPosY1;
}
void bullet::render() {
	gBulletTexture.render(bPosX1, bPosY1, NULL, pAngle);
	gBulletTexture.render(bPosX2, bPosY2, NULL, pAngle);
}
SDL_Rect bullet::getCollider() {
	return bCollider;
}
bool bullet::checkCollision(SDL_Rect* a, SDL_Rect* b) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	leftA = a->x;
	rightA = a->x + a->w;
	topA = a->y;
	bottomA = a->y + a->h;
	leftB = b->x;
	rightB = b->x + b->w;
	topB = b->y;
	bottomB = b->y + b->h;
	if (bPosX1 < 0 || bPosX1 > 1920 || bPosY1 < 0 || bPosY1 > 1920) {
		alive = false;
		return false;
	}
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
	alive = false;
	return true;
}