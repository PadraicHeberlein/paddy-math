#include <concepts>
#include <type_traits>

template <typename T>
concept Scalar = std::is_arithmetic_v<T>; // A basic rule: T must be a number

template <typename T>
concept Group = std::copyable<T> && requires(const T a, const T b) {
  { a + b } -> std::same_as<T>;
  { a - b } -> std::same_as<T>;     // Closure
  { T::zero() } -> std::same_as<T>; // Identity
  { -a } -> std::same_as<T>;        // Inverse
  { a == b } -> std::same_as<bool>; // Equality
  { a != b } -> std::same_as<bool>; // Inequality
};