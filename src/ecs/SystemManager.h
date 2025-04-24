#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <memory>
#include <vector>

#include "IInitializer.h"
#include "ISystem.h"
#include "World.h"

class SystemManager {
  std::vector<std::shared_ptr<IInitializer>> _newInitializers;
  std::vector<std::shared_ptr<IInitializer>> _initializers;
  std::vector<std::shared_ptr<ISystem>> _systems;
  World& _world;

 public:
  SystemManager(World& world) : _world(world) {}
  SystemManager& AddInitializer(std::shared_ptr<IInitializer> initializer);
  SystemManager& AddSystem(std::shared_ptr<ISystem> system);
  void Initialize();
  void Update();
};

#endif  // SYSTEMMANAGER_H
