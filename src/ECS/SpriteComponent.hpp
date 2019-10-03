#pragma once

#include "Components.hpp"
#include "SDL2/SDL.h"
#include "../TextureManager.hpp"
#include "Animation.hpp"
#include <map>

class SpriteComponent : public Component {
 private:
  bool animated = false;
  int frames = 0;
  int speed = 100;
  TransformComponent* transform;
  SDL_Texture* texture;
  SDL_Rect srcRect, destRect;
  SDL_Texture* texture2 = TextureManager::LoadTexture("assets/Tower.png");

 public:
  double angle = 0;
  int animIndex = 0;
  std::map<const char*, Animation> animations;

  SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

  SpriteComponent() = default;

  SpriteComponent(const char* path) {
 
    setTex(path);
  }

  SpriteComponent(const char* path, bool isAnimated) {
    animated = isAnimated;
    Animation idle = Animation(0, 8, 100);
    Animation walkUp = Animation(1, 9, 100);
    Animation walkLeft = Animation(2, 9, 100);
    Animation walkDown = Animation(3, 9, 100);
    Animation walkRight = Animation(4, 9, 100);

    animations.emplace("Idle", idle);
    animations.emplace("walkUp", walkUp);
    animations.emplace("walkLeft", walkLeft);
    animations.emplace("walkDown", walkDown);
    animations.emplace("walkRight", walkRight);

    Play("Idle");

    setTex(path);
  }

  ~SpriteComponent() { SDL_DestroyTexture(texture); }

  void setTex(const char* path) {
    texture = TextureManager::LoadTexture(path);
  }
  void changeTex() { texture = texture2; }

  void init() override {
    transform = &entity->getComponent<TransformComponent>();
    srcRect.x = srcRect.y = 0;
    srcRect.w = transform->width;
    srcRect.h = transform->height;
  }

  void update() override {
    if (animated) {
      srcRect.x =
          srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
    }

    srcRect.y = animIndex * transform->height;
    destRect.x = static_cast<int>(transform->position.x);
    destRect.y = static_cast<int>(transform->position.y);
    destRect.w = transform->width * transform->scale;
    destRect.h = transform->height * transform->scale;
  }

  void draw() override {
    TextureManager::Draw(texture, srcRect, destRect, angle, spriteFlip);
  }

  void Play(const char* animName) {
    frames = animations[animName].frames;
    animIndex = animations[animName].index;
    speed = animations[animName].speed;
  }

  bool isInside(int x) {
    SDL_Point mPosition;
    SDL_GetMouseState(&mPosition.x, &mPosition.y);
    if (SDL_PointInRect(&mPosition, &destRect)) {
      printf("%d inside sprite cord: %d:%d\n", x, mPosition.x, mPosition.y);
      return true;
    }
    return false;
  }
};
