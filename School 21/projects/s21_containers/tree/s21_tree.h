#ifndef S21_CONTAINERS_S21_TREE_TREE_H_
#define S21_CONTAINERS_S21_TREE_TREE_H_

#include <climits>
#include <iostream>
#include <utility>
#include <vector>

// namespace s21 {
template <typename K, typename V>
class s21_tree {
 public:
  using key_type = K;
  using mapped_type = V;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;

  s21_tree();
  s21_tree(std::initializer_list<value_type> const &items);
  s21_tree(const s21_tree &other_tree);
  s21_tree(s21_tree &&other_tree);
  ~s21_tree();

  class iterator {
   public:
    s21_tree *node_;

    // Constructors of iterator
    iterator() : node_(nullptr){};
    iterator(s21_tree *other_node) : node_(other_node) {}
    iterator(const iterator &other_iter) {
      node_ = other_iter.node_;
      // *this = other_iter;
    }
    ~iterator() = default;

    bool empty() { return !node_->data; }

    bool ItLeftChild() {
      bool res = false;
      if (node_->parent != node_->null_node)
        res = node_ == node_->parent->left_node;
      return res;
    }

    bool ItRighChild() {
      bool res = false;
      if (node_->parent != node_->null_node)
        res = node_ == node_->parent->right_node;
      return res;
    }

    bool operator==(const iterator &other_iter) {
      return node_ == other_iter.node_;
    }

    bool operator!=(const iterator &other_iter) {
      return node_ != other_iter.node_;
    }

    iterator operator=(const iterator &other_iter) {
      // this->node_ = other_iter.node_;
      if (&other_iter != this) {
        node_ = nullptr;
        node_ = other_iter.node_;
      }
      return *this;
    }

    iterator operator=(iterator &other_iter) {
      if (&other_iter != this) {
        node_ = nullptr;
        node_ = other_iter.node_;
      }
      return *this;
    }

    iterator operator=(s21_tree *tree) { return node_ = tree; }
    value_type &operator*() { return *(node_->data); }

    value_type *operator->() { return (*this).node_->data; }

    iterator next(iterator &it);
    iterator prev(iterator &it);
    iterator next() { return next(*this); }
    iterator prev() { return prev(*this); }

    iterator operator++() { return *this = next(*this); }
    iterator operator--() { return *this = prev(*this); }
    iterator operator++(int) {
      iterator tmp(*this);
      *this = next(*this);
      return tmp;
    }
    iterator operator--(int) {
      iterator tmp(*this);
      *this = prev(*this);
      return tmp;
    }

    iterator operator+=(size_type n) {
      while (n-- > 0) {
        operator++();
      }
      return *this;
    }

    iterator operator-=(size_type n) {
      while (n-- > 0) operator--();
      return *this;
    }
  };

  class const_iterator : public iterator {
   public:
    const_iterator() : iterator() {}
    const_iterator(s21_tree<K, V> *other_node) : iterator(other_node) {}
    ~const_iterator() = default;

    const value_type *operator->() { return (*this).node_->data; }
  };

  // operatots
  s21_tree &operator=(const s21_tree &other_tree);
  s21_tree &operator=(s21_tree &&other_tree);  // {

  // Element access
  V &at(const K &key);
  V &operator[](const K &key);

  // Iterators
  iterator begin(s21_tree &tree_node);
  iterator end(s21_tree &tree_node);
  iterator pre_end(s21_tree &tree_node);
  iterator begin() { return begin(*this); };
  iterator end() { return end(*this); }
  iterator pre_end() { return pre_end(*this); }
  s21_tree *GetAdress(iterator A) { return A.node_; }
  s21_tree *GetRoot();
  // Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Modifiers
  void s21_clear();
  std::pair<iterator, bool> insert(const value_type &value) {
    return s21_insert(value);
  }
  std::pair<iterator, bool> insert(const K &key, const V &obj) {
    return s21_insert({key, obj});
  }
  std::pair<iterator, bool> MultInsert(const value_type &value) {
    return s21_MultInsert(value);
  }
  std::pair<iterator, bool> MultInsert(const K &key, const V &obj) {
    return s21_MultInsert({key, obj});
  }

  std::pair<iterator, bool> insert_or_assign(const K &key, const V &obj);
  void erase(iterator pos);
  void swap(s21_tree &other);
  void merge(s21_tree &other);

  iterator s21_search(const K &key);
  void print();
  void OneByOne(const s21_tree &other_tree);

  // Lookup
  bool contains(const K &key);

 private:
  value_type *data;
  s21_tree *left_node;
  s21_tree *right_node;
  s21_tree *parent;
  s21_tree *null_node;
  char color;

  // Private functions
  std::pair<iterator, bool> s21_insert(const value_type &value);
  std::pair<iterator, bool> s21_MultInsert(const value_type &value);
  void BalanceAfterInsert();
  bool ReBalanceCase2_3();
  bool ReBalanceCase4();
  bool ReBalanceCase5();
  void BalanceAfterErase(s21_tree *tree);
  bool BalanceEraseCase1_3(s21_tree *tree);
  bool BalanceEraseCase2(s21_tree *tree);
  bool BalanceEraseCase4(s21_tree *tree);
  bool BalanceEraseCase5(s21_tree *tree);
  bool BalanceEraseCase6(s21_tree *tree);
  void turn_left(s21_tree *GrDad);
  void turn_right(s21_tree *GrDad);
  void SwapData(s21_tree *A, s21_tree *B);
  void SwapColor(s21_tree *A, s21_tree *B);
  void UpdateNullNode();
  bool ItCanDelete(const iterator &pos);
  void DeleteNode();
  bool EraseCase1();
  bool EraseCase2();
  bool EraseCase3();
  bool ItLeftChild();
  bool ItRighChild();
  // iterator next(iterator &it) { return iterator:: next(it);}
  // iterator prev(iterator &it) { return iterator:: prev(it);}
};

// Constructors
template <typename K, typename V>
s21_tree<K, V>::s21_tree()
    : data(nullptr),
      left_node(nullptr),
      right_node(nullptr),
      parent(nullptr),
      null_node(nullptr),
      color('B') {}

template <typename K, typename V>
s21_tree<K, V>::s21_tree(std::initializer_list<value_type> const &items)
    : s21_tree() {
  for (value_type i : items) insert(i);
}

template <typename K, typename V>
s21_tree<K, V>::s21_tree(const s21_tree &other_tree) : s21_tree() {
  *this = other_tree;
}

template <typename K, typename V>
s21_tree<K, V>::s21_tree(s21_tree &&other_tree) : s21_tree() {
  *this = std::move(other_tree);
}

template <typename K, typename V>
s21_tree<K, V>::~s21_tree() {
  if (data) {
    if (left_node) {
      left_node->~s21_tree();
    }
    if (right_node) {
      right_node->~s21_tree();
    }
    DeleteNode();
  }
}

template <typename K, typename V>
s21_tree<K, V> &s21_tree<K, V>::operator=(const s21_tree<K, V> &other_tree) {
  if (&other_tree != this) {
    s21_clear();
    data = nullptr;
    left_node = nullptr;
    right_node = nullptr;
    parent = nullptr;
    null_node = nullptr;
    color = 'B';
    OneByOne(other_tree);
  }
  return *this;
}

template <typename K, typename V>
s21_tree<K, V> &s21_tree<K, V>::operator=(s21_tree<K, V> &&other_tree) {
  if (&other_tree != this) {
    s21_clear();
    data = other_tree.data;
    left_node = other_tree.left_node;
    right_node = other_tree.right_node;
    parent = other_tree.parent;
    null_node = other_tree.null_node;
    color = other_tree.color;
    // other_tree.s21_clear();
    other_tree.data = nullptr;
    other_tree.left_node = nullptr;
    other_tree.right_node = nullptr;
    other_tree.parent = nullptr;
    other_tree.null_node = nullptr;
  }
  return *this;
}

template <typename K, typename V>
V &s21_tree<K, V>::at(const K &key) {
  iterator it(s21_search(key));
  // V result = 0;
  if (!it.node_) {
    //   result = it->second;
    // } else {
    throw std::out_of_range("Invalid Key");
  }
  return it->second;
}

template <typename K, typename V>
V &s21_tree<K, V>::operator[](const K &key) {
  if (contains(key))
    return iterator(s21_search(key))->second;
  else
    return iterator(insert(key, V()).first)->second;
}

template <typename K, typename V>
typename s21_tree<K, V>::iterator s21_tree<K, V>::s21_search(const K &key) {
  iterator result;
  if (data) {
    if (data->first == key) {
      result = this;
    } else if (data->first < key) {
      result = (*right_node).s21_search(key);
    } else /*if (data->first < key)*/ {
      result = (*left_node).s21_search(key);
    }
  }
  return result;
}

template <typename K, typename V>
bool s21_tree<K, V>::contains(const K &key) {
  return s21_search(key).node_;
}

template <typename K, typename V>
std::pair<typename s21_tree<K, V>::iterator, bool> s21_tree<K, V>::s21_insert(
    const value_type &value) {
  std::pair<iterator, bool> res = {iterator(), false};
  if (data == nullptr) {
    data = new value_type(value);
    color = 'R';
    left_node = new s21_tree();
    right_node = new s21_tree();
    left_node->parent = this;
    right_node->parent = this;
    res.second = true;
    res.first = this;
  } else {
    if ((*data).first > value.first)
      res = (*left_node).s21_insert(value);
    else if ((*data).first < value.first)
      res = (*right_node).s21_insert(value);
    else {
      res.second = false;
      res.first = this;
    }
  }

  if (!parent) {
    null_node = new s21_tree();
    parent = null_node;
    null_node->left_node = this;
    null_node->right_node = this;
    null_node->parent = this;
  }
  if (parent ==
      null_node)  // && data->first > null_node->left_node->data->first)
    UpdateNullNode();
  BalanceAfterInsert();
  return res;
}

template <typename K, typename V>
std::pair<typename s21_tree<K, V>::iterator, bool>
s21_tree<K, V>::s21_MultInsert(const value_type &value) {
  std::pair<iterator, bool> res = {iterator(), false};
  if (data == nullptr) {
    data = new value_type(value);
    color = 'R';
    left_node = new s21_tree();
    right_node = new s21_tree();
    left_node->parent = this;
    right_node->parent = this;
    res.second = true;
    res.first = this;
  } else {
    if ((*data).first >= value.first)
      res = (*left_node).s21_MultInsert(value);
    else
      res = (*right_node).s21_MultInsert(value);
  }

  if (!parent) {
    null_node = new s21_tree();
    parent = null_node;
    null_node->left_node = this;
    null_node->right_node = this;
    null_node->parent = this;
  }
  if (parent ==
      null_node)  // && data->first > null_node->left_node->data->first)
    UpdateNullNode();
  BalanceAfterInsert();
  return res;
}

template <typename K, typename V>
void s21_tree<K, V>::s21_clear() {
  this->~s21_tree();
}

template <typename K, typename V>
void s21_tree<K, V>::OneByOne(const s21_tree &other_tree) {
  if (other_tree.data != nullptr) {
    if (other_tree.left_node != nullptr) {
      OneByOne(*other_tree.left_node);
    }
    s21_insert(*other_tree.data);
    if (other_tree.right_node != nullptr) {
      OneByOne(*other_tree.right_node);
    }
  }
}

template <typename K, typename V>
void s21_tree<K, V>::print() {
  if (data != nullptr) {
    if (left_node != nullptr) {
      left_node->print();
    }
    std::cout << (*data).first << color << (*data).second;
    if (right_node != nullptr) {
      right_node->print();
    }
  }
}

template <typename K, typename V>
void s21_tree<K, V>::BalanceAfterInsert() {
  if (parent == null_node && color == 'R')
    color = 'B';
  else if (ReBalanceCase2_3()) {
  } else if (ReBalanceCase4()) {
  } else if (ReBalanceCase5()) {
  }
}

template <typename K, typename V>
bool s21_tree<K, V>::ReBalanceCase2_3() {
  bool result = false;
  if (parent && parent->parent && color == 'R') {
    s21_tree *GrDad = parent->parent;
    s21_tree *Dad = parent;
    s21_tree *Uncle =
        GrDad->left_node == Dad ? GrDad->right_node : GrDad->left_node;
    result = Dad->color == 'R' && Uncle->color == 'R';
    if (result) {
      Dad->color = 'B';
      Uncle->color = 'B';
      if (GrDad->parent != nullptr) GrDad->color = 'R';
    }
  } else
    result = true;
  return result;
}

template <typename K, typename V>
bool s21_tree<K, V>::ReBalanceCase4() {
  bool result = false;
  if (parent && parent->parent && color == 'R') {
    s21_tree *GrDad = parent->parent;
    s21_tree *Dad = parent;
    s21_tree *Uncle =
        GrDad->left_node == Dad ? GrDad->right_node : GrDad->left_node;
    if (Dad->color == 'R' && Uncle->color == 'B') {
      bool zigzag_left =
          (*data > *(Dad->data) && *(GrDad->data) > *(Dad->data));
      bool zigzag_right =
          (*data < *(Dad->data) && *(GrDad->data) < *(Dad->data));
      if (zigzag_left or zigzag_right) {
        if (zigzag_left) {
          turn_left(Dad);
          Dad->color = 'B';
          GrDad->color = 'R';
          turn_right(GrDad);
        } else if (zigzag_right) {
          turn_right(Dad);
          Dad->color = 'B';
          GrDad->color = 'R';
          turn_left(GrDad);
        }
        result = true;
      }
    }
  }
  return result;
}

template <typename K, typename V>
bool s21_tree<K, V>::ReBalanceCase5() {
  bool result = false;
  if (parent && parent->parent && color == 'R') {
    s21_tree *GrDad = parent->parent;
    s21_tree *Dad = parent;
    s21_tree *Uncle =
        GrDad->left_node == Dad ? GrDad->right_node : GrDad->left_node;
    if (Dad->color == 'R' && Uncle->color == 'B') {
      bool dir_line_left =
          (*data > *(Dad->data) && *(Dad->data) > *(GrDad->data));
      bool dir_line_right =
          (*data < *(Dad->data) && *(Dad->data) < *(GrDad->data));
      if (dir_line_left or dir_line_right) {
        Dad->color = 'B';
        GrDad->color = 'R';
        if (dir_line_left)
          turn_left(GrDad);
        else if (dir_line_right)
          turn_right(GrDad);
      }
    }
  }
  return result;
}

template <typename K, typename V>
void s21_tree<K, V>::turn_right(s21_tree *GrDad) {
  SwapData(GrDad, GrDad->left_node);
  SwapColor(GrDad, GrDad->left_node);
  s21_tree *buffer_node = GrDad->right_node;
  GrDad->right_node = GrDad->left_node;
  GrDad->left_node = GrDad->left_node->left_node;
  GrDad->left_node->parent = GrDad;  //
  GrDad->right_node->left_node = GrDad->right_node->right_node;
  GrDad->right_node->right_node = buffer_node;
  GrDad->right_node->right_node->parent = GrDad->right_node;  //
}

template <typename K, typename V>
void s21_tree<K, V>::turn_left(s21_tree *GrDad) {
  SwapData(GrDad, GrDad->right_node);
  SwapColor(GrDad, GrDad->right_node);
  s21_tree *buffer_node = GrDad->left_node;
  GrDad->left_node = GrDad->right_node;
  GrDad->right_node = GrDad->right_node->right_node;
  GrDad->right_node->parent = GrDad;
  GrDad->left_node->right_node = GrDad->left_node->left_node;
  GrDad->left_node->left_node = buffer_node;
  GrDad->left_node->left_node->parent = GrDad->left_node;
}

template <typename K, typename V>
void s21_tree<K, V>::SwapData(s21_tree *A, s21_tree *B) {
  value_type buffer_data = *(A->data);
  *(A->data) = *(B->data);
  *(B->data) = buffer_data;
}

template <typename K, typename V>
void s21_tree<K, V>::SwapColor(s21_tree *A, s21_tree *B) {
  char color = A->color;
  A->color = B->color;
  B->color = color;
}

template <typename K, typename V>
void s21_tree<K, V>::UpdateNullNode() {
  s21_tree *A = GetRoot();
  s21_tree *B = GetAdress(this->pre_end());
  if (A && B) {
    if (A->null_node->left_node != B) {
      A->null_node->parent = B;
      A->null_node->right_node = B;
      A->null_node->left_node = B;
    }
  }
}

template <typename K, typename V>
bool s21_tree<K, V>::empty() {
  return !data;
}

template <typename K, typename V>
typename s21_tree<K, V>::size_type s21_tree<K, V>::size() {
  size_type num = 0;
  if (!empty()) {
    num += 1;
    num += (*left_node).size();
    num += (*right_node).size();
  }
  return num;
}

template <typename K, typename V>
typename s21_tree<K, V>::size_type s21_tree<K, V>::max_size() {
  return /*std::numeric_limits<size_type>::max()*/ LONG_MAX /
         sizeof(s21_tree<K, V>);
}

template <typename K, typename V>
typename s21_tree<K, V>::iterator s21_tree<K, V>::begin(s21_tree &tree_node) {
  s21_tree *result = tree_node.null_node;
  s21_tree *temp = &tree_node;
  while (temp->data) {
    result = temp;
    temp = temp->left_node;
  }
  iterator res(result);
  return res;
}

template <typename K, typename V>
typename s21_tree<K, V>::iterator s21_tree<K, V>::end(s21_tree &tree_node) {
  return iterator(tree_node.null_node);
}

template <typename K, typename V>
typename s21_tree<K, V>::iterator s21_tree<K, V>::pre_end(
    s21_tree<K, V> &tree_node) {
  s21_tree *result = nullptr;
  s21_tree *temp = &tree_node;
  while (temp->data) {
    result = temp;
    temp = temp->right_node;
  }
  iterator res(result);
  return res;
}

template <typename K, typename V>
typename s21_tree<K, V>::s21_tree *s21_tree<K, V>::GetRoot() {
  s21_tree *temp = this;
  if (!empty()) {
    while (temp->parent != null_node) {
      temp = temp->parent;
    }
  }
  return temp;
};

template <typename K, typename V>
std::pair<typename s21_tree<K, V>::iterator, bool>
s21_tree<K, V>::insert_or_assign(const K &key, const V &obj) {
  std::pair<iterator, bool> res = s21_insert({key, obj});
  if (!res.second) {
    if (res.first.node_) {
      res.first->second = obj;
    }
  }
  return res;
}

template <typename K, typename V>
void s21_tree<K, V>::swap(s21_tree &other) {
  s21_tree temp = other;
  other = *this;
  *this = temp;
}

template <typename K, typename V>
void s21_tree<K, V>::merge(s21_tree &other) {
  for (iterator it = other.begin(); it != other.end(); ++it) {
    this->insert_or_assign((*it).first, (*it).second);
  }
}

template <typename K, typename V>
void s21_tree<K, V>::erase(iterator pos) {
  if (!pos.empty()) {
    if (ItCanDelete(pos)) {
      if (pos.node_->EraseCase1()) {
      } else if (pos.node_->EraseCase2()) {
      } else if (pos.node_->EraseCase3()) {
      }
      UpdateNullNode();
    } else {
      auto it = pos.prev();
      SwapData(pos.node_, it.node_);
      erase(it);
    }
  }
}

template <typename K, typename V>
bool s21_tree<K, V>::ItCanDelete(const iterator &pos) {
  return !pos.node_->left_node->data or !pos.node_->right_node->data;
}

template <typename K, typename V>
bool s21_tree<K, V>::ItLeftChild() {
  bool res = false;
  if (parent != null_node) res = this == parent->left_node;
  return res;
}

template <typename K, typename V>
bool s21_tree<K, V>::ItRighChild() {
  bool res = false;
  if (parent != null_node) res = this == parent->right_node;
  return res;
}

template <typename K, typename V>
void s21_tree<K, V>::DeleteNode() {
  delete data;
  delete left_node;
  delete right_node;
  data = nullptr;
  left_node = nullptr;
  right_node = nullptr;
  parent = nullptr;
  if (null_node) {
    delete null_node;
    null_node = nullptr;
  }
}

template <typename K, typename V>
bool s21_tree<K, V>::EraseCase1() {
  bool res = false;
  if (color == 'R' and left_node->empty() and right_node->empty()) {
    DeleteNode();
    res = true;
  }
  return res;
}

template <typename K, typename V>
bool s21_tree<K, V>::EraseCase2() {
  bool res = false;
  if (color == 'B') {
    if (!left_node->empty() and right_node->empty()) {
      if (left_node->color == 'R') {
        SwapData(this, left_node);
        color = 'B';
        left_node->DeleteNode();
        res = true;
      }
    } else if (left_node->empty() and !right_node->empty()) {
      if (right_node->color == 'R') {
        SwapData(this, right_node);
        color = 'B';
        right_node->DeleteNode();
        res = true;
      }
    }
  }
  return res;
}

template <typename K, typename V>
bool s21_tree<K, V>::EraseCase3() {
  bool res = false;
  if (left_node->empty() and right_node->empty()) {
    s21_tree *Brother =
        parent->left_node == this ? parent->right_node : parent->left_node;
    DeleteNode();
    res = true;
    if (!Brother->empty() and Brother->parent != null_node)
      BalanceAfterErase(Brother);
  }
  return res;
}

template <typename K, typename V>
void s21_tree<K, V>::BalanceAfterErase(s21_tree *tree) {
  if (tree->color == 'B') {
    if (BalanceEraseCase1_3(tree)) {
    } else if (BalanceEraseCase2(tree)) {
    } else if (BalanceEraseCase4(tree)) {
    }
  } else if (tree->color == 'R') {
    tree->color = 'B';
    tree->parent->color = 'R';
    if (tree->ItRighChild())
      turn_left(tree->parent);
    else if (tree->ItLeftChild())
      turn_right(tree->parent);
  }
}

template <typename K, typename V>
bool s21_tree<K, V>::BalanceEraseCase1_3(s21_tree *tree) {
  bool res = false;
  if ((tree->ItRighChild() and tree->right_node->color == 'R') or
      (tree->ItLeftChild() and tree->left_node->color == 'R')) {
    tree->color = tree->parent->color;
    tree->parent->color = 'B';
    tree->right_node->color = 'B';
    if (tree->ItLeftChild())
      turn_right(tree->parent);
    else if (tree->ItRighChild())
      turn_left(tree->parent);
    res = true;
  }
  return res;
}

template <typename K, typename V>
bool s21_tree<K, V>::BalanceEraseCase2(s21_tree *tree) {
  bool res = false;
  if (tree->left_node->color == 'B' and tree->right_node->color == 'B') {
    if (tree->parent == GetRoot())
      tree->color = 'R';
    else if (tree->parent->color == 'R') {
      tree->color = 'R';
      tree->parent->color = 'B';
    } else {
      tree->parent->color = 'R';
      if (tree->ItRighChild()) {
        turn_left(tree->parent);
        turn_left(tree->parent->parent);
      } else if (tree->ItLeftChild()) {
        turn_right(tree->parent);
        turn_right(tree->parent->parent);
      }
    }
    res = true;
  }
  return res;
}

template <typename K, typename V>
bool s21_tree<K, V>::BalanceEraseCase4(s21_tree *tree) {
  bool res = false;
  bool BrotherRight = tree->right_node->color == 'B' and
                      tree->left_node->color == 'R' and tree->ItRighChild();
  bool BrotherLeft = tree->right_node->color == 'R' and
                     tree->left_node->color == 'B' and tree->ItLeftChild();
  if (BrotherRight or BrotherLeft) {
    tree->color = 'R';
    if (BrotherRight) {
      tree->left_node->color = 'B';
      turn_right(tree);
      tree->parent->color = 'R';
      turn_left(tree->parent);
    } else if (BrotherLeft) {
      tree->right_node->color = 'B';
      turn_left(tree);
      tree->parent->color = 'R';
      turn_right(tree->parent);
    }
    // tree->parent->color = 'R';
    res = true;
  }
  return res;
}

template <typename K, typename V>
typename s21_tree<K, V>::iterator s21_tree<K, V>::iterator::next(iterator &it) {
  iterator result;
  if (it.node_->right_node->data) {
    result = it.node_->right_node;
    while (!result.node_->left_node->empty()) {
      result = result.node_->left_node;
    }
  } else if (it.ItLeftChild()) {
    result = it.node_->parent;
  } else if (it.ItRighChild()) {
    if (it.node_->parent != node_->null_node) result = it.node_->parent;
    while (result.node_->parent->data && !result.ItLeftChild()) {
      result = result.node_->parent;
    }
    if (result.ItLeftChild())
      result = result.node_->parent;
    else
      result = result.node_->null_node;
  }
  return result;
}

template <typename K, typename V>
typename s21_tree<K, V>::iterator s21_tree<K, V>::iterator::prev(iterator &it) {
  iterator result;
  if (it.node_->left_node->data) {
    result = it.node_->left_node;
    while (!result.node_->right_node->empty()) {
      result = result.node_->right_node;
    }
  } else if (it.ItRighChild()) {
    result = it.node_->parent;
  } else if (it.ItLeftChild()) {
    if (it.node_->parent->data) result = it.node_->parent;
    while (result.node_->parent->data && !result.ItRighChild()) {
      result = result.node_->parent;
    }
    if (result.ItRighChild())
      result = result.node_->parent;
    else
      result = result.node_->null_node;
  }
  return result;
}

// } // namespace s21

#endif  // S21_CONTAINERS_S21_TREE_TREE_H_