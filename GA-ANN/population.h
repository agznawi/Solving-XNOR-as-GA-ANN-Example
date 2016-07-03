#ifndef POPULATION_H
#define POPULATION_H

#include "individual.h"
#include "population.h"

#include <vector>
using std::vector;

class Population
{
private:
    int populationSize;
    static inline bool compFitness(Individual indiv1, Individual indiv2);

public:
    Population(int populationSize);
    int getPopulationCount();

    void sortByFitness();
    Individual& getFittest();

    vector<Individual> individuals;
    Individual &getIndividual(int pos);
};

#endif // POPULATION_H
