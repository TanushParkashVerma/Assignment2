//
// Created by tanus on 2019-11-24.
//

#include "geneticAlgo.hpp"

/* Select the fittest tour and place it to front of tour list*/
void geneticAlgo::selection(population &population) const {
    tour fittest = population.getFittestTour();
    for (auto iter = population.getTours().begin(); iter != population.getTours().end(); iter++) {
        if (*iter == fittest) {
            //rotates the order of elements in range [first,last], in such a way
            // that the element pointed by middle becomes the new first element.
            std::rotate(population.getTours().begin(), iter, population.getTours().end());
            break;
        }
    }
}

/* Creates a child tour by filling it with random cities from parent1 and
   * rest cities from parent2 */
tour geneticAlgo::crossover(tour tour1, tour tour2) {
    tour childTour(true);
    //parent1 vector of type city, putting tour1 in it.
    vector<city> parent1 = tour1.getTour();
    //parent1 vector of type city, putting tour2 in it.
    vector<city> parent2 = tour2.getTour();
    // Get random number
    auto endIndex = 0 + rand() % ((((int) parent1.size() - 1) + 1) - 0);
    // Loop through it and add the tour from parent1 to child
    for (int i = 0; i <= endIndex; i++) {
        childTour.getTour().push_back(tour1.getCity(i));
    }
    // loop through parent2's tour, than add city if it doesn't already exist
    int counter = 0;
    while (childTour.getTour().size() < 32) {
        if (!childTour.contains_city(tour2.getCity(counter))) {
            childTour.getTour().push_back(tour2.getCity(counter));
        }
        counter++;
    }
    return childTour;
}

/*Takes a tour and do mutation by randomly selecting 2 cities and
    * swaps their position*/
void geneticAlgo::mutation(tour &tour) {
    for (unsigned long int tourIndex1 = 0; tourIndex1 < tour.getTour().size(); tourIndex1++) {
        //random double number generator
        auto rand_doubleNumber = (1 - 0) * ((double) rand() / (double) RAND_MAX) + 0;
        //checks if random number is less than Mutation rate, then
        // swapping will be done
        if (rand_doubleNumber < MUTATION_RATE) {
            auto tourIndex2 = 0 + rand() % (((CITIES_IN_TOUR - 1) + 1) - 0);
            // Swapping tour with index1 with index2
            swap(tour.getTour().at(tourIndex1), tour.getTour().at((unsigned long) tourIndex2));
        }
    }
}

/* Creates a subgroup of tour from population and returns the fittest*/
vector<tour> geneticAlgo::selectParents(population &population) {
    //calling selection function to get the fittest one.
    selection(population);
    //creates vector population copy of type tour
    vector<tour> populationCopy = population.getTours();
    //erase and shrink to fit
    populationCopy.erase(populationCopy.begin());
    populationCopy.shrink_to_fit();
    vector<tour> parents;
    //loop through vector
    for (int i = 0; i < NUMBER_OF_PARENTS; i++) {
        vector<tour> pool;
        for (int j = 0; j < PARENT_POOL_SIZE; j++) {
            // seed represent current point in atime
            long seed = chrono::system_clock::now().time_since_epoch().count();
            //shuffle populationcCopy
            shuffle(populationCopy.begin(), populationCopy.end(), default_random_engine(seed));
            //generates random number
            auto randomNumber = 0 + rand() % ((((int) population.getTours().size() - 1) + 1) - 0);
            //push back the pool vector of type tour
            pool.push_back(population.getTour(randomNumber));
            //again erase and shrink to fit
            populationCopy.erase(populationCopy.begin());
            populationCopy.shrink_to_fit();
        }
        //sorting done
        sort(pool.begin(), pool.end());
        parents.push_back(pool.at(0));
        pool.clear();
    }
    return parents;
}

/* Assigns each new tour a fitness level by moving fittest to front,
   * than adding child tours to rest and then do mutation */
void geneticAlgo::evolution(population &population) {
    // made population object
    class population newPopulation;
    tour fittestTour = population.getFittestTour();
    //creates vector newPopulationTours of type tour
    vector<tour> newPopulationTours;
    //push back the newPopulationTours vector of type tour with fittest tour
    newPopulationTours.push_back(fittestTour);
    //creates vector parents of type tour
    vector<tour> parents = selectParents(population);
    //loop through the population starting with i=NUMBER_OF_ELITES
    // and do crossover
    for (int i = NUMBER_OF_ELITES; i < population::getSize(); i++) {
        tour child = crossover(parents.at(0), parents.at(1));
        newPopulationTours.push_back(child);
    }
    //loop through the population starting with k=NUMBER_OF_ELITES
    // and do mutation
    for (int k = NUMBER_OF_ELITES; k < population::getSize(); k++) {
        mutation(newPopulationTours.at((unsigned long) k));
    }
    //set newPopulationTours into newPopulation
    newPopulation.setTours(newPopulationTours);
    //and then newPopulation into Population
    population = newPopulation;
}

/* Optimization implements genetic algorithm iteratively
    * until we observe best_distance / base_distance < improvement_factor
    * i.e it stops after it passes that number
    * when improvement factor is less than a specific number  */
void geneticAlgo::optimization(population &population) {
    //Printing Report message before evolutions
    cout << "Population's starting Report : \nFitness Report: " <<
         population.getFittestTour().determine_fitness() << "\nFittest tour's total distance: " <<
         population.getFittestTour().get_tour_distance() << endl;
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    cout << "Report in progress...... Please wait a moment......" << endl;
    //get base distance and putting into variable base_distance
    int base_distance = population.get_base_distance();
    int iterations = 0;
    double improvement_factor{0.0};
    /* Checks if improvement_factor greater than IMPROVEMENT or iterations is less than ITERATIONS
     * and than call the evolution function followed by printing report with corrosponding Improvement Factor */
    while (improvement_factor > IMPROVEMENT || iterations < ITERATIONS) {
        evolution(population);
        improvement_factor = (double) population.getFittestTour().get_tour_distance() / (double) base_distance;
        if (iterations != 0 && iterations % 100 == 0) {
            cout << "Fitness Report after " << iterations << " Evolutions: " <<
                 population.getFittestTour().determine_fitness() << "\nImprovement Factor: " <<
                 setprecision(5) << improvement_factor << "\n" << endl;
        }
        iterations++;
    }
    //Printing Report message after evolutions
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    cout << "Population's Report after " << iterations << " Evolutions: " << "\nFitness Report: "
         << population.getFittestTour().determine_fitness() <<
         "\nFittest tour's total distance: " <<
         population.getFittestTour().get_tour_distance() << endl;
}