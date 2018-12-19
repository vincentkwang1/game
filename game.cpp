#include "LTexture.h"
#include "global.h"
#include "bullet.h"
#include "enemy.h"
#include "ship.h"
#include "background.h"
#include "node.h"
#include "crew.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

//METHODS: init, load_image, close, loadSurface
bool init();
void close();
bool loadMedia();
bool checkClicked(SDL_Rect a, SDL_Event* e);
bool checkCollision(SDL_Rect a, SDL_Rect b);

//METHODS DEFINED
bool init() {
	bool success = true;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	//gWindow = SDL_CreateWindow("Vincent's Game!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDO_FULLSCREEN);
	gWindow = SDL_CreateWindow("Vincent's Game!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags) & imgFlags;
	TTF_Init();
	return success;
}
bool loadMedia() {
	bool success = true;
	gFont = TTF_OpenFont("resource/font1.ttf", 80);
	gShipTexture.loadFromFile("resource/temp.png");
	gNodeTexture.loadFromFile("resource/node.png");
	gBackgroundTexture.loadFromFile("resource/background2.png");
	gSelectedTexture.loadFromFile("resource/selected.png");
	gTurretTexture.loadFromFile("resource/turret.png");
	gTurret2Texture.loadFromFile("resource/turret2.png");
	gLightTexture.loadFromFile("resource/light.png");
	gLSelectedTexture.loadFromFile("resource/lightselected.png");
	gLSelected2Texture.loadFromFile("resource/lightselected2.png");
	gBeamTexture.loadFromFile("resource/beam.png");
	gEnemyTexture.loadFromFile("resource/enemy.png");
	gBulletTexture.loadFromFile("resource/bullet.png");
	gCrewSpriteSheetTexture.loadFromFile("resource/crew.png");
	return success;
}
void close() {
	gTextTexture.free();
	TTF_CloseFont(gFont);
	gFont = NULL;
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
bool checkClicked(SDL_Rect a, SDL_Event* e) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (x < a.x) {
			return false;
		}
		else if (x > a.x + a.w) {
			return false;
		}
		else if (y < a.y) {
			return false;
		}
		else if (y > a.y + a.h) {
			return false;
		}
		else {
			return true;
		}
}
bool checkCollision(SDL_Rect a, SDL_Rect b) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;
	if (bottomA <= topB){
		return false;
	}
	if (topA >= bottomB){
		return false;
	}
	if (rightA <= leftB){
		return false;
	}
	if (leftA >= rightB){
		return false;
	}
	return true;
}

//MAIN FUNCTION
int main(int argc, char* args[]) {
	init();
	loadMedia();
	bool quit = false;
	bool pause = false;
	int selected = 0;
	SDL_Event e;
	ship ship;
	crew crew;
	background background;
	int bulletnumber;
	int frame = 0;
	bullet bullets[100];
	enemy enemies[10];
	node nodes[6];
	for (int i = 1; i <= 6; i++) {
		nodes[i - 1].setPosition(i);
	}
	for (int i = 0; i <= 8; i++) {
		enemies[i] = { 200*(i), 0 };
	}
	//GAME MAIN LOOP
	while (!quit) {
		//ALLOWS QUITTING
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_ESCAPE: quit = true; break;
					case SDLK_SPACE: pause = !pause; break;
					case SDLK_1: selected = 1; break;
					case SDLK_2: selected = 2; break;
					case SDLK_3: selected = 3; break;
					case SDLK_4: selected = 4; break;
					case SDLK_5: selected = 5; break;
					case SDLK_6: selected = 6; break;
					case SDLK_l: selected = 7; break;
					}
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
				if (checkClicked(nodes[0].getCollider(), &e) == true) {
					selected = 1;
				}
				else if (checkClicked(nodes[1].getCollider(), &e) == true) {
					selected = 2;
				}
				else if (checkClicked(nodes[2].getCollider(), &e) == true) {
					selected = 3;
				}
				else if (checkClicked(nodes[3].getCollider(), &e) == true) {
					selected = 4;
				}
				else if (checkClicked(nodes[4].getCollider(), &e) == true) {
					selected = 5;
				}
				else if (checkClicked(nodes[5].getCollider(), &e) == true) {
					selected = 6;
				}
				else if (checkClicked(ship.getLCollider(), &e) == true) {
					selected = 7;
				}
			}
			ship.handleEvent(e, selected);
			for (int i = 1; i <= 6; i++) {
				nodes[i-1].handleEvent(e, selected);
			}
		}
		SDL_RenderClear(gRenderer);
		SDL_Color textColor = { 255, 0 ,0 };
		background.render();	
		for (int i = 0; i < 100; i++) {
			bullets[i].checkCollision(&bullets[i].getCollider(), &ship.getSCollider());
			if (bullets[i].getAlive() == true) {
				if (pause == false) {
					for (int a = 0; a < 10; a++) {
						if (enemies[a].getAlive() == true && bullets[i].getAlive()==true) {
							if (enemies[a].checkCollision(&bullets[i].getCollider()) == true) {
								bullets[i].setAlive(false);
							}
						}
					}
					if (bullets[i].getAlive() == true) {
						bullets[i].move();
					}
				}
				bullets[i].render();
			}
		}
		for (int i = 0; i <= 9; i++) {
			if (enemies[i].getAlive() == true) {
				enemies[i].render();
			}
		}
		ship.renderBeam();
		ship.render(selected); 
		crew.render(frame);
		for (int i = 1; i <= 6; i++) {
			if (nodes[i - 1].getFiring() == true && nodes[i - 1].getReloading() == false) {
				bulletnumber = 0;
				SDL_Point a = { 0, 0 };
				nodes[i - 1].setAngle(nodes[i - 1].findAngle(&enemies[3].getCenter()));
				do {
					bulletnumber++;
				} while (bullets[bulletnumber].getAlive() == true);
				bullets[bulletnumber] = { &nodes[i - 1].getPoint(), nodes[i - 1].getAngle() };
			}
			nodes[i - 1].render(selected);
		}
		if (pause == false) {
			if (frame < 79) {
				frame++;
			}
			else {
				frame = 0;
			}
			for (int i = 0; i <= 9; i++) {
				enemies[i].move(&ship.getSCollider());
			}
			background.move();
			ship.move();
			crew.move();
			for (int i = 1; i <= 6; i++) {
				nodes[i-1].move();
			}
		}
		else {
			gTextTexture.loadFromRenderedText("Paused!", textColor);
			gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, (SCREEN_HEIGHT) - 200);
		}
		SDL_RenderPresent(gRenderer);
	}
	close();
	return 0;
}