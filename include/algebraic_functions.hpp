#ifndef ALGEBRAIC_FUNCTIONS_HPP
#define ALGEBRAIC_FUNCTIONS_HPP

#include "algebra_concepts.hpp"
#include "complex.hpp"
#include "matrix.hpp"
#include <cmath>
#include <cassert>

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
    T res = T(1); 
    T current_term = T(1);
    
    for (int i = 1; i <= terms; ++i) {
        current_term = (current_term * x) * (1.0 / i);
        res = res + current_term;
    }
    
    return res;
}

/**
 * @brief Fallback generic exp for other NormedAlgebra types
 * that don't have a specialized analytical exp.
 */
template <NormedAlgebra T>
requires (!std::is_same_v<T, Complex> && !std::is_same_v<T, Matrix<typename T::value_type>>) // Avoid ambiguity
T exp_generic(const T& x) {
    return exp_taylor(x);
}

#endif // ALGEBRAIC_FUNCTIONS_HPP
