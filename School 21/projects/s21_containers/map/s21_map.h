#ifndef S21_CONTAINERS_S21_MAP_MAP_H_
#define S21_CONTAINERS_S21_MAP_MAP_H_

#include "../tree/s21_tree.h"

namespace s21 {
template <typename Key, typename T>
class map : public s21_tree<Key, T> {
 private:
  /* data */
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename s21_tree<Key, T>::iterator;
  // using const_iterator =

  // Constructors
  map() : s21_tree<Key, T>(){};
  map(std::initializer_list<typename s21_tree<Key, T>::value_type> const &items)
      : s21_tree<Key, T>(items){};
  map(const map &m) : s21_tree<Key, T>(m){};
  map(map &&m) : s21_tree<Key, T>() { *this = std::move(m); };  //?

  // Destructor
  ~map() = default;  //{ ~s21_tree<Key, T>(); };

  // Overload operators
  map &operator=(map &&m) {
    s21_tree<Key, T>::operator=(std::move(m));
    return *this;
  };
  map &operator=(const map &m) {
    s21_tree<Key, T>::operator=(m);
    return *this;
  };

  // Element access
  T &at(const Key &key) { return s21_tree<Key, T>::at(key); };
  T &operator[](const Key &key) { return s21_tree<Key, T>::operator[](key); }

  // Map Iterators
  typename s21_tree<Key, T>::iterator begin() {
    return s21_tree<Key, T>::begin();
  }
  typename s21_tree<Key, T>::iterator end() { return s21_tree<Key, T>::end(); }

  // Map Capacity
  bool empty() { return s21_tree<Key, T>::empty(); };
  typename s21_tree<Key, T>::size_type size() {
    return s21_tree<Key, T>::size();
  };
  typename s21_tree<Key, T>::size_type max_size() {
    return s21_tree<Key, T>::max_size();
  };

  // Map Modifiers
  void clear() { s21_tree<Key, T>::clear(); };
  std::pair<typename s21_tree<Key, T>::iterator, bool> insert(
      const value_type &value) {
    return s21_tree<Key, T>::insert(value);
  };
  std::pair<typename s21_tree<Key, T>::iterator, bool> insert(const Key &key,
                                                              const T &obj) {
    return s21_tree<Key, T>::insert(key, obj);
  };

  // template <typename... Args>
  // std::vector<std::pair<typename s21_tree<Key, T>::iterator, bool>>
  // insert_many(
  //     Args &&...args) {
  //   return s21_tree<Key, T>::insert_many(args...);
  // };

  std::pair<typename s21_tree<Key, T>::iterator, bool> insert_or_assign(
      const Key &key, const T &obj) {
    return s21_tree<Key, T>::insert_or_assign(key, obj);
  };

  void erase(typename s21_tree<Key, T>::iterator pos) {
    s21_tree<Key, T>::erase(pos);
  };
  void swap(map &other) { s21_tree<Key, T>::swap(other); };
  void merge(map &other) { s21_tree<Key, T>::merge(other); };

  // Map Lookup
  bool contains(const Key &key) { return s21_tree<Key, T>::contains(key); };

  // bonus Part 3
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> res;
    res.reserve(sizeof...(args));
    for (auto i : {args...}) {
      res.push_back(insert(i));
    }
    return res;
  };
};

// template<typename K, typename V>
// s21_map::s21_map(/* args */)
// {
// }

// template<typename K, typename V>
// s21_map::~s21_map()
// {
}  // namespace s21

#endif