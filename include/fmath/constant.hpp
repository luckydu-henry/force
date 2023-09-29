#pragma once
#include <concepts>
namespace force::math {
    using float32_t = float;
    using float64_t = double;

    template <std::floating_point loat>
    constexpr loat pi     = static_cast<loat>(3.1415926535897932384626433832795);
    template <std::floating_point loat>
    constexpr loat twopi  = static_cast<loat>(6.283185307179586476925286766559);
    template <std::floating_point loat>
    constexpr loat halfpi = static_cast<loat>(1.5707963267948966192313216916398);
    template <std::floating_point loat>
    constexpr loat rpi    = static_cast<loat>(0.31830988618379067153776752674503);
    template <std::floating_point loat>
    constexpr loat sqrtpi = static_cast<loat>(1.7724538509055160272981674833411);
    template <std::floating_point loat>
    constexpr loat e      = static_cast<loat>(2.7182818284590452353602874713527);
    template <std::floating_point loat>
    constexpr loat re     = static_cast<loat>(0.36787944117144232159552377016146);
    template <std::floating_point loat>
    constexpr loat sqrt2  = static_cast<loat>(1.4142135623730950488016887242097);
    template <std::floating_point loat>
    constexpr loat sqrt3  = static_cast<loat>(1.7320508075688772935274463415059);
}