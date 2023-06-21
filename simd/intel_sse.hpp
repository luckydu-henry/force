#pragma once
#include <concepts>
#include <xmmintrin.h>

namespace force::simd {

    constexpr unsigned int c_add = 0;
    constexpr unsigned int c_sub = 1;
    constexpr unsigned int c_mul = 3;
    constexpr unsigned int c_div = 4;

    // Result would be a +- b and stores it into destination
    // Cmd is which operation you want to use could only be c_add or c_sub.
    template <unsigned int Cmd>
    inline void a_vec4f_add_sub(const float* a, const float* b, float* dst) {
        __m128 A = _mm_load_ps(a);
        __m128 B = _mm_load_ps(b);
        __m128 C;
        if constexpr (Cmd == c_add)      C = _mm_add_ps(A, B);
        else if constexpr (Cmd == c_sub) C = _mm_sub_ps(A, B);
        _mm_store_ps(dst, C);
    }
    // Vector multiply or divide a scalar, result would be a */ s and stores in destination.
    // Cmd is which operation you want to use could only be c_mul or c_div.
    template <unsigned int Cmd>
    inline void a_vec4f_mul_div_s(const float* a, float s, float* dst) {
        __m128 A = _mm_load_ps(a);
        __m128 S = _mm_set_ps1(s);
        __m128 C;
        if constexpr (Cmd == c_mul)      C = _mm_mul_ps(A, S);
        else if constexpr (Cmd == c_div) C = _mm_div_ps(A, S);
        _mm_store_ps(dst, C);
    }
    inline void a_init_vec4f(float* a, const float* b) {
        __m128 S = _mm_load_ps(b);
        _mm_store_ps(a, S);
    }
    inline const bool a_compare_vec4f(const float* a, const float* b) {
        __m128 A = _mm_load_ps(a);
        __m128 B = _mm_load_ps(b);

        return _mm_movemask_ps(_mm_cmpeq_ps(A, B)) == 0xf;
    }
    inline void a_complex_mul(float a, float b, float c, float d, float* dst) {
        // Loading values into the 128 bit register
        // __mm_set_ps accepts the parameters in reverse order
        __m128 data = _mm_set_ps(d, c, b, a);

        __m128 aabb = _mm_shuffle_ps(data, data, 0x50);
        __m128 cdcd = _mm_shuffle_ps(data, data, 0xee);

        // Multiplication is done as a single operation
        __m128 mulres = _mm_mul_ps(aabb, cdcd);

        // Retrieving the results
        _mm_storeu_ps(dst, mulres);

        dst[0] -= dst[3];
        dst[1] += dst[2];
        dst[2] = dst[3] = 0.f;
    }

    inline void a_complex_div(float a, float b, float c, float d, float* dst) {
        // Loading values into the 128 bit register
        // __mm_set_ps accepts the parameters in reverse order
        __m128 data = _mm_set_ps(d, c, b, a);

        __m128 bbaa = _mm_shuffle_ps(data, data, 0x50);
        __m128 dcdc = _mm_shuffle_ps(data, data, 0xee);
        __m128 cccc = _mm_shuffle_ps(data, data, 0xaa);
        __m128 dddd = _mm_shuffle_ps(data, data, 0xff);

        // Multiplication is done as a single operation
        __m128 mulres = _mm_mul_ps(bbaa, dcdc);
        __m128 csquar = _mm_mul_ps(cccc, cccc);
        __m128 dsquar = _mm_mul_ps(dddd, dddd);
        __m128 coeffi = _mm_add_ps(csquar, dsquar);

        // Retrieving the results
        _mm_storeu_ps(dst, mulres);

        dst[0] = dst[0] + dst[3];
        dst[1] = dst[2] - dst[1];
        dst[2] = dst[3] = 0.f;

        __m128 x = _mm_load_ps(dst);
        __m128 r = _mm_div_ps(x, coeffi);

        _mm_storeu_ps(dst, r);
    }
}