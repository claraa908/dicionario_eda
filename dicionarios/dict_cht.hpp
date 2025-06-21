#ifndef DICT_CHT_HPP
#define DICT_CHT_HPP
#include "../estruturas/CHT.hpp"

namespace d_cht{
    template <typename Key, typename Value>
    class Dictionary{
        private:
            CHT<Key, Value> c_hash;
        public:
            //construtor default, cria um dicionário vazio
            Dictionary() = default;

            //construtor que recebe um par
            Dictionary(Key k, Value v){
                insert(k, v);
            }

            void insert(Key k, Value v){
                c_hash.insert(k, v);
            }

            void update(Key k, Value newValue){
                insert(k, newValue);
            }

            Value& getValue(Key& k){
                c_hash.getValue(k);
            }

            const Value& getValue(const Key& k) const{
                c_hash.getValue(k);
            }

            void erase(Key k){
                c_hash.erase(k);
            }

            bool contains(Key k){
                c_hash.contains(k);
            }

            int size(){
                c_hash.size();
            }

            void clear(){
                c_hash.clear();
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