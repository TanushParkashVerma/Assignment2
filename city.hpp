//
// Created by tanus on 2019-11-24.
//

#ifndef ASSIGNMENT2_CITY_HPP
#define ASSIGNMENT2_CITY_HPP

#include <iostream>
#include <utility>
#include <random>

using namespace std;

/*door class*/
class city {
private:
    /*constants*/
    constexpr static auto MIN = 0;
    constexpr static auto MAP_BOUNDARY = 1000;

    /*variables*/
    string city_name;
    int x;
    int y;

public:
    /*default city constructor*/
    city();

    /*genRandomCityName function generates random city names*/
    string genRandomCityName();

    /*get_Distance_Between_Cities function calculates distance b/w two cities*/
    double get_Distance_Between_Cities(const city &);

    /*getter function for x*/
    int getX() const;

    /*getter function for y*/
    int getY() const;

    /*overloaded equals operator*/
    bool operator==(const city &) const;

    /*overloaded insertion operator*/
    friend ostream &operator<<(ostream &, const city &);
};


#endif //ASSIGNMENT2_CITY_HPP
