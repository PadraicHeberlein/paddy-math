#ifndef ALGEBRA_FUNCTIONS_HPP
#define ALGEBRA_FUNCTIONS_HPP

#include "algebra_concepts.hpp"
#include "complex.hpp"
#include "matrix.hpp"
#include <type_traits>
#include <cassert>
#include <cmath>

// Helper to check if a type is a Matrix
template<typename T>
struct is_matrix : std::false_type {};

template<typename T>
struct is_matrix<Matrix<T>> : std::true_type {};

/**
 * @brief Generic Exponential function using Taylor Series expansion.
 * Suitable for any type satisfying the Algebra concept.
 */
template <Algebra T> T exp_taylor(const T &x, int terms = 50);

template <Algebra T> T factorial(int n);

/**
 * @brief Fallback generic exp for other Algebra types
 * that don't have a specialized analytical exp.
 */
template <Algebra T>
requires (!std::is_same_v<T, Complex> && !is_matrix<T>::value)
T exp_generic(const T &x);

#endif // ALGEBRA_FUNCTIONS_HPP
