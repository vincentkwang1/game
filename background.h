#pragma once
class background {
public:
	background();
	void move();
	void render();
	//void handleEvent(SDL_Event& e);
private:
	int bgPos = -0;
	int bgVel;
};
