#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif

#include <cmath>
#include "../src/math/ActivationFunction.hpp"
#include "../src/math/Matrix.hpp"
#include "headers/catch.hpp"

TEST_CASE("Testing application of ReLU")
{
    ActivationFunction *reLu = new ReLU();
    Matrix test = Matrix(2, 2);
    test(0, 0) = -1;
    test(0, 1) = 2;
    test(1, 0) = 0;
    test(1, 1) = 1;

    Matrix groundThruth = Matrix(2, 2);
    groundThruth(0, 0) = 0;
    groundThruth(0, 1) = 2;
    groundThruth(1, 0) = 0;
    groundThruth(1, 1) = 1;

    CHECK(reLu->apply(test) == groundThruth);
    delete reLu;
}

TEST_CASE("Testing application of ReLU derivative")
{
    ActivationFunction *reLu = new ReLU();
    Matrix test = Matrix(2, 2);
    test(0, 0) = -1;
    test(0, 1) = 2;
    test(1, 0) = 0;
    test(1, 1) = 1;

    Matrix groundThruth = Matrix(2, 2);
    groundThruth(0, 0) = 0;
    groundThruth(0, 1) = 1;
    groundThruth(1, 0) = 0;
    groundThruth(1, 1) = 1;

    CHECK(reLu->applyDerivative(test) == groundThruth);
    delete reLu;
}

TEST_CASE("Testing application of LeakyReLU")
{
    ActivationFunction *leakyRelu = new LeakyReLU();
    Matrix test = Matrix(2, 2);
    test(0, 0) = -1;
    test(0, 1) = 2;
    test(1, 0) = 0;
    test(1, 1) = 1;

    Matrix groundThruth = Matrix(2, 2);
    groundThruth(0, 0) = -0.01;
    groundThruth(0, 1) = 2;
    groundThruth(1, 0) = 0;
    groundThruth(1, 1) = 1;

    CHECK(leakyRelu->apply(test) == groundThruth);
    delete leakyRelu;
}

TEST_CASE("Testing application of LeakyReLU derivative")
{
    ActivationFunction *leakyRelu = new LeakyReLU();
    Matrix test = Matrix(2, 2);
    test(0, 0) = -1;
    test(0, 1) = 2;
    test(1, 0) = 0;
    test(1, 1) = 1;

    Matrix groundThruth = Matrix(2, 2);
    groundThruth(0, 0) = 0.01;
    groundThruth(0, 1) = 1;
    groundThruth(1, 0) = 0.01;
    groundThruth(1, 1) = 1;

    CHECK(leakyRelu->applyDerivative(test) == groundThruth);
    delete leakyRelu;
}

TEST_CASE("Testing application of Sigmoid")
{
    ActivationFunction *sig = new Sigmoid();
    Matrix test = Matrix(2, 2);
    test(0, 0) = -1;
    test(0, 1) = 2;
    test(1, 0) = 0;
    test(1, 1) = 1;

    Matrix groundThruth = Matrix(2, 2);
    // results obtained at https://keisan.casio.com/exec/system/15157249643325
    groundThruth(0, 0) = 0.26894142137;
    groundThruth(0, 1) = 0.88079707797788;
    groundThruth(1, 0) = 0.5;
    groundThruth(1, 1) = 0.73105857863001;

    CHECK(sig->apply(test) == groundThruth);
    delete sig;
}

TEST_CASE("Testing application of Sigmoid derivative")
{
    ActivationFunction *sig = new Sigmoid();
    Matrix test = Matrix(2, 2);
    test(0, 0) = -1;
    test(0, 1) = 2;
    test(1, 0) = 0;
    test(1, 1) = 1;

    Matrix groundThruth = Matrix(2, 2);
    // results obtained at https://keisan.casio.com/exec/system/15157249643425
    groundThruth(0, 0) = 0.19661193324148;
    groundThruth(0, 1) = 0.10499358540351;
    groundThruth(1, 0) = 0.25;
    groundThruth(1, 1) = 0.19661193324148;

    CHECK(sig->applyDerivative(test) == groundThruth);
    delete sig;
}

TEST_CASE("Testing application of Softmax")
{
    ActivationFunction *softmax = new Softmax();
    Matrix test = Matrix(5, 1);
    test(0, 0) = 3;
    test(1, 0) = 2;
    test(2, 0) = 4;
    test(3, 0) = 1;
    test(4, 0) = 0;

    Matrix groundThruth = Matrix(5, 1);
    // results obtained at https://keisan.casio.com/exec/system/15168444286206
    groundThruth(0, 0) = 0.23412165725274;
    groundThruth(1, 0) = 0.086128544436269;
    groundThruth(2, 0) = 0.63640864655883;
    groundThruth(3, 0) = 0.031684920796124;
    groundThruth(4, 0) = 0.01165623095604;

    CHECK(softmax->apply(test) == groundThruth);
    delete softmax;
}

TEST_CASE("Testing application of Softmax derivative")
{
    ActivationFunction *softmax = new Softmax();
    Matrix test = Matrix(5, 1);
    test(0, 0) = 3;
    test(1, 0) = 2;
    test(2, 0) = 4;
    test(3, 0) = 1;
    test(4, 0) = 0;

    Matrix groundThruth = Matrix(5, 1);
    // results obtained at https://keisan.casio.com/exec/system/15168444286206
    groundThruth(0, 0) = 0.23412165725274;
    groundThruth(1, 0) = 0.086128544436269;
    groundThruth(2, 0) = 0.63640864655883;
    groundThruth(3, 0) = 0.031684920796124;
    groundThruth(4, 0) = 0.01165623095604;

    for (int i = 0; i < groundThruth.getRows(); i++)
    {
        for (int j = 0; j < groundThruth.getCols(); j++)
        {
            groundThruth(i, j) *= 1 - groundThruth(i, j);
        }
    }

    CHECK(softmax->applyDerivative(test) == groundThruth);
    delete softmax;
}
