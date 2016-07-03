#include "globals.h"
#include "individual.h"

#include <random>
using std::uniform_int_distribution;


Individual::Individual()
{
    // Initialize individual with random weights
    uniform_int_distribution<int> randWieght(-100, 100);
    for(int i = 0; i < 9; i++)
        genome[i] = randWieght(e1);
    constructTHETA();
}

Individual::Individual(int genome[])
{
    // Initialize individual with a provided weights
    for(int i = 0; i < 9; i++)
        this->genome[i] = genome[i];
    constructTHETA();
}


void Individual::constructTHETA()
{
    // Construct THETA1[2][3] from genome[0:5]
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < 3; j++)
            THETA1[i][j] = genome[i*3+j];

    // Construct THETA2[3] from genome[6:8]
    for(int i = 0; i < 3; i++)
        THETA2[i] = genome[i+6];
}

float Individual::sigmoid(int z)
{
    //                   1
    // sigmoid(z) = ___________
    //                     -z
    //                 1 + e
    return 1 / (1 + exp(-z));
}

float Individual::computeNeuron(float input[], float THETA[])
{
    // Compute one neuron
    //
    //   BIAS*THETA0 --___    _____       ____________
    //                    -->|     |     | ACTIVATION |
    // INPUT1*THETA1 ------->| SUM |---->| (sigmoid)  |----> OUTPUT
    //                 ___-->|_____|     |____________|
    // INPUT2*THETA2 --
    //
    float sum = 0;
    for(int i = 0; i < 3; i++)
        sum += input[i] * THETA[i];
    return sigmoid(sum);
}

float Individual::computeNN(float x1, float x2)
{
    // Compute the whole network
    // Add bias(=1) to input layer
    float inputLayer[3] = { 1, x1, x2 };

    // Add bias to hidden layer,
    // calculate 1st neuron OUTPUT of hidden layer,
    // calculate 2nd neuron OUTPUT of hidden layer
    float hiddenLayer[3] = { 1, computeNeuron(inputLayer, THETA1[0]),
                             computeNeuron(inputLayer, THETA1[1]) };

    // Calculate the only neuron of output layer
    return computeNeuron(hiddenLayer, THETA2);
}
