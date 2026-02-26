#ifndef S21_CONTAINERS_S21_SET_SET_H_
#define S21_CONTAINERS_S21_SET_SET_H_

#include "../tree/s21_tree.h"

namespace s21 {

template <typename Key>
class set : public s21_tree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename s21_tree<Key, Key>::iterator;
  using size_type = typename s21_tree<Key, Key>::size_type;

  // Constructors
  set() : s21_tree<Key, Key>(){};
  set(std::initializer_list<value_type> const &items) : set() {
    for (value_type i : items) insert(i);
  }
  set(const set &s) : s21_tree<Key, Key>(s){};
  set(set &&s) : s21_tree<Key, Key>() { *this = std::move(s); };
  // Destructor
  ~set() = default;

  // Overload operators
  set operator=(set &s) {
    s21_tree<Key, Key>::operator=(s);
    return *this;
  }

  set operator=(set &&s) {
    s21_tree<Key, Key>::operator=(std::move(s));
    return *this;
  }

  // value_type *operator->() { return &(node_set->data->element_); }
  reference operator*() {
    typename s21_tree<Key, Key>::s21_tree *rt;
    rt = s21_tree<Key, Key>::GetAdress(this);
    return rt->data->first;
  }

  // Set Iterators
  iterator begin() { return s21_tree<Key, Key>::begin(); }

  iterator end() { return s21_tree<Key, Key>::end(); }

  // Set Capacity
  bool empty() { return s21_tree<Key, Key>::empty(); }
  size_type size() { return s21_tree<Key, Key>::size(); }
  size_type max_size() { return s21_tree<Key, Key>::max_size(); }

  // Set Modifiers
  void clear() { s21_tree<Key, Key>::clear(); }
  std::pair<iterator, bool> insert(const value_type &value) {
    return s21_tree<Key, Key>::insert(value, value);
  }
  void erase(iterator pos) { s21_tree<Key, Key>::erase(pos); }
  void swap(set &other) { s21_tree<Key, Key>::swap(other); }
  void merge(set &other) { s21_tree<Key, Key>::merge(other); }

  // Set Lookup
  iterator find(const Key &key) { return s21_tree<Key, Key>::s21_search(key); }
  bool contains(const Key &key) { return s21_tree<Key, Key>::contains(key); }

  // bonus Part 3
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> res;
    res.reserve(sizeof...(args));
    for (auto i : {args...}) {
      res.push_back(insert(i));
    }
    return res;
  }
};

}  // namespace s21

#endif  // S21_CONTAINERS_S21_SET_SET_H_
