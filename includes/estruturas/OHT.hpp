/**
 * @file OHT.hpp
 * @author Clara Cruz
 * @brief Uma tabela hash com tratamento de colisao por endereçamento aberto
 * Estrutura de dados avancada - 2025.1
 * @version 0.2
 * @date 2025-07-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef OHT_HPP
#define OHT_HPP
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <string>
#include <list>
#include <vector>
#include <utility>
#include <functional>

/**
 *  @brief status que serão usados para definir o estado de uma posição na tabela
 * se nunca foi acessada (empty), se ela está ocupada por um par (active) ou se já
 * foi ocupada por um par mas este foi apagado (deleted).
 */
enum status{
    EMPTY,
    ACTIVE,
    DELETED
};

/**
 * @brief Classe que implementa uma tabela hash com tratamento de
 * colisao por endereçamento aberto (open hash table).
 * 
 * @tparam Key key type
 * @tparam Value value type
 * @tparam Hash hash function type
 * @tparam Compare less function type
 * @tparam Equals equal_to function type
 */
template <typename Key, typename Value, typename Hash = std::hash<Key>, 
          typename Compare = std::less<Key>, typename Equals = std::equal_to<Key>>
class OHT{
    private:

        /**
         * @brief Estrutura que representa um nó dentro da tabela.
         * Possui um par de chave e valor e o status do nó.
         */
        struct Node{
            std::pair<Key, Value> tuple; // Par de chave e valor
            status n_status; // Estado do nó(vazio, ativo ou deletado)

            /**
             * @brief Construtor default
             * Usado para criação da tabela vazia
             */
            Node() : tuple(), n_status(EMPTY){}

            /**
             * @brief Construtor
             * @param k Chave
             * @param v Valor
             */
            Node(Key k, Value v){
                this->tuple = std::make_pair(k, v);
                n_status = ACTIVE;
            }
        };


        //variáveis
        size_t numElem; // Quantidade de pares na tabela
        float maxLoadFactor; // O valor máximo que o fator de carga pode ter
        size_t tableSize; // Tamanho atual da tabela
        Hash hashing; // Referência para função de codificação
        std::vector<Node> table; // tabela do tipo node
        mutable int count_comp; // Contador de comparações de chaves
        mutable int count_collisions; // Contador de colisões na tabela
        mutable int count_rehash; // Contador de rehash
        Compare less; // Referência para função de less
        Equals equal; // Referência para função to_equal

        /**
         * @brief Atualiza o tamanho da tabela caso o novo valor seja 
         * maior que o anterior. Caso seja, cria uma tabela temporária para
         * guardar os dados antigos, passa um novo vetor redimensinado para table,
         * zera seu número de elemento e copia os valores da tabela temporária 
         * para a nova tabela redimensionada.
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
         * @brief Função auxiliar que dado uma chave faz a busca por ela dentro 
         * da tabela, caso exista retorna o número de sua posição na tabela, 
         * caso contrário retorna -1.
         * 
         * @param k Chave que será buscada
         * @return A posição da chave na tabela se existir ou -1 caso contrário
         */
        int _contains(const Key& k);

        //funções de hashing duplo

        /**
         * @brief Função de hashing primária.
         * 
         * Recebe uma chave k, aplica a função de dispersão e faz o módulo pelo tamanho 
         * atual da tabela. Retorna a posição inicial da busca por essa chave.
         * 
         * @param k Chave.
         * @return A posição inicial da chave na tabela.
         */
        size_t hash1 (const Key& k) const;

        /**
         * @brief Função de hashing secundária.
         * 
         * Aplica uma função de dispersão sobre a chave k e faz o módulo pelo 
         * tamanho da tabela menos 1. Soma 1 ao resultado para garantir um valor 
         * de salto válido, diferente de 0, que será usado na sondagem dupla.
         * 
         * @param k Chave.
         * @return O valor do salto entre as tentativas.
         */
        size_t hash2 (const Key& k) const;

        /**
         * @brief Função de compressão para sondagem dupla (double hashing).
         * 
         * Combina as funções hash1 e hash2 para calcular a posição da tentativa  i
         * durante a inserção ou busca de uma chave k.
         * 
         * @param k Chave.
         * @param i Número da tentativa.
         * @return Um slot possível para a chave k.
         */
        size_t compress(const Key& k, size_t i);
        
    public:
        /**
         * @brief Construtor com parâmetros padrões.
         * 
         * Cria uma tabela hash com número primo de slots, inicializa os seus
         * contadores e o fator máximo de carga.
         * @param table_size O número de slots da tabela.
         * @param load_factor O fator máximo de carga da tabela.
         * @param hash O hash sobrecarregado da estrutura.
         * @param comp O comparador less sobrecarregado da estrutura.
         * @param eq_comp O comparador equals sobrecarregado da estrutura.
         */
        OHT(size_t table_size = 10, float load_factor = 0.75, Hash hasher = Hash{}, 
            Compare comp = Compare{}, Equals eq_comp = Equals{});

        /**
         * @brief Destrutor default
         */
        ~OHT();

        /**
         * @brief Insere um elemento na tabela.
         * 
         * Antes de inserir verifica se a tabela não está cheia verificando se 
         * seu fator de carga não está no máximo. Caso esteja, chama a função rehash
         * para aumentar a tabela.
         * 
         * Caso a chave já esteja na tabela atualiza o valor e retorna false, 
         * caso contrário percorre a tabela em busca do primeiro campo não ativo
         * para fazer a inserção e atualizar o número de elementos da tabela.
         * 
         * Ao fim da função, caso mesmo tendo sido feito o rehash, não seja possível
         * inserir, lança uma exceção notificando que a tabela está cheia.
         * 
         * @param k Chave para inserção.
         * @param v Valor para inserção ou atualização.
         * @return True caso insira um novo valor, false caso atualize.
         * @exception std::overflow_error Caso mesmo após o redimensionamento não
         * encontre slots vazios
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
         * exista e decrementa o número de elementos totais contidos na tabela.
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
         * @brief Percorre todos os nós da tabela chamando o construtor default do
         * node para esvaziar as tuplas e mudar o estado de todos os slots para empty
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
         * @return O valor atual do fator de carga da tabela
         */
        float load_factor()const;

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
         * @brief Redimensiona a tabela a fim de comportar pelo menos n elementos.
         * Só fará o redimensionamento caso o valor n passado seja maior que a
         * multiplicação do tamanho atual da tabela pelo fator máximo de carga. 
         * Após a verificação, chama a função rehash.
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
        int getCountComparation();

        /**
         * @brief Função getter que mostra o estado do contador de colisões de 
         * dentro da estrutura
         * @return Retorna o número de colisões feitas após todas as operações 
         * realizadas dentro da tabela
         */
        int getCountCollision();

        /**
         * @brief Função getter que mostra o estado do contador de rehash dentro
         * da estrutura
         * @return Retorna o número de rehash feitas após todas as operações 
         * realizadas dentro da tabela
         */
        int getCountRehash();
};
#include "..\..\src\estruturas\OHT.tpp"
#endif