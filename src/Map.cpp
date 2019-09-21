#include "Map.hpp"
#include "Game.hpp"
#include <fstream>

Map::Map(){}

Map::~Map(){}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	int srcX, srcY, pathX, pathY;
	char c;
	std::fstream mapFile;
	mapFile.open(path);
	printf("Loading Map:" );

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
		mapFile.ignore();

	for(int y = 0; y < sizeY+1; y++){
		for(int x = 0; x < sizeX; x++){	
			mapFile.get(c);
			pathX =atoi(&c);
			mapFile.get(c);
			pathY =atoi(&c);
			mapFile.ignore();
			//printf("x:%d\n",x );
			if(pathY == 1 && pathX == 1){
				Game::path.emplace(Game::path.end(), Vector2D(0.0,1.0));
				//printf("0,1\n");
			}else if(pathY == 2 && pathX == 2){
				Game::path.emplace(Game::path.end(), Vector2D(1.0,0.0));
				//printf("1,0\n");
			}else if(pathY == 3 && pathX == 3){
				Game::path.emplace(Game::path.end(), Vector2D(0.0,-1.0));
				//printf("0,-1\n");
			}else if(pathY == 4 && pathX == 4){
				Game::path.emplace(Game::path.end(), Vector2D(-1.0,0.0));
				//printf("-1,0\n");
			}

		}

	}
	mapFile.close();

}



