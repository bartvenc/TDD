#include "Tower.hpp"

Tower::Tower(Manager* man) : manager(man){

}

Tower::~Tower(){}

void Tower::addTower(float x, float y){
	auto& tower(manager->addEntity());
	tower.addComponent<TransformComponent>(x, y, 64, 64,1);
	tower.addComponent<SpriteComponent>("assets/T1.png", false);
	tower.addComponent<CircleComponent>(x,y,128);
	//tower.addComponent<ColliderComponent>("tower");
	tower.addGroup(Game::groupTowers);	
	t = &tower.getComponent<TransformComponent>();
	s = &tower.getComponent<SpriteComponent>();	
}

void Tower::update(){
	
}
