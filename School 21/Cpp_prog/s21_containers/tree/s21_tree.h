#ifndef CPP2_S21_CONTAINERS_1_SRC_TREE_S21_TREE_H_
#define CPP2_S21_CONTAINERS_1_SRC_TREE_S21_TREE_H_

#include <iostream>
#include <limits>
#include <utility>
#include <vector>

namespace s21 {

template <typename K, typename V>
class Tree {
    public:
        using key_type = K;
        using mapped_type = V;
        using value_type = std::pair<const key_type, mapped_type>;
        using reference = value_type&;
        using const_reference = const value_type&;
        using size_type = size_t;

        Tree() noexcept;
        explicit Tree(const value_type& item);
        Tree(std::initializer_list<value_type> const &items) noexcept;
        Tree(const Tree& other);
        Tree(Tree&& other);

        virtual ~Tree();

    private:

};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_TREE_S21_TREE_H_