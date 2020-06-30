#include "Matrix.hpp"

Matrix::Matrix(int rows, int cols)
{
    if (rows <= 0 || cols <= 0)
        __throw_invalid_argument("The matrix order has to be at least 1 x 1");

    this->rows = rows;
    this->cols = cols;
    this->values.resize(rows * cols);
}

int Matrix::getRows()
{
    return this->rows;
}

int Matrix::getCols()
{
    return this->cols;
}

void Matrix::add(Matrix &other)
{
    *this = *this + other;
}

void Matrix::sub(Matrix &other)
{
    *this = *this - other;
}

void Matrix::mult(double scalar)
{
    *this = *this * scalar;
}

void Matrix::mult(Matrix &other)
{
    *this = *this * other;
}

double Matrix::operator()(int row, int col) const
{
    if (row < 0 || row >= rows)
    {
        if (col < 0 || col >= cols)
        {
            throw IndexOutOfMatrixException(row, col);
        }
    }
    return values[row * cols + col];
}

double &Matrix::operator()(int row, int col)
{
    if (row < 0 || row >= rows)
    {
        if (col < 0 || col >= cols)
        {
            throw IndexOutOfMatrixException(row, col);
        }
    }
    return values[row * cols + col];
}

Matrix Matrix::operator+(Matrix &other) const
{
    if (this->rows != other.rows || this->cols != other.cols)
        throw MatrixOrdersMismatchException(this->rows, this->cols, other.rows, other.cols);

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
    if (this->rows != other.rows || this->cols != other.cols)
        throw MatrixOrdersMismatchException(this->rows, this->cols, other.rows, other.cols);

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
    if (this->cols != other.rows)
        throw MatrixOrdersMismatchException(this->rows, this->cols, other.rows, other.cols);

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
    if (this->rows != other.rows || this->cols != other.cols)
        return false;

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