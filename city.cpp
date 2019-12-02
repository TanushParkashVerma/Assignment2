//
// Created by tanus on 2019-11-24.
//

#include "city.hpp"

/*default city constructor*/
city::city() {
    x = MIN + rand() % ((MAP_BOUNDARY + 1) - MIN);
    y = MIN + rand() % ((MAP_BOUNDARY + 1) - MIN);
    city_name = genRandomCityName();
}

/*genRandomCityName function generates random city names*/
string city::genRandomCityName() {
    string randomCityName;
    static const char array[] = "0123456789" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < 8; i++) {
        randomCityName += array[rand() % (sizeof(array) - 1)];
    }
    return randomCityName;
}

/*get_Distance_Between_Cities function calculates distance b/w two cities*/
double city::get_Distance_Between_Cities(const city &city1) {
    int distanceX = abs(getX() - city1.getX());
    int distanceY = abs(getY() - city1.getY());
    //calculates distance
    return sqrt(pow(distanceX, 2) + pow(distanceY, 2));
}

/*getter function for x*/
int city::getX() const {
    return this->x;
}

/*getter function for y*/
int city::getY() const {
    return this->y;
}

/*overloaded equals operator*/
bool city::operator==(const city &city) const {
    return (city_name == city.city_name) && (x == city.x) && (y == city.y);
}

/*overloaded insertion operator*/
ostream &operator<<(ostream &out, const city &city) {
    return out << city.city_name << ", <" << city.x << ", " << city.y << ">" << endl;
}