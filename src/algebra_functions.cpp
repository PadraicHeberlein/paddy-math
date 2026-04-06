#include "../include/algebra_functions.hpp"
#include "../include/pm_math.h"

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
T sin_taylor(const T &x, int terms) {
  T res = x;
  T current_term = x;
  T x_squared = x * x;

  for (int i = 3; i <= terms; i += 2) {
    // (-1)^((i-1)/2) * x^i / i!
    // current_term = previous_term * x^2 / (i * (i-1)) * -1
    current_term = (current_term * x_squared) * (-1.0 / (static_cast<double>(i) * (i - 1)));
    res = res + current_term;
  }

  return res;
}

template <Algebra T> 
T cos_taylor(const T &x, int terms) {
  auto get_identity = [&]() {
    if constexpr (is_matrix<T>::value) {
      return T::identity(x.get_rows());
    } else {
      return T(1);
    }
  };

  T res = get_identity();
  T current_term = get_identity();
  T x_squared = x * x;

  for (int i = 2; i <= terms; i += 2) {
    // (-1)^(i/2) * x^i / i!
    current_term = (current_term * x_squared) * (-1.0 / (static_cast<double>(i) * (i - 1)));
    res = res + current_term;
  }

  return res;
}

template <>
Complex exp_taylor<Complex>(const Complex &z, int) {
    double r, i;
    complex_exp_backend(&r, &i, z.real(), z.imag());
    return Complex(r, i);
}

template <>
Matrix<double> exp_taylor<Matrix<double>>(const Matrix<double>& m, int) {
    double in[8] = {m(0,0), 0, m(0,1), 0, m(1,0), 0, m(1,1), 0};
    double out[8];
    complex_matrix_exp_backend(out, in);
    Matrix<double> res(2, 2);
    res(0,0) = out[0]; res(0,1) = out[2];
    res(1,0) = out[4]; res(1,1) = out[6];
    return res;
}

template <>
Matrix<Complex> exp_taylor<Matrix<Complex>>(const Matrix<Complex>& m, int) {
    double in[8] = {m(0,0).real(), m(0,0).imag(), m(0,1).real(), m(0,1).imag(),
                     m(1,0).real(), m(1,0).imag(), m(1,1).real(), m(1,1).imag()};
    double out[8];
    complex_matrix_exp_backend(out, in);
    Matrix<Complex> res(2, 2);
    res(0,0) = {out[0], out[1]}; res(0,1) = {out[2], out[3]};
    res(1,0) = {out[4], out[5]}; res(1,1) = {out[6], out[7]};
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

template double factorial<double>(int);
template Complex factorial<Complex>(int);
template Matrix<double> factorial<Matrix<double>>(int);
template Matrix<Complex> factorial<Matrix<Complex>>(int);

template double exp_generic<double>(const double &);
