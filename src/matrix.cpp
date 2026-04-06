#include "../include/matrix.hpp"
#include "../include/complex.hpp"
#include "../include/algebraic_functions.hpp" // IWYU pragma: keep
#include <cassert>
#include <cmath>

template <typename T>
Matrix<T>::Matrix(std::size_t r, std::size_t c) : rows(r), cols(c), data(r * c, T(0)) {}

template <typename T>
Matrix<T>::Matrix(std::size_t r, std::size_t c, const std::vector<T>& d) : rows(r), cols(c), data(d) {
    assert(d.size() == r * c);
}

template <typename T>
Matrix<T>::Matrix(const T& value) : rows(1), cols(1), data(1, value) {}

template <typename T>
std::size_t Matrix<T>::get_rows() const { return rows; }

template <typename T>
std::size_t Matrix<T>::get_cols() const { return cols; }

template <typename T>
T& Matrix<T>::operator()(std::size_t r, std::size_t c) { return data[r * cols + c]; }

template <typename T>
const T& Matrix<T>::operator()(std::size_t r, std::size_t c) const { return data[r * cols + c]; }

template <typename T>
Matrix<T> Matrix<T>::identity(std::size_t n) {
    Matrix res(n, n);
    for (std::size_t i = 0; i < n; ++i) res(i, i) = T(1);
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) const {
    assert(rows == other.rows && cols == other.cols);
    Matrix res(rows, cols);
    for (size_t i = 0; i < data.size(); ++i) res.data[i] = data[i] + other.data[i];
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator-() const {
    Matrix res(rows, cols);
    for (size_t i = 0; i < data.size(); ++i) res.data[i] = -data[i];
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix& other) const {
    assert(rows == other.rows && cols == other.cols);
    Matrix res(rows, cols);
    for (size_t i = 0; i < data.size(); ++i) res.data[i] = data[i] - other.data[i];
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix& other) const {
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

template <typename T>
Matrix<T> Matrix<T>::operator*(double scalar) const {
    Matrix res(rows, cols);
    for (size_t i = 0; i < data.size(); ++i) res.data[i] = data[i] * scalar;
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(double scalar) const {
    Matrix res(rows, cols);
    for (size_t i = 0; i < data.size(); ++i) res.data[i] = data[i] / scalar;
    return res;
}

template <typename U>
Matrix<U> operator*(double scalar, const Matrix<U>& m) {
    return m * scalar;
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix res(cols, rows);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            res(j, i) = (*this)(i, j);
        }
    }
    return res;
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const Matrix<U>& m) {
    for (size_t i = 0; i < m.rows; ++i) {
        for (size_t j = 0; j < m.cols; ++j) {
            os << m(i, j) << (j == m.cols - 1 ? "" : "  ");
        }
        os << "\n";
    }
    return os;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix& other) const {
    return rows == other.rows && cols == other.cols && data == other.data;
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix& other) const {
    return !(*this == other);
}

template <typename T>
double norm(const Matrix<T>& m) {
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

// Explicit Template Instantiation
template class Matrix<double>;
template class Matrix<Complex>;

template double norm(const Matrix<double>& m);
template double norm(const Matrix<Complex>& m);

template std::ostream& operator<<(std::ostream& os, const Matrix<double>& m);
template std::ostream& operator<<(std::ostream& os, const Matrix<Complex>& m);

template Matrix<double> operator*(double scalar, const Matrix<double>& m);
template Matrix<Complex> operator*(double scalar, const Matrix<Complex>& m);

template Matrix<double> exp(const Matrix<double>& A, int terms);
template Matrix<Complex> exp(const Matrix<Complex>& A, int terms);
