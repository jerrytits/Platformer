#include "variables.h"



SDL_Window* window = NULL;
SDL_Surface* screen = NULL;
SDL_Renderer* render = NULL;
SDL_Rect sprite;
SDL_Surface* fontSurface = NULL;
SDL_Rect camera = {0,0,screenW, screenH};
SDL_Event e;