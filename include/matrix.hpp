#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>
#include <cassert>
#include <cstddef>
#include <cmath>
#include <type_traits>
#include "algebra_concepts.hpp"

template <typename T>
class Matrix {
private:
    std::size_t rows, cols;
    std::vector<T> data;

public:
    Matrix(std::size_t r, std::size_t c) : rows(r), cols(c), data(r * c, T(0)) {}
    Matrix(std::size_t r, std::size_t c, const std::vector<T>& d) : rows(r), cols(c), data(d) {
        assert(d.size() == r * c);
    }
    // Constructor from scalar to satisfy Group/Ring identity requirements
    Matrix(const T& value) : rows(1), cols(1), data(1, value) {}

    std::size_t get_rows() const { return rows; }
    std::size_t get_cols() const { return cols; }

    T& operator()(std::size_t r, std::size_t c) { return data[r * cols + c]; }
    const T& operator()(std::size_t r, std::size_t c) const { return data[r * cols + c]; }

    static Matrix identity(std::size_t n) {
        Matrix res(n, n);
        for (std::size_t i = 0; i < n; ++i) res(i, i) = T(1);
        return res;
    }

    Matrix operator+(const Matrix& other) const {
        assert(rows == other.rows && cols == other.cols);
        Matrix res(rows, cols);
        for (size_t i = 0; i < data.size(); ++i) res.data[i] = data[i] + other.data[i];
        return res;
    }

    Matrix operator-() const {
        Matrix res(rows, cols);
        for (size_t i = 0; i < data.size(); ++i) res.data[i] = -data[i];
        return res;
    }

    Matrix operator-(const Matrix& other) const {
        assert(rows == other.rows && cols == other.cols);
        Matrix res(rows, cols);
        for (size_t i = 0; i < data.size(); ++i) res.data[i] = data[i] - other.data[i];
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

    Matrix operator/(double scalar) const {
        Matrix res(rows, cols);
        for (size_t i = 0; i < data.size(); ++i) res.data[i] = data[i] / scalar;
        return res;
    }

    friend Matrix operator*(double scalar, const Matrix& m) {
        return m * scalar;
    }

    Matrix transpose() const {
        Matrix res(cols, rows);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                res(j, i) = (*this)(i, j);
            }
        }
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

    bool operator==(const Matrix& other) const {
        return rows == other.rows && cols == other.cols && data == other.data;
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }
};

/**
 * @brief Frobenius Norm for a Matrix
 */
template <typename T>
inline double norm(const Matrix<T>& m) {
    double res = 0.0;
    for (std::size_t i = 0; i < m.get_rows(); ++i) {
        for (std::size_t j = 0; j < m.get_cols(); ++j) {
            T val = m(i, j);
            if constexpr (std::is_arithmetic_v<T>) {
                res += static_cast<double>(val) * static_cast<double>(val);
            } else if constexpr (NormedAlgebra<T>) {
                double val_norm = norm(val);
                res += val_norm * val_norm;
            } else {
                res += 1.0; 
            }
        }
    }
    return std::sqrt(res);
}

#endif // MATRIX_HPP
