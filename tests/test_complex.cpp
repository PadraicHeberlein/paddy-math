#include <iostream>
#include <cassert>
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
    
    // Using a small epsilon for floating point comparison is safer than ==
    if (result3.real() == -5.0 && result3.imag() == 10.0) {
        std::cout << "\nSUCCESS: Complex Multiplication is mathematically sound!" << std::endl;
    } else {
        std::cout << "\nFAILURE: Math mismatch. Check your operator* logic." << std::endl;
        return 1;
    }

    return 0;
}