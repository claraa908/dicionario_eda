#ifndef DICT_RBT_HPP
#define DICT_RBT_HPP
#include "..\estruturas\RBT.hpp"

namespace d_rbt{
    template <typename Key, typename Value>
    class Dictionary{
        private:
            RBT<Key, Value> rbt_tree;
        public:
            //construtor default, cria um dicionário vazio
            Dictionary() = default;

            //construtor que recebe um par
            Dictionary(Key k, Value v){
                insert(k, v);
            }

            ~Dictionary() = default;

            void insert(Key k, Value v){
                rbt_tree.insert(k, v);
            }

            void update(Key k, Value newValue){
                insert(k, newValue);
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

            /*
            * TODO: iteração = percorre os pares da estrutura
            * na rbt provavelmente é para percorrer os pares em ordem simétrica e usar a chave como iterador
            * talvez uma sobrecarga do operador [] (???)
            */
    };
}

#endif