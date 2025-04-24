#include "Filter.h"

#include <cstdio>

MyIterator Filter::begin() {
  _minStorageIndex = FindMinComponentStorage();
  const auto& minStorageEntities =
      _componentStorages[_minStorageIndex]->Entities();
  const int current = 0;
  return MyIterator(current, _componentStorages, minStorageEntities,
                    _minStorageIndex);
}

MyIterator Filter::end() {
  _minStorageIndex = FindMinComponentStorage();
  const auto& minStorageEntities =
      _componentStorages[_minStorageIndex]->Entities();
  const int current = minStorageEntities.size();
  return MyIterator(current, _componentStorages, minStorageEntities,
                    _minStorageIndex);
}

size_t Filter::FindMinComponentStorage() const {
  size_t minIndex = 0;
  size_t minCount = _componentStorages[0]->Count();
  for (size_t i = 1; i < _componentStorages.size(); ++i) {
    if (_componentStorages[i]->Count() < minCount) {
      minCount = _componentStorages[i]->Count();
      minIndex = i;
    }
  }
  return minIndex;
}
