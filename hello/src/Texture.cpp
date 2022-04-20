#include "Texture.h"

Texture::Texture()
{
	mTexture = NULL;
	mFont = NULL;
	w = 0;
	h = 0;
}

Texture::~Texture()
{
	free();
}


bool Texture::loadFontFromFile(std::string path, SDL_Color fontColour)
{
	/*free previous texture so we can load a new one
	free();

	//render text
	//SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, path.c_str(), fontColour);

	//create texture from SDL_Surface pixels
	mTexture = SDL_CreateTextureFromSurface(render, textSurface);
	w = textSurface->w;
	h = textSurface->h;
	SDL_FreeSurface(textSurface);*/

	return mTexture != NULL;
}



bool Texture::loadFromFile(std::string path)
{
	free();

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 0, 255));

	SDL_Texture* newText = SDL_CreateTextureFromSurface(render, loadedSurface);
	w = loadedSurface->w;
	h = loadedSurface->h;

	SDL_FreeSurface(loadedSurface);

	mTexture = newText;
	return mTexture!=NULL;
}



void Texture::free()
{
	//free texture if it exists
	if(mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		w=0;
		h=0;
	}
}

void Texture::renderTex(int x, int y, SDL_Rect* clip, double angle, SDL_Point* centre, SDL_RendererFlip flip)
{
	SDL_Rect dest = {x,y,w,h};
	

	if(clip != NULL)
	{
		dest.w = clip->w;
		dest.h = clip->h;
	}

	//draw what part of the image to set coords
	//SDL_RenderCopy(render, mTexture, clip, &dest);
	SDL_RenderCopyEx(render, mTexture, clip, &dest, angle, centre, flip);
}

void Texture::setColour(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(mTexture, blending);
}

void Texture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

int Texture::getWidth()
{
	return w;
}

int Texture::getHeight()
{
	return h;
}

