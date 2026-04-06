.text
.align 16
.global complex_matrix_mul_2x2_sse

# Function: void complex_matrix_mul_2x2_sse(double* out, const double* a, const double* b)
# Layout: [r00, i00, r01, i01, r10, i10, r11, i11] (8 doubles = 64 bytes)
complex_matrix_mul_2x2_sse:
    push %rbp
    mov %rsp, %rbp
    # rdi: out, rsi: a, rdx: b

    # A[0,0] is (rsi), A[0,1] is 16(rsi), A[1,0] is 32(rsi), A[1,1] is 48(rsi)
    # B[0,0] is (rdx), B[0,1] is 16(rdx), B[1,0] is 32(rdx), B[1,1] is 48(rdx)

    # I'll use a slightly safer approach: load all elements into registers if possible
    # or just do term by term.

    # Helper macro for complex multiply: res = x * y
    # (xr*yr - xi*yi), (xr*yi + xi*yr)
    # xmm0: (xr, xi), xmm1: (yr, yi) -> xmm2: (res_r, res_i)
    .macro COMPLEX_MUL x, y, res, tmp1, tmp2
        movapd \x, \res          # res = (xr, xi)
        unpckhpd \res, \tmp1     # tmp1 = (xi, xi)
        unpcklpd \res, \res      # res = (xr, xr)
        
        movapd \y, \tmp2         # tmp2 = (yr, yi)
        mulpd \res, \tmp2        # tmp2 = (xr*yr, xr*yi)
        
        movapd \y, \res          # res = (yr, yi)
        shufpd $1, \res, \res    # res = (yi, yr)
        mulpd \tmp1, \res        # res = (xi*yi, xi*yr)
        
        # Now tmp2 is (xr*yr, xr*yi), res is (xi*yi, xi*yr)
        # We want (xr*yr - xi*yi, xr*yi + xi*yr)
        addsubpd \res, \tmp2     # wait, addsubhd is (a0-b0, a1+b1)
        # Yes! Exactly what we need.
        movapd \tmp2, \res
    .endm

    # C00 = A00*B00 + A01*B10
    movupd (%rsi), %xmm0     # A00
    movupd (%rdx), %xmm1     # B00
    COMPLEX_MUL %xmm0, %xmm1, %xmm8, %xmm14, %xmm15
    
    movupd 16(%rsi), %xmm0   # A01
    movupd 32(%rdx), %xmm1   # B10
    COMPLEX_MUL %xmm0, %xmm1, %xmm9, %xmm14, %xmm15
    addpd %xmm9, %xmm8       # C00 finished
    
    # C01 = A00*B01 + A01*B11
    movupd (%rsi), %xmm0     # A00
    movupd 16(%rdx), %xmm1    # B01
    COMPLEX_MUL %xmm0, %xmm1, %xmm10, %xmm14, %xmm15
    
    movupd 16(%rsi), %xmm0   # A01
    movupd 48(%rdx), %xmm1   # B11
    COMPLEX_MUL %xmm0, %xmm1, %xmm11, %xmm14, %xmm15
    addpd %xmm11, %xmm10      # C01 finished
    
    # C10 = A10*B00 + A11*B10
    movupd 32(%rsi), %xmm0   # A10
    movupd (%rdx), %xmm1     # B00
    COMPLEX_MUL %xmm0, %xmm1, %xmm12, %xmm14, %xmm15
    
    movupd 48(%rsi), %xmm0   # A11
    movupd 32(%rdx), %xmm1   # B10
    COMPLEX_MUL %xmm0, %xmm1, %xmm13, %xmm14, %xmm15
    addpd %xmm13, %xmm12      # C10 finished
    
    # C11 = A10*B01 + A11*B11
    movupd 32(%rsi), %xmm0   # A10
    movupd 16(%rdx), %xmm1    # B01
    COMPLEX_MUL %xmm0, %xmm1, %xmm14, %xmm15, %xmm11 # reused xmm11 as tmp
    
    movupd 48(%rsi), %xmm0   # A11
    movupd 48(%rdx), %xmm1   # B11
    COMPLEX_MUL %xmm0, %xmm1, %xmm15, %xmm11, %xmm9 # reused xmm9, xmm11
    addpd %xmm15, %xmm14      # C11 finished

    # Store results
    movupd %xmm8, (%rdi)
    movupd %xmm10, 16(%rdi)
    movupd %xmm12, 32(%rdi)
    movupd %xmm14, 48(%rdi)

    mov %rbp, %rsp
    pop %rbp
    ret
