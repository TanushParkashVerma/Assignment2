//
// Created by tanus on 2019-11-24.
//

#ifndef ASSIGNMENT2_TOUR_HPP
#define ASSIGNMENT2_TOUR_HPP

#include <vector>
#include <algorithm>
#include <cmath>
#include "city.hpp"

/*tour class*/
class tour {
private:
    /*constants*/
    constexpr static int CITIES_IN_TOUR = 32;
    constexpr static int SHUFFLES = 64;

    /*vector of type city*/
    vector<city> cities;

    /*variables*/
    int distance;
    double fitness;

public:
    /*default tour constructor, initializes fitness & distance to 0, than fills it and
     * calls determine fitness and tour distance */
    explicit tour(bool);

    /*Getter, gets the city at given index in a tour*/
    city &getCity(int);

    /*shuffle_cities to shuffle the cities in a tour*/
    void shuffle_cities();

    /*swap_cities to two cities in a tour*/
    void swap_cities();

    /*get_tour_distance reports distance b/w cities in a tour*/
    int get_tour_distance();

    /*determine_fitness determines fitness of a tour*/
    double determine_fitness();

    /*contains_city checks if a tour contains specified city*/
    bool contains_city(city);

    /*Getter for tour vector*/
    vector<city> &getTour();

    /*Overloaded insertion operator*/
    friend ostream &operator<<(ostream &, tour &);

    /*Overloaded equals operator*/
    bool operator==(tour &);

    /*Overloaded comparison operator*/
    bool operator<(const tour &) const;

    /*tour destructor*/
    ~tour() = default;
};

#endif //ASSIGNMENT2_TOUR_HPP
