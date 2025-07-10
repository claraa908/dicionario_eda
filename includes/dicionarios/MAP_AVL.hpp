#ifndef MAP_AVL_HPP
#define MAP_AVL_HPP
#include "..\estruturas\AVL.hpp"
#include <functional>
#include <vector>

template <typename Key, typename Value, 
          typename Compare = std::less<Key>, typename Equals = std::equal_to<Key>>
    class MAP_AVL{
        private:
            AVL<Key, Value, Compare, Equals> avl_tree;

        public:
            MAP_AVL() : avl_tree(){};

            MAP_AVL(Compare comp, Equals eq_comp) : avl_tree(comp, eq_comp){};

            ~MAP_AVL() = default;

            void insert(Key k, Value v){
                if (contains(k)) {
                    throw std::invalid_argument("Chave ja existe no dicionario");
                }
                avl_tree.insert(k, v);
            }

            void update(Key k, Value newValue){
                if(!contains(k)){
                    throw std::invalid_argument("Chave nao encontrada para atualizacao");
                }
                avl_tree[k] = newValue;
            }

            Value& at(const Key& k){
                return avl_tree.at(k);
            }

            const Value& at(const Key& k) const{
                return avl_tree.at(k);
            }

            void erase(const Key& k){
                if(empty()){
                    throw std::runtime_error("Dicionario vazio, nao ha o que remover");
                }
                if(!contains(k)){
                    throw std::invalid_argument("Chave nao encontrada para remocao");
                }

                avl_tree.erase(k);
            }

            bool contains(const Key& k){
                return avl_tree.contains(k);
            }

            int size(){
                return avl_tree.size();
            }

            void clear(){
                if(empty()){
                    throw std::runtime_error("Dicionario vazio, nao ha o que limpar");
                }
                avl_tree.clear();
            }

            bool empty(){
                return avl_tree.empty();
            }

            void show(){
                avl_tree.show();
            }

            const Value& operator[](const Key& k) const{
                 if(!avl_tree.contains(k)){
                    throw std::invalid_argument("chave inexistente");
                }
                return avl_tree.at(k);
            }

            Value& operator[](const Key& k){
                if(!avl_tree.contains(k)){
                    avl_tree.insert(k, Value());
                }
                return avl_tree.at(k);
            }

            std::vector<std::pair<Key, Value>> rout() const{ 
                return avl_tree.inOrder();
            }
}; 
#include "..\..\src\dicionarios\MAP_AVL.tpp"
#endif