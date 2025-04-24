#include "World.h"
#include "EntityId.h"

World::World() {
  _entities.reserve(DefaultEntitiesCapacity);
  _freeEntities.reserve(DefaultEntitiesCapacity);
}

bool World::UnpackEntity(const EntityId& eId, int& e) const {
  e = eId.Id;
  return IsEntityAlive(e) && eId.Gen() == _entities[e].Gen();
}

bool World::IsEntityAlive(int e) const {
  auto& entity = _entities[e];
  return !entity.IsRemoved() && entity.Id > 0 && entity.Id < _entities.size() &&
         e == entity.Id;
}

int World::CreateEntity() {
  int entityId = 0;
  if (!_freeEntities.empty()) {
    entityId = _freeEntities.back();
    _freeEntities.pop_back();
    _entities[entityId].Recycle();
  } else {
    entityId = _entities.size();
    _entities.emplace_back(entityId, 1);
  }
  return entityId;
}

void World::EntityComponentsChanged(const int ent, const int storageId,
                                    const bool added) {
  auto& entity = _entities[ent];
  if (added) {
    entity.AddComponent(storageId);
  } else {
    const int newComponentsCount = entity.RemoveComponent(storageId);
    if (newComponentsCount == 0) {
      RemoveEntity(ent);
    }
  }
}

void World::RemoveEntity(int ent) {
  auto& entity = _entities[ent];
  if (entity.IsRemoved()) return;
  const auto& components = entity.Components();
  if (!components.empty()) {
    for (int i = components.size() - 1; i >= 0; i--)
      _componentStorages[components[i]]->Remove(ent);
  } else {
    entity.Remove();
    _freeEntities.push_back(entity.Id);
  }
}
