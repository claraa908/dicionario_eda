#ifndef DICT_AVL_HPP
#define DICT_AVL_HPP
#include "../estruturas/AVL.hpp"

namespace d_avl{
    template <typename Key, typename Value>
    class Dictionary{
        private:
            AVL<Key, Value> avl_tree;

        public:
            //construtor default, cria um dicionário vazio
            Dictionary() = default;

            //construtor que recebe um par
            Dictionary(Key k, Value v){
                insert(k, v);
            }

            void insert(Key k, Value v){
                avl_tree.insert(k, v);
            }

            void update(Key k, Value newValue){
                insert(k, newValue);
            }

            Value& getValue(Key& k){
                avl_tree.getValue(k);
            }

            const Value& getValue(const Key& k) const{
                avl_tree.getValue(k);
            }

            void erase(Key k){
                avl_tree.erase(k);
            }

            bool contains(Key k){
                avl_tree.contains(k);
            }

            int size(){
                avl_tree.size();
            }

            void clear(){
                avl_tree.clear();
            }

            //teste
            void show(){
                avl_tree.show();
            }

            /*funções pra implementar:
            * -- criacao = construtor
            * -- inserção = insert
            * -- atualização = ??
            * -- acesso = pegar um valor baseado na chave
            * -- remoção = erase
            * -- verificação = contains
            * iteração = percorre os pares da estrutura(talvez imprimir???)
            * -- Tamanho = size
            * -- Limpeza = remover todos os pares de chave
            */
    }; 
}
#endif