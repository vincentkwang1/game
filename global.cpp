#ifndef global_h_
#define global_h_
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "LTexture.h"
typedef int32_t s32;
SDL_Window* gWindow;
SDL_Renderer* gRenderer;
TTF_Font *gFont;
LTexture gTextTexture;
LTexture gShipTexture;
LTexture gSelectedTexture;
LTexture gBackgroundTexture;
LTexture gNodeTexture;
LTexture gTurretTexture;
LTexture gLightTexture;
LTexture gLSelectedTexture;
LTexture gLSelected2Texture;
LTexture gBeamTexture;
LTexture gEnemyTexture;
LTexture gBulletTexture;
LTexture gTurret2Texture;
LTexture gCrewSpriteSheetTexture;
#endif // !global_h_