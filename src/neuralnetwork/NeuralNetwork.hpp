#if !defined(NEURAL_NETWORK_HPP)
#define NEURAL_NETWORK_HPP

#include <vector>
#include "../math/Matrix.hpp"
#include "../math/ActivationFunction.hpp"

class NeuralNetwork
{
private:
    int inputSize, hiddenLayersAmount, outputSize, layersCount;

    // Weights: array to store each layer weights

    // This two other matrices are not really usefull to the class itself, but they're useful for training it
    // Sums: array used to store the results of inputs * weights + bias of each neuron
    // values: array used to store each neuron activation
    std::vector<Matrix> weights, sums, values;
    // Activation functions to be used on each layer
    std::vector<ActivationFunction *> activation_functions;

    void initializeBiases();

public:
    // Constructs the neural network
    NeuralNetwork(int inputSize, int hiddenLayersSize[], int hiddenLayersAmount, int outputSize);

    // Returns the reference to neural network weights
    // WARNING: Change weights values wisely or else it may break the network
    std::vector<Matrix> *getWeights();

    // Return a copy of the neural network sums
    std::vector<Matrix> getSums();

    // Return a copy of the neural network activations
    std::vector<Matrix> getValues();

    // Returns the size of the neural network
    int getNetworkSize();

    // Sets a activation function for the WHOLE neural network
    void setNeuralNetworkActivationFunction(ActivationFunction *function);

    // Set a activation function for each neural network layer
    void setNeuralNetworkActivationFunctions(std::vector<ActivationFunction *> functions);

    // Randomizes the weights of the neural network
    void randomize();
};

#endif // NEURAL_NETWORK_HPP
