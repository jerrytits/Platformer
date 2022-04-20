#ifndef PLAYER_H
#define PLAYER_H
#include "Texture.h"
#include "functions.h"
#include "Map.h"

class Player
{
private:
	SDL_Rect mpos;
	Texture mTexture;
	int mVelX, mVelY;
	int mX, mY;
	static const int mSpeed = 4;
	bool falling;
	bool canJump;
	int jumpPower;
	

public:
	Player();
	void onLoad(std::string spriteSheet, int x, int y);
	void onEvent(SDL_Event& e);
	void onLoop();
	void onRender(int camX, int camY);
	int getX();
	int getY();

};

extern Map gameMap;

#endif