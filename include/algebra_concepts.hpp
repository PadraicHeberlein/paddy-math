#ifndef ALGEBRA_CONCEPTS_HPP
#define ALGEBRA_CONCEPTS_HPP

#include <concepts>
#include <type_traits>
#include <cmath>

template <typename T>
concept Scalar = std::is_arithmetic_v<T>; // A basic rule: T must be a number (built-in)

template <typename T>
concept Group = std::copyable<T> && requires(const T a, const T b) {
  { a + b } -> std::same_as<T>;
  { a - b } -> std::same_as<T>;     // Closure
  { T(0) } -> std::same_as<T>;      // Identity
  { -a } -> std::same_as<T>;         // Inverse
  { a == b } -> std::same_as<bool>; // Equality
  { a != b } -> std::same_as<bool>; // Inequality
};

template <typename T>
concept Ring = Group<T> && requires(const T a, const T b) {
  { a * b } -> std::same_as<T>;    // Multiplication
  { T(1) } -> std::same_as<T>;      // Unity
};

template <typename T>
concept Field = Ring<T> && requires(const T a, const T b) {
  { a / b } -> std::same_as<T>; // Division
};

/**
 * @brief Vector Space concept.
 * A Vector Space V over a Scalar S (defaults to double).
 * Requires vector addition and scalar multiplication/division.
 */
template <typename V, typename S = double>
concept VectorSpace = Group<V> && Scalar<S> && requires(const V v, const S s) {
  { v * s } -> std::convertible_to<V>;
  { s * v } -> std::convertible_to<V>;
  { v / s } -> std::convertible_to<V>;
};

/**
 * @brief Algebra concept.
 * A Vector Space that is also a Ring.
 */
template <typename A, typename S = double>
concept Algebra = VectorSpace<A, S> && Ring<A>;

/**
 * @brief Normed Algebra concept.
 * An Algebra equipped with a norm function.
 */
template <typename T, typename S = double>
concept NormedAlgebra = Algebra<T, S> && requires(const T a) {
    { norm(a) } -> std::floating_point;
};

// Default norm for scalar types
template <Scalar T>
inline double norm(T x) {
    return std::abs(static_cast<double>(x));
}

#endif // ALGEBRA_CONCEPTS_HPP