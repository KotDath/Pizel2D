#ifndef COMPONENTSTORAGE_H
#define COMPONENTSTORAGE_H

#include <algorithm>  // for std::fill_n
#include <span>
#include <vector>

#include "BaseComponentStorage.h"

class World;

template <typename T>
class ComponentStorage : public BaseComponentStorage {
  std::vector<T> _data;
  std::vector<int> _sparse;
  std::vector<int> _dense;

  int _count;

  void Resize(const int sparseSize, const int dataSize) {
    int oldSparseSize = _sparse.size();
    if (oldSparseSize < sparseSize) {
      _sparse.resize(sparseSize);
      std::fill_n(_sparse.data() + oldSparseSize, sparseSize - oldSparseSize,
                  -1);
    }
    int oldDataSize = _dense.size();
    if (oldDataSize < dataSize) {
      _dense.resize(dataSize);
      _data.resize(dataSize);
      std::fill_n(_dense.data() + oldDataSize, dataSize - oldDataSize, -1);
    }
  }

 public:
  ComponentStorage() { Resize(64, 64); }

  bool Has(const int entityIid) const override {
    return entityIid < _sparse.size() && _sparse[entityIid] != -1;
  }
  

  T &Ref(const int entityIid) { return _data[_sparse[entityIid]]; }

  void Add(const int entityIid, const T &value) {
    Resize((entityIid / 64 + 1) * 64,
           _data.size() == _count + 1 ? _data.size() + 64 : _data.size());
    _data[_count] = value;
    _dense[_count] = entityIid;
    _sparse[entityIid] = _count;
    _count++;
  }

  void Remove(const int entityIid) override {
    int arrayIndex = _sparse[entityIid];
    int lastEntityIid = _dense[--_count];
    _data[arrayIndex] = _data[_count];
    _dense[arrayIndex] = lastEntityIid;
    _sparse[lastEntityIid] = arrayIndex;
    _sparse[entityIid] = -1;
  }

  const std::span<const T> All() const {
    return std::span(_data.begin(), _count);
  }

  std::span<const int> Entities() const override {
    return std::span(_dense.begin(), _count);
  }

  int Count() const override {
    return _count;
  }
};

#endif  // COMPONENTSTORAGE_H
