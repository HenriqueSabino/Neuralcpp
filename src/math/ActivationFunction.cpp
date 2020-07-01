#include <cmath>
#include "ActivationFunction.hpp"

Matrix ReLU::apply(Matrix mat) const
{
    for (int i = 0; i < mat.getRows(); i++)
    {
        for (int j = 0; j < mat.getCols(); j++)
        {
            if (mat(i, j) <= 0)
                mat(i, j) = 0;
        }
    }

    return mat;
}

Matrix ReLU::applyDerivative(Matrix mat) const
{
    for (int i = 0; i < mat.getRows(); i++)
    {
        for (int j = 0; j < mat.getCols(); j++)
        {
            mat(i, j) = mat(i, j) <= 0 ? 0 : 1;
        }
    }

    return mat;
}

Matrix LeakyReLU::apply(Matrix mat) const
{
    for (int i = 0; i < mat.getRows(); i++)
    {
        for (int j = 0; j < mat.getCols(); j++)
        {
            if (mat(i, j) <= 0)
                mat(i, j) *= 0.01;
        }
    }

    return mat;
}

Matrix LeakyReLU::applyDerivative(Matrix mat) const
{
    for (int i = 0; i < mat.getRows(); i++)
    {
        for (int j = 0; j < mat.getCols(); j++)
        {
            mat(i, j) = mat(i, j) <= 0 ? 0.01 : 1;
        }
    }

    return mat;
}

Matrix Sigmoid::apply(Matrix mat) const
{
    for (int i = 0; i < mat.getRows(); i++)
    {
        for (int j = 0; j < mat.getCols(); j++)
        {
            mat(i, j) = 1 / (1 + exp(-mat(i, j)));
        }
    }

    return mat;
}

Matrix Sigmoid::applyDerivative(Matrix mat) const
{
    mat = apply(mat);

    for (int i = 0; i < mat.getRows(); i++)
    {
        for (int j = 0; j < mat.getCols(); j++)
        {
            mat(i, j) *= 1 - mat(i, j);
        }
    }

    return mat;
}

Matrix Softmax::apply(Matrix mat) const
{
    double maxValue = mat(0, 0);

    for (int i = 0; i < mat.getRows(); i++)
    {
        for (int j = 0; j < mat.getCols(); j++)
        {
            if (maxValue < mat(i, j))
                maxValue = mat(i, j);
        }
    }

    for (int i = 0; i < mat.getRows(); i++)
    {
        for (int j = 0; j < mat.getCols(); j++)
        {
            mat(i, j) -= maxValue;
        }
    }

    double sum = 0;

    for (int i = 0; i < mat.getRows(); i++)
    {
        for (int j = 0; j < mat.getCols(); j++)
        {
            mat(i, j) = exp(mat(i, j));
            sum += mat(i, j);
        }
    }

    mat.mult(1 / sum);

    return mat;
}

Matrix Softmax::applyDerivative(Matrix mat) const
{
    mat = apply(mat);

    for (int i = 0; i < mat.getRows(); i++)
    {
        for (int j = 0; j < mat.getCols(); j++)
        {
            mat(i, j) *= 1 - mat(i, j);
        }
    }

    return mat;
}
