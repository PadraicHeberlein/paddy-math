#include "../../include/pm_math.h"
#include <math.h>
#include <string.h>

// Helper: 2x2 Complex Matrix Multiplication in C
static void complex_matrix_mul_2x2_c(double* res, const double* a, const double* b) {
    // res = a * b
    // A complex matrix is 8 doubles: [r00, i00, r01, i01, r10, i10, r11, i11]
    for (int r = 0; r < 2; ++r) {
        for (int c = 0; c < 2; ++c) {
            double sum_r = 0, sum_i = 0;
            for (int k = 0; k < 2; ++k) {
                // a[r,k] * b[k,c]
                double ar = a[(r * 2 + k) * 2];
                double ai = a[(r * 2 + k) * 2 + 1];
                double br = b[(k * 2 + c) * 2];
                double bi = b[(k * 2 + c) * 2 + 1];
                sum_r += (ar * br - ai * bi);
                sum_i += (ar * bi + ai * br);
            }
            res[(r * 2 + c) * 2] = sum_r;
            res[(r * 2 + c) * 2 + 1] = sum_i;
        }
    }
}

void complex_exp_taylor_kernel(double* r_out, double* i_out, 
                               double r_in, double i_in, 
                               int max_terms) {
    double sum_r = 1.0, sum_i = 0.0;
    double term_r = 1.0, term_i = 0.0;
    for (int k = 1; k <= max_terms; ++k) {
        double next_r = (term_r * r_in - term_i * i_in) / k;
        double next_i = (term_r * i_in + term_i * r_in) / k;
        term_r = next_r; term_i = next_i;
        sum_r += term_r; sum_i += term_i;
    }
    *r_out = sum_r; *i_out = sum_i;
}

void complex_exp_backend(double* r_out, double* i_out, double r_in, double i_in) {
    double norm = sqrt(r_in * r_in + i_in * i_in);
    int s = (norm > 0.5) ? (int)ceil(log2(norm / 0.5)) : 0;
    double factor = pow(2.0, s);
    double r_scaled = r_in / factor, i_scaled = i_in / factor;
    double r_tmp, i_tmp;
    complex_exp_taylor_kernel(&r_tmp, &i_tmp, r_scaled, i_scaled, 50);
    for (int j = 0; j < s; ++j) {
        double next_r = r_tmp * r_tmp - i_tmp * i_tmp;
        double next_i = 2.0 * r_tmp * i_tmp;
        r_tmp = next_r; i_tmp = next_i;
    }
    *r_out = r_tmp; *i_out = i_tmp;
}

void complex_matrix_exp_backend(double* out, const double* in) {
    // 1. Frobenius norm approx
    double norm_f = 0;
    for(int i=0; i<8; ++i) norm_f += in[i]*in[i];
    norm_f = sqrt(norm_f);
    
    int s = (norm_f > 0.5) ? (int)ceil(log2(norm_f / 0.5)) : 0;
    double factor = pow(2.0, s);
    
    // 2. Scale matrix
    double scaled[8];
    for(int i=0; i<8; ++i) scaled[i] = in[i] / factor;
    
    // 3. Taylor Series for scaled matrix: I + A + A^2/2! + ...
    double res[8] = {1,0, 0,0, 0,0, 1,0}; // Identity
    double term[8] = {1,0, 0,0, 0,0, 1,0};
    double next_term[8];
    
    for(int k=1; k<=50; ++k) {
        // next_term = (term * scaled) / k
        pm_complex_matrix_mul_2x2(next_term, term, scaled);
        for(int i=0; i<8; ++i) {
            term[i] = next_term[i] / k;
            res[i] += term[i];
        }
    }
    
    // 4. Square s times
    double sq[8];
    for(int j=0; j<s; ++j) {
        pm_complex_matrix_mul_2x2(sq, res, res);
        memcpy(res, sq, sizeof(double)*8);
    }
    memcpy(out, res, sizeof(double)*8);
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
    complex_matrix_mul_2x2_c(out, a, b);
#endif
}
