#pragma once

#include "Components.hpp"
#include "SDL2/SDL.h"
#include "../TextureManager.hpp"
#include "Animation.hpp"
#include <map>

class SpriteComponent : public Component{
private:
	bool animated = false;
	int frames = 0;
	int speed = 100;
	TransformComponent *transform;
	SDL_Texture *texture;
	SDL_Rect  srcRect, destRect;
	SDL_Texture *texture2 = TextureManager::LoadTexture("assets/Tower.png");
public:

	int animIndex = 0;
	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;

	SpriteComponent(const char* path){
		//printf("%s\n","Loaded Sprite" );
		setTex(path);
	}

	SpriteComponent(const char* path, bool isAnimated){
		animated = isAnimated;
		Animation idle = Animation(0,8,100);
		Animation walkUp = Animation(1,9,100);
		Animation walkLeft = Animation(2,9,100);
		Animation walkDown = Animation(3,9,100);
		Animation walkRight = Animation(4,9,100);

		animations.emplace("Idle", idle);
		animations.emplace("walkUp", walkUp);
		animations.emplace("walkLeft", walkLeft);
		animations.emplace("walkDown", walkDown);
		animations.emplace("walkRight", walkRight);
	//	printf("%d\n",animations["Walk"].frames );

		Play("Idle");
	//	printf("%s\n","after Play(Idle);" );


	//	printf("%s\n","Loaded Animation Sprites" );
		setTex(path);
	}

	~SpriteComponent(){
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path){
		texture = TextureManager::LoadTexture(path);
		printf("%s\n","Loaded Animation Texture" );
	}
	void changeTex(){
		texture = texture2;
	}

	void init() override{
		//printf("%s\n", "Sprite initiliazed");
		transform = &entity->getComponent<TransformComponent>();
		//printf("transform x = %d\n",transform->x() );
		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override{
		//printf("%s\n","Tried updating" );
		if (animated){
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;
		//printf("%s\n", "updating");
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override{
		//printf("%s\n","tried to draw" );
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}	

	void Play(const char* animName){
		//printf("%s\n", animName);
	//	printf("play frames %d\n",animations["Walk"].frames );
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}

	bool isInside(SDL_Point *mPosition){
		if(SDL_PointInRect(mPosition, &destRect)){
			printf("%s\n", "inside sprite");
			return true;
		}
		return false;
	}

};
