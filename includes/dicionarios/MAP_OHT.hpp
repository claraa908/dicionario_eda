#ifndef MAP_OHT_HPP
#define MAP_OHT_HPP
#include "..\estruturas\OHT.hpp"

//TODO
template <typename Key, typename Value>
    class MAP_OHT{
        private:
            OHT<Key, Value> o_hash;

        public:
            Dictionary() = default;

            Dictionary(Key k, Value v){
                insert(k, v);
            }

            ~Dictionary() = default;

            void insert(Key k, Value v){
                if(!contains(k)){
                    o_hash.insert(k, v);
                } 
            }

            void update(Key k, Value newValue){
                if(contains(k)){
                    o_hash.insert(k, newValue);
                }
            }

            Value& getValue(const Key& k){
                return o_hash.getValue(k);
            }

            const Value& getValue(const Key& k) const{
                return o_hash.getValue(k);
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
                return o_hash.getValue(k);
            }

            Value& operator[](const Key& k){
                if(!o_hash.contains(k)){
                    o_hash.insert(k, Value());
                }
                return o_hash.getValue(k);
            }
};
#include "..\..\src\dicionarios\MAP_OHT.tpp"
#endif