#include "Button.h"

Button::Button()
{
	mPosition.x=0;
	mPosition.y=0;
	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;


}

void Button::setPosition(int x, int y)
{
	mPosition.x=x;
	mPosition.y=y;
}

void Button::Load()
{
	sprite.loadFromFile("media/button.png");
}

void Button::handleEvents(SDL_Event* e)
{
	if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;

		//left of the button
		if(x < mPosition.x)
		{
			inside=false;
		}
		else if(x > mPosition.x + BUTTON_WIDTH)
		{
			inside = false;
		}
		else if(y <mPosition.y)
		{
			inside = false;
		}
		else if(y > mPosition.y + BUTTON_HEIGHT)
		{
			inside = false;
		}

		if(!inside)
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}

		//if it is inside
		else
		{
			switch(e->type)
			{
			case SDL_MOUSEMOTION: mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION; break;
			case SDL_MOUSEBUTTONDOWN: mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN; break;
			case SDL_MOUSEBUTTONUP: mCurrentSprite = BUTTON_SPRITE_MOUSE_UP; break;
			}
		}
	}
}

void Button::render()
{
	sprite.getHeight();
}