#pragma once

#include "../Game.hpp"
#include "ECS.hpp"
#include "Components.hpp"


class KeyboardController : public Component{
public:
	TransformComponent * transform;
	SpriteComponent *sprite;

	void init() override{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		//printf("%d\n",sprite->animIndex );

		//printf("transform->velocity.y =  %d\n",transform->velocity.y );
	}

	void update() override{
		//printf("%s\n","update override KC" );
		const Uint8* keyState = SDL_GetKeyboardState(NULL);
		

		if(keyState[SDL_SCANCODE_S] && keyState[SDL_SCANCODE_D]){
			transform->velocity.y = 1;
			transform->velocity.x = 1;
			sprite->Play("walkDown");
		}else if(keyState[SDL_SCANCODE_A] && keyState[SDL_SCANCODE_S]){
			transform->velocity.x = -1;
			transform->velocity.y = 1;
			sprite->Play("walkDown");
		}else if(keyState[SDL_SCANCODE_W] && keyState[SDL_SCANCODE_D]){
			transform->velocity.y = -1;
			transform->velocity.x = 1;
			sprite->Play("walkUp");
		}else if(keyState[SDL_SCANCODE_W] && keyState[SDL_SCANCODE_A] ){
			transform->velocity.y = -1;
			transform->velocity.x = -1;
			sprite->Play("walkUp");
		}else if(keyState[SDL_SCANCODE_S]){
			transform->velocity.y = 1;
			sprite->Play("walkDown");
			//printf("%s\n","aaaaaaaaaaaaa" );
		}else if(keyState[SDL_SCANCODE_D]){
			transform->velocity.x = 1;
			sprite->Play("walkRight");
			//printf("%s\n","aaaaaaaaaaaaa" );
		}else if(keyState[SDL_SCANCODE_A]){
			transform->velocity.x = -1;
			sprite->Play("walkLeft");
			//printf("%s\n","aaaaaaaaaaaaa" );
		}else if(keyState[SDL_SCANCODE_W]){
			transform->velocity.y = -1;
			sprite->Play("walkUp");
			//SDL_PumpEvents();
			//printf("%s\n","aaaaaaaaaaaaa" );
		}else{
			transform->velocity.x = 0;
			transform->velocity.y = 0;
			sprite->Play("Idle");

		}




/*
		if (Game::event.type == SDL_KEYDOWN){
			printf("%s\n","update override SDL_KEYDOWN" );
			//printf("%s\n",Game::event.key.keysym.sym );
			switch (Game::event.key.keysym.sym){

				case SDLK_w :
					transform->velocity.y = -1;
					printf("%s\n","w" );
					break;
				case SDLK_a :
					transform->velocity.x = -1;
					break;
				case SDLK_d :
					transform->velocity.x = 1;
					break;
				case SDLK_s :
					transform->velocity.y = 1;
					break;
				default:
					break;		
			}
		}

		if (Game::event.type == SDL_KEYUP){
			printf("%s\n","update override SDL_KEYUP" );
			switch (Game::event.key.keysym.sym){
				case SDLK_w :
					transform->velocity.y = 0;
					break;
				case SDLK_a :
					transform->velocity.x = 0;
					break;
				case SDLK_d :
					transform->velocity.x = 0;
					break;
				case SDLK_s :
					transform->velocity.y = 0;
					break;
				default:
					break;		
			}
		}
		*/
	}
};