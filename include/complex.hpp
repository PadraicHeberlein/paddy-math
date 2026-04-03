#ifndef COMPLEX_HPP
#define COMPLEX_HPP

class Complex {
public:
  double a, b;

  Complex() : a(0.0), b(0.0) {}
  Complex(double a, double b) : a(a), b(b) {}
  Complex(double a) : a(a), b(0.0) {}
  Complex(const Complex &other) : a(other.a), b(other.b) {}
  Complex(Complex &&other) : a(other.a), b(other.b) {}

  double real() const { return a; }
  double imag() const { return b; }

  static Complex zero() { return {0.0, 0.0}; }
  static Complex one() { return {1.0, 0.0}; }

  Complex operator-() const;

  Complex operator+(const Complex &other) const;
  Complex operator-(const Complex &other) const;

  bool operator==(const Complex &other) const;
  bool operator!=(const Complex &other) const;

  Complex operator*(const Complex &other) const;
  Complex operator/(const Complex &other) const;

  Complex operator*(double scalar) const;
  Complex operator/(double scalar) const;
};

#endif // COMPLEX_HPP