#pragma once
#include <concepts>
#include "constants.hpp"

namespace force {
    template <std::floating_point Float>
    using rounding = typename std::conditional<std::is_same_v<Float, float>, int, long long>;

    template <std::floating_point Float>
    constexpr Float mod(Float x, Float y);

    ////////////////////////
    // Round functions
    ////////////////////////
    template <std::floating_point Float>
    [[nodiscard]] constexpr rounding<Float>::type trunc(Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr rounding<Float>::type ceil (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr rounding<Float>::type floor(Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr rounding<Float>::type round(Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr rounding<Float>::type bround(Float x);
    ////////////////////////
    // Arithmetic functions
    ////////////////////////
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float abs    (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float recp   (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float inv    (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float sqrt   (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float rsqrt  (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float cbrt   (Float x);
    ////////////////////////
    // Exp & log functions
    ////////////////////////
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float log    (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float log2   (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float log10  (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float exp    (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float exp2   (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float exp10  (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float loga   (Float a, Float b);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float pow    (Float x, Float n);
    //////////////////////////
    // Trignometric functions
    //////////////////////////
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float sin   (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float cos   (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float tan   (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float cot   (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float sec   (Float x);
    template <std::floating_point Float>
    [[nodiscard]] constexpr Float csc   (Float x);
}
// Implementation of functions.
#include "f32/prmthfn.hpp"
// #include "f64/prmthfn.hpp"
