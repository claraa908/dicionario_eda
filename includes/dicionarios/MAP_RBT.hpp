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
            MAP_RBT() : rbt_tree(){};

            MAP_RBT(Compare comp, Equals eq_comp) : rbt_tree(comp, eq_comp){};

            ~MAP_RBT() = default;

            void insert(Key k, Value v){
                if (contains(k)) {
                    throw std::invalid_argument("Chave ja existe no dicionario");
                }
                rbt_tree.insert(k, v); 
            }

            void update(Key k, Value newValue){
                if(!contains(k)){
                    throw std::invalid_argument("Chave nao encontrada para atualizacao");
                }
                rbt_tree[k] = newValue;
            }

            Value& at(const Key& k){
                return rbt_tree.at(k);
            }

            const Value& at(const Key& k) const{
                return rbt_tree.at(k);
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

            const Value& operator[](const Key& k) const{
                if(!rbt_tree.contains(k)){
                    throw std::invalid_argument("chave inexistente");
                }
                return rbt_tree.at(k);
            }

            Value& operator[](const Key& k){
                if(!rbt_tree.contains(k)){
                    rbt_tree.insert(k, Value());
                }
                return rbt_tree.at(k);
            }

            std::vector<std::pair<Key, Value>> rout() const{ 
                return rbt_tree.inOrder();
            }
};
#include "..\..\src\dicionarios\MAP_RBT.tpp"
#endif