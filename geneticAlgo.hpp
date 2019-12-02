//
// Created by tanus on 2019-11-24.
//

#ifndef ASSIGNMENT2_GENETICALGO_HPP
#define ASSIGNMENT2_GENETICALGO_HPP

#include "population.hpp"
#include <algorithm>
#include <iomanip>
#include <chrono>

/* geneticAlgo class*/
class geneticAlgo {
private:
    /* constants*/
    constexpr static int PARENT_POOL_SIZE = 5;
    constexpr static int NUMBER_OF_ELITES = 1;
    constexpr static int ITERATIONS = 1000;
    constexpr static double IMPROVEMENT = 0.54;
    constexpr static double MUTATION_RATE = 0.15;
    constexpr static int CITIES_IN_TOUR = 32;
    constexpr static int NUMBER_OF_PARENTS = 2;

public:
    /* default constructor*/
    geneticAlgo() = default;

    /* Select the fittest tour and place it to front of tour list*/
    void selection(population &) const;

    /* Creates a child tour by filling it with random cities from parent1 and
     * rest cities from parent2 */
    tour crossover(tour, tour);

    /*Takes a tour and do mutation by randomly selecting 2 cities and
     * swaps their position*/
    void mutation(tour &tour);

    /* Creates a subgroup of tour from population and returns the fittest*/
    vector<tour> selectParents(population &);

    /* Assigns each new tour a fitness level by moving fittest to front,
     * than adding child tours to rest and then do mutation */
    void evolution(population &);

    /* Optimization implements genetic algorithm iteratively
     * until we observe best_distance / base_distance < improvement_factor
     * i.e it stops after it passes that number
     * when improvement factor is less than a specific number  */
    void optimization(population &);
};


#endif //ASSIGNMENT2_GENETICALGO_HPP
