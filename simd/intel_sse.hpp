#pragma once
#include <concepts>
#include <xmmintrin.h>

namespace force::simd::sse {

    template <typename Ty>
    struct vec128 { using type = Ty; };
    // No simd optimized type can't even pass compile.
    template <>
    struct vec128<float> {
        using type = __m128;
        static constexpr unsigned int vsize = 4;
        static inline type    add_p(type a, type b) { return _mm_add_ps(a, b); }
        static inline type    sub_p(type a, type b) { return _mm_sub_ps(a, b); }
        static inline type    mul_p(type a, type b) { return _mm_mul_ps(a, b); }
        static inline type    div_p(type a, type b) { return _mm_div_ps(a, b); }
        static inline void    store_p(float* a, type v) { return _mm_store_ps(a, v); }

        template <unsigned int imm>
        static inline type    shuffle_p(type a, type b) { return _mm_shuffle_ps(a, b, imm); }

        static inline type    load_p(const float* v) { return _mm_load_ps(v); }
        static inline float   cvt_s(type v) { return _mm_cvtss_f32(v); }
        static inline type    cmpeq_p(type a, type b) { return _mm_cmpeq_ps(a, b); }
        static inline int     movemask_p(type a) { return _mm_movemask_ps(a); }
        static inline type    movehl_p(type a, type b) { return _mm_movehl_ps(a, b); }
        static inline type    set1_p(float a) { return _mm_set1_ps(a); }
    };


    constexpr unsigned int c_add = 0;
    constexpr unsigned int c_sub = 1;
    constexpr unsigned int c_mul = 3;
    constexpr unsigned int c_div = 4;


    // Result would be a +- b and stores it into destination
    // Cmd is which operation you want to use could only be c_add or c_sub.
    template <typename Ty, unsigned int Cmd, typename SimdType = vec128<Ty>::type>
    inline void a_vec128_add_sub(SimdType a, SimdType b, SimdType& dst) {
        if constexpr (Cmd == c_add)      dst = vec128<Ty>::add_p(a, b);
        else if constexpr (Cmd == c_sub) dst = vec128<Ty>::sub_p(a, b);
    }
    // Vector multiply or divide a scalar, result would be a */ s and stores in destination.
    // Cmd is which operation you want to use could only be c_mul or c_div.
    template <typename Ty, unsigned int Cmd, typename SimdType = vec128<Ty>::type>
    inline void a_vec128_mul_div_s(SimdType a, Ty s, SimdType& dst) {
        SimdType S = vec128<Ty>::set1_p(s);
        if constexpr (Cmd == c_mul)      dst = vec128<Ty>::mul_p(a, S);
        else if constexpr (Cmd == c_div) dst = vec128<Ty>::div_p(a, S);
    }
    template <typename Ty, typename SimdType = vec128<Ty>::type>
    inline void a_init_vec128(Ty* a, const Ty* b) {
        SimdType S = vec128<Ty>::load_p(b);
        vec128<Ty>::store_p(a, S);
    }
    template <typename Ty, typename SimdType = vec128<Ty>::type>
    inline const bool a_compare_vec128(SimdType a, SimdType b) {
        return _mm_movemask_ps(_mm_cmpeq_ps(a, b)) == 0xf;
    }
    template <typename Ty, typename SimdType = vec128<Ty>::type>
    inline Ty a_dot_product_vec128(SimdType a, SimdType b) {
        SimdType c = vec128<Ty>::mul_p(a, b);

        SimdType shuf = vec128<Ty>::shuffle_p<0xb1>(c, c);
        SimdType sums = vec128<Ty>::add_p(c, shuf);
        shuf = vec128<Ty>::movehl_p(shuf, sums);
        sums = vec128<Ty>::add_p(sums, shuf);
        return vec128<Ty>::cvt_s(sums);
    }
    // Complex number optimization
    // This is not generable.
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