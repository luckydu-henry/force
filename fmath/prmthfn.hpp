#pragma once
#include <bit>
#include <concepts>
#include "constants.hpp"

namespace force {
    template <std::floating_point Float>
    using rounding = typename std::conditional<std::is_same_v<Float, float>, int, long long>;

    template <std::floating_point Float>
    constexpr Float mod(Float x, Float y);

    ////////////////////////
    // Round functions
    ////////////////////////
    template <std::floating_point Float>
    [[nodiscard]] constexpr rounding<Float>::type trunc(Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr rounding<Float>::type ceil (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr rounding<Float>::type floor(Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr rounding<Float>::type round(Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr rounding<Float>::type bround(Float x);
    ////////////////////////
    // Arithmetic functions
    ////////////////////////
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float abs    (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float recp   (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float inv    (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float sqrt   (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float rsqrt  (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float cbrt   (Float x);
    ////////////////////////
    // Exp & log functions
    ////////////////////////
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float log    (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float log2   (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float log10  (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float exp    (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float exp2   (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float exp10  (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float loga   (Float a, Float b);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float pow    (Float x, Float n);
    //////////////////////////
    // Trignometric functions
    //////////////////////////
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float sin   (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float cos   (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float tan   (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float cot   (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float sec   (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float csc   (Float x);

    //////////////////////////////
    // Arc-Trignometric functions
    //////////////////////////////
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float asin(Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float acos(Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float atan(Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float acot(Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float asec(Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float acsc(Float x);
}
// Floating point 32-bit.
namespace force {
    // Using this makes my progress much easier.
    using std::bit_cast;

    template <>
    constexpr inline float mod(float x, float y) {
        float f = x / y;
        int   q = (int)f;
        float r = (f - q) * y;
        return r;
    }
    template <>
    constexpr inline int trunc(float x) {
        return static_cast<int>(x);
    }
    template <>
    constexpr inline int ceil(float x) {
        return static_cast<int>(x + 0.5f);
    }
    template <>
    constexpr inline int floor(float x) {
        return static_cast<int>(x - 0.5f);
    }
    template <>
    constexpr inline int round(float x) {
        int   i = bit_cast<int>(x);
        float s = bit_cast<float>((i & 0x8000'0000) | 0x3f80'0000);
        return static_cast<int>(x + s * 0.5f);
    }
    template <>
    constexpr inline int bround(float x) {
        int   k = ((int)x) & 1;
        int   i = bit_cast<int>(x);
        float s = bit_cast<float>((i & 0x8000'0000) | 0x3f80'0000);
        return static_cast<int>(x + s * ((float)k - 0.5f));
    }
    template <>
    constexpr inline float abs(float x) {
        int i = bit_cast<int>(x);
        i = i & 0x7fff'ffff;
        return  bit_cast<float>(i);
    }
    template <>
    constexpr inline float recp(float x) {
        return 1.f / x;
    }
    template <>
    constexpr inline float inv(float x) {
        int i = bit_cast<int>(x);
        i = i ^ 0x8000'0000;
        return  bit_cast<float>(i);
    }
    template <>
    constexpr inline float sqrt(float x) {
        float n = 0.5f * x;
        // Bit approximation
        int   i = bit_cast<int>(x);
        i = 0x1fbd'1df5 + (i >> 1);
        float y = bit_cast<float>(i);
        // Newton method approximation.
        y = 0.5f * y + n / y;
        y = 0.5f * y + n / y;

        return y;
    }
    template <>
    constexpr inline float rsqrt(float x) {
        float n = 0.5f * x;

        int   i = bit_cast<int>(x);
        i = 0x5f37'5a86 - (i >> 1); // wtf, this is better?
        float y = bit_cast<float>(i);

        y = y * (1.5f - n * y * y);
        y = y * (1.5f - n * y * y);

        return y;
    }
    template <>
    constexpr inline float cbrt(float x) {

        int   h = bit_cast<int>(x);
        float s = bit_cast<float>((h & 0x8000'0000) | 0x3f80'0000);

        float x0 = bit_cast<float>(h & 0x7fff'ffff);
        float n = 0.333333f * x0;

        int   i = bit_cast<int>(x0);
        i = 0x2a2e'5c2f + (i / 3);
        float y = bit_cast<float>(i);

        y = 0.666666f * y + n * (1.f / (y * y));
        y = 0.666666f * y + n * (1.f / (y * y));
        y = 0.666666f * y + n * (1.f / (y * y));

        return s * y;
    }
    template <>
    constexpr inline float log(float x) {
        constexpr float ln2 = 0.693'1471'8055'9945'3094'1723f;
        // Evil floating point bit hacking.
        int   i = bit_cast<int>(x);
        int   e = (i >> 23) - 0x7f;
        int   f = (((i << 1) & 0x00ff'ffff) >> 1) | 0x3f80'0000;
        float m = bit_cast<float>(f);

        // Approximation using talor expination.
        float t = (m - 1.f) / (m + 1.f);
        float t2 = t * t;
        float y = 2.f * (t + t2 * t * (0.333333f + t2 * (0.2f + t2 * (0.142857f + t2 * (0.111111f + t2 * 0.090909f)))));

        return ln2 * (float)e + y;
    }
    template <>
    constexpr inline float log2(float x) {
        constexpr float rln2 = 1.4'4269'5021'6293'3349'6093f;
        return rln2 * ::force::log(x);
    }
    template <>
    constexpr inline float log10(float x) {
        constexpr float rln10 = 0.4'3429'4481'9032'5182'7651f;
        return rln10 * ::force::log(x);
    }
    template <>
    constexpr inline float exp(float x) {
        constexpr float ln2 = 0.6'9314'7182'4645'9960'9375f; // actual ieee754 value of ln2.
        // Split exponent to interger part and floating point part.
        // Since x = i + f
        // 2^(x) = 2^(i + f) = 2^i * 2^f.
        float t = x / ln2;
        // Can be replaced by split but I don't do it here.
        int   i = (int)t;
        float f = t - (float)i;

        int   a = (i + 0x7f) << 23;
        float b = ln2 * f;      // 2^f = e^(ln2 * f) = e^b
        // Calculates e^b using talor expination since b : (-ln2, ln2)-
        // expination can be very approximate.
        float y = 1.f + b * (1.f + b * (0.5f + b * (0.166666f + b * (0.0416666f + b * (0.0083333f + b * 0.0013888f)))));
        return bit_cast<float>(a) * y;
    }
    template <>
    constexpr inline float exp2(float x) {
        constexpr float ln2 = 0.6'9314'7182'4645'9960'9375f;
        return ::force::exp(x * ln2);
    }
    template <>
    constexpr inline float exp10(float x) {
        constexpr float ln10 = 2.3'0258'5124'9694'8242'1875f;
        return ::force::exp(x * ln10);
    }
    // Log in any base.
    template <>
    constexpr inline float loga(float a, float b) {
        float lnb = ::force::log(b);
        float lna = ::force::log(a);
        return lnb / lna;
    }
    // Real exponent power function.
    template <>
    constexpr inline float pow(float a, float b) {
        float lna = ::force::log(a);
        return ::force::exp(b * lna);
    }

    template <>
    constexpr inline float sin(float x) {

        int   i = bit_cast<int>(x);
        int   g = (i & 0x8000'0000) | 0x3f80'0000;
        float s = bit_cast<float>(g);               // Original angle's sign.
        float k = bit_cast<float>(i & 0x7fff'ffff); // Absoulute value.
        float f = k / halfpi<float>;                // Fraction is the result.
        int   q = (int)f;                           // Quotient is int part of f.
        float r = (f - q) * halfpi<float>;          // Remainder is a the angle remainded.
        int   d = q & 3;                            // q mod 4.
        float a = 1.5f - (float)d;
        int   b = bit_cast<int>(a) & 0x7fff'ffff;   // Distance between 1.5 and 0, 1, 2, 3.
        int   e = (int)(bit_cast<float>(b) + 1.f);  // Translate sign's exponent
        float m = (r - (d & 1) * halfpi<float>);    // Translate angle.
        int   p = ((e & 1) << 31) | 0x3f80'0000;
        float t = bit_cast<float>(p) * m;           // theta is the angle translated between [-pi/2, pi/2].

        float h = t / 9;
        float h2 = h * h;
        float l = (((0.000027553f * h2 - 0.0001984f) * h2 + 0.0083333f) * h2 - 0.1666666f) * h * h2 + h;
        float j = l * (3.f - 4.f * l * l);
        float y = j * (3.f - 4.f * j * j);

        // Fix sign accoeding to original sign.
        return s * y;
    }
    template <>
    constexpr inline float cos(float x) {
        int   i = bit_cast<int>(x);
        float a = bit_cast<float>(i & 0x7fff'ffff); // Absolute.
        float f = x / pi<float>;
        int   q = (int)f;
        float r = (f - q) * pi<float>;
        int   d = q & 1;
        float s = bit_cast<float>((d << 31) | 0x3f80'0000);
        float t = s * r + (float)d * pi<float>;
        // 1/27x Talor expination approximation.
        float h = t / 27;
        float h2 = h * h;
        float l = (((0.000024797f * h2 - 0.001388888f) * h2 + 0.04166666f) * h2 - 0.49999999f) * h2 + 1.f;
        // 27x angle approximation.
        float b = l * (4.f * l * l - 3.f);
        float e = b * (4.f * b * b - 3.f);
        float y = e * (4.f * e * e - 3.f);

        return y;
    }
    template <>
    constexpr inline float tan(float x) {
        int   i = bit_cast<int>(x);
        int   g = (i & 0x8000'0000) | 0x3f80'0000;
        float s = bit_cast<float>(g);
        float v = bit_cast<float>(i & 0x7fffffff); // Absolute value.
        float f = x / halfpi<float>;
        int   q = (int)f;
        float r = (f - q) * halfpi<float>;
        int   d = q & 1;
        float t = r - (float)d * halfpi<float>;

        float h = t / 4;
        float h2 = h * h;
        float l = h * (1.f + h2 * (0.333333f + h2 * (0.1333333f + h2 * 0.05396825f)));
        float l2 = l * l;
        float y = (4 * l * (1 - l2)) / (1 - 6 * l2 + l2 * l2);

        return s * y;
    }
    template <>
    constexpr inline float cot(float x) {
        return 1.f / tan(x);
    }
    template <>
    constexpr inline float sec(float x) {
        return 1.f / cos(x);
    }
    template <>
    constexpr inline float csc(float x) {
        return 1.f / sin(x);
    }
}
