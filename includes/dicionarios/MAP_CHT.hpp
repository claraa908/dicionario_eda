#ifndef MAP_CHT_HPP
#define MAP_CHT_HPP
#include "..\estruturas\CHT.hpp"
#include <stdexcept>

//TODO
template <typename Key, typename Value>
    class MAP_CHT{
        private:
            CHT<Key, Value> c_hash;

        public:
            Dictionary() = default;

            Dictionary(Key k, Value v){
                insert(k, v);
            }

            ~Dictionary() = default;

            void insert(Key k, Value v){
                if(!contains(k)){
                    c_hash.insert(k, v);
                } 
            }

            void update(Key k, Value newValue){
                if(contains(k)){
                    c_hash.insert(k, newValue);
                }
            }

            Value& getValue(const Key& k){
                return c_hash.getValue(k);
            }

            const Value& getValue(const Key& k) const{
                return c_hash.getValue(k);
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
                return c_hash.getValue(k);
            }

            Value& operator[](const Key& k){
                if(!c_hash.contains(k)){
                    c_hash.insert(k, Value());
                }
                return c_hash.getValue(k);
            }
};
#include "..\..\src\dicionarios\MAP_CHT.tpp"
#endif