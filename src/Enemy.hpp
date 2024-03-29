#pragma once

#include "Game.hpp"
#include "ECS/Components.hpp"

class Enemy {
 public:
  Enemy(Manager* man);
  ~Enemy();

  TransformComponent* t;
  SpriteComponent* s;
  void init();
  void update(int id);
  void draw();
  void addEnemy(float x, float y, float velX, float velY);
  void takeDamage(int x);
  void die();
  int pathLenght;
  int it;
  int health = 100;
  Timer* eTimer;

 private:
  Manager* manager;
};
