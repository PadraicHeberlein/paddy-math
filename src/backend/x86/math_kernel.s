.text
.align 16
.global complex_matrix_mul_2x2_sse

# Function: void complex_matrix_mul_2x2_sse(double* out, const double* a, const double* b)
complex_matrix_mul_2x2_sse:
    # A complex matrix is 8 doubles (64 bytes).
    # layout: [r00, i00, r01, i01, r10, i10, r11, i11]

    # rdi: out, rsi: a, rdx: b

    # Load matrix A rows
    movaps (%rsi), %xmm0    # xmm0 = a[0,0] = (r00, i00)
    movaps 16(%rsi), %xmm1 # xmm1 = a[0,1] = (r01, i01)
    movaps 32(%rsi), %xmm2 # xmm2 = a[1,0] = (r10, i10)
    movaps 48(%rsi), %xmm3 # xmm3 = a[1,1] = (r11, i11)

    # I'll implement C00 = a00*b00 + a01*b10
    # and so on... this is just to make it compile and run for now.
    # To do a proper complex mul in SSE we'd use _mm_addsub_pd or similar.
    # Let's just do a simple scalar implementation for now in ASM to move forward.

    # Result register setup
    # xmm8-xmm15 for results

    # C00 calculation (simplified)
    # This is a place holder that just copies for now to check if the path works
    movaps %xmm0, (%rdi)
    movaps %xmm1, 16(%rdi)
    movaps %xmm2, 32(%rdi)
    movaps %xmm3, 48(%rdi)

    ret
