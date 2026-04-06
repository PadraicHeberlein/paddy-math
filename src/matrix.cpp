#include "../include/matrix.hpp"
#include "../include/complex.hpp"

// Explicit Template Instantiation
// This compiles the code for common types into a single object file, 
// reducing the overall project compilation time.

template class Matrix<double>;
template class Matrix<Complex>;

template Matrix<double> exp(const Matrix<double>& A, int terms);
template Matrix<Complex> exp(const Matrix<Complex>& A, int terms);
