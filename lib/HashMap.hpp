//
// Created by korbiwe on 2019-02-05.
//

#ifndef HASH_TABLE_HASHMAP_H
#define HASH_TABLE_HASHMAP_H

#include <functional>
#include <list>

#include "util.h"

template <class Key, class T, class Hash = std::hash<T>>
class HashMap {
public:
    using key_t = Key;
    using mapped_t = T;
    using value_t = std::pair<const Key, T>;
    using bucket_t = std::vector<T>;
    using table_t = std::vector<value_t>;
    using reference = value_t&;
    using const_reference = const value_t&;

    explicit HashMap(size_t capacity = 8, double load_factor = 0.75);

    mapped_t& at(const key_t& key);
    const mapped_t& at(const key_t& key) const;
    mapped_t& operator[](key_t&& key);
    mapped_t& operator[](const key_t& key);

    size_t size();
    bool empty();
private:
    size_t _capacity;
    size_t _size = 0;
    double _load_factor;
    table_t _table;
};

template<class Key, class T, class Hash>
HashMap<Key, T, Hash>::HashMap(size_t capacity, double load_factor) :
_capacity(round_up_to_power_of_two(capacity)),
_load_factor(load_factor),
_table(table_t(_capacity)) {

}



#endif //HASH_TABLE_HASHMAP_H
