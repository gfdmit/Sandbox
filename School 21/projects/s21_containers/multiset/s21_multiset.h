#ifndef S21_CONTAINERS_S21_MULTISET_MULTISET_H_
#define S21_CONTAINERS_S21_MULTISET_MULTISET_H_

#include "../set/s21_set.h"

namespace s21 {

template <typename Key>
class multiset : public s21::set<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename set<Key>::iterator;

  multiset() : set<Key>(){};
  multiset(std::initializer_list<value_type> const &items) : multiset() {
    for (value_type i : items) insert(i);
  }
  multiset(const multiset &ms) : set<Key>(ms){};
  multiset(multiset &&ms) : set<Key>(std::move(ms)){};
  ~multiset() = default;

  multiset operator=(multiset &&ms) {
    set<Key>::operator=(std::move(ms));
    return *this;
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    return s21_tree<Key, Key>::MultInsert(value, value);
  }

  iterator lower_bound(const Key &key) {
    auto it = s21::set<Key>::begin();
    for (; it != s21::set<Key>::end() and key > it->first; it++)
      ;
    return it;
  }

  iterator upper_bound(const Key &key) {
    auto it = s21::set<Key>::begin();
    for (; it != s21::set<Key>::end() and key >= it->first; it++)
      ;
    return it;
  }
};

}  // namespace s21

#endif  // S21_CONTAINERS_S21_MULTISET_MULTISET_H_
