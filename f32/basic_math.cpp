#include "basic_math.h"
#include "constants.h"

// If you are fimiliar with QuakeIII --
// Then you will absolutely feel warm here.
namespace force::f32 {

    // Bit operation based absolute.
    float abs(float n) {
        int i = *(int*)&n;
        i &= 0x7fffffff;
        return *(float*)&i;
    }

    //
    // Algos below won't do any range check.
    // It will gives you a result even you pass in a negative number to sqrt.
    // "You should do checking yourself".
    //

    // Sqrt function inspired by QuakeIII.
    float sqrt(float n) {
        float num = 0.5f * n;

        // I learned this trick from QuakeIII.
        int i = *(int*)&n;
        i = 0x1fbb4eee + (i >> 1);
        float x = *(float*)&i;

        x = 0.5f * x + num / x; // 1st Newton iteration.
        x = 0.5f * x + num / x; // 2nd Newton iteration.

        return x;
    }

    // Here it is the classic QuakeIII Q_rsqrt
    // But some little changes here.
    float rsqrt(float n) {
        float num = 0.5f * n;

        // The QuakeIII's wtf.
        int i = *(int*)&n;
        i = 0x5f375a86 - (i >> 1); // I changed the magic number to a better one.
        float x = *(float*)&i;

        x = x * (1.5f - num * x * x);
        x = x * (1.5f - num * x * x);

        return x;
    }

    // Sqrt uses very often but cbrt doesn't.
    // Infact, you won't use cbrt except from playing with volume.
    // However I would still provide you a cbrt. This one only works fine when your n >= 0.
    // So if you want to calculate the cbrt of a negative number use cbrt(-x) = -cbrt(x) to transform.
    // Use this in pure physics purpose, no if statement because that would cause many issues.
    float cbrt(float n) {
        float x0 = abs(n);
        float num = 0.333333f * n;

        int i = *(int*)&x0;
        i = 0x2a2e5c2f + (i / 3);
        float x = *(float*)&i;

        x = 0.666666f * x + num * (1.f / (x * x));
        x = 0.666666f * x + num * (1.f / (x * x));
        x = 0.666666f * x + num * (1.f / (x * x));

        return x;
    }

    //int floor(float n) {
    //}

    //int ceil(float n)
    //{
    //    return 0;
    //}

    //int round(float n)
    //{
    //    return 0;
    //}

    float to_rad(float _Deg) {
        return _Deg * (c_pi / 180.f);
    }

    float to_deg(float _Rad) {
        return _Rad * 180.f * c_rpi;
    }
}