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
        void read(Map& map, const std::string input){
            //std::cerr << "Tentando abrir arquivo: " << input << std::endl;
            std::fstream in(input);

            if(!in.is_open()){
                std::cerr << "Nao foi possivel abrir o arquivo" << std::endl;
                return;
            }

            std::string line;
            UErrorCode status = U_ZERO_ERROR;
            const icu::Normalizer2* norm2 = icu::Normalizer2::getNFCInstance(status);
            if(U_FAILURE(status)){
                std::cerr << "Erro ao obter Normalizer2 NFC: " << u_errorName(status) << std::endl;
                return;
            }

            while(std::getline(in, line)){
                icu::UnicodeString uline = icu::UnicodeString::fromUTF8(line);
                uline = norm2->normalize(uline, status);
                uline.toLower();

                icu::UnicodeString word;
                for(int32_t i = 0; i < uline.length(); ){
                    UChar32 ch = uline.char32At(i);
                    i += U16_LENGTH(ch);

                    if(u_isalnum(ch) || (!word.isEmpty() && ch == 0x002D)){ 
                        word.append(ch);
                    }else{
                        if(!word.isEmpty()){
                            ++map[uniStringKey(word)];
                            word.remove();
                        }
                    }
                }

                if(!word.isEmpty()){
                    ++map[uniStringKey(word)];
                }
            }

            in.close();
        }

        /**
         * @brief Função genérica que escreve um novo arquivo a partir de um
         * dicinário.
         * 
         * Abre um arquivo e vê se deu certo a abertura.
         * Inicializa o arquivo com o cabeçalho de construção do dicionário.
         * Chama a função de dicionário que o transforma em um vetor e o ordena
         * caso seja uma tabela hash.
         * 
         * Percorre o vetor de pares convertendo as chaves de unicodeString para 
         * string e escrevendo estas com seus respectivos valores de frequência.
         * Finaliza fechando o arquivo e dizendo onde ele se encontra.
         * 
         * @param map O dicionário que será lido para criação do arquivo.
         * @param start String que contém o cabeçalho com as informações de 
         * construção do dicionário (métricas e tempo de inserção).
         * @param output O nome do arquivo que será criado.
         */
        template <typename Map>
        void write(const Map& map, std::string& start, const std::string& output){
            std::ofstream out(output);
            if(!out.is_open()){
                std::cerr << "Nao foi possivel criar/abrir o arquivo";
            }

            std::vector<std::pair<uniStringKey, int>> tuple = map.toVector();
            std::sort(tuple.begin(), tuple.end(), uniStringPairLess());

            out << start << std::endl;

            const int word_width = 43;
            const int freq_width = 22;
            const int total = word_width + freq_width + 3;

            out << std::string(total, '=') << std::endl;

            out << std::setw(word_width) << std::left << "PALAVRA"
            << std::setw(freq_width) << std::right << "FREQUENCIA"
            << std::endl;

            out << std::string(total, '-') << std::endl;

            for(const auto& p : tuple){
                out << "|" << std::setw(word_width) << std::left << p.first;
                out << "|" << std::setw(freq_width) << std::right << p.second << "|";
                out << std::endl;
            }
            out << std::string(total, '-') << std::endl;
            out << std::string(total, '=') << std::endl;
            out.close();
            std::cout << "Conteudo do dicionario gravado em '" << output << "'" << std::endl;
        }
};

#endif