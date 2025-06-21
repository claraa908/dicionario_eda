#ifndef DICT_RBT_HPP
#define DICT_RBT_HPP
#include "../estruturas/RBT.hpp"

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

            void insert(Key k, Value v){
                rbt_tree.insert(k, v);
            }

            void update(Key k, Value newValue){
                insert(k, newValue);
            }

            Value& getValue(Key& k){
                rbt_tree.getValue(k);
            }

            const Value& getValue(const Key& k) const{
                rbt_tree.getValue(k);
            }

            void erase(Key k){
                rbt_tree.erase(k);
            }

            bool contains(Key k){
                rbt_tree.contains(k);
            }

            int size(){
                rbt_tree.size();
            }

            void clear(){
                rbt_tree.clear();
            }

            //teste
            void show(){
                rbt_tree.show();
            }
        /*funções pra implementar:
        * criacao = construtor
        * inserção = insert
        * atualização = ??
        * acesso = pegar um valor baseado na chave
        * remoção = erase
        * verificação = contains
        * iteração = percorre os pares da estrutura(talvez imprimir???)
        * Tamanho = size
        * Limpeza = remover todos os pares de chave
        */
    };
}

#endif