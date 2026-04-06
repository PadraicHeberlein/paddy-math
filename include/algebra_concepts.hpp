#include <concepts>
#include <type_traits>

template <typename T>
concept Scalar = std::is_arithmetic_v<T>; // A basic rule: T must be a number

template <typename T>
concept Group = std::copyable<T> && requires(const T a, const T b) {
  { a + b } -> std::same_as<T>;
  { a - b } -> std::same_as<T>;     // Closure
  { T(0) } -> std::same_as<T>; // Identity
  { -a } -> std::same_as<T>;        // Inverse
  { a == b } -> std::same_as<bool>; // Equality
  { a != b } -> std::same_as<bool>; // Inequality
};

template <typename T>
concept Ring = Group<T> && requires(const T a, const T b) {
  { a * b } -> std::same_as<T>;    // Multiplication
  { T(1) } -> std::same_as<T>; // Unity
};

template <typename T>
concept Field = Ring<T> && requires(const T a, const T b) {
  { a / b } -> std::same_as<T>; // Division
};

template<typename T>
concept NormedAlgebra = Ring<T> && requires(T a) {
    { norm(a) } -> std::floating_point;  
};