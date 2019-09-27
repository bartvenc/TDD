#include "Tower.hpp"
#include <math.h> 

Tower::Tower(Manager* man) : manager(man){

}

Tower::~Tower(){}

void Tower::addTower(float x, float y){
	auto& tower(manager->addEntity());
	tower.addComponent<TransformComponent>(x, y, 64, 64,1);
	tower.addComponent<SpriteComponent>("assets/T1.png", false);
	tower.addComponent<CircleComponent>(x,y,200);
	//tower.addComponent<ColliderComponent>("tower");
	tower.addGroup(Game::groupTowers);	
	t = &tower.getComponent<TransformComponent>();
	s = &tower.getComponent<SpriteComponent>();	
}

void Tower::targetEnemy(Vector2D pos, Vector2D vel){

	//enemyPos.x = 1 * pos.x / (fabs(pos.x) +  fabs(pos.y)); 
	//enemyPos.y = 1 * pos.x / (fabs(pos.x) +  fabs(pos.y)); 
	
	//enemyPos.x = pos.x - t->position.x;	
	//enemyPos.y = pos.y - t->position.y;


	Vector2D totarget = (pos+vel*25) - t->position;
	Vector2D trackTarget = pos - t->position;
	//printf("totarget created: ");
	//std::cout<<totarget<<std::endl;

	trackTarget = trackTarget.Normalize();
	enemyPos = totarget.Normalize();
	//printf("totarget normalized: ");
	//std::cout<<enemyPos<<std::endl;
	//printf("Enemy pos Velocitt: ");
	//std::cout<<enemyPos<<std::endl;
	s->angle= (atan2(totarget.x, -totarget.y)*180/3.14159);

	//totarget;
	//printf("totarget mutiplied by 3: ");
	//std::cout<<totarget<<std::endl;

	enemyPos*7;

	//printf("pos: ");
	//std::cout<<pos<<std::endl;

	//
	hasTarget = true;
}

void Tower::update() {
	int currentTime = SDL_GetTicks();
	//printf("%s","tower update enemyPos" );
	//printf("(currentTime % 2000)= %d\n",(currentTime % 5000) );
	//std::cout<<enemyPos<<std::endl;
	if((currentTime % 1000) < 10  && hasTarget){
		
		printf("Creating projectile with angle: %f\n", s->angle );
		auto& projectile(manager->addEntity());
		projectile.addComponent<TransformComponent>(t->position.x, t->position.y, 35, 35, 1);
		projectile.addComponent<SpriteComponent>("assets/Bullet.png", false);
		projectile.addComponent<ProjectileComponent>(800, 7, enemyPos);
		projectile.addComponent<CircleComponent>(t->position.x, t->position.y,50);
		projectile.addComponent<ColliderComponent>("projectile");
		projectile.addGroup(Game::groupProjectiles);
	}
	hasTarget = false;
}
