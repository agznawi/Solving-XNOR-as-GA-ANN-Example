#include "evolution.h"
#include "globals.h"

#include <iostream>
using std::cout;
using std::endl;


Individual Evolution::crossover(Individual indiv1, Individual indiv2)
{
    int newGenome[9];
    // Half uniform crossover
    uniform_int_distribution<int> rSwap(1, 2);
    for(int i = 0; i < 9; i++)
        newGenome[i] = ((rSwap(e1) == 1)? indiv1.genome[i] : indiv2.genome[i]);

    return newGenome;
}

void Evolution::mutate(Individual &indiv)
{
    uniform_int_distribution<int> rGene(0, 8);
    int gene = rGene(e1);
    uniform_int_distribution<int> randV(-100, 100);
    int value = randV(e1);
    indiv.genome[gene] = value;
}

void Evolution::calculateFitness(Population &pop)
{
    // Loop over population
    for(int i = 0; i < pop.getPopulationCount(); i++)
    {
        Individual &indiv = pop.getIndividual(i);
        indiv.fitness = 0.0;

        /* XNOR gate:
            A B | O
            ----|--
            0 0 | 1
            0 1 | 0
            1 0 | 0
            1 1 | 1  */

        // Compute for 0 XNOR 0 = 1
        float zz = indiv.computeNN(0, 0);
        indiv.fitness += zz; // the closer to 1 the better

        // Compute for 0 XNOR 1 = 0
        float zo = indiv.computeNN(0, 1);
        indiv.fitness += (1 - zo); // the closer to 0 the better

        // Compute for 1 XNOR 0 = 0
        float oz = indiv.computeNN(1, 0);
        indiv.fitness += (1 - oz); // the closer to 0 the better

        // Compute for 1 XNOR 1 = 1
        float oo = indiv.computeNN(1, 1);
        indiv.fitness += oo; // the closer to 1 the better
    }
}
