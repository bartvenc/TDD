#include "Tower.hpp"
#include <math.h>
//#include "Timer.hpp"

Tower::Tower(Manager* man) : manager(man) {}

Tower::~Tower() {}

void Tower::addTower(float x, float y) {
  auto& tower(manager->addEntity());
  tower.addComponent<TransformComponent>(x, y, 64, 64, 1);
  tower.addComponent<SpriteComponent>("assets/T1.png", false);
  tower.addComponent<CircleComponent>(x, y, 128);
  // tower.addComponent<ColliderComponent>("tower");
  tower.addGroup(Game::groupTowers);
  t = &tower.getComponent<TransformComponent>();
  s = &tower.getComponent<SpriteComponent>();
  hitList = false;
  sTimer = new Timer();
}

void Tower::targetEnemy(Enemy* enemy) {
  Vector2D targetPos = enemy->t->position;
  Vector2D targetVel = enemy->t->velocity;
  Vector2D totarget = (targetPos + targetVel * 25) - t->position;
  // Vector2D trackTarget = pos - t->position;

  // trackTarget = trackTarget.Normalize();
  enemyPosx = totarget.Normalize();

  s->angle = (atan2(totarget.x, -totarget.y) * 180 / 3.14159);

  enemyPosx * 7;
  enemys = enemy;
  printf("Enemys.health %d\n", enemys->health);
  // objects.emplace(enemy, enemyPosx);
  // printf("enemy pos: ");
  // std::cout << enemy->t->position << std::endl;
  // printf("enemyPosx:");
  //	std::cout << enemyPosx << std::endl;
  // hasTarget = true;
}

void Tower::targetEnemy(Vector2D pos, Vector2D vel) {
  // enemyPos.x = 1 * pos.x / (fabs(pos.x) +  fabs(pos.y));
  // enemyPos.y = 1 * pos.x / (fabs(pos.x) +  fabs(pos.y));

  // enemyPos.x = pos.x - t->position.x;
  // enemyPos.y = pos.y - t->position.y;

  Vector2D totarget = (pos + vel * 25) - t->position;
  Vector2D trackTarget = pos - t->position;
  // printf("totarget created: ");
  // std::cout<<totarget<<std::endl;

  trackTarget = trackTarget.Normalize();
  enemyPos = totarget.Normalize();
  // printf("totarget normalized: ");
  // std::cout<<enemyPos<<std::endl;
  // printf("Enemy pos Velocitt: ");
  // std::cout<<enemyPos<<std::endl;
  s->angle = (atan2(totarget.x, -totarget.y) * 180 / 3.14159);

  // totarget;
  // printf("totarget mutiplied by 3: ");
  // std::cout<<totarget<<std::endl;

  enemyPos * 7;
  // printf("Enemys.health %d\n", enemys->health);
  // printf("pos: ");
  // std::cout<<pos<<std::endl;

  //
  // hasTarget = true;
}

void Tower::update(int h) {
  if (enemys != NULL && hitList) {
    printf("hasTarget pos: ");
    std::cout << enemys->t->position << std::endl;
    hasTarget = true;
  } else {
    hasTarget = false;
  }

  printf("Tower Update.---\n");
  printf("hitList: %d, hasTarget %d \n", hitList, hasTarget);

  sTimer->update();
  if ((sTimer->deltaTime() >= 2) && hasTarget) {
    printf("Creating projectile with angle: %f\n", s->angle);
    auto& projectile(manager->addEntity());
    projectile.addComponent<TransformComponent>(t->position.x, t->position.y,
                                                35, 35, 1);
    projectile.addComponent<SpriteComponent>("assets/Bullet.png", false);
    projectile.addComponent<ProjectileComponent>(800, 7, enemyPosx);
    projectile.addComponent<CircleComponent>(t->position.x, t->position.y, 50);
    projectile.addComponent<ColliderComponent>("projectile");
    projectile.addGroup(Game::groupProjectiles);
    sTimer->reset();
    hasTarget = false;
  }
  hasTarget = false;
}
// int currentTime = SDL_GetTicks();
// printf("%s","tower update enemyPos" );
// printf("(currentTime % 2000)= %d\n",(currentTime % 5000) );
// std::cout<<enemyPos<<std::endl;
/*printf("HitList %d =\n", hitList);
if(hitList < objects.size()){
        for(int i = 0; i < hitList; i++){
                objects.erase(0);
        }
}
printf("objects.size() %d \n", objects.size());
std::map<Enemy*, Vector2D>::iterator ems = objects.begin();
/*while(ems != objects.end()){

        if(ems->first != NULL){
                hasTarget = true;
                enemyPos = ems->second;
        }

}*/