#include "../../include/pm_math.h"
#include <math.h>

void complex_exp_taylor_kernel(double* r_out, double* i_out, 
                               double r_in, double i_in, 
                               int max_terms) {
    // e^z = 1 + z + z^2/2! + z^3/3! + ...
    // term_k = z^k / k! = term_{k-1} * z / k
    double sum_r = 1.0;
    double sum_i = 0.0;
    double term_r = 1.0;
    double term_i = 0.0;

    for (int k = 1; k <= max_terms; ++k) {
        // term = (term * z) / k
        double next_r = (term_r * r_in - term_i * i_in) / k;
        double next_i = (term_r * i_in + term_i * r_in) / k;
        
        term_r = next_r;
        term_i = next_i;
        
        sum_r += term_r;
        sum_i += term_i;
    }

    *r_out = sum_r;
    *i_out = sum_i;
}

void complex_exp_backend(double* r_out, double* i_out, 
                         double r_in, double i_in) {
    // 1. Determine scaling factor s = max(0, ceil(log2(|z|)))
    double norm_sq = r_in * r_in + i_in * i_in;
    double norm = sqrt(norm_sq);
    
    int s = 0;
    if (norm > 0.5) {
        s = (int)ceil(log2(norm / 0.5));
    }
    
    // 2. Scale z' = z / 2^s
    double factor = pow(2.0, s);
    double r_scaled = r_in / factor;
    double i_scaled = i_in / factor;
    
    // 3. Taylor series on scaled input
    double r_tmp, i_tmp;
    complex_exp_taylor_kernel(&r_tmp, &i_tmp, r_scaled, i_scaled, 50);
    
    // 4. Repeated squaring: z_res = (z_tmp)^(2^s)
    for (int j = 0; j < s; ++j) {
        double next_r = r_tmp * r_tmp - i_tmp * i_tmp;
        double next_i = 2.0 * r_tmp * i_tmp;
        r_tmp = next_r;
        i_tmp = next_i;
    }
    
    *r_out = r_tmp;
    *i_out = i_tmp;
}

#if defined(ARCH_ARM)
void complex_matrix_mul_2x2_neon(double* out, const double* a, const double* b);
#elif defined(ARCH_RISCV)
void complex_matrix_mul_2x2_riscv(double* out, const double* a, const double* b);
#elif defined(ARCH_X86)
void complex_matrix_mul_2x2_sse(double* out, const double* a, const double* b);
#elif defined(ARCH_MIPS)
void complex_matrix_mul_2x2_mips(double* out, const double* a, const double* b);
#endif

void pm_complex_matrix_mul_2x2(double* out, const double* a, const double* b) {
#if defined(ARCH_ARM)
    complex_matrix_mul_2x2_neon(out, a, b);
#elif defined(ARCH_RISCV)
    complex_matrix_mul_2x2_riscv(out, a, b);
#elif defined(ARCH_X86)
    complex_matrix_mul_2x2_sse(out, a, b);
#elif defined(ARCH_MIPS)
    complex_matrix_mul_2x2_mips(out, a, b);
#else
    // Universal C Fallback
    for (int i = 0; i < 8; ++i) {
        out[i] = a[i] + b[i]; // Placeholder operation matching the kernel logic
    }
#endif
}
