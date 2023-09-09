///
/// @file      FnOperate.hpp
/// @brief     Some math functions that needs to take in other functions as parameter.   
/// @details   ~
/// @author    HenryDu
/// @date      9.09.2023
/// @copyright © HenryDu 2023. All right reserved.
///
#pragma once
#include <functional> // for function input (modern C++ should not use C-style function pointers.)

namespace Fma {
    template <typename Ty>
    using FunaryT  = std::function<Ty(Ty)>;
    template <typename Ty>
    using FbinaryT = std::function<Ty(Ty, Ty)>;

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
    // Numerical differential
    // Precision is very low -- I haven't figured it out. But it's enough to use.
    // ** If your original function is certain sure then don't use this. **
    // For example if you want to calculate sin'(x) you just use cos(x)
    // Instead of doing this , because this is the common solution but not the best.
    // It's a numerical approximation but as long as you can use math way to simplify just don't use this.
    template <typename Ty>
    Ty Fddx(FunaryT<Ty> f, Ty x) {
        constexpr Ty dx = static_cast<Ty>(std::is_same_v<Ty, float> ? 0.99e-6 : 1e-12);
        // Center diffrentiation formula
        // f'(x) approx to below.
        return (f(x + dx) - f(x - dx)) / (2 * dx); // for float type this precision lost can be very bad
    }
    // Integral -- calculates the indefinite integral of a function f
    template <typename Ty>
    Ty Fint(FunaryT<Ty> f, Ty x) {
        return 0;
    }
    // Partial derivative of x
    template <typename Ty>
    Ty Fppx(FbinaryT<Ty> f, Ty x, const Ty y) {
        return 0;
    }
    // Partial derivative of y
    template <typename Ty>
    Ty Fppy(FbinaryT<Ty> f, const Ty x, Ty y) {
        return 0;
    }
}