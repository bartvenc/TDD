#pragma once 

#include "ECS.hpp"
#include <SDL2/SDL.h>

class TileComponent : public Component{
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, dstRect;

	TileComponent() = default;

	~TileComponent(){
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xPos, int yPos, const char* path ){

		texture = TextureManager::LoadTexture(path);
		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 64;

		dstRect.x = xPos;
		dstRect.y = yPos;
		dstRect.w = dstRect.h = 64;
	}

	void draw() override{
		TextureManager::Draw(texture, srcRect, dstRect, SDL_FLIP_NONE);
	}
};