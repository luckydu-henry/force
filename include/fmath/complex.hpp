#pragma once
#include "primary.hpp"
#include "pipe.hpp"
namespace force::math {

    template <std::floating_point Real, class VecPipeT>
    class complex {
    public:
        using value_type = Real;
        using pipe_type  = VecPipeT;
        union {
            // This part is use to align Data and use simd.
            value_type Data[2]; // Don't touch this outside in any purpose.
            // Two varibles to store the Data
            struct { value_type real, imag; };
        };

        constexpr complex(std::initializer_list<Real> lst) {
            std::fill(Data, Data + 2, static_cast<Real>(0));
            std::copy(lst.begin(), lst.end(), Data);
        }
        constexpr complex(const pipe_type& v) {
            std::fill(Data, Data + 2, static_cast<Real>(0));
            std::copy(v.vdata, v.vdata + std::min(2, v.vsize), Data);
        }
        complex(const complex& right) { 
            std::fill(Data, Data + 2, static_cast<Real>(0));
            std::copy(right.Data, right.Data + 2, Data);
        }
        complex(complex&& right)      {
            std::fill(Data, Data + 2, static_cast<Real>(0));
            std::move(right.Data, right.Data + 2, Data);
        }
        complex& operator= (const complex& right) { 
            std::copy(right.Data, right.Data + 2, Data);
            return *this; 
        }
        complex& operator= (complex&& right) {
            std::move(right.Data, right.Data + 2, Data);
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
            for (int32_t i = 0; i < 2; ++i)  Data[i] += right.Data[i]; 
            return *this;
        }
        complex& operator-=(const complex& right) { 
            #pragma omp simd
            for (int32_t i = 0; i < 2; ++i) Data[i] -= right.Data[i]; 
            return *this; 
        }
        complex& operator*=(value_type k) { 
            #pragma omp simd
            for (int32_t i = 0; i < 2; ++i) Data[i] *= k;             
            return *this; 
        }
        complex& operator/=(value_type k) {
            #pragma omp simd
            for (int32_t i = 0; i < 2; ++i) Data[i] /= k;             
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

    template <typename Ty, class VecPipeT>
    [[nodiscard]] constexpr complex<Ty, VecPipeT> operator+(const complex<Ty, VecPipeT>& a, const complex<Ty, VecPipeT>& b) {
        complex<Ty, VecPipeT> tmp(a);
        tmp += b;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr complex<Ty, VecPipeT> operator+(const complex<Ty, VecPipeT>& a, const Ty& b) {
        complex<Ty, VecPipeT> tmp(a);
        tmp += b;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr complex<Ty, VecPipeT> operator+(const Ty& a, const complex<Ty, VecPipeT>& b) {
        complex<Ty, VecPipeT> tmp(b);
        tmp += a;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr complex<Ty, VecPipeT> operator-(const complex<Ty, VecPipeT>& a, const complex<Ty, VecPipeT>& b) {
        complex<Ty, VecPipeT> tmp(a);
        tmp -= b;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr complex<Ty, VecPipeT> operator-(const complex<Ty, VecPipeT>& a, const Ty& b) {
        complex<Ty, VecPipeT> tmp(a);
        tmp -= b;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr complex<Ty, VecPipeT> operator-(const Ty& a, const complex<Ty, VecPipeT>& b) {
        complex<Ty, VecPipeT> tmp(a);
        tmp -= b;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr complex<Ty, VecPipeT> operator*(const complex<Ty, VecPipeT>& a, const complex<Ty, VecPipeT>& b) {
        complex<Ty, VecPipeT> tmp(a);
        tmp *= b;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr complex<Ty, VecPipeT> operator*(const complex<Ty, VecPipeT>& a, const Ty& b) {
        complex<Ty, VecPipeT> tmp(a);
        tmp *= b;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr complex<Ty, VecPipeT> operator*(const Ty& a, const complex<Ty, VecPipeT>& b) {
        complex<Ty, VecPipeT> tmp(b);
        tmp *= a;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr complex<Ty, VecPipeT> operator/(const complex<Ty, VecPipeT>& a, const complex<Ty, VecPipeT>& b) {
        complex<Ty, VecPipeT> tmp(a);
        tmp /= b;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr complex<Ty, VecPipeT> operator/(const complex<Ty, VecPipeT>& a, const Ty& b) {
        complex<Ty, VecPipeT> tmp(a);
        tmp /= b;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr complex<Ty, VecPipeT> operator/(const Ty& a, const complex<Ty, VecPipeT>& b) {
        complex<Ty, VecPipeT> tmp(a);
        tmp /= b;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr complex<Ty, VecPipeT> operator+(const complex<Ty, VecPipeT>& a) {
        return a;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr complex<Ty, VecPipeT> operator-(const complex<Ty, VecPipeT>& a) {
        return complex<Ty, VecPipeT>(-a.real, -a.imag);
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr bool operator==(const complex<Ty, VecPipeT>& a, const complex<Ty, VecPipeT>& b) {
        return ::force::math::abs(a.real - b.real) < std::numeric_limits<float32_t>::epsilon() && ::force::math::abs(a.imag - b.imag) < std::numeric_limits<float32_t>::epsilon();
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr bool operator==(const complex<Ty, VecPipeT>& a, const Ty& b) {
        return ::force::math::abs(a.real - b) < std::numeric_limits<float32_t>::epsilon() && ::force::math::abs(a.imag) < std::numeric_limits<float32_t>::epsilon();
    }

    //////////////////////////////////
    // complex type_traits and concept
    //////////////////////////////////
    template <typename Ty>
    struct complex_traits : std::false_type {};
    template <>
    struct complex_traits<complex<float32_t, pipe4f>> : std::true_type {};

    template <typename Ty>
    concept complex_number = complex_traits<Ty>::value;

    /////////////////////
    // complex functions 
    /////////////////////

    template <complex_number Comp>
    Comp conjucate(const Comp& z) {
        return Comp{ z.real, ::force::math::inv(z.imag) };
    }
    template <complex_number Comp>
    Comp inv(const Comp& z) {
        return Comp{ ::force::math::inv(z.real), ::force::math::inv(z.imag) };
    }
    template <complex_number Comp>
    Comp::value_type abs(const Comp& z) {
        return ::force::math::sqrt(z.real * z.real + z.imag * z.imag);
    }

    namespace complex_literals {
        constexpr complex<float32_t, pipe4f>  operator""if(long double x) {
            return { 0.0f, static_cast<float32_t>(x) };
        }
        constexpr complex<float32_t, pipe4f>  operator""if(unsigned long long x) {
            return { 0.0f, static_cast<float32_t>(x) };
        }
    }

    using complexf = complex<float32_t, pipe4f>;
}