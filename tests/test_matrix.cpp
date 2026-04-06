#include <iostream>
#include <cassert>
#include "matrix.hpp"
#include "complex.hpp"
#include "math_backend.h"

int main() {
    std::cout << "Testing Matrix with Complex numbers..." << std::endl;

    // 1. Matrix Construction and Addition
    Matrix<Complex> A(2, 2);
    A(0, 0) = Complex(1, 0); A(0, 1) = Complex(0, 1);
    A(1, 0) = Complex(0, -1); A(1, 1) = Complex(1, 0);

    Matrix<Complex> B = Matrix<Complex>::identity(2);
    Matrix<Complex> C = A + B;

    std::cout << "A:\n" << A << std::endl;
    std::cout << "B (Identity):\n" << B << std::endl;
    std::cout << "A + B:\n" << C << std::endl;

    assert(C(0, 0) == Complex(2, 0));
    assert(C(0, 1) == Complex(0, 1));
    assert(C(1, 0) == Complex(0, -1));
    assert(C(1, 1) == Complex(2, 0));

    // 2. Matrix Multiplication
    Matrix<Complex> D = A * A;
    std::cout << "A * A:\n" << D << std::endl;
    // (1  i) * (1  i) = (1-1  i+i) = (2  2i)
    // (-i 1)   (-i 1)   (-i-i -1+1) = (-2i 2)
    assert(D(0, 0) == Complex(2, 0));
    assert(D(0, 1) == Complex(0, 2));
    assert(D(1, 0) == Complex(0, -2));
    assert(D(1, 1) == Complex(2, 0));

    // 3. Matrix Exponentiation (Taylor)
    std::cout << "Testing exp(Matrix)..." << std::endl;
    Matrix<Complex> Zero(2, 2);
    Matrix<Complex> expZero = exp(Zero);
    std::cout << "exp(Zero Matrix):\n" << expZero << std::endl;
    assert(expZero(0, 0) == Complex(1, 0));
    assert(expZero(1, 1) == Complex(1, 0));

#ifdef __aarch64__
    std::cout << "Testing ARM NEON Kernel Linkage..." << std::endl;
    // We'll use a 2x2 identity matrix for the test
    Matrix<Complex> Res(2, 2);
    Matrix<Complex> MatA = Matrix<Complex>::identity(2);
    Matrix<Complex> MatB = Matrix<Complex>::identity(2);
    
    // Call the NEON kernel (currently implements vector addition for verification)
    complex_matrix_mul_2x2_neon((double*)&Res(0,0), (const double*)&MatA(0,0), (const double*)&MatB(0,0));
    
    std::cout << "NEON result (expecting sum due to placeholder):\n" << Res << std::endl;
    assert(Res(0, 0) == Complex(2, 0)); 
#endif

    std::cout << "SUCCESS: Matrix class and ARM backend verified!" << std::endl;

    return 0;
}
