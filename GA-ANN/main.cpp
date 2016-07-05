#include "globals.h"
#include "individual.h"
#include "population.h"
#include "evolution.h"

#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <math.h>

using namespace std;

void printPopulation(Population pop, int count);

random_device r;
default_random_engine e1(r());

int main()
{
    int POP_SIZE = 5000;
    Population pop(POP_SIZE);
    Evolution::calculateFitness(pop);
    pop.sortByFitness();
    printPopulation(pop, 18);

    uniform_int_distribution<int> survRand(0, POP_SIZE/2);
    for(int generation = 1;; generation++)
    {
        vector<Individual> newPopulation;

        for(int i = 0; i < POP_SIZE-1; i++)
        {
            // Crossover
            int parent1 = survRand(e1);
            int parent2 = survRand(e1);
            Individual newIndiv =
                    Evolution::crossover(pop.getIndividual(parent1),
                                         pop.getIndividual(parent2));
            // Mutation
            uniform_int_distribution<int> r(1, 100);
            if(r(e1) <= 50)
                Evolution::mutate(newIndiv);
            newPopulation.push_back(newIndiv);
        }

        // Saving best individual from previous generation
        Individual indiv = pop.individuals.front();
        // Replace new population
        pop.individuals = newPopulation;
        // Best individual from previous generation is added
        // to the new generation (elitism = 1)
        pop.individuals.push_back(indiv);

        Evolution::calculateFitness(pop);
        pop.sortByFitness();
        system("clear");
        cout << "Generation " << generation << endl;
        printPopulation(pop, 18);

        if(pop.getIndividual(0).fitness >= 4)
        {
            cout << "\nFound solution. Press <RETURN> to verify\n";
            getchar();
            system("clear");
            Individual finIndiv = pop.getIndividual(0);

            cout << "Genome (all thetas values):\n[ ";
            for(int j = 0; j < 9; j++)
                cout << right << setw(3) << finIndiv.genome[j] << ", ";
            cout << "\b\b ]\n\n";

            cout << "THETA1 matrix:\n";
            for(int i = 0; i < 2; i++)
            {
                for(int j = 0; j < 3; j++)
                    cout << finIndiv.THETA1[i][j] << "\t";
                cout << endl;
            }
            cout << endl;

            cout << "THETA2 matrix:\n";
            for(int i = 0; i < 3; i++)
                cout << finIndiv.THETA2[i] << "\t";
            cout << "\n\n";

            const float THLD = 0.5;
            cout << "XNOR gate:\nA B | O\n----|--\n"
                    // If finIndiv.computeNN() >= threshold output 1, else 0
                 << "0 0 | " << (finIndiv.computeNN(0, 0) >= THLD) << endl
                 << "0 1 | " << (finIndiv.computeNN(0, 1) >= THLD) << endl
                 << "1 0 | " << (finIndiv.computeNN(1, 0) >= THLD) << endl
                 << "1 1 | " << (finIndiv.computeNN(1, 1) >= THLD) << endl
                 << endl;
            break;
        }
    }
    return 0;
}

void printPopulation(Population pop, int count)
{
    int popSize = pop.getPopulationCount();
    float avg = 0;
    for(int i = 0; i < popSize; i++)
        avg += pop.getIndividual(i).fitness;
    avg /= popSize;

    cout << "Solving XOR as an example of GA-ANN...\n";
    cout << "Best fit = " << pop.getIndividual(0).fitness <<
            " | Worst fit = " << pop.getIndividual(popSize-1).fitness <<
            " | Avg fit = " << avg << endl;

    for(int i = 0; i < count; i++)
    {
        Individual indiv = pop.getIndividual(i); // a copy of individual
        cout << "Indiv" << left << setw(2) << i << " fitness = "
             << setprecision(4) << setw(5) << indiv.fitness << " [ ";
        for(int j = 0; j < 9; j++)
            cout << right << setw(3) << indiv.genome[j] << ", ";
        cout << "\b\b ]\n";
    }
}
