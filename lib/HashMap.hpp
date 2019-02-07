//
// Created by korbiwe on 2019-02-05.
//

#ifndef HASH_TABLE_HASHMAP_H
#define HASH_TABLE_HASHMAP_H

#include <functional>
#include <vector>
#include <list>
#include <string>

#include "util.h"

namespace lib {

namespace {
using index_t = unsigned;
};


template<class Key, class T, class Hash = std::hash<T>>
class HashMap {
public:
  using key_t = Key;
  using mapped_t = T;
  using pair_t = std::pair<const Key, T>;
  using bucket_t = std::list<pair_t>;
  using table_t = std::vector<bucket_t>;
  using reference = pair_t&;
  using const_reference = const pair_t&;

  explicit HashMap(size_t capacity = 8, double load_factor = 0.75);

  T& at(const key_t& key);

  T& operator[](const key_t& key);

  void erase(key_t&& key);

  void insert(const pair_t& pair);

  size_t size() const;

  bool empty() const;

private:
  void _expand_and_rehash();

  const bucket_t& _resolve_key(const Key& key) const;

  bucket_t& _resolve_key(const Key& key);

  size_t _capacity;
  size_t _size = 0;
  double _load_factor;
  table_t _table;
  Hash _hash_f;
};

template<class Key, class T, class Hash>
HashMap<Key, T, Hash>::HashMap(size_t capacity, double load_factor) :
    _capacity(round_up_to_power_of_two(capacity)),
    _load_factor(load_factor),
    _table(table_t(_capacity)) {

}

template<class Key, class T, class Hash>
void HashMap<Key, T, Hash>::insert(const HashMap::pair_t& pair) {
  Key key = pair.first;
  T value = pair.second;

  bucket_t& bucket = _resolve_key(key);
  bucket.push_back(pair);

  _size++;

  if (_size > _capacity * _load_factor)
    _expand_and_rehash();

}

template<class Key, class T, class Hash>
T& HashMap<Key, T, Hash>::at(const Key& key) {
  bucket_t& bucket = _resolve_key(key);
#ifdef DEBUG
  std::cout << "Lookup in a bucket with " << std::to_string(bucket.size()) << " elements.";
#endif
  auto found = std::find_if(bucket.begin(), bucket.end(), [&key](pair_t pair) { return pair.first == key; });
  if (bucket.empty() || found == bucket.end()) {
    throw std::out_of_range("HashMap::at");
  }
  return found->second;
}

template<class Key, class T, class Hash>
void HashMap<Key, T, Hash>::_expand_and_rehash() {
#ifdef DEBUG
  std::cout << "Rehashing at capacity "
            << std::to_string(_capacity)
            << " and size "
            << std::to_string(_size)
            << "."
            << std::endl;

  std::cout << "Load factor at "
            << std::to_string(static_cast<double>(_size) / _capacity)
            << " before rehashing"
            << std::endl;
#endif

  table_t temporary = _table;
  _capacity *= 2;
  _table = table_t(_capacity);
  for (bucket_t bucket : temporary) {
    if (bucket.empty()) continue;

    for (pair_t entry : bucket) {
      bucket_t& new_bucket = _resolve_key(entry.first);
      new_bucket.push_back(entry);
    }
  }

#ifdef DEBUG
  std::cout
          << "... and "
          << std::to_string(static_cast<double>(_size) / _capacity)
          << " after rehashing."
          << std::endl;
#endif
}

template<class Key, class T, class Hash>
T& HashMap<Key, T, Hash>::operator[](const Key& key) {
  bucket_t& bucket = _resolve_key(key);
#ifdef DEBUG
  std::cout << "Lookup in a bucket with " << std::to_string(bucket.size()) << " elements.";
#endif
  auto found = std::find_if(bucket.begin(), bucket.end(), [&key](const pair_t& pair) { return pair.first == key; });
  if (bucket.empty() || found == bucket.end()) {
    pair_t& default_ = bucket.emplace_back(key, T());
    return default_.second;
  }
  return found->second;
}

template<class Key, class T, class Hash>
bool HashMap<Key, T, Hash>::empty() const {
  return _size == 0;
}

template<class Key, class T, class Hash>
size_t HashMap<Key, T, Hash>::size() const {
  return _size;
}

template<class Key, class T, class Hash>
void HashMap<Key, T, Hash>::erase(Key&& key) {
  bucket_t& bucket = _resolve_key(key);
  auto found = std::find_if(bucket.begin(), bucket.end(), [&key](const pair_t& pair) { return pair.first == key; });
  if (bucket.empty() || found == bucket.end()) {
    throw std::out_of_range("HashMap::erase");
  }
  bucket.erase(found);
}

template<class Key, class T, class Hash>
const typename HashMap<Key, T, Hash>::bucket_t& HashMap<Key, T, Hash>::_resolve_key(const Key& key) const {
  return _table[_hash_f(key) % _capacity];
}

template<class Key, class T, class Hash>
typename HashMap<Key, T, Hash>::bucket_t& HashMap<Key, T, Hash>::_resolve_key(const Key& key) {
  return _table[_hash_f(key) % _capacity];
}

}; // end namespace lib

#endif //HASH_TABLE_HASHMAP_H
