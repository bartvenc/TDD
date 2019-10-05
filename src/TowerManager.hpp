#pragma once
#include "Collision.hpp"
#include "ECS/Components.hpp"
#include "Game.hpp"
#include "Timer.hpp"
#include "Tower.hpp"

class TowerManager {
public:
  TowerManager(Manager *man);
  ~TowerManager();

  // void init();

  void update();

  void createTower(int x, int y);

  void targeting();

  bool checkPlacement();

  static int towerNr;
  static std::vector<Tower *> towerList;

private:
  Manager *manager;
  std::map<std::string, SDL_Texture *> textures;
};
