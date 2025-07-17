#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <chrono>
#include <iomanip>
#include <vector>

#include "../includes/dicionarios/MAP_AVL.hpp"
#include "../includes/dicionarios/MAP_CHT.hpp"
#include "../includes/dicionarios/MAP_OHT.hpp"
#include "../includes/dicionarios/MAP_RBT.hpp"
#include "../includes/UnicodeComparator.hpp"
#include "../includes/DictIO.hpp"

#define INPUT_FILE "texts/"
#define TIMES 5

struct Results{
    double insertTime;
    double searchFoundTime;
    double searchNotFoundTime;
    double removeTime;
    int totalWords;
    int totalElements;
};

int countWords(std::vector<std::pair<uniStringKey, int>> v){
    int count = 0;
    for(const auto &p : v){
        count += p.second;
    }
    return count;
}

template <typename Map>
void saveResults(const std::string& output, const std::string& mapName, const std::string& fileName, const Results& m, const Map& map){
    std::ofstream out(output);

    if(!out.is_open()){
    std::cerr << "Nao foi possivel criar/abrir o arquivo";
    }

    const int total = 81;

    out << std::string(total, '=') << std::endl;
    out << std::string(26, '-');
    out << " INFORMAÇÕES DO ARQUIVO LIDO "; 
    out << std::string(26, '-') << std::endl;
    out << "Arquivo analisado: " << fileName << "\n";
    out << "Total de palavras no arquivo: " << m.totalWords << "\n";
    out << "Total de palavras no dicionário: " << m.totalElements << "\n";

    std::string estatistica = " ESTATÍSTICAS DA " + mapName + " ";
    int tracos = (total - estatistica.length()+1)/2;
    out << std::string(tracos, '-');
    out << estatistica;
    out << std::string(tracos, '-') << std::endl;
    
    out << map.metric() << "\n";
    out << std::fixed << std::setprecision(8);
    out << "Tempo médio de inserção: " << m.insertTime << "s\n";
    out << "Tempo médio de busca (existe): " << m.searchFoundTime << "s\n";
    out << "Tempo médio de busca (inexistente): " << m.searchNotFoundTime << "s\n";
    out << "Tempo médio de remoção: " << m.removeTime << "s\n";

    out << std::string(total, '=') << std::endl;

}

template<typename Map>
Results tests(std::string filename, uniStringKey& foundKey, uniStringKey& notFoundKey, int runs, Map& map){
    Results result;
    DictIO d_io;

    for(int i = 0; i < runs; i++){
        //teste de inserção
        Map map_test;
        auto startInsert = std::chrono::high_resolution_clock::now();
        d_io.read(map_test, filename);
        auto endInsert = std::chrono::high_resolution_clock::now();
        result.insertTime += std::chrono::duration<double>(endInsert - startInsert).count();

        //teste de busca de uma palavra existente
        auto startContains = std::chrono::high_resolution_clock::now();
        map_test.contains(foundKey);
        auto endContains = std::chrono::high_resolution_clock::now();
        result.searchFoundTime += std::chrono::duration<double>(endContains - startContains).count();

        //teste de busca de uma palavra não existente
        auto startNotContains = std::chrono::high_resolution_clock::now();
        map_test.contains(notFoundKey);
        auto endNotContains = std::chrono::high_resolution_clock::now();
        result.searchNotFoundTime += std::chrono::duration<double>(endNotContains - startNotContains).count();

        //teste de remoção de uma palavra
        auto startErase = std::chrono::high_resolution_clock::now();
        map_test.erase(foundKey);
        auto endErase = std::chrono::high_resolution_clock::now();
        result.removeTime += std::chrono::duration<double>(endErase - startErase).count();

        if(i == runs - 1){
            map = map_test;
        }
    }

    //média
    result.insertTime /= runs;
    result.searchFoundTime /= runs;
    result.searchNotFoundTime /= runs;
    result.removeTime /= runs;

    //Informações gerais
    Map temp_map;
    d_io.read(temp_map, filename);
    result.totalWords = countWords(temp_map.toVector());
    result.totalElements = temp_map.size();
    
    return result;
}

int main(){
    std::string input =  "kjv-bible.txt";
    std::string foundKey = "god", notFoundKey = "aisjda";
    uniStringKey found(foundKey), notFound(notFoundKey);
    std::string metricsOutput = "tests_dictionary/";

    MAP_AVL<uniStringKey, int, uniStringLess, uniStringEquals> avl_test;
    auto avl_result = tests(INPUT_FILE + input, found, notFound, TIMES, avl_test);
    saveResults(metricsOutput + "TestAVL.txt", "AVL", input, avl_result, avl_test);
    
    MAP_RBT<uniStringKey, int, uniStringLess, uniStringEquals> rbt_test;
    auto rbt_result = tests(INPUT_FILE + input, found, notFound, TIMES, rbt_test);
    saveResults(metricsOutput + "TestRBT.txt", "RBT", input, rbt_result, rbt_test);

    MAP_CHT<uniStringKey, int, uniStringHasher, uniStringLess, uniStringEquals> cht_test;
    auto cht_result = tests(INPUT_FILE + input, found, notFound, TIMES, cht_test);
    saveResults(metricsOutput + "TestCHT.txt", "CHT", input, cht_result, cht_test);

    MAP_OHT<uniStringKey, int, uniStringHasher, uniStringLess, uniStringEquals> oht_test;
    auto oht_result = tests(INPUT_FILE + input, found, notFound, TIMES, oht_test);
    saveResults(metricsOutput + "TestOHT.txt", "OHT", input, oht_result, oht_test);

}