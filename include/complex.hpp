#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <ostream>

class Complex {
private:
  double r, i;

public:
  Complex() : r(0.0), i(0.0) {}
  Complex(double r, double i) : r(r), i(i) {}
  Complex(double r) : r(r), i(0.0) {}
  Complex(const Complex &other) = default;
  Complex(Complex &&other) = default;

  double real() const { return r; }
  double imag() const { return i; }

  static Complex zero() { return {0.0, 0.0}; }
  static Complex one() { return {1.0, 0.0}; }

  Complex &operator=(const Complex &other) = default;
  Complex &operator=(Complex &&other) = default;

  Complex operator-() const;

  Complex operator+(const Complex &other) const;
  Complex operator-(const Complex &other) const;

  bool operator==(const Complex &other) const;
  bool operator!=(const Complex &other) const;

  Complex operator*(const Complex &other) const;
  Complex operator/(const Complex &other) const;

  Complex operator*(double scalar) const;
  Complex operator/(double scalar) const;

  friend inline Complex operator*(double scalar, const Complex &c) {
    return c * scalar;
  }
  friend std::ostream &operator<<(std::ostream &os, const Complex &c);
};

#endif // COMPLEX_HPP