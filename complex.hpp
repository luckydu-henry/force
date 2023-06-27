#pragma once
#include <concepts>
#include "prmthfn.hpp"
#include "simd.hpp"

#if defined _WIN32
#pragma warning(disable:4455)
#endif 

namespace force {
    ////////////////
    // Complex type.
    ////////////////
    template <std::floating_point Float>
    class alignas(16) complex {}; // Not support for other types.

    template <>
    class complex<float> {
        union {
            alignas(16) float m_val[4];
#if defined FORCE_USE_SIMD_COMPLEX
            alignas(16) simd::vec128<float>::type m_vdata;
#endif
        };
    public:

        constexpr explicit complex()                  { m_val[0] = 0.f; m_val[1] = 0.f; }
        constexpr explicit complex(float r)           { m_val[0] = r;   m_val[1] = 0.f; }
        constexpr explicit complex(float r, float i)  { m_val[0] = r;   m_val[1] = i; }

        complex(const complex& z)  {  m_val[0] = z.m_val[0]; m_val[1] = z.m_val[1]; }

        constexpr const float real() const  { return m_val[0]; }
        constexpr const float imag() const  { return m_val[1]; }
        constexpr void        real(float r) { m_val[0] = r; }
        constexpr void        imag(float i) { m_val[1] = i; }

        constexpr complex& operator=(float z)   { m_val[0] = z; m_val[1] = 0; return *this;}
        constexpr complex& operator=(const complex& z) { m_val[0] = z.m_val[0]; m_val[1] = z.m_val[1]; return *this;}
        constexpr complex& operator+=(float z)  { m_val[0] += z; return *this;}
        constexpr complex& operator-=(float z)  { m_val[0] -= z; return *this;}
        // simd activate
#if defined FORCE_USE_SIMD_COMPLEX
        complex& operator+=(const complex& z) { simd::a_vec128_add_sub<float, simd::c_add>(m_vdata, z.m_vdata, m_vdata); return *this; }
        complex& operator-=(const complex& z) { simd::a_vec128_add_sub<float, simd::c_sub>(m_vdata, z.m_vdata, m_vdata); return *this; }
        complex& operator*=(float k) { simd::a_vec128_mul_div_s<float, simd::c_mul>(m_vdata, k, m_vdata); return *this; }
        complex& operator/=(float k) { simd::a_vec128_mul_div_s<float, simd::c_div>(m_vdata, k, m_vdata); return *this; }
        // Waiting for better optimize.
        complex& operator*=(const complex& z) { simd::a_complex_mul(m_val[0], m_val[1], z.m_val[0], z.m_val[1], m_val); return *this; }
        complex& operator/=(const complex& z) { simd::a_complex_div(m_val[0], m_val[1], z.m_val[0], z.m_val[1], m_val); return *this; }
#else
        constexpr complex& operator*=(const float& z) { m_val[0] = m_val[0] * z; m_val[1] = m_val[1] * z; return *this; }
        constexpr complex& operator/=(const float& z) { m_val[0] = m_val[0] / z; m_val[1] = m_val[1] / z; return *this; }
        constexpr complex& operator+=(const complex& z) {
            m_val[0] = m_val[0] + z.m_val[0];
            m_val[1] = m_val[1] + z.m_val[1];
            return *this;
        }
        constexpr complex& operator-=(const complex& z) {
            m_val[0] = m_val[0] - z.m_val[0];
            m_val[1] = m_val[1] - z.m_val[1];
            return *this;
        }
        constexpr complex& operator*=(const complex& z) {
            float tr = m_val[0] * z.m_val[0] - m_val[1] * z.m_val[1];
            float ti = m_val[0] * z.m_val[1] + m_val[1] * z.m_val[0];
            m_val[0] = tr;
            m_val[1] = ti;
            return *this;
        }
        constexpr complex& operator/=(const complex& z) {
            float d = z.m_val[0] * z.m_val[0] + z.m_val[1] * z.m_val[1];
            float tr = (m_val[0] * z.m_val[0] + m_val[1] * z.m_val[1]) / d;
            float ti = (m_val[1] * z.m_val[0] - m_val[0] * z.m_val[1]) / d;
            m_val[0] = tr;
            m_val[1] = ti;
            return *this;
        }
#endif  
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
        return complex<Ty>(-a.real(), -a.imag());
    }
    template <typename Ty>
        [[nodiscard]] constexpr bool operator==(const complex<Ty>& a, const complex<Ty>& b) {
        return ::force::abs(a.real() - b.real()) < FLT_EPSILON && ::force::abs(a.imag() - b.imag()) < FLT_EPSILON;
    }
    template <typename Ty>
        [[nodiscard]] constexpr bool operator==(const complex<Ty>& a, const Ty& b) {
        return ::force::abs(a.real() - b) < FLT_EPSILON && ::force::abs(a.imag()) < FLT_EPSILON;
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
    typename Comp::value_type abs(const Comp& z) {
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