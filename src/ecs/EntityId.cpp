#include "EntityId.h"

#include <algorithm>

EntityId::EntityId(int id, int gen) : _gen(gen), Id(id) {
  _components.reserve(6);
}

void EntityId::AddComponent(int component) { _components.push_back(component); }

int EntityId::RemoveComponent(int component) {
    auto it = std::find(_components.begin(), _components.end(), component);
    if (it != _components.end()) {
        _components.erase(it);
        return 1;
    }
    return 0;
 }

const std::vector<int>& EntityId::Components() const { return _components; }

int EntityId::Gen() const { return _gen; }

bool EntityId::Equals(const EntityId& other) const {
  return Id == other.Id && _gen == other._gen;
}

bool EntityId::operator==(const EntityId& other) const { return Equals(other); }

bool EntityId::operator!=(const EntityId& other) const {
  return !Equals(other);
}

std::ostream& operator<<(std::ostream& os, const EntityId& eId) {
  os << eId.Id << "(" << eId.Gen() << ")";
  return os;
}

bool EntityId::IsRemoved() const { return _gen < 0; }

void EntityId::Remove() {
  _gen = -(_gen + 1);
  _components.clear();
}
void EntityId::Recycle() { _gen *= -1; }
