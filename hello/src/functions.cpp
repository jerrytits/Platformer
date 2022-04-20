#include "functions.h"
#include "variables.h"
//#include "Font.h"
#include "Texture.h"
#include "Map.h"
#include <SDL.h>
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Timer.h"
Mix_Music *gMusic = NULL;
//Font gameFont;
Texture mario;
Texture tiles;
Texture background;
SDL_Rect clip[4];
SDL_Rect anim[4];
SDL_Rect mari={10,10};
Uint8 r = 255;
Uint8 g = 255;
Uint8 b = 255;
Uint8 a =255;

Timer gameTimer;
Player mPlayer;

int tx=0;

int frame=0;
int scrollingOffset = 0;
SDL_Rect tileRect[2];

double degrees = 0;
SDL_RendererFlip flipType = SDL_FLIP_NONE;

//320x216 map
const int mapW = 10;
const int mapH = 6;
int map[mapW][mapH];

bool quit = false;

bool init()
{
	bool success = true;
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	//TTF_Init();
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	window = SDL_CreateWindow("FakeTaxiMario", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenW, screenH, SDL_WINDOW_SHOWN);	
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	screen = SDL_GetWindowSurface(window);
	
		
	
	return success;
}

SDL_Texture* loadTexture(std::string path)
{
	//load surface
	//optimize surface
	//create texture from surface
	//delete old shit
	//return optimized texture
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	SDL_Surface* optimizedSurface = SDL_ConvertSurface(loadedSurface, screen->format, 0);

	SDL_Texture* optimized = SDL_CreateTextureFromSurface(render, optimizedSurface);
	
	SDL_FreeSurface(loadedSurface);
	return optimized;
}


bool load()
{
	bool success = true;
	
	mPlayer.onLoad("media/mario.png", 150, 10);

	gameMap.loadFromFile("media/map.txt", "media/tiles.png", 10, 20, 32);
	background.loadFromFile("media/bg.png");
	tiles.loadFromFile("media/tiles.png");
	mario.loadFromFile("media/mario.png");
	mario.setBlendMode(SDL_BLENDMODE_BLEND);
	
	SDL_Color col = {0,0,0};
	//gameFont.Init("media/verdanab.ttf", col, 16);
	//gameFont.Load();


	//load sounds
	gMusic = Mix_LoadMUS("sound/beat.wav");

	

	

	for(int i=0; i<4; i++)
	{
		clip[i].x=i*32;
		clip[i].y=0;
		clip[i].w=32;
		clip[i].h=64;
	}

	for(int i=0; i<4; i++)
	{
		anim[i].x=0;
		anim[i].y=i*64;
		anim[i].w=32;
		anim[i].h=64;
	}

	for(int n=0; n<4; n++)
	{
		printf("Clip %i\n", anim[n].y);
	}

	return success;
}

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
	SDL_Rect objA = a;
	SDL_Rect objB = b;

	int objARight = a.x+a.w;
	int objABot = a.y+a.h;
	int objBRight = b.x+a.w;
	int objBBot = b.y+b.h;

	if(objA.x>objB.x)
	{
		return true;
	}
	if(objA.x>objBRight)
	{
		return true;
	}
}

void draw()
{
	

	mario.setAlpha(a);
	mario.setColour(r,g,b);
	SDL_Rect* currentClip = &anim[frame/4];
	background.renderTex(scrollingOffset, 0);
	background.renderTex(scrollingOffset + background.getWidth(), 0);
	
	//gameFont.renderText(mari.x,tx, "Peach is a thot");
	
	
	//mario.renderTex(mari.x-camera.x,mari.y-camera.y, currentClip, degrees, NULL, flipType);
	gameMap.renderMap();
	mPlayer.onRender(camera.x, camera.y);

	

}

void loop()
{

	
	

	while(quit==false)
	{
		gameTimer.start();
		int xVel=0;
		int yVel=0;
		bool canJump=true;
		int gravity=-5;
		int speed=4;

		//if player hasnt hit bottom of screen
		if(mari.y+64 < screenH-32)
		{
			//apply gravity
			mari.y++;
			canJump=false;
		}
		else
		{
			canJump=true;
		}

		
		

		scrollingOffset--;
		if(scrollingOffset < -background.getWidth())
		{
			scrollingOffset=0;
		}

		if(tx>300)
		{
			tx-=300;
		}
		tx++;
		while(SDL_PollEvent(&e) !=0)
		{
			
			if(e.type == SDL_QUIT)
			{
				quit=true;
			}
			
			else if(e.type == SDL_KEYDOWN)
			{
				switch(e.key.keysym.sym)
				{
				case SDLK_q: r+=32; break;
				case SDLK_w: g+=32; break;
				case SDLK_e: b+=32; break;
				case SDLK_a: r-=32; break;
				case SDLK_s: g-=32; break;
				case SDLK_d: b-=32; break;
				case SDLK_t: degrees-=60; break;
				case SDLK_g: degrees+=60; break;
				case SDLK_y: flipType=SDL_FLIP_HORIZONTAL; break;
				case SDLK_h: flipType=SDL_FLIP_VERTICAL; break;
				case SDLK_SPACE: if(canJump==true) {mari.y-=50;} break;
				case SDLK_RETURN: Mix_PlayMusic(gMusic, 0); break;
				}
			}
			
			mPlayer.onEvent(e);
			
		}
		
		mari.x+=xVel;
		
		
		if(frame/4 >=4)
		{
			frame=0;
		}


		if((mari.x<0) || (mari.x + mari.w > levelW))
		{
			mari.x -= xVel;
		}
		if((mari.y + mari.h) >screenH)
		{
			mari.y -=yVel;
		}

	mPlayer.onLoop();
	camera.x = (mPlayer.getX() + 32 / 2) - screenW / 2;
	camera.y = (mPlayer.getY() + 64 / 2) - screenH / 2;
	camera.w = screenW;
	camera.h = screenH;

	if(camera.x <0)
	{
		camera.x = 0;
	}
	if(camera.y<0)
	{
		camera.y = 0;
	}
	if(camera.x>levelW - camera.w)
	{
		camera.x = levelW - camera.w;
	}
	if(camera.y>levelH - camera.h)
	{
		camera.y = levelH - camera.h;
	}

		
		
					
		//make screen background white
		SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);
		//clear current rendering target with last set colour
		SDL_RenderClear(render);

		draw();

		
		SDL_RenderPresent(render);
		gameTimer.regulate(60);
	}
}

void close()
{
	mario.free();
	//gameFont.Close();
	Mix_FreeMusic(gMusic);
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	window = NULL;
	render = NULL;
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}
