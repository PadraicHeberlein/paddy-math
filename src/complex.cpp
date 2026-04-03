#include "complex.hpp"

Complex Complex::operator-() const { return {-r, -i}; }

Complex Complex::operator+(const Complex &other) const {
  return {r + other.r, i + other.i};
}

Complex Complex::operator-(const Complex &other) const {
  return {r - other.r, i - other.i};
}

bool Complex::operator==(const Complex &other) const {
  return r == other.r && i == other.i;
}

bool Complex::operator!=(const Complex &other) const {
  return !(*this == other);
}

Complex Complex::operator*(const Complex &other) const {
  return {r * other.r - i * other.i, r * other.i + i * other.r};
}

Complex Complex::operator/(const Complex &other) const {
  double den = other.r * other.r + other.i * other.i;
  return Complex((r * other.r + i * other.i) / den,
                 (i * other.r - r * other.i) / den);
}

Complex Complex::operator*(double scalar) const {
  return {r * scalar, i * scalar};
}

Complex Complex::operator/(double scalar) const {
  return {r / scalar, i / scalar};
}

std::ostream &operator<<(std::ostream &os, const Complex &c) {
  os << c.r << " + " << c.i << "i";
  return os;
}
