// Matrix.hpp
#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <vector>

using namespace std;

/// Class used to represent mathematical matrices
class Matrix
{
    vector<double> values;
    int rows, cols;

public:
    /// Constructs a matrix [rows] x [cols]
    Matrix(int rows, int cols);

    /// Returns the number of rows this matrix has
    int getRows();

    /// Returns the number of columns this matrix has
    int getCols();

    /// Returns the value at row [row] and column [col] of this matrix
    double operator()(int row, int col) const;

    /// Returns the addres of the value at row [row] and column [col] of this matrix
    double &operator()(int row, int col);

    /// Adds two matrices (does not affect any of the matrices)
    Matrix operator+(Matrix &other) const;

    /// Subtracts two matrices (does not affect any of the matrices)
    Matrix operator-(Matrix &other) const;

    /// Multiplies a matrix by a scalar value (does not affect the matrix)
    Matrix operator*(double scalar) const;

    /// Multiplies two matrices (does not affect any of the matrices)
    Matrix operator*(Matrix &other) const;

    /// Compares the values of two matrices
    bool operator==(const Matrix &other) const;

    /// Returns the identity matrix of order [order]
    static Matrix identity(int order);

    /// Returns the zero matrix of order [order]
    static Matrix zero(int order);

    /// Returns the zero matrix of order [rows] x [cols]
    static Matrix zero(int rows, int cols);
};

#endif