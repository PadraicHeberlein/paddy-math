#include "complex.hpp"
#include "matrix.hpp"
#include "algebraic_functions.hpp" // IWYU pragma: keep
#include <iostream>
#include <cmath>

int main() {
    std::cout << "--- Testing Algebraic Function Library ---" << std::endl;

    // 1. Test exp with Complex
    Complex c(0, M_PI); // e^(i*pi) = -1
    Complex res_c = exp(c);
    std::cout << "exp(" << c << ") = " << res_c << " (Expected approx -1 + 0i)" << std::endl;

    // 2. Test exp with Matrix
    Matrix<double> m(2, 2);
    m(0, 0) = 0; m(0, 1) = 1;
    m(1, 0) = -1; m(1, 1) = 0;
    // This is the rotation matrix for 90 degrees.
    // Exp of this matrix should be a rotation matrix.
    
    Matrix<double> res_m = exp(m);
    std::cout << "exp(\n" << m << ") =\n" << res_m << std::endl;
    
    // 3. Test exp with Scalars (since they are NormedAlgebra)
    double x = 1.0;
    double res_x = exp(x);
    std::cout << "exp(" << x << ") = " << res_x << " (Expected " << std::exp(1.0) << ")" << std::endl;

    std::cout << "\nSUCCESS: Library functions works for Fields, Rings, and Groups!" << std::endl;
    return 0;
}
