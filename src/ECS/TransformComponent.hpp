#pragma once
#include "../Vector2D.hpp"
#include "Components.hpp"

class TransformComponent : public Component {
 private:
 public:
  Vector2D position;
  Vector2D velocity;

  int height = 64;
  int width = 64;
  int scale = 1;

  int speed = 1;

  TransformComponent() { position.Zero(); }

  TransformComponent(int sc) {
    position.Zero();
    scale = sc;
  }

  TransformComponent(float x, float y) { position.Zero(); }

  TransformComponent(int h, int w, int sc) {
    height = h;
    width = w;
    scale = scale;
  }

  TransformComponent(float x, float y, int h, int w, int sc) {
    position.x = x;
    position.y = y;
    height = h;
    width = w;
    scale = scale;
  }

  TransformComponent(float x, float y, float velX, float velY, int h, int w,
                     int sc) {
    position.x = x;
    position.y = y;
    height = h;
    width = w;
    scale = scale;
    velocity.x = velX;
    velocity.y = velY;
  }

  void printPosition() { printf("pos = %d, %d, \n", position.x, position.y); }

  void init() override { velocity.Zero(); }
  void update() override {
    position.x += velocity.x * speed;
    position.y += velocity.y * speed;
    // printf("%s\n", "transform.position.x update" );
  }
};