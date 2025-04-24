#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

#include "Component.h"

template <class T>
class Entity {
  std::vector<Component> _components;

 public:
  Entity() {}
  void Add<T>(args);
  T& Get<T>();
};

#endif  // ENTITY_H
