#ifndef ship_h_
#include "ship.h"
#include <SDL.h>
#include "global.h"
#define ship_h_

ship::ship() {
	pPosX = -1+(1920 - ship_width) / 2;
	pPosY = -3+(1080 - ship_height) / 2;
	pVelX = 0;
	pVelY = 0;
	sCollider.x = pPosX + 10;
	sCollider.y = pPosY + 10;
	sCollider.w = ship_width - 20;
	sCollider.h = ship_height - 20;
	lCollider.x = 895;
	lCollider.y = 469;
	lCollider.w = 120;
	lCollider.h = 120;
}
void ship::handleEvent(SDL_Event& e, int selected) {
	if (selected == 7) {
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			switch (e.key.keysym.sym) {
			case SDLK_q: rotVel = rotVel - rotSpd; break;
			case SDLK_e: rotVel = rotVel + rotSpd; break;
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
void ship::move() {
	pPosY += pVelY;
	pPosX += pVelX;
	angle = angle + rotVel;
}
void ship::render(int selected) {
	SDL_Point center = { 10,50 };
	SDL_Point center1 = { 12,52 };
	gShipTexture.render(pPosX, pPosY);
	if (selected == 7) {
		gLSelectedTexture.render(895, 469);
		gLSelected2Texture.render(940, 479, NULL, angle, &center1);
	}
	else {
		gLightTexture.render(945, 484, NULL, angle, &center);
	}
}
void ship::renderBeam() {
	SDL_Point center1 = { 1250, 1282 };
	gBeamTexture.setAlpha(10);
	gBeamTexture.render(-300, -750, NULL, angle + 90, &center1);
}
SDL_Rect ship::getLCollider() {
	return lCollider;
}
SDL_Rect ship::getSCollider() {
	return sCollider;
}
#endif // !ship_h_