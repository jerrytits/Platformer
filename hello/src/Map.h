#ifndef MAP_H
#define MAP_H
#include "variables.h"
#include "Texture.h"

class Map
{
private:
	int mapWidth;
	int mapHeight;
	int tileSize;
	int map[500][500];
	Texture tileSheet;
	SDL_Rect tileSet[25];
	SDL_Rect collisionTiles[25];
public:
	Map();
	~Map();
	void loadFromFile(std::string mapFilename, std::string tileSetFilename, int width, int height, int tileSize);
	void loadTileSheet(std::string tileSetFilename, int tileW, int tileH, int rows, int columns);
	void renderMap();
	int collision(SDL_Rect collision);

	//SDL_Rect getTileSetRect() {return tileSet;}
};



#endif