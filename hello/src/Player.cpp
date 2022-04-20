#include "Player.h"

Player::Player()
{
	mpos.x =0; 
	mpos.y = 0;
	mpos.w = 32;
	mpos.h = 64;
	mVelX = mVelY = 0;
	mX=0;
	mY=0;
	falling = true;
	canJump = false;
	jumpPower = 0;
}

void Player::onLoad(std::string spriteSheet, int x, int y)
{
	mX = x;
	mY = y;
	mTexture.loadFromFile(spriteSheet);
}

void Player::onLoop()
{
	mVelY=2;
	mX += mVelX;
	mY+=mVelY;
	mY+=jumpPower;
	SDL_Rect pos = {mX, mY, mpos.w, mpos.h};
	

	//if we jumped up, go back down
	if(jumpPower<0)
	{
		jumpPower++;
	}
	
	int none=0;
	int either=1;
	int top=2;
	int bottom=3;


	//stop player walking off screen
	if(mX < 0 || mX+32 > levelW || gameMap.collision(pos)==either)
	{
		mX -= mVelX;
	}


	//if the player has hit bottom of screen
	if(mY > screenH-64|| gameMap.collision(pos)==top)
	{
		mY -= mVelY;
		canJump=true;
	}
	
}

void Player::onEvent(SDL_Event& e)
{
	if(e.type == SDL_KEYDOWN && e.key.repeat ==0)
	{
		switch(e.key.keysym.sym)
		{
		case SDLK_LEFT: mVelX -= mSpeed; break;
		case SDLK_RIGHT: mVelX += mSpeed; break;
		case SDLK_UP: if(canJump == true) { jumpPower-=12; canJump = false;}
		}
	}
	else if(e.type = SDL_KEYUP && e.key.repeat ==0)
	{
		switch(e.key.keysym.sym)
		{
		case SDLK_LEFT: mVelX += mSpeed; break;
		case SDLK_RIGHT: mVelX -= mSpeed; break;
		}
	}
}

void Player::onRender(int camX, int camY)
{
	mTexture.renderTex(mX - camX, mY - camY, &mpos);
}

int Player::getX()
{
	return mX;
}

int Player::getY()
{
	return mY;
}