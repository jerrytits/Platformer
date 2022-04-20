#include "Map.h"

Map gameMap;

Map::Map()
{
	mapWidth=0;
	mapHeight=0;
	tileSize = 0;

}

Map::~Map()
{
	tileSheet.free();
}

void Map::loadFromFile(std::string mapFilename,std::string tileSetFilename, int width, int height, int tileSize)
{
	this->tileSize = tileSize;
	std::string name = tileSetFilename;
	tileSheet.loadFromFile(tileSetFilename);
	//printf("%s\n", name);
	std::fstream file(mapFilename.c_str());
	if(file.is_open())
	{
		for(int x=0; x<width; x++)
		{
			for(int y=0; y<height; y++)
			{
				file>>map[x][y];
			}
		}
	} 
	file.close(); 

	//set the tiles array
	int test=2;
	int maxTiles = ( (tileSheet.getWidth() / tileSize) * (tileSheet.getHeight() / tileSize) );

	for(int i=0; i<maxTiles; i++)
	{
		/*for(int j=0; j<columns; j++)
		tileSet[i].y=i*32;*/

		tileSet[i].x = i*tileSize;
		tileSet[i].y = 0;
		tileSet[i].w = tileSize;
		tileSet[i].h = tileSize;
	}

	for(int x=0; x<20; x++)
	{
		for(int y=0; y<10; y++)
		{
			int max=0;
			if(map[x][y] == 2)
			{
					
				collisionTiles[max].x=x*tileSize;
				collisionTiles[max].y=y*tileSize;
				collisionTiles[max].w = tileSize;
				collisionTiles[max].h = tileSize;
				printf("Tile X:%i\n ", collisionTiles[max].x);
			}
			max++;
		}
	}
	printf("\n");
	

	for(int x=0; x<width; x++)
	{
		for(int y=0; y<height; y++)
		{
			if(map[x][y]==0)
			{
				printf("%i ", 0);
			}
			else if(map[x][y]==1)
			{
				printf("%i ", 1);
			}
			else if(map[x][y]==2)
			{
				printf("%i ", 2);
			}
		}
		printf("\n");
	}
	/*
	for(int i=0; i<columns; i++)
	{
		tileSet[i].y=i*32;
	}
	*/

}

int Map::collision(SDL_Rect collision)
{
	int none=0;
	int either=1;
	int top=2;
	int bottom=3;

	
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 20; y++)
		{
			if (map[x][y] == 2)
			{
					
				if (((collision.x + collision.w) >= y * tileSize) && (collision.x <= (y * tileSize+tileSize)) &&
					( (collision.y + collision.h) >= x * tileSize) && (collision.y <= (x * tileSize+tileSize)))
				{
					
				
				if(collision.y+64 <= y*32)
				{
					return top;
				}
				return either;
				}

				
			}
		}
	}
		
	return 0;
}

void Map::renderMap()
{
	int frame=1;
	int width = 10;
	int height = 20;
	for(int w=0; w<width; w++)
	{
		for(int h=0; h<height; h++)
		{
			if(map[w][h]==frame)
			{
				tileSheet.renderTex((h*tileSize) - camera.x, (w*tileSize) - camera.y, &tileSet[frame]);
			}
			if(map[w][h]==2)
			{
				tileSheet.renderTex((h*tileSize) - camera.x, (w*tileSize) - camera.y, &tileSet[2]);
			}
		
		}
	}
}



