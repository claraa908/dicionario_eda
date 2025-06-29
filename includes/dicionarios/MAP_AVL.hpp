#ifndef MAP_AVL_HPP
#define MAP_AVL_HPP
#include "..\estruturas\AVL.hpp"

template <typename Key, typename Value>
    class MAP_AVL{
        private:
            AVL<Key, Value> avl_tree;

        public:
            //construtor default, cria um dicionário vazio
            Dictionary() = default;

            //construtor que recebe um par
            Dictionary(Key k, Value v){
                insert(k, v);
            }

            ~Dictionary() = default;

            //função de inserção no dicionario
            void insert(Key k, Value v){
                avl_tree.insert(k, v);
            }

            void update(Key k, Value newValue){
                insert(k, newValue);
            }

            Value& getValue(const Key& k){
                return avl_tree.getValue(k);
            }

            const Value& getValue(const Key& k) const{
                return avl_tree.getValue(k);
            }

            void erase(const Key k){
                avl_tree.erase(k);
            }

            bool contains(const Key k){
                return avl_tree.contains(k);
            }

            int size(){
                return avl_tree.size();
            }

            void clear(){
                avl_tree.clear();
            }

            //teste
            void show(){
                avl_tree.show();
            }

            /*
            * TODO: iteração = percorre os pares da estrutura
            * na avl provavelmente é para percorrer os pares em ordem simétrica e usar a chave como iterador
            * talvez uma sobrecarga do operador [] (???)
            */
}; 
#endif