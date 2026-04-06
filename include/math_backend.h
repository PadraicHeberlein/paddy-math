#ifndef MATH_BACKEND_H
#define MATH_BACKEND_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @brief Core Taylor series kernel for complex exponential.
 * This is designed to be replaced by ARM NEON assembly.
 */
void complex_exp_taylor_kernel(double* r_out, double* i_out, 
                               double r_in, double i_in, 
                               int max_terms);

/**
 * @brief Scaling and squaring wrapper for the exponential function.
 * Ensures the Taylor series converges quickly by scaling the input.
 */
void complex_exp_backend(double* r_out, double* i_out, 
                         double r_in, double i_in);

#ifdef __cplusplus
}
#endif

#endif // MATH_BACKEND_H
