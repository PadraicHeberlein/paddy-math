#include <iostream>
#include <cassert>
#include <cmath>
#include "complex.hpp"

int main() {
    std::cout << "Testing Complex Multiplication..." << std::endl;

    // 1. Basic Multiplicative Identity Test: z * 1 = z
    Complex z1(3.0, 4.0);
    Complex identity = Complex::one();
    Complex result1 = z1 * identity;

    std::cout << "  Identity Test: (" << z1 << ") * (" << identity << ") = " << result1 << std::endl;
    assert(result1.real() == 3.0 && result1.imag() == 4.0);

    // 2. Zero Property Test: z * 0 = 0
    Complex zero = Complex::zero();
    Complex result2 = z1 * zero;

    std::cout << "  Zero Test: (" << z1 << ") * (" << zero << ") = " << result2 << std::endl;
    assert(result2.real() == 0.0 && result2.imag() == 0.0);

    // 3. Standard Multiplication: (a + bi)(c + di) = (ac - bd) + (ad + bc)i
    // Let (1 + 2i) * (3 + 4i)
    // Expected: (1*3 - 2*4) + (1*4 + 2*3)i = (3 - 8) + (4 + 6)i = -5 + 10i
    Complex a(1.0, 2.0);
    Complex b(3.0, 4.0);
    Complex result3 = a * b;

    std::cout << "  Standard Test: (" << a << ") * (" << b << ") = " << result3 << std::endl;
    
    std::cout << "\nTesting Complex Exponential (exp)..." << std::endl;

    // 1. exp(0) should be 1
    Complex e0 = exp(Complex(0.0, 0.0));
    std::cout << "  exp(0) = " << e0 << "   (Expected: 1 + 0i)" << std::endl;
    assert(std::abs(e0.real() - 1.0) < 1e-9 && std::abs(e0.imag()) < 1e-9);

    // 2. exp(i * pi) should be -1
    const double PI = std::acos(-1.0);
    Complex epi = exp(Complex(0.0, PI));
    std::cout << "  exp(i * pi) = " << epi << "   (Expected: -1 + 0i)" << std::endl;
    assert(std::abs(epi.real() + 1.0) < 1e-9 && std::abs(epi.imag()) < 1e-9);

    // 3. exp(1) should be e
    Complex e1 = exp(Complex(1.0, 0.0));
    std::cout << "  exp(1) = " << e1 << "   (Expected: approx 2.71828 + 0i)" << std::endl;
    assert(std::abs(e1.real() - std::exp(1.0)) < 1e-9 && std::abs(e1.imag()) < 1e-9);

    std::cout << "SUCCESS: Complex Exponential is mathematically sound!" << std::endl;

    return 0;
}
