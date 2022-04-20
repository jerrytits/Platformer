#ifndef VARIABLES_H
#define VARIABLES_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <cmath>

extern SDL_Window* window;
extern SDL_Surface* screen;
extern SDL_Renderer* render;
extern SDL_Rect sprite;
extern SDL_Surface* fontSurface;

extern bool quit;
extern SDL_Event e;

const int screenW = 640;
const int screenH = 320;
const int levelW = 960;
const int levelH = 320;

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

extern SDL_Rect camera;


enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

#endif