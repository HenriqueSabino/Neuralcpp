#include <random>
#include <ctime>
#include "NeuralNetwork.hpp"

void NeuralNetwork::initializeBiases()
{
    for (int i = 0; i < this->layersCount; i++)
    {
        // Setting the last column of the activation to 1
        this->values[i](0, this->values[i].getCols() - 1) = 1;
    }
}

NeuralNetwork::NeuralNetwork(int inputSize, int hiddenLayersSize[], int hiddenLayersAmount, int outputSize)
{
    this->inputSize = inputSize;
    this->hiddenLayersAmount = hiddenLayersAmount;
    this->outputSize = outputSize;
    this->layersCount = hiddenLayersAmount + 1;

    // First layer
    weights.push_back(Matrix(inputSize + 1, hiddenLayersSize[0]));
    sums.push_back(Matrix(1, hiddenLayersSize[0]));
    values.push_back(Matrix(1, hiddenLayersSize[0] + 1));

    // Hidden layers
    for (int i = 1; i < hiddenLayersAmount; i++)
    {
        weights.push_back(Matrix(hiddenLayersSize[i - 1] + 1, hiddenLayersSize[i]));
        sums.push_back(Matrix(1, hiddenLayersSize[i]));
        values.push_back(Matrix(1, hiddenLayersSize[i] + 1));
    }

    // ouput layer
    weights.push_back(Matrix(hiddenLayersSize[hiddenLayersAmount - 1] + 1, outputSize));
    sums.push_back(Matrix(1, outputSize));
    values.push_back(Matrix(1, outputSize + 1));

    initializeBiases();
}

std::vector<Matrix> *NeuralNetwork::getWeights()
{
    return &(this->weights);
}

std::vector<Matrix> NeuralNetwork::getSums()
{
    return this->sums;
}

std::vector<Matrix> NeuralNetwork::getValues()
{
    return this->values;
}

int NeuralNetwork::getNetworkSize()
{
    return this->layersCount;
}

void NeuralNetwork::setNeuralNetworkActivationFunction(ActivationFunction *function)
{
    this->activation_functions.clear();
    this->activation_functions.push_back(function);
}

void NeuralNetwork::setNeuralNetworkActivationFunctions(std::vector<ActivationFunction *> functions)
{
    if (functions.size() != this->layersCount)
    {
        this->activation_functions = functions;
    }
    else
    {
        // exception
    }
}

void NeuralNetwork::randomize()
{
    std::default_random_engine engine{static_cast<long unsigned int>(time(0))};
    std::uniform_real_distribution<double> distribution(0, 1);

    for (int i = 0; i < this->layersCount; i++)
    {
        for (int j = 0; j < this->weights[i].getRows(); j++)
        {
            for (int k = 0; k < this->weights[i].getCols(); k++)
            {
                // Generates a random number between 0 and 1
                this->weights[i](j, k) = distribution(engine);
            }
        }
    }
}