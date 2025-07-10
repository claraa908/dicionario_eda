#ifndef MAP_OHT_HPP
#define MAP_OHT_HPP
#include "..\estruturas\OHT.hpp"
#include <functional>

//TODO
template <typename Key, typename Value, typename Hash = std::hash<Key>,
          typename Compare = std::less<Key>, typename Equals = std::equal_to<Key>>
    class MAP_OHT{
        private:
            OHT<Key, Value, Hash, Compare, Equals> o_hash;

        public:
            MAP_OHT(size_t table_size = 10, float load_factor = 0.75, Hash hasher = Hash(), Compare comp = Compare(), Equals eq = Equals())
            : o_hash(table_size, load_factor, hasher, comp, eq) {};

            ~MAP_OHT() = default;

            void insert(Key k, Value v){
                if (contains(k)) {
                    throw std::invalid_argument("Chave ja existe no dicionario");
                }
                o_hash.insert(k, v);
            }

            void update(Key k, Value newValue){
                if(!contains(k)){
                    throw std::invalid_argument("Chave nao encontrada para atualizacao");
                }
                o_hash[k] = newValue;
            }

            Value& at(const Key& k){
                return o_hash.at(k);
            }

            const Value& at(const Key& k) const{
                return o_hash.at(k);
            }

            void erase(Key k){
                o_hash.erase(k);
            }

            bool contains(Key k){
                return o_hash.contains(k);
            }

            int size(){
                return o_hash.size();
            }

            void clear(){
                o_hash.clear();
            }

            void show(){
                o_hash.show();
                std::cout << std::endl;
            }

            const Value& operator[](const Key& k) const{
                if(!o_hash.contains(k)){
                    throw std::invalid_argument("chave inexistente");
                }
                return o_hash.at(k);
            }

            Value& operator[](const Key& k){
                if(!o_hash.contains(k)){
                    o_hash.insert(k, Value());
                }
                return o_hash.at(k);
            }

            std::vector<std::pair<Key, Value>> rout() const{ 
                return o_hash.toVector();
            }
};
#include "..\..\src\dicionarios\MAP_OHT.tpp"
#endif