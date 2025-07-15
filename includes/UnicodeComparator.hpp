/**
 * @file UnicodeComparator.hpp
 * @author Clara Cruz
 * @brief Definição para chaves unicodes e seus comparadores.
 * Estrutura de dados avancada - 2025.1
 * @version 0.2
 * @date 2025-07-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef UNICODE_COMPARATORS_HPP
#define UNICODE_COMPARATORS_HPP

#include <unicode/unistr.h>
#include <unicode/coll.h>
#include <unicode/locid.h>
#include <mutex>
#include <functional>
#include <iostream>
#include <utility>

/**
 * @brief Encapsula icu::UnicodeString para para ser usado como chave nas
 * estruturas de dados.
 *
 * Fornece construtores para inicialização, um método para acesso à string interna, 
 * e uma sobrecarga do operador de inserção para facilitar a impressão.
 */
class uniStringKey{
    private:
        //instância do UnicodeString.
        icu::UnicodeString str;
    public:

        /**
         * @brief Construtor Default.
         */
        uniStringKey() = default;

        /**
         * @brief Construtor que define um valor para varíavel unicode da classe.
         * @param k Valor que será associada a variável unicode.
         */
        uniStringKey(const icu::UnicodeString& k){
            str = k;
        }

        /**
         * @brief Construtor que recebe uma string, converte e associa o valor para
         * a variável unicode da classe.
         * @param k string que será associada a variável unicode.
         */
        uniStringKey(const std::string k){
            str = icu::UnicodeString::fromUTF8(k);
        }

        /**
         * @brief Método get que retorna a variável unicode contida na classe.
         * @return Variável unicode da classe.
         */
        const icu::UnicodeString& getStr() const { return str; }

        /**
         * @brief Sobrecarga do operador de inserção (<<) para imprimir objetos 
         * uniStringKey. 
         * 
         * Converte a variável uniStringKey para string e insere na stream de saída. 
         * Permitindo sua impressão direta do objeto.
         * (<<).
         * 
         * @param os Referência para o objeto ostream.
         * @param key Referência para o objeto uniStringKey.
         * @return Referência para o ostream.
         */
        friend std::ostream& operator<<(std::ostream& os, const uniStringKey& key) {
            std::string utf8_result;
            key.str.toUTF8String(utf8_result);
            os << utf8_result;
            return os;
        }
};

/**
 * @brief Função que configura um collator. 
 * 
 * Caso não haja nenhum problema em sua criação, configura o collator em 
 * nível secundário, ou seja, as comparações realizadas por ele com objetos 
 * uniStringKey, serão:
 * - a != á != à --> Sensíveis a acentuação.
 * - A == a --> Insensíveis a letras maiúsculas e minúsculas.
 * 
 * @return Um ponteiro para instancia de um collator em nível secundário. Ou
 * nullptr, em caso de falha na criação
 */
static icu::Collator* getGlobalCollator(){
    static icu::Collator* collator = nullptr;
    static std::once_flag once_flag;

    std::call_once(once_flag, []() {
        UErrorCode status = U_ZERO_ERROR;
        collator = icu::Collator::createInstance(icu::Locale::getDefault(), status);
        if (U_FAILURE(status)) {
            std::cerr << "Erro fatal ao criar Collator: " << u_errorName(status) << std::endl;
            collator = nullptr;
        } else {
            collator->setStrength(icu::Collator::SECONDARY);
        }
    });
    return collator;
}

/**
 * @brief Struct para comparação de variáveis uniStringKey quanto a igualdade.
 * 
 * Utiliza o Collator global configurado em nível secundário para determinar
 * a comparação entre duas chaves.
 */
struct uniStringEquals{
    /**
     * @brief Compara se duas uniStringKey são iguais.
     * 
     * Cria um collator por meio da função global getGlobalCollator. Se collator 
     * for nullptr, faz a comparação binária padrão sem o tratamento. Caso contrário,
     * faz a comparação de nivel secondário do collator.
     * 
     * @param a A primeira uniStringKey para comparação.
     * @param b A segunda uniStringKey para comparação.
     * @return true se as chaves são consideradas iguais pelo Collator, 
     * false caso contrário.
     */
    bool operator()(const uniStringKey& a, const uniStringKey& b) const {
        icu::Collator* collator = getGlobalCollator();
        if (!collator) {
            return a.getStr() == b.getStr();
        }
        return collator->compare(a.getStr(), b.getStr()) == icu::Collator::EComparisonResult::EQUAL;
    }
};

/**
 * @brief Struct que compara se uma uniStringKey é menor que a outra.
 * 
 * Utiliza o Collator global configurado em nível secundário para determinar
 * a ordem lexicográfica entre duas chaves.
 */
struct uniStringLess{
    /**
     * @brief Compara se uma uniStringKey 'a' é menor que uma uniStringKey 'b'.
     * 
     * Cria um collator por meio da função global getGlobalCollator. Se collator 
     * for nullptr, faz a comparação binária padrão sem o tratamento. Caso contrário,
     * faz a comparação de nivel secondário do collator.
     * 
     * @param a A primeira uniStringKey para comparação.
     * @param b A segunda uniStringKey para comparação.
     * @return true se a variável "a" for considerada menor que a variável "b"  
     * pelo Collator, false caso contrário.
     */
    bool operator()(const uniStringKey& a, const uniStringKey& b) const {
        icu::Collator* collator = getGlobalCollator();
        if (!collator) {
            return a.getStr() < b.getStr();
        }
        return collator->compare(a.getStr(), b.getStr()) == icu::Collator::EComparisonResult::LESS;
    }
};

/**
 * @brief Struct que gera um valor hash para o objeto uniStringKey.
 */
struct uniStringHasher {
    size_t operator()(const uniStringKey& key) const {
        std::string str;
        key.getStr().toUTF8String(str);
        return std::hash<std::string>{}(str);
    }
};

/**
 * @brief Struct que faz a comparação de pares, usando apenas o primeiro valor do
 * par, no caso a chave.
 */
struct uniStringPairLess {
    bool operator()(const std::pair<uniStringKey, int>& a, const std::pair<uniStringKey, int>& b) const {
        return uniStringLess()(a.first, b.first);
    }
};

#endif