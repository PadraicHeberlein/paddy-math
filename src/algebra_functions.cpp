#include "../include/algebra_functions.hpp"

template <Algebra T> 
T exp_taylor(const T &x, int terms) {
  T res = T(1);
  T current_term = T(1);

  for (int i = 1; i <= terms; ++i) {
    current_term = (current_term * x) * (1.0 / i);
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
