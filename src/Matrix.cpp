#include "headers/Matrix.hpp"

Matrix::Matrix(int rows, int cols)
    : rows(rows),
      cols(cols),
      values(rows * cols)
{
}

int Matrix::getRows()
{
    return this->rows;
}

int Matrix::getCols()
{
    return this->cols;
}

double Matrix::operator()(int row, int col) const
{
    return values[row * cols + col];
}

double &Matrix::operator()(int row, int col)
{
    return values[row * cols + col];
}

Matrix Matrix::operator+(Matrix &other) const
{
    Matrix result(this->rows, this->cols);

    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            result(i, j) = (*this)(i, j) + other(i, j);
        }
    }

    return result;
}

Matrix Matrix::operator-(Matrix &other) const
{
    Matrix result(this->rows, this->cols);

    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            result(i, j) = (*this)(i, j) - other(i, j);
        }
    }

    return result;
}

Matrix Matrix::operator*(double scalar) const
{
    Matrix result(this->rows, this->cols);

    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            result(i, j) = (*this)(i, j) * scalar;
        }
    }

    return result;
}

Matrix Matrix::operator*(Matrix &other) const
{
    Matrix result(this->rows, other.cols);

    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < other.cols; j++)
        {
            for (int k = 0; k < this->cols; k++)
            {
                double otherValue = other(k, j);
                result(i, j) += (*this)(i, k) * otherValue;
            }
        }
    }

    return result;
}

Matrix Matrix::identity(int order)
{
    Matrix identity(order, order);

    for (int i = 0; i < order; i++)
    {
        identity(i, i) = 1;
    }

    return identity;
}

Matrix Matrix::zero(int order)
{
    return Matrix(order, order);
}

Matrix Matrix::zero(int rows, int cols)
{
    return Matrix(rows, cols);
}

bool Matrix::operator==(const Matrix &other) const
{

    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            if ((*this)(i, j) != other(i, j))
                return false;
        }
    }

    return true;
}