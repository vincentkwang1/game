#include "background.h"
#include "global.h"
background::background() {
	bgPos = 0;
	bgVel = 1;
}
void background::move() {
	bgPos -= bgVel;
	if (bgPos < -1080) {
		bgPos = -0;
	}
}
void background::render() {
	gBackgroundTexture.render(0, bgPos);
}