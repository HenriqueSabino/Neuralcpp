#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif

#include "headers/catch.hpp"
#include "../src/neuralnetwork/NeuralNetwork.hpp"

// There's not much to test here other than the construction of the neural network
// Wether it functions or not will be tested when neural network training is implemented

TEST_CASE("Testing neural network construction")
{
    int inputSize = 2;
    int hiddenLayersAmount = 3;
    int hiddenLayerSizes[3] = {3, 3, 2};
    int outputSize = 2;
    NeuralNetwork neunet(inputSize, hiddenLayerSizes, hiddenLayersAmount, outputSize);

    // There must be 3 weight matrices because there are three layers
    REQUIRE(neunet.getWeights()->size() == hiddenLayersAmount + 1);

    // The first layer must have the weight rows equal to the input amount + 1 (bias)
    REQUIRE(neunet.getWeights()->at(0).getRows() == inputSize + 1);
    REQUIRE(neunet.getWeights()->at(0).getCols() == hiddenLayerSizes[0]);

    REQUIRE(neunet.getSums()[0].getRows() == 1);
    REQUIRE(neunet.getSums()[0].getCols() == hiddenLayerSizes[0]);

    REQUIRE(neunet.getValues()[0].getRows() == 1);
    REQUIRE(neunet.getValues()[0].getCols() == hiddenLayerSizes[0] + 1);

    // Checking other hidden layers
    for (int i = 1; i < hiddenLayersAmount; i++)
    {
        // A hidden layer must have the weight rows equal to the size of the previous layer + 1 (bias)
        REQUIRE(neunet.getWeights()->at(i).getRows() == hiddenLayerSizes[i - 1] + 1);
        REQUIRE(neunet.getWeights()->at(i).getCols() == hiddenLayerSizes[i]);

        REQUIRE(neunet.getSums()[i].getRows() == 1);
        REQUIRE(neunet.getSums()[i].getCols() == hiddenLayerSizes[i]);

        REQUIRE(neunet.getValues()[i].getRows() == 1);
        REQUIRE(neunet.getValues()[i].getCols() == hiddenLayerSizes[i] + 1);
    }

    // Checking output layer
    // The output layer must have the weight rows equal to the size of the previous layer + 1 (bias)
    REQUIRE(neunet.getWeights()->at(neunet.getNetworkSize() - 1).getRows() == hiddenLayerSizes[hiddenLayersAmount - 1] + 1);
    REQUIRE(neunet.getWeights()->at(neunet.getNetworkSize() - 1).getCols() == outputSize);

    REQUIRE(neunet.getSums()[neunet.getNetworkSize() - 1].getRows() == 1);
    REQUIRE(neunet.getSums()[neunet.getNetworkSize() - 1].getCols() == outputSize);

    REQUIRE(neunet.getValues()[neunet.getNetworkSize() - 1].getRows() == 1);
    REQUIRE(neunet.getValues()[neunet.getNetworkSize() - 1].getCols() == outputSize + 1);
}

TEST_CASE("Testing neural network exceptions")
{
    // TODO
}

TEST_CASE("Testing neural network biases initialization")
{
    int inputSize = 2;
    int hiddenLayersAmount = 3;
    int hiddenLayersSizes[3] = {3, 3, 2};
    int outputSize = 2;
    NeuralNetwork neunet(inputSize, hiddenLayersSizes, hiddenLayersAmount, outputSize);

    for (int i = 0; i < neunet.getNetworkSize(); i++)
    {
        std::vector<Matrix> activations = neunet.getValues();

        REQUIRE(activations[i](0, activations[i].getCols() - 1) == 1);
    }
}