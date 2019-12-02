//
// Created by tanus on 2019-11-24.
//

#ifndef ASSIGNMENT2_POPULATION_HPP
#define ASSIGNMENT2_POPULATION_HPP

#include "tour.hpp"

/*population class*/
class population {
private:
    /*constant*/
    constexpr static int POPULATION_SIZE = 32;

    /*variable base_distance*/
    int base_distance;

    /*vector of type tour*/
    vector<tour> tours;

public:
    /*Default constructor that fills tours vector with the shuffled ones*/
    population();

    /*getter for get population size*/
    static int getSize();

    /*getter for vector of tour*/
    vector<tour> &getTours();

    /*setter for vector of tour*/
    void setTours(const vector<tour> &tours);

    /*getter for tour at specific index*/
    tour &getTour(int);

    /*getter to get the tour with the best fitness rating*/
    tour getFittestTour();

    /*getter for base distance*/
    int get_base_distance();
};

#endif //ASSIGNMENT2_POPULATION_HPP
