/* DEMO: using fixed32 to do FFT */
// ref: https://github.com/CW-B-W/DIC-Frequency_Analysis_System/blob/master/cpp_verification/src/FFT_std_complex.cpp
// verification: https://ideone.com/1euM3Q
#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "fixed32.h"

typedef struct {
    fixed32 real;
    fixed32 imag; 
} complex_fixed32;

complex_fixed32 complex_fixed32_neg(complex_fixed32 x)
{
    return (complex_fixed32) {.real = fixed32_neg(x.real), .imag = fixed32_neg(x.imag)};
}

complex_fixed32 complex_fixed32_add(complex_fixed32 x, complex_fixed32 y)
{
    complex_fixed32 z;
    z.real = fixed32_add(x.real, y.real);
    z.imag = fixed32_add(x.imag, y.imag);
    return z;
}

complex_fixed32 complex_fixed32_mul(complex_fixed32 x, complex_fixed32 y)
{
    // (a+bi) * (c+di) = (ac-bd) + i(bc+ad)
    complex_fixed32 z;
    fixed32 ac = fixed32_mul(x.real, y.real);
    fixed32 bd = fixed32_mul(x.imag, y.imag);
    fixed32 bc = fixed32_mul(x.imag, y.real);
    fixed32 ad = fixed32_mul(x.real, y.imag);
    z.real = fixed32_add(ac, fixed32_neg(bd));
    z.imag = fixed32_add(bc, ad);
    return z;
}

complex_fixed32 complex_fixed32_polar(fixed32 r, fixed32 theta)
{
    float r_f = fixed32_tofloat(r);
    float theta_f = fixed32_tofloat(theta);
    float x = r_f * cos(theta_f);
    float y = r_f * sin(theta_f);

    complex_fixed32 z;
    z.real = fixed32_fromfloat(x);
    z.imag = fixed32_fromfloat(y);
    return z;
}

void fft_recursive(complex_fixed32 x[], int x_len)
{
    if (x_len <= 1)
        return;

    int N = x_len;
    int M = x_len/2;

    complex_fixed32 x_even[M];
    complex_fixed32 x_odd[M];

    for (int i = 0; i < M; ++i) {
        x_even[i] = x[i*2];
        x_odd[i]  = x[i*2+1];
    }
    
    fft_recursive(x_even, M);
    fft_recursive(x_odd, M);

    complex_fixed32 w = (complex_fixed32){.real = fixed32_fromfloat(1.0f), .imag = 0};
    complex_fixed32 w_rotate = complex_fixed32_polar(fixed32_fromfloat(1.0f), fixed32_fromfloat(-M_PI / M));
    for (int i = 0; i < M; ++i) {
        x[i]   = complex_fixed32_add(x_even[i], complex_fixed32_mul(w, x_odd[i]));
        x[i+M] = complex_fixed32_add(x_even[i], complex_fixed32_neg(complex_fixed32_mul(w, x_odd[i])));
        // x[i]   = x_even[i] + W * x_odd[i];
        // x[i+M] = x_even[i] - W * x_odd[i];

        w = complex_fixed32_mul(w, w_rotate);
        // w = w * polar(1.0, -M_PI / M);
    }
}

void fft(complex_fixed32 x[], int x_len)
{
    assert((x_len != 0) && ((x_len & (x_len-1)) == 0)); // x_len is power of 2

    fft_recursive(x, x_len);
}

int main()
{
    int N = 32;
    complex_fixed32 x[N];
    for (int i = 0; i < N; ++i) {
        x[i].real = fixed32_fromfloat(sin(M_PI * i / N));
        x[i].imag = 0;
    }

    fft(x, N);

    for (int i = 0; i < N;) {
        for (int j = 0; j < 4; ++j){
            printf("(%f, %f), ", fixed32_tofloat(x[i].real), fixed32_tofloat(x[i].imag));
            i++;
        }
        puts("");
    }

    return 0;
}