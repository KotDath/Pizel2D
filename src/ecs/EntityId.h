#ifndef ENTITYID_H
#define ENTITYID_H

#include <iostream>
#include <vector>

class EntityId {
 public:
  const int Id;
  EntityId(int id, int gen);
  void AddComponent(int component);
  int RemoveComponent(int component);
  bool IsRemoved() const;
  const std::vector<int>& Components() const;
  int Gen() const;
  void Remove();
  void Recycle();
  bool Equals(const EntityId& other) const;
  bool operator==(const EntityId& other) const;
  bool operator!=(const EntityId& other) const;
  friend std::ostream& operator<<(std::ostream& os, const EntityId& eId);

 private:
  std::vector<int> _components;
  int _gen;
};

#endif  // ENTITYID_H
