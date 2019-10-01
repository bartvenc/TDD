#include "Enemy.hpp"

Enemy::Enemy(Manager* man) : manager(man) {}

Enemy::~Enemy() {}

void Enemy::addEnemy(float x, float y, float velX, float velY) {
  printf("addEnemy()\n");
  auto& enemy(manager->addEntity());
  enemy.addComponent<TransformComponent>(x, y, 64, 64, 1);
  enemy.addComponent<SpriteComponent>("assets/Ranger.png", true);
  enemy.addComponent<ColliderComponent>("enemy");
  enemy.addGroup(Game::groupEnemies);

  t = &enemy.getComponent<TransformComponent>();
  s = &enemy.getComponent<SpriteComponent>();
  pathLenght = Game::path.size();
  it = 0;
  printf("it= %d\n", it);
}

void Enemy::update(int id) {
  // printf("updating enemyList[%d].health = %d\n",id, health);
  int posX = static_cast<int>(t->position.x);
  int posY = static_cast<int>(t->position.y);
  // printf("id:%d, path[%d] : ",id, it );
  /// std::cout<<Game::path[it]<<std::endl;
  // std::cout << Enemy::t->position <<std::endl;
  if (posY % 64 == 0 && posX % 64 == 0 && it < pathLenght) {
    t->velocity = Game::path[it];
    // printf("id:%d, path[%d] : ",id, it );
    // std::cout<<Game::path[it]<<std::endl;
    it++;
  }

  if (t->velocity.x == 0 && t->velocity.y == 1) {
    s->Play("walkDown");
  } else if (t->velocity.x == 1 && t->velocity.y == 0) {
    s->Play("walkRight");
  } else if (t->velocity.x == 0 && t->velocity.y == -1) {
    s->Play("walkUp");
  } else if (t->velocity.x == -1 && t->velocity.y == 0) {
    s->Play("walkLeft");
  }
  // printf("%d: ",id );
  //	std::cout << Enemy::t->position <<std::endl;
}

void Enemy::takeDamage(int x) {
  this->health -= x;
  printf("Damage Taken\n");
}

void Enemy::die() {
  printf("Dead Motherfucker\n");
  t->entity->destroy();
}