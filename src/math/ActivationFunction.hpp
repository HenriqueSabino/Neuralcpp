#ifndef ACTIVATION_FUNCTION_HPP
#define ACTIVATION_FUNCTION_HPP
#include "Matrix.hpp"

class ActivationFunction
{
public:
    virtual Matrix apply(Matrix mat) const = 0;
    virtual Matrix applyDerivative(Matrix mat) const = 0;
};

class ReLU : public ActivationFunction
{
public:
    Matrix apply(Matrix mat) const;
    Matrix applyDerivative(Matrix mat) const;
};

class LeakyReLU : public ActivationFunction
{
public:
    Matrix apply(Matrix mat) const;
    Matrix applyDerivative(Matrix mat) const;
};

class Sigmoid : public ActivationFunction
{
public:
    Matrix apply(Matrix mat) const;
    Matrix applyDerivative(Matrix mat) const;
};

class Softmax : public ActivationFunction
{
public:
    Matrix apply(Matrix mat) const;
    Matrix applyDerivative(Matrix mat) const;
};

#endif