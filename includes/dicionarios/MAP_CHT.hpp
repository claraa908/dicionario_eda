#ifndef MAP_CHT_HPP
#define MAP_CHT_HPP
#include "..\estruturas\CHT.hpp"
#include <stdexcept>
#include <functional>

//TODO
template <typename Key, typename Value, typename Hash = std::hash<Key>,
          typename Compare = std::less<Key>, typename Equals = std::equal_to<Key>>
    class MAP_CHT{
        private:
            CHT<Key, Value, Hash, Compare, Equals> c_hash;

        public:
            MAP_CHT(size_t table_size = 10, float load_factor = 0.75, Hash hasher = Hash(), Compare comp = Compare(), Equals eq = Equals())
            : c_hash(table_size, load_factor, hasher, comp, eq) {};
            
            ~MAP_CHT() = default;

            void insert(Key k, Value v){
                if (contains(k)) {
                    throw std::invalid_argument("Chave ja existe no dicionario");
                }
                c_hash.insert(k, v);
            }

            void update(Key k, Value newValue){
                if(!contains(k)){
                    throw std::invalid_argument("Chave nao encontrada para atualizacao");
                }
                c_hash[k] = newValue;
            }

            Value& at(const Key& k){
                return c_hash.at(k);
            }

            const Value& at(const Key& k) const{
                return c_hash.at(k);
            }

            void erase(Key k){
                c_hash.erase(k);
            }

            bool contains(Key k){
                return c_hash.contains(k);
            }

            int size(){
                return c_hash.size();
            }

            void clear(){
                c_hash.clear();
            }

            void show(){
                c_hash.show();
                std::cout << std::endl;
            }

            const Value& operator[](const Key& k) const{
                if(!c_hash.contains(k)){
                    throw std::invalid_argument("chave inexistente");
                }
                return c_hash.at(k);
            }

            Value& operator[](const Key& k){
                if(!c_hash.contains(k)){
                    c_hash.insert(k, Value());
                }
                return c_hash.at(k);
            }

            std::vector<std::pair<Key, Value>> rout() const{ 
                return c_hash.toVector();
            }
};
#include "..\..\src\dicionarios\MAP_CHT.tpp"
#endif