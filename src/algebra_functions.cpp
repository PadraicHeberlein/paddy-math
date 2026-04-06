#include "../include/algebra_functions.hpp"

template <Algebra T> 
T exp_taylor(const T &x, int terms) {
  auto get_identity = [&]() {
    if constexpr (is_matrix<T>::value) {
      return T::identity(x.get_rows());
    } else {
      return T(1);
    }
  };

  T res = get_identity();
  T current_term = get_identity();

  for (int i = 1; i <= terms; ++i) {
    // Multiply by x then scale by 1/i (scalar), avoiding Matrix/Matrix division
    current_term = (current_term * x) * (1.0 / static_cast<double>(i));
    res = res + current_term;
  }

  return res;
}

template <Algebra T> 
T factorial(int n) {
  T res = T(1);
  for (int i = 1; i <= n; ++i) {
    res = res * T(i);
  }
  return res;
}

template <Algebra T>
requires (!std::is_same_v<T, Complex> && !is_matrix<T>::value)
T exp_generic(const T &x) {
  return exp_taylor(x);
}

// Explicit Template Instantiation
template double exp_taylor<double>(const double &, int);
template Complex exp_taylor<Complex>(const Complex &, int);
template Matrix<double> exp_taylor<Matrix<double>>(const Matrix<double> &, int);
template Matrix<Complex> exp_taylor<Matrix<Complex>>(const Matrix<Complex> &, int);

template double factorial<double>(int);
template Complex factorial<Complex>(int);
template Matrix<double> factorial<Matrix<double>>(int);
template Matrix<Complex> factorial<Matrix<Complex>>(int);

template double exp_generic<double>(const double &);
