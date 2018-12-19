#ifndef global_h_
#define global_h_
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "LTexture.h"
typedef int32_t s32;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font *gFont;
extern LTexture gTextTexture;
extern LTexture gShipTexture;
extern LTexture gSelectedTexture;
extern LTexture gBackgroundTexture;
extern 	LTexture gNodeTexture;
extern 	LTexture gTurretTexture;
extern 	LTexture gLightTexture;
extern 	LTexture gLSelectedTexture;
extern 	LTexture gLSelected2Texture;
extern LTexture gBeamTexture;
extern 	LTexture gEnemyTexture;
extern 	LTexture gBulletTexture;
extern LTexture gTurret2Texture;
extern LTexture gCrewSpriteSheetTexture;
#endif // !global_h_