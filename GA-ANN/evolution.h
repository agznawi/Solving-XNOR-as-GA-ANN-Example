#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "globals.h"
#include "individual.h"
#include "population.h"

#include <string>
using std::string;

class Evolution
{
public:
    static Individual crossover(Individual indiv1, Individual indiv2);
    static void mutate(Individual &indiv);
    static void calculateFitness(Population &pop);
};

#endif // EVOLUTION_H
