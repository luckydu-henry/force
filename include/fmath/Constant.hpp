#pragma once
#include <concepts>
namespace Fma {
    template <std::floating_point Float>
    constexpr Float pi     = static_cast<Float>(3.1415926535897932384626433832795);
    template <std::floating_point Float>
    constexpr Float twopi  = static_cast<Float>(6.283185307179586476925286766559);
    template <std::floating_point Float>
    constexpr Float halfpi = static_cast<Float>(1.5707963267948966192313216916398);
    template <std::floating_point Float>
    constexpr Float rpi    = static_cast<Float>(0.31830988618379067153776752674503);
    template <std::floating_point Float>
    constexpr Float sqrtpi = static_cast<Float>(1.7724538509055160272981674833411);
    template <std::floating_point Float>
    constexpr Float e      = static_cast<Float>(2.7182818284590452353602874713527);
    template <std::floating_point Float>
    constexpr Float re     = static_cast<Float>(0.36787944117144232159552377016146);
    template <std::floating_point Float>
    constexpr Float sqrt2  = static_cast<Float>(1.4142135623730950488016887242097);
    template <std::floating_point Float>
    constexpr Float sqrt3  = static_cast<Float>(1.7320508075688772935274463415059);
}