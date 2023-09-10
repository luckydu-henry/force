///
/// @file      FnOperate.hpp
/// @brief     Some math functions that needs to take in other functions as parameter.   
/// @details   ~
/// @author    HenryDu
/// @date      9.09.2023
/// @copyright © HenryDu 2023. All right reserved.
///
#pragma once
#include "PrMathFn.hpp"
namespace Fma {

    template <typename Ty>
    using FunaryT  = Ty(*)(Ty);
    template <typename Ty>
    using FbinaryT = Ty(*)(Ty, Ty);

    // DerivativeMap stores functions derivative
    // High precision solution
    // Uses function pointer, so make sure you do not pass in std::function.
    template <typename Ty, FunaryT<Ty> f>
    struct CalculusMap { 
        static constexpr FunaryT<Ty> integral   = nullptr;
        static constexpr FunaryT<Ty> derivative = nullptr; 
    };
    // std::function doesn't have compile time support
    // So I still use function pointers.
    template <> struct CalculusMap<float, Fsin> { 
        static constexpr FunaryT<float> integral   = [](float x)->float { return -Fcos(x); };
        static constexpr FunaryT<float> derivative = Fcos; 
    };
    template <> struct CalculusMap<float, Fcos> { 
        static constexpr FunaryT<float> integral   = Fsin;
        static constexpr FunaryT<float> derivative = [](float x)->float {return -Fsin(x); }; 
    };

    // Big-Sigma notation when doing math.
    // Again this is a common solution but not the best.
    // Forexample you want to calculate 1^2 + 2^2 + ... + n^2 use n(n+1)(2n+1)/6 instead of using this.
    // Why not use std::accumulate I hear you ask, because accumulate is too bad to do this and my way is easier.
    template <typename Ty>
    Ty Fsum(FunaryT<Ty> f, size_t i, size_t n) {
        Ty s = 0;
        for (; i < n + 1; ++i) s += f(static_cast<Ty>(i));
        return s;
    }
    // Big-Pi notation when doing math. (product)
    // Again this is a common solution but not the best.
    // I don't know when this will use very often.
    template <typename Ty>
    Ty Fpro(FunaryT<Ty> f, size_t i, size_t n) {
        Ty s = 1;
        for (; i < n + 1; ++i) s *= f(static_cast<Ty>(i));
        return s;
    }
    // Numerical & Automatic differential
    // When your function is added to compile time DerivativeMap it uses your function
    // Otherwise it uses the original definition of derivative which is numerical derivate.
    template <typename Ty, FunaryT<Ty> f>
    Ty Fddx(Ty x) {
        if (CalculusMap<Ty, f>::derivative == nullptr) {
            constexpr Ty dx = static_cast<Ty>(std::is_same_v<Ty, float> ? 0.99e-6 : 1e-12);
            // Center diffrentiation formula
            // f'(x) approx to below.
            return (f(x + dx) - f(x - dx)) / (2 * dx); // for float type this precision lost can be very bad
        }
        return CalculusMap<Ty, f>::derivative(x);
    }
    // Integral -- calculates the indefinite integral of a function f
    template <typename Ty, FunaryT<Ty> f>
    Ty Fint(Ty x) {
        return CalculusMap<Ty, f>::integral(x);
    }
    // Partial derivative of x
    template <typename Ty, FbinaryT<Ty> f>
    Ty Fppx(Ty x, const Ty y) {
        return 0;
    }
    // Partial derivative of y
    template <typename Ty, FbinaryT<Ty> f>
    Ty Fppy(const Ty x, Ty y) {
        return 0;
    }
}