#ifndef MAP_RBT_HPP
#define MAP_RBT_HPP
#include "..\estruturas\RBT.hpp"

//TODO
template <typename Key, typename Value, 
          typename Compare = std::less<Key>, typename Equals = std::equal_to<Key>>
    class MAP_RBT{
        private:
            RBT<Key, Value, Compare, Equals> rbt_tree;

        public:
            MAP_RBT();

            MAP_RBT(Compare comp, Equals eq_comp);

            ~MAP_RBT();

            void insert(Key k, Value v);

            void update(Key k, Value newValue);

            Value& at(const Key& k);

            const Value& at(const Key& k) const;

            void erase(const Key& k);

            bool contains(const Key& k);

            int size();

            void clear();

            void show();

            const Value& operator[](const Key& k) const;

            Value& operator[](const Key& k);

            std::vector<std::pair<Key, Value>> toVector() const;
};
#include "..\..\src\dicionarios\MAP_RBT.tpp"
#endif