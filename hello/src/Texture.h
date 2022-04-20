#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <stdio.h>
#include <string>
#include <SDL_image.h>
#include "variables.h"

class Texture
{
private:
	SDL_Texture* mTexture;
	SDL_Surface* mFont;
	int w;
	int h;

public:
	Texture();
	~Texture();
	bool loadFromFile(std::string path);
	bool loadFontFromFile(std::string path, SDL_Color fontColour);
	void free();
	void renderTex(int x, int y, SDL_Rect* clip=NULL, double angle =0.0, SDL_Point* centre=NULL, SDL_RendererFlip flip= SDL_FLIP_NONE); 
	
	void setColour( Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode( SDL_BlendMode blending);
	void setAlpha(Uint8 alpha);

	int getWidth();
	int getHeight();
	int getX();
	int getY();
};

#endif