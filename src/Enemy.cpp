#include "Enemy.hpp"

Enemy::Enemy(Manager* man) : manager(man){}

Enemy::~Enemy(){}

void Enemy::addEnemy(float x, float y, float velX, float velY){

	auto& enemy(manager->addEntity());
	enemy.addComponent<TransformComponent>(x, y, 64, 64, 1);
	enemy.addComponent<SpriteComponent>("assets/All.png", true);
	enemy.addGroup(Game::groupEnemies);
	t = &enemy.getComponent<TransformComponent>();
	s = &enemy.getComponent<SpriteComponent>();
	pathLenght = Game::path.size();
	int it = 0;
	//printf("%d\n", pathLenght );
}

void Enemy::update(int id){

	int posX = static_cast<int>(t->position.x);
	int posY = static_cast<int>(t->position.y);
	if(posY%64 == 0 && posX%64 == 0 && it < pathLenght){
		t->velocity = Game::path[it];
		//printf("id:%d, path[%d] : ",id, it );
		//std::cout<<Game::path[it]<<std::endl;
		it++;
	}

	if(t->velocity.x == 0 && t->velocity.y == 1){
		s->Play("walkDown");
	}else if(t->velocity.x == 1 && t->velocity.y == 0){
		s->Play("walkRight");
	}else if(t->velocity.x == 0 && t->velocity.y == -1){
		s->Play("walkUp");
	}else if(t->velocity.x == -1 && t->velocity.y == 0){
		s->Play("walkLeft");	
	}
	//printf("%d: ",id );
	//	std::cout << Enemy::t->position <<std::endl;
}	

