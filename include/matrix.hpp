#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>
#include <cassert>
#include "algebra_concepts.hpp"

template <typename T>
class Matrix {
private:
    size_t rows, cols;
    std::vector<T> data;

public:
    Matrix(size_t r, size_t c) : rows(r), cols(c), data(r * c, T(0)) {}
    Matrix(size_t r, size_t c, const std::vector<T>& d) : rows(r), cols(c), data(d) {
        assert(d.size() == r * c);
    }

    size_t get_rows() const { return rows; }
    size_t get_cols() const { return cols; }

    T& operator()(size_t r, size_t c) { return data[r * cols + c]; }
    const T& operator()(size_t r, size_t c) const { return data[r * cols + c]; }

    static Matrix identity(size_t n) {
        Matrix res(n, n);
        for (size_t i = 0; i < n; ++i) res(i, i) = T(1);
        return res;
    }

    Matrix operator+(const Matrix& other) const {
        assert(rows == other.rows && cols == other.cols);
        Matrix res(rows, cols);
        for (size_t i = 0; i < data.size(); ++i) res.data[i] = data[i] + other.data[i];
        return res;
    }

    Matrix operator*(const Matrix& other) const {
        assert(cols == other.rows);
        Matrix res(rows, other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                T sum = T(0);
                for (size_t k = 0; k < cols; ++k) {
                    sum = sum + (*this)(i, k) * other(k, j);
                }
                res(i, j) = sum;
            }
        }
        return res;
    }

    Matrix operator*(double scalar) const {
        Matrix res(rows, cols);
        for (size_t i = 0; i < data.size(); ++i) res.data[i] = data[i] * scalar;
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        for (size_t i = 0; i < m.rows; ++i) {
            for (size_t j = 0; j < m.cols; ++j) {
                os << m(i, j) << (j == m.cols - 1 ? "" : "  ");
            }
            os << "\n";
        }
        return os;
    }
};

/**
 * @brief Matrix Exponentiation using Scaling and Squaring
 */
template <typename T>
Matrix<T> exp(const Matrix<T>& A, int terms = 15) {
    assert(A.get_rows() == A.get_cols());
    size_t n = A.get_rows();
    
    // 1. Calculate a simple Frobenius-style norm for scaling
    double norm = 0.0;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            T val = A(i, j);
            // Assuming T has a real() or equivalent for norm calculation
            // For Complex, we'll use a simplified check
            double v = 0;
            if constexpr (std::is_arithmetic_v<T>) v = std::abs((double)val);
            else v = std::sqrt(val.real()*val.real() + val.imag()*val.imag());
            norm += v;
        }
    }

    // 2. Scaling: Find s such that ||A / 2^s|| < 0.5
    int s = 0;
    if (norm > 0.5) {
        s = (int)std::ceil(std::log2(norm / 0.5));
    }

    Matrix<T> A_scaled = A * (1.0 / std::pow(2.0, s));

    // 3. Taylor series on scaled matrix
    Matrix<T> res = Matrix<T>::identity(n);
    Matrix<T> term = Matrix<T>::identity(n);
    
    for (int i = 1; i <= terms; ++i) {
        term = (term * A_scaled) * (1.0 / i);
        res = res + term;
    }
    
    // 4. Squaring: res = res^(2^s)
    for (int i = 0; i < s; ++i) {
        res = res * res;
    }
    
    return res;
}

#endif // MATRIX_HPP
