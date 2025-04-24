#ifndef MYITERATOR_H
#define MYITERATOR_H

#include <iterator>
#include <memory>
#include <span>
#include <vector>

#include "BaseComponentStorage.h"

class MyIterator {
  const std::span<const int> _minStorageEntities;
  const std::vector<std::shared_ptr<BaseComponentStorage>> &_storages;
  const size_t _minStorageIndex;
  int _currentEntity;
  size_t _current;

  // Helper method to check if the current entity exists in all component
  // storages
  bool HasAllComponents() const;

 public:
  bool operator!=(const MyIterator &other) const;
  using iterator_category = std::input_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = int;
  using pointer = int *;
  using reference = int &;

  // Constructor with all necessary parameters
  MyIterator(size_t current,
             const std::vector<std::shared_ptr<BaseComponentStorage>> &storages,
             std::span<const int> minStorageEntities, size_t minStorageIndex);

  MyIterator &operator++();
  int operator*() const;
};

#endif  // MYITERATOR_H
