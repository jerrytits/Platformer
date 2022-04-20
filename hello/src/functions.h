#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>



bool init();
void loop();
bool load();
void close();
void draw();

SDL_Texture* loadTexture(std::string path);

#endif