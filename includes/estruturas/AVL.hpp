/**
 * @file AVL.hpp
 * @author Clara Cruz
 * @brief Uma árvore AVL
 * Estrutura de dados avancada - 2025.1
 * @version 0.2
 * @date 2025-07-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef AVL_HPP
#define AVL_HPP
#include <string>
#include <vector>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <functional>

/**
 * @brief Classe que implementa uma árvore binária do tipo AVL.
 * 
 * Implementa operações como inserção, remoção e busca mantendo o balanceamento 
 * através das propriedades de uma árvore AVL.
 * 
 * @tparam Key key type
 * @tparam Value value type
 * @tparam Compare less function type
 * @tparam Equals equal_to function type
 */
template <typename Key, typename Value, 
          typename Compare = std::less<Key>, typename Equals = std::equal_to<Key>>
class AVL{
    private:
        /**
         * @brief Estrutura que representa um nó dentro da árvore.
         * Possui um par de chave e valor, a altura do nó para balanceamento,
         * além dos ponteiros para o filho esquerdo e direito.
         */
        struct Node{
            std::pair <Key, Value> tuple; // Par de chave e valor do nó
            int height; // Altura do nó da árvore
            Node* left; // Ponteiro para o filho esquerdo do nó
            Node* right; // Ponteiro para o filho direito do nó

            /**
             * @brief construtor do nó
             * @param k Chave
             * @param v Valor
             * @param h Altura
             * @param l ponteiro para o filho esquerdo
             * @param r ponteiro para o filho direito
             */
            Node (Key k, Value v, int h, Node* l, Node* r) {
                tuple = std::make_pair(k, v);
                left = l;
                right = r;
                height = h;
            }
        };

        //variáveis
        Node* root; // Ponteiro que aponta para a raiz da árvore
        mutable int count_comp; //Contador de comparações de chaves
        mutable int count_rotation; // Contador de rotações realizadas
        Compare less; // Referência para função de less
        Equals equal; // Referência para função to_equal

        //funções privadas

        /**
         * @brief Função que recebe um nó e calcula de forma recursiva
         * sua altura em relação a árvore.
         * @param node Pnteiro para o nó que será calculado a altura
         * @return Retorna a altura atual do nó
         */
        int height (Node* node);

        /**
         * @brief Função que calcula o fator de balanceamento do nó em relação a
         * árvore. O fator de balanceamento de uma árvore é obtido através do 
         * calculo da diferença da altura do lado direito e esquerdo
         * @param node Ponteiro para o nó que será calculado o balanço
         * @return Retorna o balanço do nó
         */
        int balance (Node* node);

        /**
         * @brief Função de rotação para direita.
         * Recebe um nó e realoca seus ponteiros de modo que ele vá para a 
         * direita. No fim, recalcula a altura do nó em sua nova posição.
         * @param p Ponteiro para um nó que é o pivô da rotação
         * @return o nó realocado na posição correta.
         */
        Node* rightRotation (Node* p);

        /**
         * @brief Função de rotação para esquerda.
         * Recebe um nó e realoca seus ponteiros de modo que ele vá para 
         * esquerda. No fim, recalcula altura do nó em sua nova posição.
         * @param p Ponteiro para um nó que é o pivô da rotação
         * @return O nó realocado na posição correta.
         */
        Node* leftRotation (Node* p);

        /**
         * @brief Função privada de inserção.
         * 
         * Recebe a raiz da árvore para iniciar a busca recursiva pela chave 
         * passada. Se a chave não existir um novo nó será criado, caso contrário
         * o valor da chave existente será atualizado. Após a inserção é chamada
         * a função de conserto para garantir o balanceamento da árvore após as mudanças.
         * @param p Ponteiro para o nó (geralmente a raiz da subárvore).
         * @param k Chave do nó.
         * @param v Valor do nó.
         * @return O ponteiro para o novo nó inserido na posição correta.
         */
        Node* _insert(Node *p , const Key& k, const Value& v);


        /**
         * @brief Função para conserto de um nó inserido.
         * 
         * Calcula o fator de balanceamento do nó p. Se o balanceamento for menor
         * que -1, significa que a subárvore esquerda está desbalanceada: se k for menor
         * que a chave do filho esquerdo de p, aplica-se uma rotação simples para a direita,
         * caso contrário, uma rotação dupla para a direita. 
         * 
         * Se o balanceamento for maior que 1, o desbalanceamento está na 
         * subárvore direita, e aplica-se o espelhamento do caso anterior: 
         * rotação simples ou dupla à esquerda. 
         * 
         * No fim, é atualizada a altura do nó p.
         * @param p Ponteiro para nó (nesse caso o do pai do nó inserido).
         * @param k Chave do nó inserido
         * @return O ponteiro para o nó balanceado.
         */
        Node* fixup_insertion(Node *p, const Key& k);

        /**
         * @brief Faz a busca recursiva de uma chave a partir de um nó
         * 
         * @param p Nó onde vai se iniciar a busca (iniciado com a raiz)
         * @param k Chave a ser buscada
         * @return referência do valor associado a chave
         * @throw std::invalid_argument caso a chave não exista na árvore
         */
        Value& _at(Node* p, const Key& k);
        const Value& _at(Node* p, const Key& k) const;

        /**
         * @brief Função privada de remoção.
         * 
         * Recebe a raiz da árvore para iniciar a busca recursiva pela chave 
         * passada para remoção. Ao encontrar a chave é necessário encontrar um
         * nó para substituir o nó que será removido. 
         * 
         * Se o nó tiver um filho (ou nenhum) a substituição será o valor desse 
         * filho (ou nulo caso não tenha filhos). 
         * Caso o nó possua ambos filhos, será chamado a função auxiliar minimum 
         * que irá retornar o sucessor (menor valor da subárvore do filho direito) 
         * do nó para substituí-lo.
         * 
         * Ao final de tudo, o nó substituto terá sua altura atualizada e a função
         * para conserto será chamada para manter o balanceamento da árvore pós remoção.
         * @param p Ponteiro para o nó (geralmente a raiz da subárvore).
         * @param k Chave do nó.
         * @return O ponteiro para o nó substituto na posição do nó removido.
         */
        Node* _erase(Node* p, const Key& k);

        /**
         * @brief Função auxiliar que retorna o menor valor de uma subárvore/árvore
         * @param p Ponteiro para o nó que irá iniciar a busca
         * @return o menor valor da subárvore passada
         */
        Node* minimum(Node* p);

        /**
         * @brief Função para conserto de um nó após remoção.
         * 
         * Calcula o fator de balanceamento do nó p. Se o balanceamento for menor 
         * que -1, significa que a subárvore esquerda está desbalanceada: se o filho 
         * esquerdo de p também estiver balanceado à esquerda ou perfeitamente balanceado,
         * aplica-se uma rotação simples para a direita. 
         * Caso contrário, é necessário aplicar uma rotação 
         * dupla para a direita.
         * 
         * Se o balanceamento for maior que 1, o desbalanceamento está na subárvore 
         * direita: se o filho direito estiver balanceado à direita ou perfeitamente 
         * balanceado, aplica-se uma rotação simples para a esquerda. 
         * Caso contrário, realiza-se uma rotação dupla para a esquerda.
         * 
         * No final, é atualizada a altura do nó p.
         * 
         * @param p Ponteiro para o nó a ser reequilibrado após a remoção.
         * @return O ponteiro para o nó balanceado.
         */
        Node* fixup_erase(Node* p);

        /**
         * @brief Função privada que verifica recursivamente se uma 
         * determinada chave está contido ou não na árvore.
         * @param p Ponteiro para nó atual (geralmente iniciado com a raiz)
         * @param k Chave que será buscada
         * @return True caso a chave esteja na árvore, false caso contrário
         */
        bool _contains(Node* p, const Key& k);

        /**
         * @brief Função privada que desaloca todos os nós contidos na 
         * árvore recursirvamente, usando o percurso em pós-ordem.
         * @param p Ponteiro para nó (geralmente iniciado com a raiz)
         * @return retorna o ponteiro para nós apontando para nullptr, indicando
         * que a árvore está vazia.
         */
        Node* _clear(Node* p);

        /**
         * @brief Função privada que verifica se a árvore possui ou não elementos
         * @param p Ponteiro para nó atual (geralmente iniciado com a raiz)
         * @return True caso a árvore esteja vazia, false caso contrário
         */
        bool _empty(Node *p);

        /**
         * @brief Função privada que conta quantos nós uma árvore possui.
         * @param p Ponteiro para o nó atual (geralmente iniciado com a raiz)
         * @return O valor total de nós que estão dentro da estrutura
        */
        int _size(Node *p);

        /**
         * @brief Função privada que permite visualizar a árvore no terminal
         * @param node Ponteiro para nó (iniciado com a raiz)
         * @param heranca String usada internamente para controlar o recuo visual 
         * e indicar a posição do nó na árvore ("r" para filho direito, "l" para esquerdo).
         */
        void bshow(Node* node, std::string heranca) const;

        /**
         * @brief Função privada que percorre a árvore em ordem e passa os seus 
         * valores para dentro de um vetor.
         * @param p nó que vai iniciar a busca (iniciado na raiz).
         * @param v vetor que receberá os pares.
         */
        void _toVector(Node* p, std::vector<std::pair<Key, Value>>& v) const;

    public:
        /**
         * @brief Construtor default.
         * O ponteiro root é inicializado como nullpter, representando uma árvore 
         * vazia. Também inicializa os contadores de comparação e rotação com zero.
         */
        AVL();

        /**
         * @brief Destrutor da árvore.
         * 
         * Libera todos os nós alocados dinamicamente da árvore.
         * Garante que não haja vazamentos de memória ao final da execução.
         */
        ~AVL();

        /**
        * @brief Insere um novo nó dentro da árvore.
        * Se a chave já existir o valor será atualizado.
        * @param k chave do novo nó.
        * @param v valor do novo nó.
        */
        void insert(const Key& k, const Value& v);


        /**
        * @brief Diz qual valor está atrelado a uma determinada chave de um nó.
        * Primeiro verifica se a árvore está vazia e depois realiza a busca 
        * recursiva caso não esteja.
        * Caso a chave não esteja na árvore lança uma exceção.
        * @param k Chave que está sendo buscada.
        * @return Referência ao valor associado a chave.
        * @throw std::runtime_error: Caso a árvore esteja vazia.
        * @throw std::invalid_argument: Caso a chave não esteja na árvore.
        */
        Value& at(const Key& k);

        /**
        * @brief Função constante do at que retorna um valor associado a 
        * uma determinada chave de um nó.
        * @param k Chave que está sendo buscada.
        * @return Referência constante ao valor associado a chave.
        * @throw std::runtime_error: Caso a árvore esteja vazia.
        * @throw std::invalid_argument: Caso a chave não esteja na árvore.
        */
        const Value& at(const Key& k) const;


        /**
         * @brief Remove um determinado nó da árvore com base na chave fornecida.
         * Primeiro verifica se o valor está na árvore.
         * Em caso afirmativo realiza uma busca recursiva para sua remoção.
         * @param k Chave que está sendo buscada para remoção.
         * @throw std::invalid_argument: Caso a chave não exista na árvore.
        */
        void erase(const Key& k);


        /**
         * @brief Verifica se um valor está ou não na árvore com base na chave
         *  fornecida.
         * @param k Chave que será buscada.
         * @return True caso a chave esteja contida na árvore, false caso contrário.
        */
        bool contains(const Key& k);

        /**
         * @brief Remove todos os nós contidos da árvore.
         * Limpa toda a estrutura, liberando todos os seus elementos.
         * @throw std::runtime_error: Caso a árvore já esteja vazia.
        */
        void clear();


        /**
         * @brief Verifica se a árvore possui nós ou não
         * @return True caso a árvore esteja vazia, false caso contrario
        */
        bool empty();

        /**
         * @brief Conta quantos nós uma árvore possui.
         * @return O valor total de nós que estão dentro da estrutura
        */
        int size();

        /**
         * @brief Sobrecarga do operador de indexação.
         * Se a chave k estiver contido na árvore retorna o seu valor
         * associado. Caso contrário, insere um novo nó na árvore e retorna um 
         * valor associado.
         * @param k Chave
         * @return Valor associado a chave
        */
        Value& operator[](const Key& k);

        /**
         * @brief Versão const da sobrecarga do operador de indexação.
         * Se a chave k estiver contido na árvore retorna o seu valor associado.
         * Caso contrário, lança uma exceção.
         * @param k Chave
         * @return Valor associado a chave
         * @throw std::runtime_error: Caso a árvre esteja vazia
         * @throw std::invalid_argument: Caso a chave não esteja na árvore
        */
        const Value& operator[](const Key& k) const;

       /**
        * @brief Exibe a estrutura da árvore no terminal.
        * Demonstra visualmente de forma hierárquica a posição dos nós dentro 
        * da estrutura.
        */
        void show();

        /**
         * @brief Função pública que transforma a árvore em um vetor
         * @return Vetor da árvore.
         */
        std::vector<std::pair<Key, Value>> toVector() const;

        /**
        * @brief Função getter que mostra o estado do contador de comparações de 
        * chaves dentro da estrutura
        * @return Retorna o número de comparações feitas após todas as operações 
        * realizadas dentro da árvore
        */
        int getCountComparation() const;

        /**
         * @brief Função getter que mostra o estado do contador de rotações
         * @return Retorna o número de total de rotações realizadas após todas 
         * as operações realizadas
         * dentro da árvore.
         */
        int getCountRotation() const;
};

#include "../../src/estruturas/AVL.tpp"
#endif