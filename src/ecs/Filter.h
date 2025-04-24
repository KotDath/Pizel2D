#ifndef FILTER_H
#define FILTER_H

#include <memory>
#include <vector>

#include "BaseComponentStorage.h"
#include "MyIterator.h"

class Filter {
  std::vector<std::shared_ptr<BaseComponentStorage>> _componentStorages;
  size_t _minStorageIndex = -1;
  size_t FindMinComponentStorage() const;

 public:
  Filter(const std::vector<std::shared_ptr<BaseComponentStorage>>
             &componentStorages)
      : _componentStorages(componentStorages) {}
  MyIterator begin();
  MyIterator end();

  friend class MyIterator;
};
#endif  // FILTER_H
