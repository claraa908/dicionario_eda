/**
 * @file CHT.hpp
 * @author Clara Cruz
 * @brief Uma tabela hash com tratamento de colisao por encadeamento exterior
 * Estrutura de dados avancada - 2025.1
 * @version 0.2
 * @date 2025-07-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef CHT_HPP
#define CHT_HPP
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <string>
#include <list>
#include <vector>
#include <utility>
#include <functional>

/**
 * @brief Classe que implementa uma tabela hash com tratamento de
 * colisao por encadeamento exterior (chained hash table).
 * 
 * @tparam Key key type
 * @tparam Value value type
 * @tparam Hash hash function type
 * @tparam Compare less function type
 * @tparam Equals equal_to function type
 */
template <typename Key, typename Value, typename Hash = std::hash<Key>, 
          typename Compare = std::less<Key>, typename Equals = std::equal_to<Key>>
class CHT{
    private:
        //variáveis
        size_t numElem; // Quantidade de pares na tabela
        float maxLoadFactor; // O valor máximo que o fator de carga pode ter
        size_t tableSize; // Tamanho atual da tabela
        Hash hashing; // Referência para função de codificação
        std::vector<std::list<std::pair<Key, Value>>> table; // tabela
        mutable int count_comp; // Contador de comparações de chaves
        mutable int count_collisions; // Contador de colisões na tabela
        mutable int count_rehash; // Contador de rehash
        Compare less; // Referência para função de less
        Equals equal; // Referência para função to_equal

        /**
         * @brief Atualiza o tamanho da tabela caso o novo valor seja 
         * maior que o anterior. Caso seja, cria uma tabela temporária para
         * guardar os dados antigos, limpa e redimensiona a tabela atual, zera
         * seu número de elementos, ajusta seu novo tamanho e copia os valores 
         * da tabela temporária para a nova tabela.
         * 
         * @param m Novo tamanho da tabela
         */
        void rehash(size_t m);

        /**
         * @brief Função encontra o próximo valor primo maior ou igual a x
         * 
         * Inicia a busca a partir de x (ou do próximo ímpar, se x for par),
         * e verifica sequencialmente até encontrar o próximo número primo.
         * @param x valor inicial da busca
         * @return O próximo valor primo de x
         */
        size_t get_next_prime(size_t x);

        /** 
         * @brief Função de compressão que retorna a posição da chave
         * dentro da tabela.
         * 
         * Retorna o slot de uma chave calculando o módulo da função de dispersão
         * pelo tamanho atual da tabela.
         * 
         * @param k Chave que será convertida.
         * @return Um inteiro no intervalo de 0 a tableSize-1.
        */
        size_t compress(const Key& k) const;

    public:

        /**
         * @brief Construtor com parâmetros padrões
         * 
         * Cria uma tabela hash com número primo de slots, inicializa os seus
         * contadores, fator máximo de carga e os comparadores.
         * @param table_size O número de slots da tabela.
         * @param load_factor O fator máximo de carga da tabela.
         * @param hash O hash sobrecarregado da estrutura.
         * @param comp O comparador less sobrecarregado da estrutura.
         * @param eq_comp O comparador equals sobrecarregado da estutura.
         */
        CHT(size_t table_size = 10, float load_factor = 0.75, Hash hasher = Hash{}, 
            Compare comp = Compare{}, Equals eq_comp = Equals{});

        /**
         * @brief Destrutor default
         */
        ~CHT();

        /**
         * @brief Insere um elemento na tabela, caso a chave já esteja na tabela 
         * atualiza o valor e retorna false.
         * 
         * Antes de inserir verifica se a tabela não está cheia verificando se 
         * seu fator de carga não está no máximo. Caso esteja, chama a função rehash
         * para aumentar a tabela.
         * 
         * Ao fim da função, incrementa o número de elementos na tabela e retorna 
         * true.
         * 
         * @param k Chave para inserção.
         * @param v Valor para inserção ou atualização.
         * @return True caso insira um novo valor, false caso atualize.
         */
        bool insert(const Key& k, const Value& v);

        /**
         * Diz qual valor está atrelado a uma determinada chave de um slot.
         * Caso a chave não esteja na tabela lança uma exceção.
         * 
         * @param k Chave para busca.
         * @return Referência da chave associada a chave.
         * @exception std::invalid_argument caso a chave não esteja na tabela.
         */
        Value& at(const Key& k);
        const Value& at(const Key& k) const;

        /**
         * @brief Remove um elemento da tabela baseado na chave passada caso ela
         * exista na tabela.
         * Ao fim da função o número de elementos da tabela é decrementado.
         * 
         * @param k Chave para busca.
         * @return True caso o elemento seja removido, false caso contrário.
         */
        bool erase(const Key& k);

        /**
         * @brief Verifica se um elemento está na tabela ou não na tabela baseado
         * na chave passada.
         * 
         * @param k Chave para busca.
         * @return  True caso encontre o elemento, false caso contrário.
         */
        bool contains(const Key& k);

        /**
         * @brief Deleta todas as listas e os pares contidos nelas da tabela.
         *  Remove todos os elementos da tabela hash liberando a memória ocupada
         * pelas listas de colisão. Ao final o número de elementos é zerado.
         */
        void clear();

        /**
         * @brief Diz se a tabela está vazia ou não
         * @return True caso a tabela não possua elementos, false caso contrário
        */
        bool empty() const;

        /**
         * @brief Diz o tamanho total da tabela
         * @return A quantidade de pares contidos dentro da tabela
         */
        size_t size() const;

        /**
         * @brief Diz quantos slots uma tabela possui
         * @return Quantidade total de slots que a tabela possui
         */
        size_t num_slot() const;

        /**
         * @brief Diz o tamanho da lista de colisão baseado em um slot passado.
         * @param n Número do slot que se quer verificar o tamanho
         * @return Quantidade total de elementos contidos na lista de colisão.
         */
        size_t slot_size(size_t n) const;

        /**
         * @return O valor atual do fator de carga da tabela
         */
        float load_factor() const;

        /**
         * @return O maior valor que o fator de carga pode ter
         */
        float max_load_factor() const;

        /**
         * @brief Muda o valor do maxLoadFactor
         * Antes de modificar o valor verifica se está dentro do intervalo
         * permitido que é 0 < maxLoadFactor caso não esteja, lança uma exceção.
         * Ao fim da modificação chama a função reserve para redimensionar a tabela
         * após a modificação do fator de carga.
         * 
         * @param lf Novo fator de carga.
         * @exception std::out_of_range caso o valor passado não seja maior que 0.
         */
        void set_max_load_factor(float lf);

        /**
         * @brief Redimensiona a tabela, por meio da função rehash, a fim desta 
         * comportar pelo menos n elementos. Só fará o redimensionamento caso o 
         * valor n passado seja maior que a multiplicação do tamanho atual da 
         * tabela pelo fator máximo de carga. Após a verificação, chama a função 
         * rehash.
         * 
         * @param n Número mínimo de elementos desejado
         */
        void reserve(size_t n);

        /**
         * @brief Sobrecarga do operador de indexação.
         * Se a chave k estiver contido na tabela retorna o seu valor
         * associado. Caso contrário, insere um novo nó na tabela e retorna um 
         * valor associado.
         * @param k Chave
         * @return Valor associado a chave
        */
        Value& operator[](const Key& k);

        /**
         * @brief Versão const da sobrecarga do operador de indexação.
         * Se a chave k estiver contido na tabela retorna o seu valor associado.
         * Caso contrário, lança uma exceção.
         * @param k Chave
         * @return Valor associado a chave
         * @throw std::invalid_argument: Caso a chave não esteja na tabela (exceção 
         * do at)
        */
        const Value& operator[](const Key& k) const;

        /**
         * @brief Exibe a tabela no terminal
         */
        void show();
        
        /**
         * @brief Função que percorre a tabela e passa os pares para um vetor.
         * @return O vetor com os pares da tabela.
         */
        std::vector<std::pair<Key, Value>> toVector() const;

        /**
         * @brief Função getter que mostra o estado do contador de comparações de 
         * chaves dentro da estrutura
         * @return Retorna o número de comparações feitas após todas as operações 
         * realizadas dentro da tabela
         */
        int getCountComparation() const;

        /**
         * @brief Função getter que mostra o estado do contador de colisões de 
         * dentro da estrutura
         * @return Retorna o número de colisões feitas após todas as operações 
         * realizadas dentro da tabela
         */
        int getCountCollision() const;

        /**
         * @brief Função getter que mostra o estado do contador de rehash dentro
         * da estrutura
         * @return Retorna o número de rehash feitas após todas as operações 
         * realizadas dentro da tabela
         */
        int getCountRehash() const;
};

#include "..\..\src\estruturas\CHT.tpp"
#endif