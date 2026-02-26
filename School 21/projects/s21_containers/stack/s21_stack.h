#ifndef CPP2_S21_CONTAINERS_1_SRC_STACK_S21_STACK_H_
#define CPP2_S21_CONTAINERS_1_SRC_STACK_S21_STACK_H_

#include "../list/s21_list.h"

namespace s21 {

template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack() noexcept;
  stack(std::initializer_list<value_type> const &items) noexcept;
  stack(const stack &other) noexcept;
  stack(stack &&other) noexcept;

  ~stack();

  const_reference top() const;
  bool empty() const noexcept;
  size_type size() const noexcept;
  void push(const_reference value) noexcept;
  void pop();
  void swap(stack &other) noexcept;

  stack &operator=(const stack &other) noexcept;
  stack &operator=(stack &&other) noexcept;
  const_reference operator[](size_t n) {
    if (n < list_.size()) {
      auto i = list_.begin();
      for (; n != 0; ++i, --n) {
      }
      return *i;
    } else {
      throw std::out_of_range("Index out of range");
    }
  }

  template <class... Args>
  void insert_many_front(Args &&...args) {
    for (const auto &item : {args...}) {
      list_.push_front(item);
    }
  }

 private:
  list<T> list_;

  void Clear_();
};

template <typename T>
inline stack<T>::stack() noexcept : list_() {}

template <typename T>
inline stack<T>::stack(std::initializer_list<value_type> const &items) noexcept
    : list_() {
  for (value_type item : items) {
    push(item);
  }
}

template <typename T>
inline stack<T>::stack(const stack &other) noexcept : list_() {
  *this = other;
}

template <typename T>
inline stack<T>::stack(stack &&other) noexcept : list_() {
  *this = std::move(other);
}

template <typename T>
inline stack<T>::~stack() {
  Clear_();
}

template <typename T>
inline void stack<T>::Clear_() {
  while (list_.size() != 0) {
    pop();
  }
}

template <typename T>
inline typename stack<T>::const_reference stack<T>::top() const {
  if (list_.empty()) {
    throw std::out_of_range("Stack is empty");
  }
  return list_.back();
}

template <typename T>
inline bool stack<T>::empty() const noexcept {
  return list_.empty();
}

template <typename T>
inline typename stack<T>::size_type stack<T>::size() const noexcept {
  return list_.size();
}

template <typename T>
inline void stack<T>::push(const_reference value) noexcept {
  list_.push_back(value);
}

template <typename T>
inline void stack<T>::pop() {
  if (list_.empty()) {
    throw std::out_of_range("Stack is empty");
  }
  list_.pop_back();
}

template <typename T>
inline void stack<T>::swap(stack &other) noexcept {
  std::swap(list_, other.list_);
}

template <typename T>
inline stack<T> &stack<T>::operator=(const stack<T> &other) noexcept {
  if (this != &other) {
    list_ = other.list_;
  }
  return *this;
}

template <typename T>
inline stack<T> &stack<T>::operator=(stack<T> &&other) noexcept {
  if (this != &other) {
    list_ = std::move(other.list_);
  }
  return *this;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_STACK_S21_STACK_H_