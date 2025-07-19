/**
 * @file DictIO.hpp
 * @author Clara Cruz
 * @brief Gerenciador de entrada e saída de arquivos.
 * Estrutura de dados avancada - 2025.1
 * @version 0.2
 * @date 2025-07-10
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef DICTIO_IO_HPP
#define DICTIO_IO_HPP

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

#include <unicode/ustream.h>
#include <unicode/unistr.h>
#include <unicode/uchar.h>
#include <unicode/brkiter.h>
#include <unicode/locid.h>
#include <unicode/normalizer2.h>
#include <unicode/ustdio.h>

#include "UnicodeComparator.hpp"

//Teste: Função para ordenar os pares pelo valor, sendo esse valor um inteiro.
// template <typename Key>
// bool compare_t(std::pair<Key, int> t1, std::pair<Key, int> t2){ return t1.second >= t2.second; }

/**
 * @brief Classe que implementa um gerenciador de arquivos de dicionário.
 * 
 * Implementa operações de leitura de um arquivo de entrada fazendo o seu devido 
 * tratamento e adicionando suas palavras em um dicionário com suas frequências.
 * 
 * Também implementa a operação de escrita de um arquivo lendo os pares de valores 
 * de um dicionario junto de um cabeçalho de construção e gerando um novo arquivo
 * com essas informações.
 */
class DictIO{
    private:

        /**
         * @brief Função que calcula a largura visual aproximada de uma UnicodeString.
         * 
         * Percorre cada código de ponto da string `icu::UnicodeString` e estima
         * sua largura visual em espaços, considerando que alguns caracteres ocupam 
         * menos ou mais espaço visual na saída de terminal ou em arquivos de texto.
         * 
         * Regras aplicadas:
         * - Combinações de acento têm largura 0.
         * - Todos os demais caracteres têm largura padrão de 1.
         * 
         * Isso é útil para alinhar colunas com texto Unicode em saídas de tabela.
         * 
         * @param str A string Unicode a ser analisada.
         * @return int Largura visual total estimada.
         */
        int visualWidth(const icu::UnicodeString& str);

    public:

        /**
         * @brief Construtor Default
         */
        DictIO() = default;

        /**
         * @brief Função genérica que lê um arquivo, trata as palvras e coloca-as
         * em um dicionário.
         * 
         * Abre um arquivo e verifica se deu certo. 
         * Cria uma varíavel string para ler a linha e
         * uma variavel status para capturar os erros do icu.
         * 
         * Cria constante de normalização de composição (NFC) responsável por 
         * padronizar a leitura de strings unicode com acentos e verifica se a 
         * crição deu certo.
         * 
         * Percorre a linha do arquivo passado, normaliza com NFC, transforma 
         * tudo em minúsculo e cria uma variavel word que vai ser construída 
         * caractere por caractere. Durante a construção verifica se o caracter 
         * faz parte do alfanúmerico e caso seja um hífen, se há um 
         * caractere antes dele, caso encontre um espaço vazio adiciona a palavra 
         * montada no dicionário e limpa a variável para montar a próxima palavra.
         * 
         * Por fora de cada for é adicionado a última palavra, já que este acaba 
         * antes da última verificação de inserção. Por fim, fecha o arquivo.
         * 
         * @param map O dicionário que será inserido
         * @param input O arquivo de entrada que será lido
         */
        template <typename Map>
        void read(Map& map, const std::string input);

        /**
         * @brief Função genérica que escreve um novo arquivo a partir de um
         * dicionário exibindo suas palavras e frequências em uma tabela visual.
         * 
         * Abre ou cria um arquivo de saída e insere um cabeçalho com métricas e
         * informações de construção do dicionário. Em seguida, converte os pares do
         * dicionário para um vetor, ordena alfabeticamente respeitando acentos e
         * collation Unicode, e imprime esses pares em formato de tabela.
         * 
         * A largura da coluna de palavras é calculada dinamicamente, considerando a
         * largura visual dos caracteres Unicode, garantindo alinhamento estético 
         * da saída. As palavras são convertidas para UTF-8 antes de serem escritas.
         * 
         * @param map O dicionário de onde as palavras e frequências serão lidas.
         * @param time Cabeçalho contendo tempo de inserção ou outras informações.
         * @param output O nome do arquivo que será criado com a saída formatada.
         */
        template <typename Map>
        void write(const Map& map, std::string& time, const std::string& output);
};
#include "../src/DictIO.tpp"
#endif