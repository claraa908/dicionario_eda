#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <chrono>
#include "includes/dicionarios/MAP_AVL.hpp"
#include "includes/dicionarios/MAP_CHT.hpp"
#include "includes/dicionarios/MAP_OHT.hpp"
#include "includes/dicionarios/MAP_RBT.hpp"
#include "includes/UnicodeComparator.hpp"
#include "includes/DictIO.hpp"

#define OUTPUT_FILE "tables_texts/"
#define INPUT_FILE "texts/"

/**
 * A main recebe dois parâmetros, o argc conta quantas palavras foram passadas no terminal
 * e o argv guarda palavra por palavra separada por espaço em um vetor.
 * 
 * Essa main foi desenvolvida para receber 4 palavras:
 * 1- nome do executavel;
 * 2- nome do comando, para escolher qual dicionario vai receber o arquivo;
 * 3- nome do arquivo de leitura, que servirá para inserção das palavras no dicionário;
 * 4- nome do arquivo que escreverá a tabela de frequencia.
 * 
 * Possui uma verificação para saber se os 4 parametros foram passados.
 * inicia o temporizador após a criação das variáveis que serão usadas, insere no dicionário
 * e finaliza o temporizador.
 * 
 * Por fim, prepara um cabeçalho para impressão na main e passa o tempo de execução
 * para o arquivo de saída colocar no cabeçalho do arquivo .txt também.
 * 
 */

int main(int argc, char* argv[]){
    if(argc != 4){
        std::cerr << "Comando errado" << std::endl;
        return 1;
    }

    DictIO arq;
    std::string metric;
    std::string option = argv[1];
    std::string arq_in = argv[2];
    std::string arq_out = argv[3];
    auto start = std::chrono::high_resolution_clock::now(); 

    if(argc == 4){
        if(option == "map_avl")
        {
            MAP_AVL<uniStringKey, int, uniStringLess, uniStringEquals> map_avl;
            arq.read(map_avl,  INPUT_FILE + arq_in);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> second = end - start;
            double time = second.count();
            
            std::string output;
            std::string outputFile;
            output += "=========================== ESTATISTICAS ===========================\n";
            output += map_avl.metric() + "\n";
            output += "Tempo de execucao: ";
            output += std::to_string(time) + "\n";
            output += "====================================================================\n";
            std::cout << output;

            outputFile += "Tempo de execucao: ";
            outputFile += std::to_string(time) + "\n";

            arq.write(map_avl, outputFile, OUTPUT_FILE + arq_out);
        }


        else if(option == "map_rbt")
        {
            MAP_RBT<uniStringKey, int, uniStringLess, uniStringEquals> map_rbt;
            arq.read(map_rbt, INPUT_FILE + arq_in);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> second = end - start;
            double time = second.count();

            std::string output;
            std::string outputFile;
            output += "=========================== ESTATISTICAS ===========================\n";
            output += map_rbt.metric() + "\n";
            output += "Tempo de execucao: ";
            output += std::to_string(time) + "\n";
            output += "====================================================================\n";
            std::cout << output;
            
            outputFile += "Tempo de execucao: ";
            outputFile += std::to_string(time) + "\n";

            arq.write(map_rbt, outputFile, OUTPUT_FILE + arq_out);
        }


        else if(option == "map_cht")
        {
            MAP_CHT<uniStringKey, int, uniStringHasher,uniStringLess, uniStringEquals> map_cht;
            arq.read(map_cht, INPUT_FILE + arq_in);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> second = end - start;
            double time = second.count();

            std::string output;
            std::string outputFile;
            output += "=========================== ESTATISTICAS ===========================\n";
            output += map_cht.metric() + "\n";
            output += "Tempo de execucao: ";
            output += std::to_string(time) + "\n";
            output += "====================================================================\n";
            std::cout << output;
            
            outputFile += "Tempo de execucao: ";
            outputFile += std::to_string(time) + "\n";

            arq.write(map_cht, outputFile, OUTPUT_FILE + arq_out);
        }


        else if(option == "map_oht")
        {
            MAP_OHT<uniStringKey, int, uniStringHasher,uniStringLess, uniStringEquals> map_oht;
            arq.read(map_oht, INPUT_FILE + arq_in);

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> second = end - start;
            double time = second.count();

            std::string output;
            std::string outputFile;
            output += "=========================== ESTATISTICAS ===========================\n";
            output += map_oht.metric() + "\n";
            output += "Tempo de execucao: ";
            output += std::to_string(time) + "\n";
            output += "====================================================================\n";
            std::cout << output;
            
            outputFile += "Tempo de execucao: ";
            outputFile += std::to_string(time) + "\n";

            arq.write(map_oht, outputFile, OUTPUT_FILE + arq_out);
        }

        else{
            std::cerr << "Estrutura escolhida nao existe" << std::endl;
        }
    }
    return 0;
}