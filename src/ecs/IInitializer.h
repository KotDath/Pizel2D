#ifndef IINITIALIZER_H
#define IINITIALIZER_H

#include "World.h"

class IInitializer {
 protected:
  World& world;

 public:
  IInitializer(World& world) : world(world) {}
  const World& GetWorld() const { return world; }
  virtual ~IInitializer() = default;
  virtual void OnInit() = 0;
};

#endif  // IINITIALIZER_H
