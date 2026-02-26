#ifndef CPP2_S21_CONTAINERS_1_SRC_LIST_S21_LIST_H_
#define CPP2_S21_CONTAINERS_1_SRC_LIST_S21_LIST_H_

#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  list() noexcept;
  explicit list(size_type n) noexcept;
  list(std::initializer_list<value_type> const& items) noexcept;
  list(const list& other) noexcept;
  list(list&& other) noexcept;

  ~list();

  void push_front(const_reference data) noexcept;
  void push_back(const_reference data) noexcept;
  void pop_front() noexcept;
  void pop_back() noexcept;
  const_reference front() const;
  const_reference back() const noexcept;
  void swap(list& other) noexcept;
  void sort() noexcept;
  void merge(list& other) noexcept;
  void reverse() noexcept;
  void unique() noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  bool empty() const noexcept;
  void clear() noexcept;

  list<T>& operator=(const list<T>& other) noexcept;
  list<T>& operator=(list<T>&& other) noexcept;
  const_reference operator[](size_t n) {
    if (n < size_) {
      auto i = begin();
      for (; n != 0; ++i, --n) {
      }
      return *i;
    } else {
      throw std::out_of_range("Index out of range");
    }
  }

 private:
  typedef struct Node_ {
    value_type data_;
    Node_* ptr_next_;
    Node_* ptr_prev_;
    explicit Node_(value_type data) noexcept
        : data_(data), ptr_next_(nullptr), ptr_prev_(nullptr) {}
  } Node_;

  Node_* head_;
  Node_* tail_;
  size_type size_;

  class ListConstIterator {
   public:
    ListConstIterator() noexcept : ptr_(nullptr){};
    explicit ListConstIterator(list::Node_* node) noexcept : ptr_(node){};
    ListConstIterator(list::Node_* node, list::Node_* last_node) noexcept
        : ptr_(node), last_node_(last_node){};
    ListConstIterator(const ListConstIterator& other) noexcept
        : ptr_(other.ptr_){};
    ~ListConstIterator() = default;

    bool operator!=(const ListConstIterator& other) const noexcept {
      return ptr_ != other.ptr_;
    }

    bool operator==(const ListConstIterator& other) const noexcept {
      return ptr_ == other.ptr_;
    }

    ListConstIterator& operator=(const ListConstIterator& other) noexcept {
      if (ptr_ != other.ptr_) {
        ptr_ = other.ptr_;
      }
      return *this;
    }

    const_reference operator*() noexcept { return ptr_->data_; }

    ListConstIterator& operator++() noexcept {
      ptr_ = ptr_->ptr_next_;
      return *this;
    }

    ListConstIterator& operator--() noexcept {
      if (this->ptr_ == nullptr) {
        this->ptr_ = this->last_node_;
      } else {
        this->ptr_ = this->ptr_->ptr_prev_;
      }
      return *this;
    }

    Node_* GetNode_() const noexcept { return ptr_; }

   protected:
    Node_* ptr_;
    Node_* last_node_;
  };
  class ListIterator : public ListConstIterator {
   public:
    ListIterator() noexcept : ListConstIterator(){};
    explicit ListIterator(Node_* node) noexcept : ListConstIterator(node){};
    ListIterator(Node_* node, Node_* last_node) noexcept
        : ListConstIterator(node, last_node){};
    ListIterator(const ListIterator& other) noexcept
        : ListConstIterator(other){};
    ~ListIterator() = default;

    ListIterator& operator=(const ListIterator& other) noexcept {
      if (this != &other) {
        this->ptr_ = other.ptr_;
      }
      return *this;
    }

    ListIterator& operator++() noexcept {
      this->ptr_ = this->ptr_->ptr_next_;
      return *this;
    }

    ListIterator& operator--() noexcept {
      if (this->ptr_ == nullptr) {
        this->ptr_ = this->last_node_;
      } else {
        this->ptr_ = this->ptr_->ptr_prev_;
      }
      return *this;
    }

    reference operator*() noexcept { return (reference)this->ptr_->data_; }
  };

 public:
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  iterator begin() noexcept { return iterator(this->head_); }
  const_iterator cbegin() const noexcept { return const_iterator(this->head_); }
  iterator end() noexcept {
    return this->tail_   ? iterator(this->tail_->ptr_next_, this->tail_)
           : this->head_ ? ++begin()
                         : begin();
  }
  const_iterator cend() const noexcept {
    return this->tail_   ? const_iterator(this->tail_->ptr_next_, this->tail_)
           : this->head_ ? ++cbegin()
                         : cbegin();
  }
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void splice(iterator pos, list& other);

  template <class... Args>
  iterator insert_many(iterator pos, Args&&... args) {
    for (const auto& item : {args...}) {
      insert(pos, item);
    }
    return pos;
  }
  template <class... Args>
  void insert_many_back(Args&&... args) {
    for (const auto& item : {args...}) {
      push_back(item);
    }
  }
  template <class... Args>
  void insert_many_front(Args&&... args) {
    for (const auto& item : {args...}) {
      push_front(item);
    }
  }

  void MergeSort_(list<T>& left, list<T>& right, list<T>& result) noexcept;
};

template <typename T>
list<T>::list() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
list<T>::list(list::size_type n) noexcept
    : head_(nullptr), tail_(nullptr), size_(0) {
  while (n-- > 0) {
    push_back(T());
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const& items) noexcept
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (value_type item : items) {
    push_back(item);
  }
}

template <typename T>
list<T>::list(const list& other) noexcept
    : head_(nullptr), tail_(nullptr), size_(0) {
  *this = other;
}

template <typename T>
list<T>::list(list&& other) noexcept
    : head_(nullptr), tail_(nullptr), size_(0) {
  if (this != &other) {
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }
}

template <typename T>
list<T>::~list() {
  clear();
}

template <typename T>
void list<T>::push_front(const_reference data) noexcept {
  Node_* new_node = new Node_(data);
  if (!head_) {
    head_ = new_node;
    head_->ptr_next_ = nullptr;
    head_->ptr_prev_ = nullptr;
  } else if (!tail_) {
    tail_ = head_;
    tail_->ptr_next_ = nullptr;
    tail_->ptr_prev_ = new_node;
    new_node->ptr_next_ = tail_;
    new_node->ptr_prev_ = nullptr;
    head_ = new_node;
  } else {
    new_node->ptr_next_ = head_;
    head_->ptr_prev_ = new_node;
    head_ = new_node;
    head_->ptr_prev_ = nullptr;
  }
  ++size_;
}

template <typename T>
void list<T>::push_back(const_reference data) noexcept {
  Node_* new_node = new Node_(data);
  if (!head_) {
    head_ = new_node;
    head_->ptr_next_ = nullptr;
    head_->ptr_prev_ = nullptr;
  } else if (!tail_) {
    tail_ = new_node;
    head_->ptr_next_ = tail_;
    tail_->ptr_next_ = nullptr;
    tail_->ptr_prev_ = head_;
  } else {
    new_node->ptr_prev_ = tail_;
    tail_->ptr_next_ = new_node;
    tail_ = new_node;
    tail_->ptr_next_ = nullptr;
  }
  ++size_;
}

template <typename T>
void list<T>::pop_front() noexcept {
  if (!empty()) {
    Node_* node = head_;
    head_ = head_->ptr_next_;
    if (head_ && head_->ptr_next_ != nullptr) {
      head_->ptr_prev_ = nullptr;
    } else if (head_) {
      head_->ptr_prev_ = nullptr;
      tail_ = nullptr;
    }
    delete node;
    --size_;
  }
}

template <typename T>
void list<T>::pop_back() noexcept {
  if (!empty()) {
    if (tail_ && size_ == 2) {
      Node_* node = tail_;
      tail_ = nullptr;
      head_->ptr_next_ = nullptr;
      delete node;
      --size_;
    } else if (tail_ && size_ > 2) {
      Node_* node = tail_;
      tail_ = tail_->ptr_prev_;
      tail_->ptr_next_ = nullptr;
      delete node;
      --size_;
    } else {
      pop_front();
    }
  }
}

template <typename T>
void list<T>::sort() noexcept {
  if (size_ <= 1) return;

  list<T> left, right;
  auto iter = begin();
  for (int i = 0; i < (int)size_ / 2; ++i, ++iter) {
    left.push_back(*iter);
  }
  for (int j = (int)size_ / 2; j < (int)size_; ++j, ++iter) {
    right.push_back(*iter);
  }

  left.sort();
  right.sort();

  MergeSort_(left, right, *this);
}

template <typename T>
void list<T>::merge(list<T>& other) noexcept {
  list<T> temp;
  temp = *this;
  MergeSort_(temp, other, *this);
  other.clear();
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  if (pos == end()) {
    push_back(value);
    pos = iterator(tail_);
  } else if (pos == begin()) {
    push_front(value);
    pos = begin();
  } else {
    Node_* current = pos.GetNode_();
    Node_* blank = new Node_(value);
    blank->ptr_next_ = current;
    blank->ptr_prev_ = current->ptr_prev_;
    current->ptr_prev_->ptr_next_ = blank;
    current->ptr_prev_ = blank;
    size_++;
    return iterator(blank);
  }
  return pos;
}

template <typename T>
void list<T>::erase(list::iterator pos) {
  if (pos == begin()) {
    pop_front();
  } else if (pos.GetNode_() == this->tail_) {
    pop_back();
  } else {
    typename list<T>::Node_* node = pos.GetNode_();
    node->ptr_prev_->ptr_next_ = node->ptr_next_;
    node->ptr_next_->ptr_prev_ = node->ptr_prev_;
    delete node;
    this->size_--;
  }
}

template <typename T>
void list<T>::splice(list::iterator pos, list<T>& other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(pos, *it);
  }
  other.clear();
}

template <typename T>
typename list<T>::const_reference list<T>::front() const {
  return head_ ? head_->data_ : throw std::out_of_range("List is empty");
}

template <typename T>
typename list<T>::const_reference list<T>::back() const noexcept {
  return tail_ ? tail_->data_ : front();
}

template <typename T>
typename list<T>::size_type list<T>::size() const noexcept {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() /
         sizeof(typename list<T>::Node_) / 2;
}

template <typename T>
bool list<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
void list<T>::clear() noexcept {
  while (size_ != 0) pop_back();
}

template <typename T>
void list<T>::swap(list& other) noexcept {
  Node_* tmp_head = head_;
  Node_* tmp_tail = tail_;
  size_t tmp_size = size_;
  head_ = other.head_;
  tail_ = other.tail_;
  size_ = other.size_;
  other.head_ = tmp_head;
  other.tail_ = tmp_tail;
  other.size_ = tmp_size;
}

template <typename T>
void list<T>::reverse() noexcept {
  if (size_ > 1) {
    Node_ tmp_head = *head_;
    Node_ tmp_tail = *tail_;
    Node_* head_ptr = head_;
    Node_* tail_ptr = tail_;
    for (size_t i = 0; i < size_ / 2; i++) {
      head_ptr->data_ = tmp_tail.data_;
      tail_ptr->data_ = tmp_head.data_;
      head_ptr = head_ptr->ptr_next_;
      tail_ptr = tail_ptr->ptr_prev_;
      tmp_head = *head_ptr;
      tmp_tail = *tail_ptr;
    }
  }
}

template <typename T>
void list<T>::unique() noexcept {
  if (size_ < 2) return;
  auto itter = begin();
  auto itter_next = ++itter;
  --itter;
  list<T> tmp_list;
  tmp_list.push_back(*itter);
  while (itter_next != end()) {
    if (*itter != *itter_next) tmp_list.push_back(*itter_next);
    ++itter;
    ++itter_next;
  }
  *this = std::move(tmp_list);
}

template <typename T>
list<T>& list<T>::operator=(const list<T>& other) noexcept {
  if (this != &other) {
    clear();
    auto other_ptr = other.cbegin();
    while (other_ptr != other.cend()) {
      push_back(*other_ptr);
      ++other_ptr;
    }
  }
  return *this;
}

template <typename T>
list<T>& list<T>::operator=(list<T>&& other) noexcept {
  if (this != &other) {
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename T>
void list<T>::MergeSort_(list<T>& left, list<T>& right,
                         list<T>& result) noexcept {
  list<T> merged;
  auto left_iter = left.begin(), right_iter = right.begin();

  while (left_iter != left.end() && right_iter != right.end()) {
    if (*left_iter <= *right_iter) {
      merged.push_back(*left_iter);
      ++left_iter;
    } else {
      merged.push_back(*right_iter);
      ++right_iter;
    }
  }

  while (left_iter != left.end()) {
    merged.push_back(*left_iter);
    ++left_iter;
  }

  while (right_iter != right.end()) {
    merged.push_back(*right_iter);
    ++right_iter;
  }

  result = merged;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_LIST_S21_LIST_H_