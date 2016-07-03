#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H


#include <random>
using std::uniform_int_distribution;


class Individual
{
public:
    int genome[9];
    float fitness = 0;
    float THETA1[2][3];
    float THETA2[3];

    void constructTHETA();
    float sigmoid(int z);
    float computeNeuron(float input[3], float THETA[3]);
    float computeNN(float x1, float x2);


public:
    Individual();
    Individual(int genome[9]);
};

#endif // INDIVIDUAL_H
