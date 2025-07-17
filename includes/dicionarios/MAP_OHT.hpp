/**
 * @file MAP_OHT.hpp
 * @author Clara Cruz
 * @brief Um dicionário que funciona com uma Tabela Hash com Endereçamento Aberto
 * Estrutura de dados avancada - 2025.1
 * @version 0.2
 * @date 2025-07-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef MAP_OHT_HPP
#define MAP_OHT_HPP
#include "..\estruturas\OHT.hpp"
#include <functional>

/**
 * @brief Classe que implementa um dicionário baseado em uma tabela hash com 
 * tratamento de colisão por endereçamento aberto.
 * 
 * @tparam Key key type
 * @tparam Value value type
 * @tparam Hash hash function type
 * @tparam Compare less function type
 * @tparam Equals equal_to function type
 */
template <typename Key, typename Value, typename Hash = std::hash<Key>, typename Compare = std::less<Key>, typename Equals = std::equal_to<Key>>
    class MAP_OHT{
        private:

            // Instância que cria uma tabela hash com encadeamento exterior.
            OHT<Key, Value, Hash, Compare, Equals> o_hash;

        public:
        
            /**
             * @brief Construtor com parâmetros padrões.
             * Possui parâmetros pré-inicializados e passa esses valores recebidos]
             * ou não para o construtor da Hash.
             * 
             * @param table_size O número de slots da tabela.
             * @param load_factor O fator máximo de carga da tabela.
             * @param hash O hash sobrecarregado.
             * @param comp O comparador less sobrecarregado.
             * @param eq_comp O comparador equals sobrecarregado.
             */
            MAP_OHT(size_t table_size = 10, float load_factor = 0.75, Hash hasher = Hash(), Compare comp = Compare(), Equals eq = Equals());

            /**
             * @brief Destrutor Default
             */
            ~MAP_OHT();

            /**
             * @brief Função de inserção.
             * Verifica se a chave passada já está no dicionário, caso não esteja
             * chama a função de inserção da estrutura, caso contrário, lança um erro.
             * @param k Chave do dicionário.
             * @param v Valor associaado a chave.
             * @throw std::invalid_argument caso a chave já esteja no dicionário.
             */
            void insert(Key k, Value v);

            /**
             * @brief Função de atualização
             * Verifica se o dicionário já contém a chave, caso tenha, atualiza 
             * o valor, caso contrário lança uma exceção.
             * @param k Chave do dicionário.
             * @param v Valor associaado a chave que será modificado.
             * @throw std::invalid_argument caso a chave não esteja no dicionário.
             */
            void update(Key k, Value newValue);

            /**
             * @brief Função que retorna qual o valor associado a chave.
             * @param k Chave para encontrar o valor.
             * @return Valor associado a chave.
             */
            Value& at(const Key& k);
            const Value& at(const Key& k) const;

            /**
             * @brief Função que remove um par do dicionário baseado na chave
             * passada. Verifica se o dicionário está vazio e se a chave está na
             * estrutura para removê-la. Se não lança uma exceção.
             * @param k chave para remoção.
             * @throw std::runtime_error caso o dicionário esteja vazio.
             * @throw std::invalid_argument caso a chave não esteja na estrutura.
             */
            void erase(Key k);
    
            /**
             * @brief Função que verifica se um valor está ou não na estrutura.
             * @param k chave que será buscada.
             * @return True, caso possua a chave, falso caso contrário
             */
            bool contains(Key k);

            /**
             * @brief Função que retorna quantos elementos estão contidos dentro
             * da estrutura.
             * @return A quantidade de elementos do dicionário.
             */
            int size();

            /**
             * @brief Remove todos os pares do dicionário.
             */
            void clear();

            /**
             * @brief Verifica se o dicionário é vazio.
             * @return True caso esteja vazia, false caso contrário. 
             */
            bool empty();

            /**
             * @brief Função que mostra visualmente a estrutura do dicionário no
             * terminal
             */
            void show();

            /**
             * @brief Versão const da sobrecarga do operador de indexação.
             * Apenas retorna o valor associado chave.
             * @param k Index de busca.
             * @return Valor associado ao index.
             */
            const Value& operator[](const Key& k) const;

            /**
             * @brief Sobrecarga do operador de indexação.
             * Baseado em uma chave retorna o valor associado, caso a chave não
             * esteja na estrutura adiciona a chave e coloca um valor padrão.
             * @param k Index da busca.
             * @return Valor associado.
             */
            Value& operator[](const Key& k);

            /**
             * @brief Função que transforma a estrutura em um vetor.
             * @return Um vetor com os valores da estrutura.
             */
            std::vector<std::pair<Key, Value>> toVector() const;

            /**
             * @brief Função que retorna uma string com todas as métricas da estrutura
             * de dados utilizada. Serve para impressão.
             * @return Uma string com as métricas.
             */
            std::string metric() const;
};
#include "..\..\src\dicionarios\MAP_OHT.tpp"
#endif