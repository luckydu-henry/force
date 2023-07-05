#pragma once
#include "prmthfn.hpp"
#include "vector_view.hpp"
namespace force {

    template <std::floating_point Real, class VecViewT>
    class complex {
    public:
        using value_type = Real;
        using view_type  = VecViewT;
        union {
            // This part is use to align data and use simd.
            value_type data[2]; // Don't touch this outside in any purpose.
            // Two varibles to store the data
            struct { value_type real, imag; };
        };

        constexpr complex(std::initializer_list<Real> lst) {
            std::fill(data, data + 2, static_cast<Real>(0));
            std::copy(lst.begin(), lst.end(), data);
        }
        constexpr complex(const view_type& v) {
            std::fill(data, data + 2, static_cast<Real>(0));
            std::copy(v.data(), v.data() + std::min(2, v.size()), data);
        }
        complex(const complex& right) { 
            std::fill(data, data + 2, static_cast<Real>(0));
            std::copy(right.data, right.data + 2, data);
        }
        complex(complex&& right)      {
            std::fill(data, data + 2, static_cast<Real>(0));
            std::move(right.data, right.data + 2, data);
        }
        complex& operator= (const complex& right) { 
            std::copy(right.data, right.data + 2, data);
            return *this; 
        }
        complex& operator= (complex&& right) {
            std::move(right.data, right.data + 2, data);
            return *this;
        }

        // All loops will be optimized when turn on release mode.
        complex& operator+=(value_type k) {
            real += k;
            return *this;
        }
        complex& operator-=(value_type k) {
            real -= k;
            return *this;
        }
        complex& operator+=(const complex& right) {
            #pragma omp simd
            for (int i = 0; i < 2; ++i)  data[i] += right.data[i]; 
            return *this;
        }
        complex& operator-=(const complex& right) { 
            #pragma omp simd
            for (int i = 0; i < 2; ++i) data[i] -= right.data[i]; 
            return *this; 
        }
        complex& operator*=(value_type k) { 
            #pragma omp simd
            for (int i = 0; i < 2; ++i) data[i] *= k;             
            return *this; 
        }
        complex& operator/=(value_type k) {
            #pragma omp simd
            for (int i = 0; i < 2; ++i) data[i] /= k;             
            return *this; 
        }
        complex& operator*=(const complex& z) {
            value_type tr = real * z.real - imag * z.imag;
            value_type ti = real * z.imag + imag * z.real;
            real = tr; imag = ti;
            return *this;
        }
        complex& operator/=(const complex& z) {
            value_type d = z.real * z.real + z.imag * z.imag;
            value_type tr = (real * z.real + imag * z.imag) / d;
            value_type ti = (imag * z.real - real * z.imag) / d;
            real = tr; imag = ti;
            return *this;
        }

        ~complex() = default;
    };

    template <typename Ty, class VecViewT>
    [[nodiscard]] constexpr complex<Ty, VecViewT> operator+(const complex<Ty, VecViewT>& a, const complex<Ty, VecViewT>& b) {
        complex<Ty, VecViewT> tmp(a);
        tmp += b;
        return tmp;
    }
    template <typename Ty, class VecViewT>
        [[nodiscard]] constexpr complex<Ty, VecViewT> operator+(const complex<Ty, VecViewT>& a, const Ty& b) {
        complex<Ty, VecViewT> tmp(a);
        tmp += b;
        return tmp;
    }
    template <typename Ty, class VecViewT>
        [[nodiscard]] constexpr complex<Ty, VecViewT> operator+(const Ty& a, const complex<Ty, VecViewT>& b) {
        complex<Ty, VecViewT> tmp(b);
        tmp += a;
        return tmp;
    }
    template <typename Ty, class VecViewT>
        [[nodiscard]] constexpr complex<Ty, VecViewT> operator-(const complex<Ty, VecViewT>& a, const complex<Ty, VecViewT>& b) {
        complex<Ty, VecViewT> tmp(a);
        tmp -= b;
        return tmp;
    }
    template <typename Ty, class VecViewT>
        [[nodiscard]] constexpr complex<Ty, VecViewT> operator-(const complex<Ty, VecViewT>& a, const Ty& b) {
        complex<Ty, VecViewT> tmp(a);
        tmp -= b;
        return tmp;
    }
    template <typename Ty, class VecViewT>
        [[nodiscard]] constexpr complex<Ty, VecViewT> operator-(const Ty& a, const complex<Ty, VecViewT>& b) {
        complex<Ty, VecViewT> tmp(a);
        tmp -= b;
        return tmp;
    }
    template <typename Ty, class VecViewT>
        [[nodiscard]] constexpr complex<Ty, VecViewT> operator*(const complex<Ty, VecViewT>& a, const complex<Ty, VecViewT>& b) {
        complex<Ty, VecViewT> tmp(a);
        tmp *= b;
        return tmp;
    }
    template <typename Ty, class VecViewT>
        [[nodiscard]] constexpr complex<Ty, VecViewT> operator*(const complex<Ty, VecViewT>& a, const Ty& b) {
        complex<Ty, VecViewT> tmp(a);
        tmp *= b;
        return tmp;
    }
    template <typename Ty, class VecViewT>
        [[nodiscard]] constexpr complex<Ty, VecViewT> operator*(const Ty& a, const complex<Ty, VecViewT>& b) {
        complex<Ty, VecViewT> tmp(b);
        tmp *= a;
        return tmp;
    }
    template <typename Ty, class VecViewT>
        [[nodiscard]] constexpr complex<Ty, VecViewT> operator/(const complex<Ty, VecViewT>& a, const complex<Ty, VecViewT>& b) {
        complex<Ty, VecViewT> tmp(a);
        tmp /= b;
        return tmp;
    }
    template <typename Ty, class VecViewT>
        [[nodiscard]] constexpr complex<Ty, VecViewT> operator/(const complex<Ty, VecViewT>& a, const Ty& b) {
        complex<Ty, VecViewT> tmp(a);
        tmp /= b;
        return tmp;
    }
    template <typename Ty, class VecViewT>
        [[nodiscard]] constexpr complex<Ty, VecViewT> operator/(const Ty& a, const complex<Ty, VecViewT>& b) {
        complex<Ty, VecViewT> tmp(a);
        tmp /= b;
        return tmp;
    }
    template <typename Ty, class VecViewT>
        [[nodiscard]] constexpr complex<Ty, VecViewT> operator+(const complex<Ty, VecViewT>& a) {
        return a;
    }
    template <typename Ty, class VecViewT>
        [[nodiscard]] constexpr complex<Ty, VecViewT> operator-(const complex<Ty, VecViewT>& a) {
        return complex<Ty, VecViewT>(-a.real, -a.imag);
    }
    template <typename Ty, class VecViewT>
        [[nodiscard]] constexpr bool operator==(const complex<Ty, VecViewT>& a, const complex<Ty, VecViewT>& b) {
        return ::force::abs(a.real - b.real) < std::numeric_limits<float>::epsilon() && ::force::abs(a.imag - b.imag) < std::numeric_limits<float>::epsilon();
    }
    template <typename Ty, class VecViewT>
        [[nodiscard]] constexpr bool operator==(const complex<Ty, VecViewT>& a, const Ty& b) {
        return ::force::abs(a.real - b) < std::numeric_limits<float>::epsilon() && ::force::abs(a.imag) < std::numeric_limits<float>::epsilon();
    }

    //////////////////////////////////
    // Complex type_traits and concept
    //////////////////////////////////
    template <typename Ty>
    struct complex_traits : std::false_type {};
    template <>
    struct complex_traits<complex<float, vec4f_view>> : std::true_type {};

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
        constexpr complex<float, vec4f_view>  operator""if(long double x) {
            return { 0.0f, static_cast<float>(x) };
        }
        constexpr complex<float, vec4f_view>  operator""if(unsigned long long x) {
            return { 0.0f, static_cast<float>(x) };
        }
    }

    using complexf = complex<float, vec4f_view>;
}