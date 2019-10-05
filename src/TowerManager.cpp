#include "TowerManager.hpp"

std::vector<Tower *> TowerManager::towerList;
int TowerManager::towerNr;

TowerManager::TowerManager(Manager *man) : manager(man) {}
TowerManager::~TowerManager() {}

void TowerManager::createTower(int x, int y) {
  towerList.emplace(towerList.end(), new Tower(manager));
  towerList.back()->addTower(x, y);
  printf("Added tower nr: %d \n", towerList.size());
}

bool TowerManager::checkPlacement() {
  for (auto &t : towerList) {
    printf("tower:\n");
    std::cout << t->t->entity->getComponent<TransformComponent>().position
              << std::endl;
    if (t->t->entity->getComponent<SpriteComponent>().isInside(
            towerList.size())) {
      printf("Cant placeit here\n");
      return false;
    }
    printf("Spare place\n");
  }
  return true;
}

void TowerManager::update() {
  targeting();
  for (auto &t : towerList) {
    t->update(2);
  }
}

void TowerManager::targeting() {
  int tNr = 0;
  int eNr = 0;
  auto &enemies(manager->getGroup(Game::groupEnemies));
  for (auto &t : towerList) {
    t->hitList = false;
    t->enemys = NULL;
    for (auto &e : enemies) {
      t->hitList = false;
      if (Collision::CC(t->t->entity->getComponent<CircleComponent>(),
                        e->getComponent<ColliderComponent>())) {
        t->targetEnemy(e);
        // towerList[tNr]->targetEnemy(e->getComponent<TransformComponent>().position,e->getComponent<TransformComponent>().velocity);
        t->hitList = true;
        break;
      }
      eNr++;
    }
    eNr = 0;
    tNr++;
  }
}