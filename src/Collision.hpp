#pragma once 

#include <SDL2/SDL.h>

class ColliderComponent;
class CircleComponent;

class Collision{

public: 

	static bool AABB(const SDL_Rect& recA,const SDL_Rect& recB);
	static bool AABB(const ColliderComponent& colA, ColliderComponent& colB);
	static bool AABB(const ColliderComponent& colA, SDL_Rect& recB);
	static bool CC(const CircleComponent& b, ColliderComponent& colA);
};
