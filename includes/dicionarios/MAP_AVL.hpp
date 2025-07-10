#ifndef MAP_AVL_HPP
#define MAP_AVL_HPP
#include "..\estruturas\AVL.hpp"
#include <functional>
#include <vector>

template <typename Key, typename Value, typename Compare = std::less<Key>, typename Equals = std::equal_to<Key>>
    class MAP_AVL{
        private:
            AVL<Key, Value, Compare, Equals> avl_tree;
        public:
            MAP_AVL();

            MAP_AVL(Compare comp, Equals eq_comp);

            ~MAP_AVL();

            void insert(Key k, Value v);

            void update(Key k, Value newValue);

            Value& at(const Key& k);

            const Value& at(const Key& k) const;

            void erase(const Key& k);

            bool contains(const Key& k);

            int size();

            void clear();

            bool empty();

            void show();

            const Value& operator[](const Key& k) const;

            Value& operator[](const Key& k);

            std::vector<std::pair<Key, Value>> toVector() const;

            std::string metric();
}; 
#include "..\..\src\dicionarios\MAP_AVL.tpp"
#endif