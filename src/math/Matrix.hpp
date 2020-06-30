// Matrix.hpp
#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <vector>
#include <exception>
#include <string>

using namespace std;

struct IndexOutOfMatrixException : public exception
{
    int i, j;

    IndexOutOfMatrixException(int i, int j) : i(i), j(j) {}

    const char *what() const throw()
    {
        string cause = "Tried to access index [" + i;
        cause += ", " + j;
        cause += "] that is not inside this matrix";
        return cause.data();
    }
};

struct MatrixOrdersMismatchException : public exception
{
    int i, j, m, n;

    MatrixOrdersMismatchException(int i, int j, int m, int n) : i(i), j(j), m(m), n(n) {}

    const char *what() const throw()
    {
        string cause = "Cannot do this operation with matrices of orders (" + i;
        cause += "x " + j;
        cause += ") and (" + m;
        cause += "x) " + n;
        return cause.data();
    }
};

// Class used to represent mathematical matrices
class Matrix
{
    vector<double> values;
    int rows, cols;

public:
    // Constructs a matrix [rows] x [cols]
    Matrix(int rows, int cols);

    // Returns the number of rows this matrix has
    int getRows();

    // Returns the number of columns this matrix has
    int getCols();

    // Adds [other] values to this matrix
    void add(Matrix &other);

    // Subtracts [other] value from this matrix
    void sub(Matrix &other);

    // Multiplies this matrix by [scalar]
    void mult(double scalar);

    // Multiplies this matrix by [other]
    void mult(Matrix &other);

    // Returns the value at row [row] and column [col] of this matrix
    double operator()(int row, int col) const;

    // Returns the addres of the value at row [row] and column [col] of this matrix
    double &operator()(int row, int col);

    // Adds two matrices (does not affect any of the matrices)
    Matrix operator+(Matrix &other) const;

    // Subtracts two matrices (does not affect any of the matrices)
    Matrix operator-(Matrix &other) const;

    // Multiplies a matrix by a scalar value (does not affect the matrix)
    Matrix operator*(double scalar) const;

    // Multiplies two matrices (does not affect any of the matrices)
    Matrix operator*(Matrix &other) const;

    // Compares the values of two matrices
    bool operator==(const Matrix &other) const;

    // Returns the identity matrix of order [order]
    static Matrix identity(int order);

    // Returns the zero matrix of order [order]
    static Matrix zero(int order);

    // Returns the zero matrix of order [rows] x [cols]
    static Matrix zero(int rows, int cols);
};

#endif