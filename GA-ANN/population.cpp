#include "population.h"
#include "individual.h"

#include <algorithm>
using std::sort;


Population::Population(int populationSize)
{
    this->populationSize = populationSize;
    for(int i = 0; i < populationSize; i++)
        individuals.push_back(Individual());
}

int Population::getPopulationCount()
{
    return populationSize;
}

inline bool Population::compFitness(Individual indiv1, Individual indiv2)
{
    return indiv1.fitness > indiv2.fitness;
}

void Population::sortByFitness()
{
    sort(individuals.begin(), individuals.end(), compFitness);
}

Individual& Population::getFittest()
{
    return individuals.front();
}

Individual& Population::getIndividual(int pos)
{
    return individuals.at(pos);
}
