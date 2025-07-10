#ifndef MAP_OHT_HPP
#define MAP_OHT_HPP
#include "..\estruturas\OHT.hpp"
#include <functional>

//TODO
template <typename Key, typename Value, typename Hash = std::hash<Key>, typename Compare = std::less<Key>, typename Equals = std::equal_to<Key>>
    class MAP_OHT{
        private:
            OHT<Key, Value, Hash, Compare, Equals> o_hash;

        public:
            MAP_OHT(size_t table_size = 10, float load_factor = 0.75, Hash hasher = Hash(), Compare comp = Compare(), Equals eq = Equals());

            ~MAP_OHT();

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
};
#include "..\..\src\dicionarios\MAP_OHT.tpp"
#endif