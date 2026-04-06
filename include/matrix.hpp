#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>
#include <cstddef>

template <typename T>
class Matrix {
private:
    std::size_t rows, cols;
    std::vector<T> data;

public:
    Matrix(std::size_t r, std::size_t c);
    Matrix(std::size_t r, std::size_t c, const std::vector<T>& d);
    Matrix(const T& value);

    std::size_t get_rows() const;
    std::size_t get_cols() const;

    T& operator()(std::size_t r, std::size_t c);
    const T& operator()(std::size_t r, std::size_t c) const;

    static Matrix identity(std::size_t n);

    Matrix operator+(const Matrix& other) const;
    Matrix operator-() const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    Matrix operator/(double scalar) const;

    template <typename U>
    friend Matrix<U> operator*(double scalar, const Matrix<U>& m);

    Matrix transpose() const;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& m);

    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
};

/**
 * @brief Frobenius Norm for a Matrix
 */
template <typename T>
double norm(const Matrix<T>& m);

template <typename T>
Matrix<T> exp(const Matrix<T>& A, int terms = 50);

#endif // MATRIX_HPP
