#ifndef S21_VECTOR_H
#define S21_VECTOR_H
#include <iostream>

using namespace std;
namespace s21 {

template <typename T>
class VectorIterator;

template <typename T>
class VectorConstIterator;

template <typename T>
class vector {
  using value_type = T;
  using size_type = size_t;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = VectorIterator<T>;
  using const_iterator = VectorConstIterator<T>;

 public:
  // Constructors
  vector() : capacity_(2), cur_space_(0) { array_ = new value_type[1]; }

  vector(size_type n) {
    capacity_ = n;
    cur_space_ = 0;
    array_ = new value_type[n];
  }

  vector(std::initializer_list<value_type> const& items) {
    capacity_ = items.size();
    cur_space_ = items.size();
    array_ = new value_type[capacity_];
    int i = 0;
    for (auto iter_list = items.begin();
         iter_list != items.end() && i < (int)items.size(); iter_list++, i++) {
      array_[i] = *iter_list;
    }
  }

  vector(const vector& v) {
    cur_space_ = v.cur_space_;
    capacity_ = v.capacity_;
    array_ = new value_type[capacity_];
    for (size_type i = 0; i < cur_space_; i++) {
      array_[i] = v.array_[i];
    }
  }

  vector(vector&& v) noexcept
      : array_(v.array_), capacity_(v.capacity_), cur_space_(v.cur_space_) {
    v.capacity_ = 0;
    v.cur_space_ = 0;
    v.array_ = nullptr;
  }

  vector& operator=(vector&& v) {
    if (this != &v) {
      delete[] array_;
      capacity_ = v.capacity_;
      cur_space_ = v.cur_space_;
      array_ = v.array_;
      v.array_ = nullptr;
    }
    return *this;
  }

  ~vector() { delete[] array_; }

  reference operator[](size_type pos) {
    if (pos >= capacity_)
      throw std::out_of_range("Index is outside the vector");
    return array_[pos];
  }

  reference at(size_type pos) {
    if (pos >= capacity_)
      throw std::out_of_range("Index is outside the vector");
    return array_[pos];
  }

  const_reference front() {
    if (this->empty()) throw std::range_error("Vector is empty");
    return array_[0];
  }

  const_reference back() {
    if (this->empty()) throw std::range_error("Vector is empty");
    return array_[cur_space_ - 1];
  }

  value_type* data() { return array_; }

  iterator begin() { return iterator(array_); }

  iterator end() { return iterator(array_ + cur_space_); }

  const_iterator begin() const { return const_iterator(array_); }

  const_iterator end() const { return const_iterator(array_ + cur_space_); }

  bool empty() {
    bool answer = false;
    if (this->size() == 0) answer = true;
    return answer;
  }

  size_type size() { return cur_space_; }

  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) - 1;
  }

  size_type capacity() { return capacity_; }

  void reserve(size_type size) {
    if (size <= cur_space_) {
      cur_space_ = size;
    } else {
      capacity_ = size;
      value_type* new_arr = new value_type[capacity_];
      for (size_type i = 0; i < cur_space_; i++) {
        new_arr[i] = array_[i];
      }
      delete[] array_;
      array_ = new_arr;
    }
  }

  void shrink_to_fit() {
    if (cur_space_ < capacity_) {
      this->reserve(cur_space_);
      capacity_ = cur_space_;
    }
  }

  void clear() { cur_space_ = 0; }

  iterator insert(iterator pos, const_reference value) {
    size_type position = &(*pos) - array_;
    cur_space_++;
    if (cur_space_ > capacity_) {
      capacity_ *= 2;
      this->reserve(capacity_);
    }
    for (int i = cur_space_; i > (int)position; i--) {
      array_[i] = array_[i - 1];
    }
    array_[position] = value;
    auto iter = begin();
    for (int i = 0; i < (int)position; i++) ++iter;
    return iter;
  }

  void erase(iterator pos) {
    size_type position = &(*pos) - array_;
    if (/*position < 0 || */ position > cur_space_) {
      throw std::out_of_range("Index is out of range");
    }
    for (size_t i = 0; i < cur_space_; i++) {
      if (i >= position) {
        array_[i] = array_[i + 1];
      }
    }
    cur_space_--;
  }

  void push_back(const value_type v) {
    if (cur_space_ >= capacity_) {
      capacity_ *= 2;
      this->reserve(capacity_);
      array_[cur_space_] = v;
      cur_space_++;
    } else {
      array_[cur_space_] = v;
      cur_space_++;
    }
  }

  void pop_back() {
    if (cur_space_ > 0)
      cur_space_--;
    else
      throw std::invalid_argument("Empty vector");
  }

  void swap(vector& other) {
    std::swap(cur_space_, other.cur_space_);
    std::swap(capacity_, other.capacity_);
    std::swap(array_, other.array_);
  }

  size_type getCapacity() { return capacity_; }

  size_type getCur_space() { return cur_space_; }

 private:
  T* array_;
  size_type capacity_;
  size_type cur_space_;
};

template <typename T>
class VectorIterator {
  using value_type = T;
  using pointer = value_type*;
  using reference = value_type&;

 public:
  VectorIterator(pointer value) : m_ptr(value) {}

  reference operator*() { return *m_ptr; }

  VectorIterator& operator++() {
    m_ptr++;
    return *this;
  }

  VectorIterator& operator--() {
    m_ptr--;
    return *this;
  }

  bool operator==(const VectorIterator& rhs) {
    bool answer = true;
    if (m_ptr == rhs.m_ptr) answer = false;
    return answer;
  }

  bool operator!=(const VectorIterator& rhs) { return !(m_ptr == rhs.m_ptr); }

 private:
  pointer m_ptr;
};

template <typename T>
class VectorConstIterator {
  using value_type = T;
  using pointer = value_type*;
  using reference = value_type&;

 public:
  VectorConstIterator(const pointer value) : m_ptr(value) {}

  reference operator*() { return *m_ptr; }

  VectorConstIterator& operator++() {
    m_ptr++;
    return *this;
  }

  VectorConstIterator& operator--() {
    m_ptr--;
    return *this;
  }

  bool operator==(VectorConstIterator& rhs) {
    bool answer = true;
    if (m_ptr == rhs.m_ptr) answer = false;
    return answer;
  }

  bool operator!=(VectorConstIterator& rhs) { return !(m_ptr == rhs.m_ptr); }

 private:
  pointer m_ptr;
};

}  // namespace s21

#endif