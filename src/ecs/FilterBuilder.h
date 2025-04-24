#ifndef FILTERBUILDER_H
#define FILTERBUILDER_H

#include <vector>
#include <memory>

#include "BaseComponentStorage.h"
#include "Filter.h"
#include "World.h"

class FilterBuilder {
  World& _world;
  std::vector<std::shared_ptr<BaseComponentStorage>> _componentStorages;

 public:
  FilterBuilder(World& world) : _world(world) { _componentStorages.reserve(4); }
  template <typename T>
  FilterBuilder& With() {
    auto storage = _world.GetRawStorage<T>();
    _componentStorages.push_back(storage);
    return *this;
  }
  Filter Build() const { return Filter(_componentStorages); }
};

#endif  // FILTERBUILDER_H
