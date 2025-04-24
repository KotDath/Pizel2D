#ifndef C_COLLISION_H
#define C_COLLISION_H

#include <vector>

using EntityId = int;
struct C_Collision {
  std::vector<EntityId> entities;
};

#endif  // C_COLLISION_H
