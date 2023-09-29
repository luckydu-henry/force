///
/// @file      nOperate.hpp
/// @brief     Some math functions that needs to take in other functions as parameter.   
/// @details   ~
/// @author    HenryDu
/// @date      9.09.2023
/// @copyright © HenryDu 2023. All right reserved.
///
#pragma once
#include "primary.hpp"
namespace force::math {

    template <typename Ty>
    using unaryT  = Ty(*)(Ty);
    template <typename Ty>
    using binaryT = Ty(*)(Ty, Ty);

    // DerivativeMap stores functions derivative
    // High precision solution
    // Uses function pointer, so make sure you do not pass in std::function.
    template <typename Ty, unaryT<Ty> f>
    struct calculus_map { 
        static constexpr unaryT<Ty> integral   = nullptr;
        static constexpr unaryT<Ty> derivative = nullptr; 
    };
    // std::function doesn't have compile time support
    // So I still use function pointers.
    template <> struct calculus_map<float32_t, sin> { 
        static constexpr unaryT<float32_t> integral   = [](float32_t x)->float32_t { return -cos(x); };
        static constexpr unaryT<float32_t> derivative = cos; 
    };
    template <> struct calculus_map<float32_t, cos> { 
        static constexpr unaryT<float32_t> integral   = sin;
        static constexpr unaryT<float32_t> derivative = [](float32_t x)->float32_t {return -sin(x); }; 
    };

    // Big-Sigma notation when doing math.
    // Again this is a common solution but not the best.
    // orexample you want to calculate 1^2 + 2^2 + ... + n^2 use n(n+1)(2n+1)/6 instead of using this.
    // Why not use std::accumulate I hear you ask, because accumulate is too bad to do this and my way is easier.
    template <typename Ty>
    Ty sum(unaryT<Ty> f, size_t i, size_t n) {
        Ty s = 0;
        for (; i < n + 1; ++i) s += f(static_cast<Ty>(i));
        return s;
    }
    // Big-Pi notation when doing math. (product)
    // Again this is a common solution but not the best.
    // I don't know when this will use very often.
    template <typename Ty>
    Ty pro(unaryT<Ty> f, size_t i, size_t n) {
        Ty s = 1;
        for (; i < n + 1; ++i) s *= f(static_cast<Ty>(i));
        return s;
    }
    // Numerical & Automatic differential
    // When your function is added to compile time DerivativeMap it uses your function
    // Otherwise it uses the original definition of derivative which is numerical derivate.
    template <typename Ty, unaryT<Ty> f>
    Ty ddx(Ty x) {
        if (calculus_map<Ty, f>::derivative == nullptr) {
            constexpr Ty dx = static_cast<Ty>(std::is_same_v<Ty, float32_t> ? 0.99e-6 : 1e-12);
            // Center diffrentiation formula
            // f'(x) approx to below.
            return (f(x + dx) - f(x - dx)) / (2 * dx); // for float32_t type this precision lost can be very bad
        }
        return calculus_map<Ty, f>::derivative(x);
    }
    // Integral -- calculates the indefinite integral of a function f
    template <typename Ty, unaryT<Ty> f>
    Ty int(Ty x) {
        return calculus_map<Ty, f>::integral(x);
    }
    // Partial derivative of x
    template <typename Ty, binaryT<Ty> f>
    Ty ppx(Ty x, const Ty y) {
        return 0;
    }
    // Partial derivative of y
    template <typename Ty, binaryT<Ty> f>
    Ty ppy(const Ty x, Ty y) {
        return 0;
    }
}