#pragma once
#include "PrMathFn.hpp"
#include "VectorPipe.hpp"
namespace Fma {

    template <std::floating_point Real, class VecPipeT>
    class Complex {
    public:
        using value_type = Real;
        using pipe_type  = VecPipeT;
        union {
            // This part is use to align Data and use simd.
            value_type Data[2]; // Don't touch this outside in any purpose.
            // Two varibles to store the Data
            struct { value_type real, imag; };
        };

        constexpr Complex(std::initializer_list<Real> lst) {
            std::fill(Data, Data + 2, static_cast<Real>(0));
            std::copy(lst.begin(), lst.end(), Data);
        }
        constexpr Complex(const pipe_type& v) {
            std::fill(Data, Data + 2, static_cast<Real>(0));
            std::copy(v.Data(), v.Data() + std::min(2, v.size()), Data);
        }
        Complex(const Complex& right) { 
            std::fill(Data, Data + 2, static_cast<Real>(0));
            std::copy(right.Data, right.Data + 2, Data);
        }
        Complex(Complex&& right)      {
            std::fill(Data, Data + 2, static_cast<Real>(0));
            std::move(right.Data, right.Data + 2, Data);
        }
        Complex& operator= (const Complex& right) { 
            std::copy(right.Data, right.Data + 2, Data);
            return *this; 
        }
        Complex& operator= (Complex&& right) {
            std::move(right.Data, right.Data + 2, Data);
            return *this;
        }

        // All loops will be optimized when turn on release mode.
        Complex& operator+=(value_type k) {
            real += k;
            return *this;
        }
        Complex& operator-=(value_type k) {
            real -= k;
            return *this;
        }
        Complex& operator+=(const Complex& right) {
            #pragma omp simd
            for (int i = 0; i < 2; ++i)  Data[i] += right.Data[i]; 
            return *this;
        }
        Complex& operator-=(const Complex& right) { 
            #pragma omp simd
            for (int i = 0; i < 2; ++i) Data[i] -= right.Data[i]; 
            return *this; 
        }
        Complex& operator*=(value_type k) { 
            #pragma omp simd
            for (int i = 0; i < 2; ++i) Data[i] *= k;             
            return *this; 
        }
        Complex& operator/=(value_type k) {
            #pragma omp simd
            for (int i = 0; i < 2; ++i) Data[i] /= k;             
            return *this; 
        }
        Complex& operator*=(const Complex& z) {
            value_type tr = real * z.real - imag * z.imag;
            value_type ti = real * z.imag + imag * z.real;
            real = tr; imag = ti;
            return *this;
        }
        Complex& operator/=(const Complex& z) {
            value_type d = z.real * z.real + z.imag * z.imag;
            value_type tr = (real * z.real + imag * z.imag) / d;
            value_type ti = (imag * z.real - real * z.imag) / d;
            real = tr; imag = ti;
            return *this;
        }

        ~Complex() = default;
    };

    template <typename Ty, class VecPipeT>
    [[nodiscard]] constexpr Complex<Ty, VecPipeT> operator+(const Complex<Ty, VecPipeT>& a, const Complex<Ty, VecPipeT>& b) {
        Complex<Ty, VecPipeT> tmp(a);
        tmp += b;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr Complex<Ty, VecPipeT> operator+(const Complex<Ty, VecPipeT>& a, const Ty& b) {
        Complex<Ty, VecPipeT> tmp(a);
        tmp += b;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr Complex<Ty, VecPipeT> operator+(const Ty& a, const Complex<Ty, VecPipeT>& b) {
        Complex<Ty, VecPipeT> tmp(b);
        tmp += a;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr Complex<Ty, VecPipeT> operator-(const Complex<Ty, VecPipeT>& a, const Complex<Ty, VecPipeT>& b) {
        Complex<Ty, VecPipeT> tmp(a);
        tmp -= b;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr Complex<Ty, VecPipeT> operator-(const Complex<Ty, VecPipeT>& a, const Ty& b) {
        Complex<Ty, VecPipeT> tmp(a);
        tmp -= b;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr Complex<Ty, VecPipeT> operator-(const Ty& a, const Complex<Ty, VecPipeT>& b) {
        Complex<Ty, VecPipeT> tmp(a);
        tmp -= b;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr Complex<Ty, VecPipeT> operator*(const Complex<Ty, VecPipeT>& a, const Complex<Ty, VecPipeT>& b) {
        Complex<Ty, VecPipeT> tmp(a);
        tmp *= b;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr Complex<Ty, VecPipeT> operator*(const Complex<Ty, VecPipeT>& a, const Ty& b) {
        Complex<Ty, VecPipeT> tmp(a);
        tmp *= b;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr Complex<Ty, VecPipeT> operator*(const Ty& a, const Complex<Ty, VecPipeT>& b) {
        Complex<Ty, VecPipeT> tmp(b);
        tmp *= a;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr Complex<Ty, VecPipeT> operator/(const Complex<Ty, VecPipeT>& a, const Complex<Ty, VecPipeT>& b) {
        Complex<Ty, VecPipeT> tmp(a);
        tmp /= b;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr Complex<Ty, VecPipeT> operator/(const Complex<Ty, VecPipeT>& a, const Ty& b) {
        Complex<Ty, VecPipeT> tmp(a);
        tmp /= b;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr Complex<Ty, VecPipeT> operator/(const Ty& a, const Complex<Ty, VecPipeT>& b) {
        Complex<Ty, VecPipeT> tmp(a);
        tmp /= b;
        return tmp;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr Complex<Ty, VecPipeT> operator+(const Complex<Ty, VecPipeT>& a) {
        return a;
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr Complex<Ty, VecPipeT> operator-(const Complex<Ty, VecPipeT>& a) {
        return Complex<Ty, VecPipeT>(-a.real, -a.imag);
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr bool operator==(const Complex<Ty, VecPipeT>& a, const Complex<Ty, VecPipeT>& b) {
        return ::Fma::Fabs(a.real - b.real) < std::numeric_limits<float>::epsilon() && ::Fma::Fabs(a.imag - b.imag) < std::numeric_limits<float>::epsilon();
    }
    template <typename Ty, class VecPipeT>
        [[nodiscard]] constexpr bool operator==(const Complex<Ty, VecPipeT>& a, const Ty& b) {
        return ::Fma::Fabs(a.real - b) < std::numeric_limits<float>::epsilon() && ::Fma::Fabs(a.imag) < std::numeric_limits<float>::epsilon();
    }

    //////////////////////////////////
    // Complex type_traits and concept
    //////////////////////////////////
    template <typename Ty>
    struct Complex_traits : std::false_type {};
    template <>
    struct Complex_traits<Complex<float, Vec4fPipe>> : std::true_type {};

    template <typename Ty>
    concept Complex_number = Complex_traits<Ty>::value;

    /////////////////////
    // Complex functions 
    /////////////////////

    template <Complex_number Comp>
    Comp Fconjucate(const Comp& z) {
        return Comp{ z.real, ::Fma::Finv(z.imag) };
    }
    template <Complex_number Comp>
    Comp Finv(const Comp& z) {
        return Comp{ ::Fma::Finv(z.real), ::Fma::Finv(z.imag) };
    }
    template <Complex_number Comp>
    Comp::value_type Fabs(const Comp& z) {
        return ::Fma::Fsqrt(z.real * z.real + z.imag * z.imag);
    }

    namespace ComplexLiterals {
        constexpr Complex<float, Vec4fPipe>  operator""if(long double x) {
            return { 0.0f, static_cast<float>(x) };
        }
        constexpr Complex<float, Vec4fPipe>  operator""if(unsigned long long x) {
            return { 0.0f, static_cast<float>(x) };
        }
    }

    using Complexf = Complex<float, Vec4fPipe>;
}