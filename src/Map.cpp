#include "Map.hpp"
#include "Game.hpp"
#include <fstream>

Map::Map(){}

Map::~Map(){}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	int srcX, srcY;
	printf("%s\n", "loadMap" );
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	for(int y = 0; y < sizeY; y++){
		for(int x = 0; x < sizeX; x++){
			mapFile.get(c);
			srcY = atoi(&c) * 64;
			mapFile.get(c);
			srcX = atoi(&c) * 64;
			Game::AddTile(srcX, srcY, x*64, y*64);
			mapFile.ignore();
		}
	}

	mapFile.close();
}



