#pragma once
#include "Constant.hpp"

namespace Fma {
    constexpr float Fmod(float x, float y);
    ///////////////////////
    // Rounding function
    ///////////////////////
    [[nodiscard]] constexpr int   Ftrunc  (float x);
    [[nodiscard]] constexpr int   Fceil   (float x);
    [[nodiscard]] constexpr int   Ffloor  (float x);
    [[nodiscard]] constexpr int   Fround  (float x);
    [[nodiscard]] constexpr int   Fbround (float x); // banker round
    ////////////////////////
    // Arithmetic functions
    ////////////////////////
    [[nodiscard]] constexpr float Fabs    (float x);
    [[nodiscard]] constexpr int   Fabs    (int x);
    [[nodiscard]] constexpr float Frecp   (float x);
    [[nodiscard]] constexpr float Finv    (float x);
    [[nodiscard]] constexpr float Fsqrt   (float x);
    [[nodiscard]] constexpr float Frsqrt  (float x);
    [[nodiscard]] constexpr float Fcbrt   (float x);
    ////////////////////////
    // Exp & log functions
    ////////////////////////
    [[nodiscard]] constexpr float      Flog    (float x);
    [[nodiscard]] constexpr float      Flog2   (float x);
    [[nodiscard]] constexpr uint32_t   Flog2   (uint32_t x);
    [[nodiscard]] constexpr float      Flog10  (float x);
    [[nodiscard]] constexpr float      Fexp    (float x);
    [[nodiscard]] constexpr float      Fexp2   (float x);
    [[nodiscard]] constexpr float      Fexp10  (float x);
    [[nodiscard]] constexpr float      Floga   (float a, float b);
    [[nodiscard]] constexpr float      Fpow    (float x, float n);
    //////////////////////////
    // Trignometric functions
    //////////////////////////
    [[nodiscard]] constexpr float Fsin   (float x);
    [[nodiscard]] constexpr float Fcos   (float x);
    [[nodiscard]] constexpr float Ftan   (float x);
    [[nodiscard]] constexpr float Fcot   (float x);
    [[nodiscard]] constexpr float Fsec   (float x);
    [[nodiscard]] constexpr float Fcsc   (float x);
    //////////////////////////////
    // Arc-Trignometric functions
    //////////////////////////////
    [[nodiscard]] constexpr float Fasin(float x);
    [[nodiscard]] constexpr float Facos(float x);
    [[nodiscard]] constexpr float Fatan(float x);
    [[nodiscard]] constexpr float Facot(float x);
    [[nodiscard]] constexpr float Fasec(float x);
    [[nodiscard]] constexpr float Facsc(float x);
}
