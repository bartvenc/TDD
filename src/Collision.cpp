#include "Collision.hpp"
#include "ECS/ColliderComponent.hpp"
#include "ECS/CircleComponent.hpp"
#include "MatH.hpp"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB) {
  if (recA.x + recA.w - 32 >= recB.x && recB.x + recB.w - 32 >= recA.x &&
      recA.y + recA.h - 32 >= recB.y && recB.y + recB.h - 32 >= recA.y) {
    return true;
  }
  return false;
}

bool Collision::AABB(const ColliderComponent& colA, SDL_Rect& recB) {
  if (AABB(colA.collider, recB)) {
    /// printf("%s hit: %s\n", colA.tag.c_str(), colB.tag.c_str() );
    printf("Cant build here\n");
    return true;
  } else {
    return false;
  }
}

bool Collision::AABB(const ColliderComponent& colA, ColliderComponent& colB) {
  if (AABB(colA.collider, colB.collider)) {
    // printf("%s hit: %s\n", colA.tag.c_str(), colB.tag.c_str() );
    return true;
  } else {
    return false;
  }
}

bool Collision::CC(const CircleComponent& a, ColliderComponent& colB) {
  SDL_Rect& b = colB.collider;

  // Closest point on collision box
  int cX, cY;
  /* printf("ax: %d\n", a.x );
   printf("ay: %d\n", a.y );
   printf("ar: %d\n", a.r );*/
  // Find closest x offset
  if (a.x < b.x) {
    cX = b.x;
  } else if (a.x > b.x + b.w) {
    cX = b.x + b.w;
  } else {
    cX = a.x;
  }

  // Find closest y offset
  if (a.y < b.y) {
    cY = b.y;
  } else if (a.y > b.y + b.h) {
    cY = b.y + b.h;
  } else {
    cY = a.y;
  }
  // printf("cX = %d, cY = %d \n", cX, cY );
  // If the closest point is inside the circle
  if (MatH::distanceSquared(a.x, a.y, cX, cY) < a.r * a.r) {
    // This box and the circle have collided
    // printf("%s\n", "in towers range" );
    return true;
  }

  // If the shapes have not collided
  return false;
}