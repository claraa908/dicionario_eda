#ifndef MAP_CHT_HPP
#define MAP_CHT_HPP
#include "..\estruturas\CHT.hpp"
#include <stdexcept>
#include <functional>

//TODO
template <typename Key, typename Value, typename Hash = std::hash<Key>, typename Compare = std::less<Key>, typename Equals = std::equal_to<Key>>
    class MAP_CHT{
        private:
            CHT<Key, Value, Hash, Compare, Equals> c_hash;

        public:
            MAP_CHT(size_t table_size = 10, float load_factor = 0.75, Hash hasher = Hash(), Compare comp = Compare(), Equals eq = Equals());
            
            ~MAP_CHT();

            void insert(Key k, Value v);

            void update(Key k, Value newValue);

            Value& at(const Key& k);

            const Value& at(const Key& k) const;

            void erase(Key k);

            bool contains(Key k);

            int size();

            void clear();

            void show();

            const Value& operator[](const Key& k) const;

            Value& operator[](const Key& k);

            std::vector<std::pair<Key, Value>> toVector() const;

            std::string metric();
};
#include "..\..\src\dicionarios\MAP_CHT.tpp"
#endif