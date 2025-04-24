#include "MyIterator.h"

int MyIterator::operator*() const { return _currentEntity; }

MyIterator::MyIterator(
    size_t current,
    const std::vector<std::shared_ptr<BaseComponentStorage>> &storages,
    std::span<const int> minStorageEntities, size_t minStorageIndex)
    : _storages(storages),
      _current(current),
      _minStorageEntities(minStorageEntities),
      _minStorageIndex(minStorageIndex),
      _currentEntity(-1) {
        for (const auto& entity : minStorageEntities) {
            _currentEntity = entity;
            if (HasAllComponents()) {
                _currentEntity = entity;
                break;
            }
        }
      }

bool MyIterator::HasAllComponents() const {
  for (size_t i = 0; i < _storages.size(); ++i) {
    if (i == _minStorageIndex) continue;
    if (!_storages[i]->Has(_currentEntity)) {
      return false;
    }
  }
  return true;
}

MyIterator &MyIterator::operator++() {
  while (++_current < _minStorageEntities.size()) {
    _currentEntity = _minStorageEntities[_current];
    if (HasAllComponents()) break;
  }
  return *this;
}

bool MyIterator::operator!=(const MyIterator &other) const {
  return _current != other._current;
}
