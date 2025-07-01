#ifndef MAP_RBT_HPP
#define MAP_RBT_HPP
#include "..\estruturas\RBT.hpp"

//TODO
template <typename Key, typename Value>
    class MAP_RBT{
        private:
            RBT<Key, Value> rbt_tree;

        public:
            Dictionary() = default;

            Dictionary(Key k, Value v){
                insert(k, v);
            }

            ~Dictionary() = default;

            void insert(Key k, Value v){
                if(!contains(k)){
                    rbt_tree.insert(k, v);
                } 
            }

            void update(Key k, Value newValue){
                if(contains(k)){
                    rbt_tree.insert(k, newValue);
                }
            }

            Value& getValue(const Key& k){
                return rbt_tree.getValue(k);
            }

            const Value& getValue(const Key& k) const{
                return rbt_tree.getValue(k);
            }

            void erase(const Key& k){
                rbt_tree.erase(k);
            }

            bool contains(const Key& k){
                return rbt_tree.contains(k);
            }

            int size(){
                return rbt_tree.size();
            }

            void clear(){
                rbt_tree.clear();
            }

            void show(){
                rbt_tree.show();
                std::cout << std::endl;
            }
};
#include "..\..\src\dicionarios\MAP_RBT.tpp"
#endif