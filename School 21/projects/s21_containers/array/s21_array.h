#ifndef S21_ARRAY_H
#define S21_ARRAY_H
#include <initializer_list>
#include <iostream>

namespace s21 {

template <typename T, size_t N>
class array {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 public:
  array() : size_(0), array_() {}

  array(std::initializer_list<value_type> const &items) {
    size_ = N;
    size_type j = 0;
    for (value_type i : items) {
      array_[j] = i;
      j++;
    }
  }

  array(const array &a) {
    size_ = a.size_;
    for (size_type i = 0; i < size_; i++) {
      array_[i] = a.array_[i];
    }
  }

  array(array &&a) {
    size_ = a.size_;
    a.size_ = 0;
    for (size_type i = 0; i < size_; i++) {
      array_[i] = a.array_[i];
    }
  }

  array &operator=(array &&a) {
    size_ = a.size_;
    a.size_ = 0;
    for (size_type i = 0; i < size_; i++) {
      array_[i] = a.array_[i];
    }
    return *this;
  }

  ~array() {}

  void swap(array &other) {
    for (int i = 0; i < (int)size_; i++) {
      value_type tmp_elem = array_[i];
      array_[i] = other.array_[i];
      other.array_[i] = tmp_elem;
    }
  }

  void fill(const_reference value) {
    for (int i = 0; i < (int)N; i++) {
      array_[i] = value;
    }
  }

  reference at(size_type pos) {
    if (pos >= size_) throw std::out_of_range("Pos > size of array");
    return array_[pos];
  }

  reference operator[](size_type pos) { return array_[pos]; }

  const_reference front() { return array_[0]; }

  const_reference back() { return array_[size_ - 1]; }

  iterator data() { return array_; }

  iterator begin() { return &array_[0]; }

  iterator end() { return &array_[size_ - 1]; }

  iterator operator++(int iter) { return array_[++iter]; }

  bool empty() {
    bool answer = false;
    if (size_ == 0) answer = true;
    return answer;
  }

  size_type size() { return N; }

  size_type max_size() { return size(); }

 private:
  size_type size_ = 0;
  value_type array_[N];
};

}  // namespace s21

#endif  // S21_ARRAY_H