#pragma once
#include "global.h"
class crew {
public:
	crew();
	void move();
	void render(int frame);
private:
	SDL_Rect gCrewClips[16];
	int cPosX, cPosY;
	int cVelX;
	int cVelY;
};
