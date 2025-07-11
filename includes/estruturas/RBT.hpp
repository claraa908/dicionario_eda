/**
 * @file RBT.hpp
 * @author Clara Cruz
 * @brief Uma árvore RBT
 * Estrutura de dados avancada - 2025.1
 * @version 0.2
 * @date 2025-07-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef RBT_HPP
#define RBT_HPP
#include <string>
#include <iostream>
#include <utility>
#include <stdexcept>
#include <algorithm>

/**
 *  @brief Define as cores padrões da rubro negra como booeleanos
 */
#define RED true
#define BLACK false

/**
 * @brief Classe que implementa uma árvore binária do tipo rubro negra.
 * 
 * Implementa operações como inserção, remoção e busca mantendo o balanceamento 
 * através das propriedades de uma árvore rubro-negra.
 * 
 * @tparam Key key type
 * @tparam Value value type
 * @tparam Compare less function type
 * @tparam Equals equal_to function type
 */
template <typename Key, typename Value, 
          typename Compare = std::less<Key>, typename Equals = std::equal_to<Key>>
class RBT{
    private:

        /**
         * @brief Estrutura que representa um nó dentro da árvore.
         * Possui um par de chave e valor, a cor do nó para balanceamento,
         * além dos ponteiros para o filho esquerdo, direito e para o pai.
         */
        struct Node{
            std::pair<Key,Value> tuple; // Par de chave e valor do nó
            bool color; // Cor do nó da árvore
            Node* left; // Ponteiro para o filho esquerdo do nó
            Node* right; // Ponteiro para o filho direito do nó
            Node* parent; // Ponteiro para o pai do nó
            
                /**
                 * @brief construtor do nó
                 * @param k Chave
                 * @param v Valor
                 * @param c Cor
                 * @param l ponteiro para o filho esquerdo
                 * @param r ponteiro para o filho direito
                 * @param p ponteiro para o pai
                 */
                Node(const Key& k, const Value& v, bool c, Node* l, Node* r, Node* p){
                    tuple.first = k;
                    tuple.second = v;
                    color = c;
                    left = l;
                    right = r;
                    parent = p;
                }
        };

        //variáveis
        Node* root; // Ponteiro que aponta para a raiz da árvore
        Node* nil; // Ponteiro que representa nó nulo (folhas e pai da raiz)
        mutable int count_comp; // Contador de comparações de chaves
        mutable int count_recolor; // Contador de recoloração
        mutable int count_rotation; // Contador de rotações realizadas
        Compare less; // Referência para função de less
        Equals equal; // Referência para função to_equal

        //funções privadas

        /**
         * @brief Função de rotação para direita.
         * Recebe um nó e realoca seus ponteiros de modo que ele vá para a 
         * direita. No fim, recalcula a altura do nó em sua nova posição.
         * @param x Ponteiro para um nó que é o pivô da rotação
         * @return o nó realocado na posição correta.
         */
        Node* rightRotation(Node* x);

        /**
         * @brief Função de rotação para esquerda.
         * Recebe um nó e realoca seus ponteiros de modo que ele vá para 
         * esquerda. No fim, recalcula altura do nó em sua nova posição.
         * @param x Ponteiro para um nó que é o pivô da rotação
         * @return O nó realocado na posição correta.
         */
        Node* leftRotation(Node* x);

        /**
         * @brief Função privada de inserção.
         * 
         * Recebe a chave do nó e seu valor caso encontre a chave passada, 
         * atualiza o valor do nó, caso contrário faz a inserção de um novo nó de
         * cor vermelha. 
         * 
         * Durante a inserção um mantido um ponteiro pai do nó atual, para que 
         * os ponteiros entre pai e filho sejam ajustados após a criação do novo 
         * nó.
         * 
         * Ao final da função será chamado a função de conserto para garantir que
         * nenhuma regra de coloração da RBT está sendo violada.
         * 
         * @param k Chave do nó.
         * @param v Valor do nó.
         */
        void _insert(const Key& k, const Value& v);


        /**
         * @brief Função de conserto após inserção em árvore rubro-negra.
         * 
         * Essa função é chamada após a inserção de um novo nó vermelho na árvore. 
         * Como a propriedade da rubro-negra exige que um nó vermelho não tenha pai vermelho,
         * a função irá subir pela árvore enquanto o pai do nó atual for vermelho.
         * 
         * Existem dois casos principais (espelhados) a considerar:
         * - Quando o pai é filho esquerdo do avô.
         * - Quando o pai é filho direito do avô.
         * 
         * Em ambos casos é verificado se o tio (irmão do pai) é vermelho. Se sim faz apenas
         * recoloração (caso 1). Caso contrário, realiza uma rotação (simples ou dupla) 
         * dependendo do lado em que está o nó atual.
         * 
         * Ao final a raiz será preta, respeitando as propriedades da rubro-negra.
         * 
         * @param x Ponteiro para o nó recém-inserido na árvore.
         */
        void fixup_insertion(Node* x);

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
         * @brief Função privada de remoção
         * 
         * Recebe uma chave e faz a busca de seu nó pela árvore, caso não 
         * encontre não faz nada, caso contrário chama a função delete_RB, 
         * que fará de fato a remoção do nó encontrado com sua respectiva chave
         * @param k Chave a ser buscada para remoção
         */
        void _erase(const Key& k);

        /**
         * @brief Função que remove um nó da árvore, mantendo suas propriedades.
         * 
         * Remove o nó p da árvore rubro-negra. Caso p possua no máximo um filho 
         * (ou nenhum), esse filho (ou o nó nil se não houver) será usado diretamente 
         * para substituí-lo.
         * 
         * Se p tiver dois filhos, será buscado o menor valor da subárvore direita — 
         * seu sucessor (y), utilizando a função minimum. O conteúdo de y será 
         * copiado para p, e o nó y será então o removido fisicamente da árvore.
         * 
         * Importante: o nó realmente desalocado da memória é y, não necessariamente p.
         * O ponteiro x representa o filho de y, que ocupará o lugar de y na árvore.
         * 
         * Se a cor original de y for preta, a operação de remoção pode violar 
         * propriedades da árvore rubro-negra. Nesse caso, a função fixup_erase 
         * será chamada para restaurar o balanceamento a partir de x.
         * 
         * @param p Ponteiro para o nó que será removido da árvore.
         */
        void delete_RB(Node* p);

        /**
         * @brief Função auxiliar que retorna o menor valor de uma subárvore/árvore
         * @param p Ponteiro para o nó que irá iniciar a busca
         * @return o menor valor da subárvore passada
         */
        Node* minimum(Node* p);
        
        /**
         * @brief Função de conserto após remoção em árvore rubro-negra.
         * 
         * Após a remoção de um nó preto a propriedade de balanceamento da árvore 
         * pode ser violada no caminho do nó substituto x que se tornará duplo preto
         * 
         * Esta função irá corrigir esse problema enquanto x for preto e diferente da raiz.
         * 
         * O algoritmo trata dois casos principais (espelhados):
         * - Quando x é filho esquerdo de seu pai.
         * - Quando x é filho direito de seu pai.
         * 
         * Em cada caso se verificará se o irmão de x (w) é vermelho 
         * (nesse caso, faz-se uma rotação e troca de cores), ou se os filhos de w são pretos.
         * Se ambos os filhos forem pretos, recolore w e sobe para o pai. 
         * Caso contrário, faz rotações (simples ou dupla) dependendo de qual filho de w é vermelho.
         * 
         * Ao final, a cor de x é ajustada para preta, restaurando as propriedades da rubro-negra.
         * 
         * @param x Ponteiro para o nó que herdou o duplo preto.
         */
        void fixup_erase(Node* x);

        /**
         * @brief Função privada que verifica se uma determinada chave está 
         * contido ou não na árvore.
         * @param k Chave que será buscada
         * @return True caso a chave esteja na árvore, false caso contrário
         */
        bool _contains(const Key& k);

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
        bool _empty(Node* p);

        /**
         * @brief Função privada que conta quantos nós uma árvore possui.
         * @param p Ponteiro para o nó atual (geralmente iniciado com a raiz)
         * @return O valor total de nós que estão dentro da estrutura
        */
        int _size(Node* p);

        /**
         * @brief Função privada que permite visualizar a árvore no terminal
         * @param node Ponteiro para nó (iniciado com a raiz)
         * @param heranca String usada internamente para controlar o recuo visual 
         * e indicar a posição do nó na árvore ("r" para filho direito, "l" para esquerdo).
         */
        void bshow(Node *node, std::string heranca);

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
         * 
         * Inicializa a árvore criando um nó nil, que representa os ponteiros nulos
         * padrão da estrutura. O nil é preto e aponta para ele mesmo em left e right.
         * 
         * O ponteiro root é inicializado apontando para nil, representando uma árvore vazia.
         * Também inicializa os contadores de comparação, rotação e recoloração com zero.
         */
        RBT();

        /**
         * @brief Construtor com comparadores.
         * realiza as mesmas operações do construtor default com diferença que
         * inicializa os comparadores, ou sebrecarrega eles, com um comparador
         * passado.
         * @param comp O comparador less sobrecarregado da estrutura.
         * @param eq_comp O comparador equals sobrecarregado da estutura.
         */
        RBT(Compare comp, Equals eq_comp);

        /**
         * @brief Destrutor da árvore.
         * 
         * Libera todos os nós alocados dinamicamente da árvore, incluindo o nó nil.
         * Garante que não haja vazamentos de memória ao final da execução.
         */
        ~RBT();

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
         * Em caso afirmativo realiza uma busca para sua remoção.
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
        * da estrutura e suas respectivas cores.
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
        int getCountComparation();

        /**
        * @brief Função getter que mostra o estado do contador de recoloração 
        * dos nós dentro da estrutura
        * @return Retorna o número de recolorações feitas após todas as operações 
        * realizadas dentro da árvore
        */
        int getCountRecolor();

        /**
         * @brief Função getter que mostra o estado do contador de rotações
         * @return Retorna o número de total de rotações realizadas após todas 
         * as operações realizadas
         * dentro da árvore.
         */
        int getCountRotation();
};
#include "..\..\src\estruturas\RBT.tpp"
#endif