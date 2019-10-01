#pragma once 
#include "Game.hpp"
#include "Enemy.hpp"
#include <map>
#include <string>
#include "TextureManager.hpp"
#include "Vector2D.hpp"
#include "Timer.hpp"
#include "ECS/ECS.hpp"

class EnemyManager{


public:

	EnemyManager(Manager* man);
	~EnemyManager();
	
	void init();
	
	void update();

	void CreateEnemy(int x);
	
	void SpawnEnemy();
	//void AddTexture(std::string id, const char* path);
	
	//SDL_Texture* GetTexture(std::string id);

	//static Timer *emTimer;
	static int enemyNr;
	static std::vector<Enemy*> enemyList;
	
private:

	Manager *manager;
	std::map<std::string, SDL_Texture*> textures;

};