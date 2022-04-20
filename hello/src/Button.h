#ifndef BUTTON_H
#define BUTTON_H
#include "variables.h"
#include "Texture.h"

class Button
{
private:
	SDL_Point mPosition;
	Texture sprite;
	LButtonSprite mCurrentSprite;
public:
	Button();
	void Load();
	void setPosition(int x, int y);
	void handleEvents(SDL_Event* e);
	void render();
};


#endif