#import "EnemyManager.hpp"

std::vector<Enemy *> EnemyManager::enemyList;
int EnemyManager::enemyNr;
Timer *emTimer = new Timer();

EnemyManager::EnemyManager(Manager *man) : manager(man) {}
EnemyManager::~EnemyManager() {}

void EnemyManager::init() {
  enemyNr = 0;

  for (int i = 0; i < 7; i++) {
    EnemyManager::CreateEnemy(5);
  }
}

void EnemyManager::CreateEnemy(int x) {
  printf("Creating enemy\n");

  enemyList.emplace(enemyList.end(), new Enemy(manager));
  enemyList.back()->addEnemy(192.0, -64.0, 0.0, 1.0);
}

void EnemyManager::SpawnEnemy() {
  emTimer->update();

  // every 2 seconds spawns new enemy, the <10 is here for the margin
  if ((emTimer->deltaTime() >= 2) && enemyNr < enemyList.size()) {
    emTimer->reset();
    enemyNr++;
    printf("enemyNr increased: %d\n", enemyNr);
  }
}

void EnemyManager::update() {
  SpawnEnemy();

  for (int i = 0; i < enemyNr; i++) {
    // loops through the enemy list, according to spawned enemies
    enemyList[i]->update(i);
    if (enemyList[i]->health <= 0) {
      printf("DEA\n");

      enemyList[i]->eTimer->update();

      if (enemyList[i]->eTimer->deltaTime() >= 0.11) {
        enemyList[i]->t->entity->destroy();
        enemyList.erase(enemyList.begin() + i);
        enemyNr--;
      }
    }
  }
}
