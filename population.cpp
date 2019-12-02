//
// Created by tanus on 2019-11-24.
//

#include "population.hpp"

/*Default constructor that fills tours vector with the shuffled ones*/
population::population() {
    //loop through it while shuffling and inserting new element at the end
    for (int i = 0; i < POPULATION_SIZE; i++) {
        tour newTour(false);
        newTour.shuffle_cities();
        tours.push_back(newTour);
    }
    base_distance = getFittestTour().get_tour_distance();
}

/*getter for get population size*/
int population::getSize() {
    return POPULATION_SIZE;
}

/*getter for vector of tour*/
vector<tour> &population::getTours() {
    return tours;
}

/*setter for vector of tour*/
void population::setTours(const vector<tour> &tours) {
    population::tours = tours;
}

/*getter for tour at specific index*/
tour &population::getTour(int index) {
    return tours.at(index);
}

/*getter to get the tour with the best fitness rating*/
tour population::getFittestTour() {
    auto fittest = tours.at(0);
    for (auto iter = tours.begin() + 1; iter < tours.end(); iter++) {
        if (fittest.determine_fitness() <= iter->determine_fitness()) {
            fittest = *iter;
        }
    }
    return fittest;
}

/*getter for base distance*/
int population::get_base_distance() {
    return base_distance;
}