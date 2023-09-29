#pragma once
#include "constant.hpp"

namespace force::math {
    [[nodiscard]] float32_t mod(float32_t x, float32_t y);
    ///////////////////////
    // Rounding function
    ///////////////////////
    [[nodiscard]] int32_t   trunc  (float32_t x);
    [[nodiscard]] int32_t   ceil   (float32_t x);
    [[nodiscard]] int32_t   floor  (float32_t x);
    [[nodiscard]] int32_t   round  (float32_t x);
    [[nodiscard]] int32_t   bround (float32_t x); // banker round
    ////////////////////////
    // Arithmetic functions
    ////////////////////////
    [[nodiscard]] float32_t abs    (float32_t x);
    [[nodiscard]] int32_t   abs    (int32_t x);
    [[nodiscard]] float32_t recp   (float32_t x);
    [[nodiscard]] float32_t inv    (float32_t x);
    [[nodiscard]] float32_t sqrt   (float32_t x);
    [[nodiscard]] float32_t rsqrt  (float32_t x);
    [[nodiscard]] float32_t cbrt   (float32_t x);
    ////////////////////////
    // Exp & log functions
    ////////////////////////
    [[nodiscard]] float32_t      log    (float32_t x);
    [[nodiscard]] float32_t      log2   (float32_t x);
    [[nodiscard]] float32_t      log10  (float32_t x);
    [[nodiscard]] float32_t      exp    (float32_t x);
    [[nodiscard]] float32_t      exp2   (float32_t x);
    [[nodiscard]] float32_t      exp10  (float32_t x);
    [[nodiscard]] float32_t      loga   (float32_t a, float32_t b);
    [[nodiscard]] float32_t      pow    (float32_t x, float32_t n);
    //////////////////////////
    // Trignometric functions
    //////////////////////////
    [[nodiscard]] float32_t sin   (float32_t x);
    [[nodiscard]] float32_t cos   (float32_t x);
    [[nodiscard]] float32_t tan   (float32_t x);
    [[nodiscard]] float32_t cot   (float32_t x);
    [[nodiscard]] float32_t sec   (float32_t x);
    [[nodiscard]] float32_t csc   (float32_t x);
    //////////////////////////////
    // Arc-Trignometric functions
    //////////////////////////////
    [[nodiscard]] float32_t asin(float32_t x);
    [[nodiscard]] float32_t acos(float32_t x);
    [[nodiscard]] float32_t atan(float32_t x);
    [[nodiscard]] float32_t acot(float32_t x);
    [[nodiscard]] float32_t asec(float32_t x);
    [[nodiscard]] float32_t acsc(float32_t x);

    // Radian and angle conversion function
    template <typename Ty> Ty radian(Ty deg) {
        return deg * (static_cast<Ty>(180) / pi<Ty>);
    }
    template <typename Ty> Ty degree(Ty rad) {
        return rad * (pi<Ty> / static_cast<Ty>(180));
    }
}
