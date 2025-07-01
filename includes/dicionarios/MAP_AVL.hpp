#ifndef MAP_AVL_HPP
#define MAP_AVL_HPP
#include "..\estruturas\AVL.hpp"

//TODO
template <typename Key, typename Value>
    class MAP_AVL{
        private:
            AVL<Key, Value> avl_tree;

        public:
            Dictionary() = default;

            Dictionary(Key k, Value v){
                insert(k, v);
            }

            ~Dictionary() = default;

            void insert(Key k, Value v){
                 if (contains(k)) {
                    throw std::invalid_argument("Chave ja existe no dicionario");
                }
                avl_tree.insert(k, v);
            }

            void update(Key k, Value newValue){
                if(!contains(k)){
                throw std::invalid_argument("Chave nao encontrada para atualizacao")
                }
                avl_tree[k] = newValue;
            }

            Value& at(const Key& k){
                if()
                return avl_tree.at(k);
            }

            const Value& at(const Key& k) const{
                return avl_tree.at(k);
            }

            void erase(const Key k){
                if(empty()){
                    throw std::runtime_error("Dicionario vazio, nao ha o que remover");
                }
                if(!contains(k)){
                    throw std::invalid_argument("Chave nao encontrada para remocao");
                }

                avl_tree.erase(k);
            }

            bool contains(const Key k){
                return avl_tree.contains(k);
            }

            int size(){
                return avl_tree.size();
            }

            void clear(){
                if(empty()){
                    throw std::runtime_error("Dicionario vazio, nao ha o que limpar")
                }
                avl_tree.clear();
            }

            bool empty(){
                return avl_tree.empty();
            }

            void show(){
                avl_tree.show();
            }
}; 
#include "..\..\src\dicionarios\MAP_AVL.tpp"
#endif