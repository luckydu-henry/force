#pragma once
#include "BasicVector.hpp"
#include "SIMD.hpp"
#if FMA_ARCH & FMA_ARCH_SSE2
#include "SIMDVector4.hpp"
#endif
namespace Fma {
    // Using for BasicVectors.
    // These usings can do conversions between.
#if SIMD_VECTOR4x32
    using Vec4f = typename SIMDVector4<float>;
    using Vec4i = typename SIMDVector4<int>;
#else
    using Vec4f = typename BasicVector<float, 4, Vec4fPipe>;
    using Vec4i = typename BasicVector
#endif
    using Vec3f = typename BasicVector<float, 3, Vec4fPipe>;
    using Vec3i = typename BasicVector<int, 3, Vec4iPipe>;
    using Vec2f = typename BasicVector<float, 2, Vec4fPipe>;
    using Vec2i = typename BasicVector<int, 2, Vec4iPipe>;
    using Vec1f = typename BasicVector<float, 1, Vec4fPipe>;
    using Vec1i = typename BasicVector<int, 1, Vec4fPipe>;
}