#ifndef _FORCE_F32_BASIC_MATH_H_
#define _FORCE_F32_BASIC_MATH_H_

// FORCE(Flaoting point Optimized Rapid Calculation Engine)
// f32 is the 32bit floating point namespace.
namespace force::f32 {

    using interger_t = int;
    using floating_t = float;


    float        abs  (float n);
    float        sqrt (float n);
    float        rsqrt(float n);
    float        cbrt (float n);

    //int          floor(float n);
    //int          ceil (float n);
    //int          round(float n);

    float        to_rad(float _Deg);
    float        to_deg(float _Rad);
}

#endif //! _FORCE_F32_BASIC_MATH_H_
