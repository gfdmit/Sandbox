#ifndef CPP2_S21_CONTAINERS_1_SRC_QUEUE_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_1_SRC_QUEUE_S21_QUEUE_H_

#include <../list/s21_list.h>

namespace s21 {

template <typename T>
class queue {
    public:
        using      value_type = T;
        using       reference = value_type &;
        using const_reference = const value_type &;
        using       size_type = size_t;

        queue() noexcept; //
        queue(std::initializer_list<value_type> const &items) noexcept; //
        queue(const queue &other) noexcept; //
        queue(queue &&other) noexcept; //

        ~queue(); //

        const_reference front(); //
        const_reference back(); //
        bool empty() const noexcept; //
        size_type size() const noexcept; //
        void push(const_reference value) noexcept; //
        void pop(); //
        void swap(queue &other) noexcept; //

        queue &operator=(const queue &other) noexcept; //
        queue &operator=(queue &&other) noexcept; //

        template <class... Args>
        void insert_many_back(Args&&... args) {
            for (const auto& item : {args...}) {
                list_.push_back(item);
            }
        }

    private:
        list<T> list_;

        void Clear_(); //
};

template <typename T>
inline queue<T>::queue() noexcept : list_() {}

template <typename T>
inline queue<T>::queue(std::initializer_list<value_type> const &items) noexcept : list_() {
    for (value_type item in items) {
        push(item);
    }
}

template <typename T>
inline queue<T>::queue(const queue &other) noexcept : list_() {
    *this = other;
}

template <typename T>
inline queue<T>::queue(queue &&other) noexcept : list_() {
    *this = std::move(other);
}

template <typename T>
inline queue<T>::~queue() {
    Clear_();
}

template <typename T>
inline void queue<T>::Clear_() {
    while (list_.size() != 0) {
        pop();
    }
}

template <typename T>
inline queue<T>::const_reference queue<T>::front() {
    if (list_.front() == T()) {
        throw std::logic_error("Queue is empty");
    }
    return list_.front();
}

template <typename T>
inline queue<T>::const_reference queue<T>::back() {
    if (list_.back() == T()) {
        throw std::logic_error("Queue is empty");
    }
    return list_.back();
}

template <typename T>
inline bool queue<T>::empty() const noexcept {
    return list_.empty();
}

template <typename T>
inline queue<T>::size_type queue<T>::size() const noexcept {
    list_.size();
}

template <typename T>
inline void queue<T>::push(const_reference value) noexcept {
    list_.push_back(value);
}

template <typename T>
inline void queue<T>::pop() {
    if (empty()) {
        throw std::logic_error("Stack is empty");
    }
    list_.pop_front();
}

template <typename T>
inline void queue<T>::swap(queue &other) noexcept {
    if (*this != other) {
        list<T> tmp_list = list_;
        list_ = other.list_;
        other.list_ = tmp_list;
    }
}

template <typename T>
inline queue<T> &queue<T>::operator=(const queue<T> &other) noexcept {
    if (this != &other) {
        Clear_();
        for (auto i = other.list_.begin(); i != other.list_.end(); ++i) {
            push(*i);
        }
    }
    return *this;
}

template <typename T>   
inline queue<T> &queue<T>::operator=(queue<T> &&other) noexcept {
    if (this != &other) {
        Clear_();
        list_ = other.list_;
        other.list_.clear();
    }
    return *this;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_QUEUE_S21_QUEUE_H_