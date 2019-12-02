//
// Created by tanus on 2019-11-24.
//

#include "tour.hpp"

/*default tour constructor, initializes fitness & distance to 0, than fills it and
    * calls determine fitness and tour distance */
tour::tour(bool children) : fitness{0}, distance{0} {
    //adding new cities into vector container by loop through it
    if (!children) {
        for (int i = 0; i < CITIES_IN_TOUR; i++) {
            cities.emplace_back();
        }
        //calling  determine_fitness function
        determine_fitness();

        //calling  get_tour_distance function
        get_tour_distance();
    }
}

/*Getter, gets the city at given index in a tour*/
city &tour::getCity(int indexPosition) {
    return cities.at(indexPosition);
}

/*shuffle_cities to shuffle the cities in a tour*/
void tour::shuffle_cities() {
    for (int i = 0; i < SHUFFLES; i++) {
        swap_cities();
    }
}

/*swap_cities to two cities in a tour*/
void tour::swap_cities() {
    auto tourLocation1 = 0 + rand() % (((CITIES_IN_TOUR - 1) + 1) - 0);
    auto tourLocation2 = 0 + rand() % (((CITIES_IN_TOUR - 1) + 1) - 0);
    //swapping cities at tourLocation1 with tourLocation2
    swap(cities.at((unsigned long) tourLocation1), cities.at((unsigned long) tourLocation2));
}

/*get_tour_distance reports distance b/w cities in a tour*/
int tour::get_tour_distance() {
    if (distance == 0) {
        int total_tour_Distance = 0;
        for (unsigned long index = 0; index < cities.size(); index++) {
            city startCity = getCity((int) index);
            city destinationCity;
            // Check if we're not on our tour's last destination city
            if (index + 1 < cities.size()) {
                destinationCity = getCity((int) index + 1);
            }
                //If we are at destination city, set it to startCity's index = 0
            else {
                destinationCity = getCity(0);
            }
            // Get the distance b/w two cities
            total_tour_Distance += (int) startCity.get_Distance_Between_Cities(destinationCity);
        }
        distance = total_tour_Distance;
    }
    return distance;
}

/*determine_fitness determines fitness of a tour*/
double tour::determine_fitness() {
    if (fitness == 0) {
        fitness = (1 / (double) get_tour_distance()) * 1000000;
    }
    return fitness;
}

/*Getter for tour vector*/
vector<city> &tour::getTour() {
    return this->cities;
}

/*contains_city checks if a tour contains specified city*/
bool tour::contains_city(city city1) {
    auto iter = find(cities.begin(), cities.end(), city1);
    //returns true if it contains city otherwise false
    return iter != cities.end();
}

/*Overloaded insertion operator*/
ostream &operator<<(ostream &out, tour &tour) {
    for (city &c: tour.getTour()) {
        out << c;
    }
    return out;
}

/*Overloaded equals operator*/
bool tour::operator==(tour &tour) {
    return (fitness == tour.fitness);
}

/*Overloaded comparison operator*/
bool tour::operator<(const tour &tour) const {
    return fitness > tour.fitness;
}