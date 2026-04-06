#ifndef PM_MATH_H
#define PM_MATH_H

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

/**
 * @brief Matrix exponential for 2x2 complex matrix.
 * Uses scaling and squaring for numerical stability.
 */
void complex_matrix_exp_backend(double* out, const double* in);

/**
 * @brief 2x2 complex matrix multiply.
 * Dispatched to optimized assembly (ARM NEON or RISC-V) based on platform.
 */
void pm_complex_matrix_mul_2x2(double* out, const double* a, const double* b);

#ifdef __cplusplus
}
#endif

#endif // PM_MATH_H
