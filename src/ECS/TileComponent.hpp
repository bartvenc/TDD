#pragma once 

#include "ECS.hpp"
#include <SDL2/SDL.h>

class TileComponent : public Component{
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, dstRect;
	Vector2D position;

	TileComponent() = default;

	~TileComponent(){
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xPos, int yPos, const char* path ){

		texture = TextureManager::LoadTexture(path);
		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 64;
		position.x = static_cast<float>(xPos);
		position.y = static_cast<float>(yPos);
		dstRect.x = xPos;
		dstRect.y = yPos;
		dstRect.w = dstRect.h = 64;
	}

	void draw() override{
		TextureManager::Draw(texture, srcRect, dstRect, SDL_FLIP_NONE);
	}
};