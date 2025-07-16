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

#define INPUT_FILE "texts/"
#define TIMES 100

double map_avl_test(int n, std::string filename){
    double avg = 0;
    DictIO d_io;

    for(int i = 0; i < n; i++){
        MAP_AVL<uniStringKey, int, uniStringLess, uniStringEquals> avl;
        auto start = std::chrono::high_resolution_clock::now();
        d_io.read(avl, filename);
        auto end = std::chrono::high_resolution_clock::now();
        avg += std::chrono::duration<double>(end - start).count();
    }

    return avg / n;
}

double map_rbt_test(int n, std::string filename){
    double avg = 0;
    DictIO d_io;

    for(int i = 0; i < n; i++){
        MAP_RBT<uniStringKey, int, uniStringLess, uniStringEquals> rbt;
        auto start = std::chrono::high_resolution_clock::now();
        d_io.read(rbt, filename);
        auto end = std::chrono::high_resolution_clock::now();
        avg += std::chrono::duration<double>(end - start).count();
    }

    return avg / n;
}

double map_cht_test(int n, std::string filename){
    double avg = 0;
    DictIO d_io;

    for(int i = 0; i < n; i++){
        MAP_CHT<uniStringKey, int, uniStringHasher, uniStringLess, uniStringEquals> cht;
        auto start = std::chrono::high_resolution_clock::now();
        d_io.read(cht, filename);
        auto end = std::chrono::high_resolution_clock::now();
        avg += std::chrono::duration<double>(end - start).count();
    }

    return avg / n;
}

double map_oht_test(int n, std::string filename){
    double avg = 0;
    DictIO d_io;

    for(int i = 0; i < n; i++){
        MAP_OHT<uniStringKey, int, uniStringHasher, uniStringLess, uniStringEquals> oht;
        auto start = std::chrono::high_resolution_clock::now();
        d_io.read(oht, filename);
        auto end = std::chrono::high_resolution_clock::now();
        avg += std::chrono::duration<double>(end - start).count();
    }

    return avg / n;
}

int main(){
    std::string input =  "kjv-bible.txt";
    std::cout << map_avl_test(TIMES, INPUT_FILE + input) << " tempo medio para leitura da biblia na avl" << std::endl;
    std::cout << map_rbt_test(TIMES, INPUT_FILE + input) << " tempo medio para leitura da biblia na rbt" << std::endl;
    std::cout << map_cht_test(TIMES, INPUT_FILE + input) << " tempo medio para leitura da biblia na cht" << std::endl;
    std::cout << map_oht_test(TIMES, INPUT_FILE + input) << " tempo medio para leitura da biblia na oht" << std::endl;
}