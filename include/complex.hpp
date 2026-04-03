class Complex {
public:
  double r, i;

  // To satisfy { a + b } -> T
  Complex operator+(const Complex &other) const {
    return {r + other.r, i + other.i};
  }

  // To satisfy { -a } -> T
  Complex operator-() const { return {-r, -i}; }

  // To satisfy { T::zero() } -> T
  static Complex zero() { return {0.0, 0.0}; }
};