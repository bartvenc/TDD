#pragma once
#include "ECS/Components.hpp"

class Tower{
private:
Manager* manager;
public: 

	Tower(Manager* man);
	~Tower();
	TransformComponent* t;
	SpriteComponent* s;
	CircleComponent * range;
	void init();
	void update();
	void draw();
	void addTower(float x, float y);


};