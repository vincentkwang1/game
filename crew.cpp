#include "crew.h"
#include "global.h"
crew::crew() {
	for (int i = 0; i < 16; i++) {
		gCrewClips[i].x = 70 * i;
		gCrewClips[i].y = 0;
		gCrewClips[i].w = 70;
		gCrewClips[i].h = 64;
	}
	cPosX = 800;
	cPosY = 0;
	cVelX = 0;
	cVelY = 1;
}
void crew::move() {
	cPosX += cVelX;
	cPosY += cVelY;
}
void crew::render(int frame) {
	SDL_Rect* currentClip = &gCrewClips[frame / 20];
	gCrewSpriteSheetTexture.render(cPosX,cPosY, currentClip);
}