#include "algebra_concepts.hpp"
#include "complex.hpp"
#include "matrix.hpp"
#include <iostream>

static_assert(Group<Complex>, "Complex class must satisfy the Group concept requirements!");
static_assert(Ring<Complex>, "Complex class must satisfy the Ring concept requirements!");
static_assert(Field<Complex>, "Complex class must satisfy the Field concept requirements!");

static_assert(VectorSpace<Complex>, "Complex must satisfy VectorSpace requirements!");
static_assert(NormedAlgebra<Complex>, "Complex must satisfy NormedAlgebra requirements!");

static_assert(Group<Matrix<double>>, "Matrix<double> class must satisfy the Group concept requirements!");
static_assert(Ring<Matrix<double>>, "Matrix<double> class must satisfy the Ring concept requirements!");
static_assert(VectorSpace<Matrix<double>>, "Matrix<double> must satisfy VectorSpace requirements!");
static_assert(NormedAlgebra<Matrix<double>>, "Matrix<double> must satisfy NormedAlgebra requirements!");
static_assert(!Field<Matrix<double>>, "Matrix<double> class does not satisfy the Field concept requirements!");

int main() {
    std::cout << "SUCCESS: All compile-time algebraic checks passed!" << std::endl;
    return 0;
}
