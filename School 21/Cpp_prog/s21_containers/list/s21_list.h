#ifndef CPP2_S21_CONTAINERS_1_SRC_LIST_S21_LIST_H_
#define CPP2_S21_CONTAINERS_1_SRC_LIST_S21_LIST_H_

#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class list {
    public:
        using      value_type = T;
        using       reference = T &;
        using const_reference = const T &;
        using       size_type = size_t;

        list() noexcept; //
        explicit list(size_type n); //
        list(std::initializer_list<value_type> const& items) noexcept; //
        list(const list& other) noexcept; //
        list(list&& other) noexcept; //

        ~list(); //

        void push_front(const_reference data) noexcept; //
        void push_back(const_reference data) noexcept; //
        void pop_front() noexcept;
        void pop_back() noexcept;
        const_reference front() const noexcept; //
        const_reference back() const noexcept; //
        void swap(list& other) noexcept; //
        void sort() noexcept;
        void merge(list& other) noexcept;
        void reverse() noexcept; //
        void unique() noexcept; //
        size_type size() const noexcept; //
        size_type max_size() const noexcept; //
        bool empty() const noexcept; //
        void clear() noexcept; //
        
        list<T>& operator=(const list<T>& other) noexcept; //
        list<T>& operator=(list<T>&& other) noexcept; //

    private:
        typedef struct Node_
        {
            value_type data_;
            Node_* ptr_next_;
            Node_* ptr_prev_;
            explicit Node_(value_type data) noexcept : data_(data), ptr_next_(nullptr), ptr_prev_(nullptr) {}
        } Node_;

        Node_* head_;
        Node_* tail_;
        size_type size_;

        class ListConstIterator {
            public:
                ListConstIterator() noexcept : ptr_(nullptr) {};
                explicit ListConstIterator(list::Node_* node) noexcept : ptr_(node) {};
                ListConstIterator(const ListConstIterator& other) noexcept : ptr_(other.ptr_) {};
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

                const_reference operator*() noexcept {
                    return ptr_->data_;
                }

                ListConstIterator& operator++() noexcept {
                    ptr_ = ptr_->ptr_next_;
                    return *this;
                }

                ListConstIterator& operator--() noexcept {
                    ptr_ = ptr_->ptr_prev_;
                    return *this;
                }

                ListConstIterator operator+(size_type n) {
                    auto tmp_ptr_ = ptr_;
                    while (n-- > 0) {
                        tmp_ptr_++;
                    }
                    return tmp_ptr_;
                }

                ListConstIterator operator+=(size_type n) {
                    while (n-- > 0) {
                        ptr_++;
                    }
                    return *this;
                }

                ListConstIterator operator-(size_type n) {
                    auto tmp_ptr_ = ptr_;
                    while (n-- > 0) {
                        tmp_ptr_--;
                    }
                    return tmp_ptr_;
                }

                ListConstIterator operator-=(size_type n) {
                    while (n-- > 0) {
                        ptr_--;
                    }
                    return *this;
                }

                Node_* GetNode_() const noexcept {
                    return ptr_;
                }

            protected:
                Node_* ptr_;
        };
        class ListIterator : public ListConstIterator {
            public:
                ListIterator() noexcept : ListConstIterator(){};
                explicit ListIterator(Node_* node) noexcept : ListConstIterator(node){};
                ListIterator(const ListIterator& other) noexcept : ListConstIterator(other){};
                ~ListIterator() = default;

                ListIterator& operator=(const ListIterator& other) noexcept {
                    if (this != &other) {
                        this->ptr_ = other.ptr_;
                    }
                    return *this;
                }

                reference operator*() noexcept { 
                    return (reference)this->ptr_->value; 
                }
            
        };

    public:
        using iterator = ListIterator;
        using const_iterator = ListConstIterator;

        iterator begin() const noexcept { return iterator(this->head_); } //
        iterator end() const noexcept { return iterator(this->tail_); } //
        iterator insert(iterator pos, const_reference value);
        void erase(iterator pos);
        void splice(const_iterator pos, list& other); 

        
        template <class... Args>
        iterator insert_many(const_iterator pos, Args&&... args) {
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
};

template <typename T>
inline list<T>::list() noexcept : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
inline list<T>::list(list::size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
    if (n <= 0) {
        throw std::out_of_range("Size must be positive");
    }
    while (n-- > 0) {
        push_back(T());
    }
}

template <typename T>       
inline list<T>::list(std::initializer_list<value_type> const& items) noexcept : head_(nullptr), tail_(nullptr), size_(0) {
    for (value_type item : items) {
        push_back(item);
    }
}

template <typename T>
inline list<T>::list(const list& other) noexcept : head_(nullptr), tail_(nullptr), size_(0) {
    *this = other;
}
        
template <typename T>
inline list<T>::list(list&& other) noexcept : head_(nullptr), tail_(nullptr), size_(0) {
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
inline list<T>::~list() {
    clear();
}

template <typename T>
inline void list<T>::push_front(const_reference data) noexcept {
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
inline void list<T>::push_back(const_reference data) noexcept {
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
inline void list<T>::pop_front() noexcept {
    if (!empty()) {
        
    }
}

template <typename T>
inline void list<T>::pop_back() noexcept {
    if (!empty()) {
        
    }
}

template <typename T>
inline void sort() noexcept {

}

template <typename T>
inline void merge(list<T>& other) noexcept {
    
}

template <typename T>
inline typename list<T>::iterator list<T>::insert(iterator pos, const_reference value) {

}

template <typename T>
inline void list<T>::erase(list::iterator pos) {
    if (pos = begin()) {
        pop_front();
    } else if (pos.node_ == this->list_.tail_) {
        pop_back();
    }
}

template <typename T>
inline void list<T>::splice(list::const_iterator pos, list<T>& other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
        insert(pos, *it);
    }
    other.clear();
}

template <typename T>
inline typename list<T>::const_reference list<T>::front() const noexcept {
    return head_ ? head_->data_ : T();
}
        
template <typename T>
inline typename list<T>::const_reference list<T>::back() const noexcept {
    return tail_ ? tail_->data_ : front();
}

template <typename T>
inline typename list<T>::size_type list<T>::size() const noexcept {
    return size_;
}

template <typename T>
inline typename list<T>::size_type list<T>::max_size() const noexcept {
    return std::numeric_limits<std::size_t>::max();
}

template <typename T>
inline bool list<T>::empty() const noexcept {
    return size_ == 0;
}

template <typename T>
inline void list<T>::clear() noexcept {
    while (size_ != 0) pop_back();
}

template <typename T>
inline void list<T>::swap(list& other) noexcept {
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
inline void list<T>::reverse() noexcept {
    if (size_ > 1) {
        Node_ tmp_head = *head_;
        Node_ tmp_tail = *tail_;
        Node_* head_ptr = head_;
        Node_* tail_ptr = tail_;
        for (size_t i = 0; i < size_ / 2; i++) {
            head_ptr->value_ = tmp_tail.value_;
            tail_ptr->value_ = tmp_head.value_;
            head_ptr = head_ptr->ptr_next_;
            tail_ptr = tail_ptr->ptr_prev_;
            tmp_head = *head_ptr;
            tmp_tail = *tail_ptr;
        }
    }
}

template <typename T>
inline void list<T>::unique() noexcept {
    if (size_ < 2) return;
    auto itter = begin();
    auto itter_next = ++itter;
    list<T> tmp_list;
    while (itter != end()) {
        if (*itter != *itter_next) tmp_list.push_back(*itter);
        ++itter;
        ++itter_next;
    }
    *this = std::move(tmp_list);
}

template <typename T>
list<T>& list<T>::operator=(const list<T>& other) noexcept {
    clear();
    size_ = other.size_;
    auto other_ptr = other.begin();
    while (other_ptr != other.end()) {
        push_back(*other_ptr);
        other_ptr++;
    }
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
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_LIST_S21_LIST_H_