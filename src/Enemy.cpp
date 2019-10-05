#include "Enemy.hpp"

Enemy::Enemy(Manager *man) : manager(man) {}

Enemy::~Enemy() {}

void Enemy::addEnemy(float x, float y, float velX, float velY) {
  printf("addEnemy()\n");
  auto &enemy(manager->addEntity());
  enemy.addComponent<TransformComponent>(x, y, 64, 64, 1);
  enemy.addComponent<SpriteComponent>("assets/Ranger3.png", true);
  enemy.addComponent<ColliderComponent>("enemy");
  enemy.addGroup(Game::groupEnemies);

  t = &enemy.getComponent<TransformComponent>();
  s = &enemy.getComponent<SpriteComponent>();
  pathLenght = Game::path.size();
  it = 0;
  eTimer = new Timer();
  printf("it= %d\n", it);
}

void Enemy::update(int id) {
  if (health > 0) {
    int posX = static_cast<int>(t->position.x);
    int posY = static_cast<int>(t->position.y);

    if (posY % 64 == 0 && posX % 64 == 0 && it < pathLenght) {
      t->velocity = Game::path[it];
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

  } else {
    // eTimer->update();
    t->entity->getComponent<ColliderComponent>().collider = {0, 0, 32, 32};

    printf("update: \n");
    // t->velocity.Zero();
  }
  // printf("%d: ",id );
  //	std::cout << Enemy::t->position <<std::endl;
}

void Enemy::takeDamage(int x) {
  this->health -= x;
  printf("Damage Taken\n");
}

void Enemy::die() {
  // s->Play("dead");
  // t->entity->getComponent<ColliderComponent>().collider = {0,0,32,32};
  // SDL_Delay(3000);
  t->velocity.Zero();
  s->Play("dead");
  eTimer->reset();
  printf("Dead Motherfucker\n");
  // t->entity->destroy();
}