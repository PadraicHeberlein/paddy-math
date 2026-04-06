#ifndef ALGEBRAIC_FUNCTIONS_HPP
#define ALGEBRAIC_FUNCTIONS_HPP

#include "algebra_concepts.hpp"
#include "complex.hpp"
#include "matrix.hpp"
#include <cmath>

/**
 * @brief Generic Exponential function using Taylor Series expansion.
 * Suitable for any type satisfying the NormedAlgebra concept.
 * 
 * @tparam T A type that satisfies NormedAlgebra (Ring with a norm function)
 * @param x The input value
 * @param terms Number of terms in the Taylor series (default 15)
 * @return T The computed value of e^x
 */
template <NormedAlgebra T>
T exp_taylor(const T& x, int terms = 50) {
    // e^x = 1 + x + x^2/2! + x^3/3! + ...
    // Using a default "1" identity. For matrices, this should be the identity matrix.
    // However, the NormedAlgebra concept doesn't know about dimensions.
    // We assume T(1) creates a suitable unity element.
    
    T res = T(1); 
    T current_term = T(1);
    
    for (int i = 1; i <= terms; ++i) {
        current_term = (current_term * x) * (1.0 / i);
        res = res + current_term;
    }
    
    return res;
}

/**
 * @brief Overload for Complex numbers using the analytical solution:
 * e^(a+bi) = e^a * (cos(b) + i*sin(b))
 */
inline Complex exp(const Complex& c) {
    double exp_real = std::exp(c.real());
    return Complex(exp_real * std::cos(c.imag()), exp_real * std::sin(c.imag()));
}

/**
 * @brief Overload for Matrix types using Scaling and Squaring
 * to ensure numerical stability and speed.
 */
template <typename T>
Matrix<T> exp(const Matrix<T>& A, int terms = 50) {
    // Scaling and Squaring algorithm
    std::size_t n = A.get_rows();
    assert(A.get_rows() == A.get_cols());

    // 1. Calculate norm for scaling
    double matrix_norm = 0.0;
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            T val = A(i, j);
            if constexpr (std::is_arithmetic_v<T>) {
                matrix_norm += std::abs(static_cast<double>(val));
            } else if constexpr (NormedAlgebra<T>) {
                matrix_norm += norm(val);
            } else {
                matrix_norm += 1.0; 
            }
        }
    }

    // 2. Scaling
    int s = 0;
    if (matrix_norm > 0.5) {
        s = static_cast<int>(std::ceil(std::log2(matrix_norm / 0.5)));
    }

    Matrix<T> A_scaled = A * (1.0 / std::pow(2.0, s));

    // 3. Taylor series on scaled matrix
    // Note: We use Matrix::identity(n) here because we know the dimensions.
    Matrix<T> res = Matrix<T>::identity(n);
    Matrix<T> current_term = Matrix<T>::identity(n);
    
    for (int i = 1; i <= terms; ++i) {
        current_term = (current_term * A_scaled) * (1.0 / i);
        res = res + current_term;
    }
    
    // 4. Squaring
    for (int i = 0; i < s; ++i) {
        res = res * res;
    }
    
    return res;
}

/**
 * @brief Fallback generic exp for other NormedAlgebra types
 */
template <NormedAlgebra T>
requires (!std::is_same_v<T, Complex>) // Avoid ambiguity with Complex overload
T exp(const T& x) {
    return exp_taylor(x);
}

#endif // ALGEBRAIC_FUNCTIONS_HPP
