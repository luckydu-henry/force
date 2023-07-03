#pragma once
#include <concepts>
#include <limits>
#include "prmthfn.hpp"
#include "simd.hpp"

#if defined _WIN32
#pragma warning(disable:4455)
#endif 

namespace force {

    template <std::floating_point Real>
    class complex;

    template <>
    class complex<float> {
    public:
        using value_type = float;
        union {
            // This part is use to align data and use simd.
            float _VAL[2]; // Don't touch this outside in any purpose.
            // Two varibles to store the data
            struct { float real, imag; };
        };

        constexpr complex(float a)          : real(a) ,imag(0.f){}
        constexpr complex(float a, float b) : real(a), imag(b)  {}
        complex(const complex& right) { std::memcpy(_VAL, right._VAL, 2 * sizeof(float)); }
        complex(complex&& right)      { std::memcpy(_VAL, right._VAL, 2 * sizeof(float)); }

        complex& operator= (const complex& right) { std::memcpy(_VAL, right._VAL, 2 * sizeof(float)); return *this; }
        // All loops will be optimized when turn on release mode.
        complex& operator+=(const complex& right) { for (int i = 0; i < 2; ++i) _VAL[i] += right._VAL[i]; return *this; }
        complex& operator-=(const complex& right) { for (int i = 0; i < 2; ++i) _VAL[i] -= right._VAL[i]; return *this; }
        complex& operator*=(float k)              { for (int i = 0; i < 2; ++i) _VAL[i] *= k;             return *this; }
        complex& operator/=(float k)              { for (int i = 0; i < 2; ++i) _VAL[i] /= k;             return *this; }
        complex& operator*=(const complex& z) {
            float tr = real * z.real - imag * z.imag;
            float ti = real * z.imag + imag * z.real;
            real = tr; imag = ti;
            return *this;
        }
        constexpr complex& operator/=(const complex& z) {
            float d = z.real * z.real + z.imag * z.imag;
            float tr = (real * z.real + imag * z.imag) / d;
            float ti = (imag * z.real - real * z.imag) / d;
            real = tr; imag = ti;
            return *this;
        }

        ~complex() = default;
    };

    template <typename Ty>
    [[nodiscard]] constexpr complex<Ty> operator+(const complex<Ty>& a, const complex<Ty>& b) {
        complex<Ty> tmp(a);
        tmp += b;
        return tmp;
    }
    template <typename Ty>
        [[nodiscard]] constexpr complex<Ty> operator+(const complex<Ty>& a, const Ty& b) {
        complex<Ty> tmp(a);
        tmp += b;
        return tmp;
    }
    template <typename Ty>
        [[nodiscard]] constexpr complex<Ty> operator+(const Ty& a, const complex<Ty>& b) {
        complex<Ty> tmp(b);
        tmp += a;
        return tmp;
    }
    template <typename Ty>
        [[nodiscard]] constexpr complex<Ty> operator-(const complex<Ty>& a, const complex<Ty>& b) {
        complex<Ty> tmp(a);
        tmp -= b;
        return tmp;
    }
    template <typename Ty>
        [[nodiscard]] constexpr complex<Ty> operator-(const complex<Ty>& a, const Ty& b) {
        complex<Ty> tmp(a);
        tmp -= b;
        return tmp;
    }
    template <typename Ty>
        [[nodiscard]] constexpr complex<Ty> operator-(const Ty& a, const complex<Ty>& b) {
        complex<Ty> tmp(a);
        tmp -= b;
        return tmp;
    }
    template <typename Ty>
        [[nodiscard]] constexpr complex<Ty> operator*(const complex<Ty>& a, const complex<Ty>& b) {
        complex<Ty> tmp(a);
        tmp *= b;
        return tmp;
    }
    template <typename Ty>
        [[nodiscard]] constexpr complex<Ty> operator*(const complex<Ty>& a, const Ty& b) {
        complex<Ty> tmp(a);
        tmp *= b;
        return tmp;
    }
    template <typename Ty>
        [[nodiscard]] constexpr complex<Ty> operator*(const Ty& a, const complex<Ty>& b) {
        complex<Ty> tmp(b);
        tmp *= a;
        return tmp;
    }
    template <typename Ty>
        [[nodiscard]] constexpr complex<Ty> operator/(const complex<Ty>& a, const complex<Ty>& b) {
        complex<Ty> tmp(a);
        tmp /= b;
        return tmp;
    }
    template <typename Ty>
        [[nodiscard]] constexpr complex<Ty> operator/(const complex<Ty>& a, const Ty& b) {
        complex<Ty> tmp(a);
        tmp /= b;
        return tmp;
    }
    template <typename Ty>
        [[nodiscard]] constexpr complex<Ty> operator/(const Ty& a, const complex<Ty>& b) {
        complex<Ty> tmp(a);
        tmp /= b;
        return tmp;
    }
    template <typename Ty>
        [[nodiscard]] constexpr complex<Ty> operator+(const complex<Ty>& a) {
        return a;
    }
    template <typename Ty>
        [[nodiscard]] constexpr complex<Ty> operator-(const complex<Ty>& a) {
        return complex<Ty>(-a.real, -a.imag);
    }
    template <typename Ty>
        [[nodiscard]] constexpr bool operator==(const complex<Ty>& a, const complex<Ty>& b) {
        return ::force::abs(a.real - b.real) < std::numeric_limits<float>::epsilon() && ::force::abs(a.imag - b.imag) < std::numeric_limits<float>::epsilon();
    }
    template <typename Ty>
        [[nodiscard]] constexpr bool operator==(const complex<Ty>& a, const Ty& b) {
        return ::force::abs(a.real - b) < std::numeric_limits<float>::epsilon() && ::force::abs(a.imag) < std::numeric_limits<float>::epsilon();
    }

    //////////////////////////////////
    // Complex type_traits and concept
    //////////////////////////////////
    template <typename Ty>
    struct complex_traits : std::false_type {};
    template <>
    struct complex_traits<complex<float>> : std::true_type {};
    template <>
    struct complex_traits<complex<double>> : std::true_type {};

    template <typename Ty>
    concept complex_number = complex_traits<Ty>::value;

    /////////////////////
    // Complex functions 
    /////////////////////

    template <complex_number Comp>
    Comp conjucate(const Comp& z) {
        return Comp{ z.real, ::force::inv(z.imag) };
    }
    template <complex_number Comp>
    Comp inv(const Comp& z) {
        return Comp{ ::force::inv(z.real), ::force::inv(z.imag) };
    }
    template <complex_number Comp>
    Comp::value_type abs(const Comp& z) {
        return ::force::sqrt(z.real * z.real + z.imag * z.imag);
    }

    namespace complex_literals {
        constexpr complex<float>  operator""fi(long double x) {
            return complex<float>(0.0f, static_cast<float>(x));
        }
        constexpr complex<float>  operator""fi(unsigned long long x) {
            return complex<float>(0.0f, static_cast<float>(x));
        }
    }

    using complexf = complex<float>;
}