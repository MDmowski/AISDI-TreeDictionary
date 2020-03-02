#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <memory>
#include <iterator>
#include <utility>
#include <fstream>

#include "loadFile.hpp"
#include "TreeMap.cpp"
#include "Benchmark.cpp"
#include "tests.h"

int main()
{
    srand(time(NULL));
    unit_test();
    std::unique_ptr< std::vector<std::string> > wordList = loadFromFile("pan-tadeusz.txt");
    std::ofstream output;
    output.open("times.csv");
    output<<"Name,numberOfElements,insertionTime,searchTime\n";
    std::cout << "std::map:\n";
    for (int k = wordList->size() - 1; k >= 0; k -= 5000)
    {
        std::map<std::string, std::string> mp;
        std::map<std::string, std::string>::iterator it;
        it = mp.begin();
        unsigned int i;
        for (i = 0; i < wordList->size() - k - 1; ++i)
        {
            mp.insert(it, std::pair<std::string, std::string>(wordList->at(i), wordList->at(i)));
        }
        output <<"std::map, "<< i+1 << ", ";

        Benchmark<> mapInserstion;
        mp.insert(it, std::pair<std::string, std::string>(wordList->at(i), wordList->at(i)));
        auto time = mapInserstion.elapsed();

        std::cout << "\tTime of insertion with size=" << i+1 << " was: " << time << std::endl;
        output << time << ", ";

        Benchmark<> mapFind;
        std::string word = wordList->at(rand()%(i + 1));
        mp.find(word);
        time = mapFind.elapsed();

        std::cout << "\tTime of finding an element with size="  << i+1 << " was: " << time << std::endl;
        output << time <<"\n";
    }
    std::cout << "\nTreeMap:\n";
    for (int k = wordList->size() - 1; k >= 0; k -= 5000)
    {
        TreeMap<std::string,std::string> splayTree;
        unsigned int i;
        for (i = 0; i < wordList->size() - k - 1; ++i)
        {
            splayTree.insert(wordList->at(i),wordList->at(i));
        }

        output <<"TreeMap, "<< i+1 << ", ";

        Benchmark<> treeInserstion;
        splayTree.insert(wordList->at(i),wordList->at(i));
        auto time = treeInserstion.elapsed();

        std::cout << "\tTime of insertion with size=" << i+1 << " was: " << time << std::endl;
        output << time << ", ";

        Benchmark<> treeFind;
        std::string word = wordList->at(rand() % (i + 1));
        splayTree[word];
        time = treeFind.elapsed();

        std::cout << "\tTime of finding an element with size=" << i+1 << " was: " << time << std::endl;
        output << time << "\n";
    }

    TreeMap<std::string,std::string> splayTree;

    std::map<std::string, std::string> mp;
    std::map<std::string, std::string>::iterator it;
    it = mp.begin();

    for(auto &word : *wordList)
    {
        splayTree.insert(word, word);
        mp.insert(it, std::pair<std::string, std::string>(word, word));
    }

    // Pick random offset between 1 and wordList.size() - 50
    int offset = rand() % (wordList->size() - 50);

    Benchmark<> treeFind;
    for(int i = 0; i < 1000; i++)
    {
        int wordIndex = offset + (rand() % 50);
        splayTree[wordList->at(wordIndex)];
    }
    auto time = treeFind.elapsed();
    std::cout << "TreeMap:\n\tFinding words 1000 times between " << offset << " and " << offset + 50 << " took: " << time << std::endl;

    Benchmark<> mapFind;
    for(int i = 0; i < 1000; i++)
    {
        int wordIndex = offset + (rand() % 50);
        mp.find(wordList->at(wordIndex));
    }
    time = mapFind.elapsed();
    std::cout << "std::map:\n\tFinding words 1000 times between " << offset << " and " << offset + 50 << " took: " << time << std::endl;

}
