#include "ECS.hpp"

void Entity::addGroup(Group mGroup) {
  groupsBitSet[mGroup] = true;
  manager.AddToGroup(this, mGroup);
}