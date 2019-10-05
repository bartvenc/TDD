#pragma once
#include "ECS/Components.hpp"
#include "Enemy.hpp"
#include "Game.hpp"
#include <boost/variant.hpp>
#include <map>

class Tower {
private:
  Manager *manager;

public:
  Tower(Manager *man);
  ~Tower();

  TransformComponent *t;
  SpriteComponent *s;
  CircleComponent *range;
  std::map<Enemy *, Vector2D> objects;
  Entity *enemys;
  void init();
  void update(int h);
  void draw();
  void addTower(float x, float y);
  void targetEnemy(Entity *enemy);
  void targetEnemy(Vector2D pos, Vector2D vel);

  Vector2D enemyPos;
  Vector2D enemyPosx;
  bool hasTarget;
  bool hitList;
  Timer *sTimer;
};