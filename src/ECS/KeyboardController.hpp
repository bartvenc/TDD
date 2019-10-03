#pragma once

#include "../Game.hpp"
#include "Components.hpp"
#include "ECS.hpp"

class KeyboardController : public Component {
 public:
  TransformComponent *transform;
  SpriteComponent *sprite;

  void init() override {
    transform = &entity->getComponent<TransformComponent>();
    sprite = &entity->getComponent<SpriteComponent>();
  }

  void update() override {
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    if (keyState[SDL_SCANCODE_S] && keyState[SDL_SCANCODE_D]) {
      transform->velocity.y = 1;
      transform->velocity.x = 1;
      sprite->Play("walkDown");
    } else if (keyState[SDL_SCANCODE_A] && keyState[SDL_SCANCODE_S]) {
      transform->velocity.x = -1;
      transform->velocity.y = 1;
      sprite->Play("walkDown");
    } else if (keyState[SDL_SCANCODE_W] && keyState[SDL_SCANCODE_D]) {
      transform->velocity.y = -1;
      transform->velocity.x = 1;
      sprite->Play("walkUp");
    } else if (keyState[SDL_SCANCODE_W] && keyState[SDL_SCANCODE_A]) {
      transform->velocity.y = -1;
      transform->velocity.x = -1;
      sprite->Play("walkUp");
    } else if (keyState[SDL_SCANCODE_S]) {
      transform->velocity.y = 1;
      sprite->Play("walkDown");
    } else if (keyState[SDL_SCANCODE_D]) {
      transform->velocity.x = 1;
      sprite->Play("walkRight");
    } else if (keyState[SDL_SCANCODE_A]) {
      transform->velocity.x = -1;
      sprite->Play("walkLeft");
    } else if (keyState[SDL_SCANCODE_W]) {
      transform->velocity.y = -1;
      sprite->Play("walkUp");
    } else {
      transform->velocity.x = 0;
      transform->velocity.y = 0;
      sprite->Play("Idle");
    }
  }
};