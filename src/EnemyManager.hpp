#pragma once
#include "ECS/ECS.hpp"
#include "Enemy.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"
#include "Timer.hpp"
#include "Vector2D.hpp"
#include <map>
#include <string>

class EnemyManager {
 public:
  EnemyManager(Manager *man);
  ~EnemyManager();

  void init();

  void update();

  void CreateEnemy(int x);

  void SpawnEnemy();

  static int enemyNr;
  static std::vector<Enemy *> enemyList;

 private:
  Manager *manager;
  std::map<std::string, SDL_Texture *> textures;
};