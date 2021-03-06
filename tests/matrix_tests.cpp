#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif

#include "headers/catch.hpp"
#include "../src/math/Matrix.hpp"

TEST_CASE("Testing getters")
{
    Matrix test(5, 2);
    REQUIRE(test.getRows() == 5);
    REQUIRE(test.getCols() == 2);
}

TEST_CASE("Testing zero matrix")
{
    Matrix zero6 = Matrix::zero(6);

    REQUIRE(zero6.getRows() == 6);
    REQUIRE(zero6.getCols() == 6);

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            REQUIRE(zero6(i, j) == 0);
        }
    }

    zero6 = Matrix::zero(2, 3);

    REQUIRE(zero6.getRows() == 2);
    REQUIRE(zero6.getCols() == 3);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            REQUIRE(zero6(i, j) == 0);
        }
    }
}

TEST_CASE("Testing IndexOutOfMatrixException")
{
    Matrix a = Matrix(2, 2);
    REQUIRE_THROWS_AS(a(2, 2), IndexOutOfMatrixException);
}

TEST_CASE("Testing MatrixOrdersMismatchException")
{
    Matrix a = Matrix(2, 2);
    Matrix b = Matrix(3, 3);

    REQUIRE_THROWS_AS(a + b, MatrixOrdersMismatchException);
    REQUIRE_THROWS_AS(a - b, MatrixOrdersMismatchException);
    REQUIRE_THROWS_AS(a * b, MatrixOrdersMismatchException);
    REQUIRE_THROWS_AS(a.add(b), MatrixOrdersMismatchException);
    REQUIRE_THROWS_AS(a.sub(b), MatrixOrdersMismatchException);
    REQUIRE_THROWS_AS(a.mult(b), MatrixOrdersMismatchException);
}

TEST_CASE("Testing Matrix constructor exception")
{
    REQUIRE_THROWS_AS(Matrix(0, 1), invalid_argument);
    REQUIRE_THROWS_AS(Matrix(1, 0), invalid_argument);
}

TEST_CASE("Testing identity matrix")
{
    Matrix id5 = Matrix::identity(5);
    REQUIRE(id5.getRows() == 5);
    REQUIRE(id5.getCols() == 5);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (i == j)
                REQUIRE(id5(i, j) == 1);
            else
                REQUIRE(id5(i, j) == 0);
        }
    }
}

TEST_CASE("Testing addition/subtraction")
{
    // Testing operator +/-
    Matrix a = Matrix(3, 3);

    for (int i = 0; i < a.getRows(); i++)
    {
        for (int j = 0; j < a.getCols(); j++)
        {
            a(i, j) = j;
        }
    }

    Matrix expected_result = Matrix(3, 3);

    for (int i = 0; i < expected_result.getRows(); i++)
    {
        for (int j = 0; j < expected_result.getCols(); j++)
        {
            expected_result(i, j) = 2 * j;
        }
    }

    REQUIRE(a + a == expected_result);

    REQUIRE(a == expected_result - a);

    // Testing functions add()/sub()

    a.add(a);

    REQUIRE(a == expected_result);

    a.sub(a);

    REQUIRE(a == Matrix::zero(3));
}

TEST_CASE("Testing scalar multiplication")
{
    // Testing operator *
    Matrix a = Matrix(3, 3);

    for (int i = 0; i < a.getRows(); i++)
    {
        for (int j = 0; j < a.getCols(); j++)
        {
            a(i, j) = j;
        }
    }

    Matrix expected_result = Matrix(3, 3);

    for (int i = 0; i < expected_result.getRows(); i++)
    {
        for (int j = 0; j < expected_result.getCols(); j++)
        {
            expected_result(i, j) = 4 * j;
        }
    }

    REQUIRE(a * 4 == expected_result);
    REQUIRE(a == expected_result * 0.25);

    // Testing function mult()

    a.mult(4);

    REQUIRE(a == expected_result);
}

TEST_CASE("Testing square matrix multiplication")
{
    // Testing operator *
    Matrix a = Matrix(3, 3);

    for (int i = 0; i < a.getRows(); i++)
    {
        for (int j = 0; j < a.getCols(); j++)
        {
            a(i, j) = i + j;
        }
    }

    Matrix i = Matrix::identity(3);

    REQUIRE(a * i == a);
    REQUIRE(i * a == a);

    // Testing function mult()

    Matrix b = a; // Saving a values

    i = i * 2;

    a.mult(i); // The same as a * 2

    REQUIRE(b * 2 == a);
}

TEST_CASE("Testing matrix multiplication")
{
    // Testing operator *
    Matrix a = Matrix(2, 3);
    Matrix b = Matrix(3, 4);

    for (int i = 0; i < a.getRows(); i++)
    {
        for (int j = 0; j < a.getCols(); j++)
        {
            int index = j + i * a.getCols() + 1;
            a(i, j) = index;
        }
    }

    for (int i = 0; i < b.getRows(); i++)
    {
        for (int j = 0; j < b.getCols(); j++)
        {
            int index = j + i * b.getCols() + 1;
            b(i, j) = index;
        }
    }

    Matrix result = a * b;

    Matrix expected_result = Matrix(2, 4);

    expected_result(0, 0) = 38;
    expected_result(0, 1) = 44;
    expected_result(0, 2) = 50;
    expected_result(0, 3) = 56;
    expected_result(1, 0) = 83;
    expected_result(1, 1) = 98;
    expected_result(1, 2) = 113;
    expected_result(1, 3) = 128;

    REQUIRE(result == expected_result);

    // Testing function mult()
    a.mult(b);
    REQUIRE(a == expected_result);
}