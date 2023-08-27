#pragma once
#include "Constant.hpp"

namespace Fma {
    [[nodiscard]] float Fmod(float x, float y);
    ///////////////////////
    // Rounding function
    ///////////////////////
    [[nodiscard]] int   Ftrunc  (float x);
    [[nodiscard]] int   Fceil   (float x);
    [[nodiscard]] int   Ffloor  (float x);
    [[nodiscard]] int   Fround  (float x);
    [[nodiscard]] int   Fbround (float x); // banker round
    ////////////////////////
    // Arithmetic functions
    ////////////////////////
    [[nodiscard]] float Fabs    (float x);
    [[nodiscard]] int   Fabs    (int x);
    [[nodiscard]] float Frecp   (float x);
    [[nodiscard]] float Finv    (float x);
    [[nodiscard]] float Fsqrt   (float x);
    [[nodiscard]] float Frsqrt  (float x);
    [[nodiscard]] float Fcbrt   (float x);
    ////////////////////////
    // Exp & log functions
    ////////////////////////
    [[nodiscard]] float      Flog    (float x);
    [[nodiscard]] float      Flog2   (float x);
    [[nodiscard]] uint32_t   Flog2   (uint32_t x);
    [[nodiscard]] float      Flog10  (float x);
    [[nodiscard]] float      Fexp    (float x);
    [[nodiscard]] float      Fexp2   (float x);
    [[nodiscard]] float      Fexp10  (float x);
    [[nodiscard]] float      Floga   (float a, float b);
    [[nodiscard]] float      Fpow    (float x, float n);
    //////////////////////////
    // Trignometric functions
    //////////////////////////
    [[nodiscard]] float Fsin   (float x);
    [[nodiscard]] float Fcos   (float x);
    [[nodiscard]] float Ftan   (float x);
    [[nodiscard]] float Fcot   (float x);
    [[nodiscard]] float Fsec   (float x);
    [[nodiscard]] float Fcsc   (float x);
    //////////////////////////////
    // Arc-Trignometric functions
    //////////////////////////////
    [[nodiscard]] float Fasin(float x);
    [[nodiscard]] float Facos(float x);
    [[nodiscard]] float Fatan(float x);
    [[nodiscard]] float Facot(float x);
    [[nodiscard]] float Fasec(float x);
    [[nodiscard]] float Facsc(float x);

    // Radian and angle conversion function
    template <typename Ty> Ty Fradian(Ty deg) {
        return deg * (static_cast<Ty>(180) / pi<Ty>);
    }
    template <typename Ty> Ty Fdegree(Ty rad) {
        return rad * (pi<Ty> / static_cast<Ty>(180));
    }
}
