#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <unordered_map>
#include <vector>

#include "ComponentStorage.h"
#include "EntityId.h"

class World {
 public:
  World();
  int CreateEntity();
  void RemoveEntity(int e);
  EntityId GetPackedEntity(int e) const;
  bool UnpackEntity(const EntityId& eId, int& e) const;
  bool IsEntityAlive(int e) const;
  void EntityComponentsChanged(int e, int storageId, bool added);
  template <typename T>
  std::shared_ptr<ComponentStorage<T>> GetRawStorage() {
    const auto typeHash = typeid(T).hash_code();
    const auto foundStorageIterator = _componentStoragesHash.find(typeHash);
    if (foundStorageIterator != _componentStoragesHash.end())
      return std::static_pointer_cast<ComponentStorage<T>>(
          foundStorageIterator->second);
    int storagesCount = _componentStorages.size();
    auto storage = std::make_shared<ComponentStorage<T>>();
    storagesCount++;
    _componentStoragesHash.insert({typeHash, storage});
    if (storagesCount == _componentStorages.capacity()) {
      const int newSize = _storagesCount << 1;
      _componentStorages.reserve(newSize);
    }
    _componentStorages.push_back(storage);
    return storage;
  }
  template <typename T>
  ComponentStorage<T>& GetStorage() {
    return *GetRawStorage<T>();
  }

 private:
  const int DefaultEntitiesCapacity = 64;
  std::vector<EntityId> _entities;
  std::vector<int> _freeEntities;
  std::unordered_map<size_t, std::shared_ptr<BaseComponentStorage>>
      _componentStoragesHash;
  std::vector<std::shared_ptr<BaseComponentStorage>> _componentStorages;
  int _storagesCount = 0;
};

#endif  // WORLD_H
