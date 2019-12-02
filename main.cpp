//
// Created by tanus on 2019-11-24.
//
#include "population.hpp"
#include "geneticAlgo.hpp"

/*Main Driver class */
int main() {
    //creating geneticAlgo object
    geneticAlgo geneAlgo{};

    //creating population object
    population p;

    //running optimization
    geneAlgo.optimization(p);
    return 0;
}