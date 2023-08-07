#pragma once
#include "BasicVector.hpp"
namespace Fma {
    // Using for BasicVectors.
    // These usings can do conversions between.
    using Vec4f = typename BasicVector<float, 4, Vec4fPipe>;
    using Vec3f = typename BasicVector<float, 3, Vec4fPipe>;
    using Vec2f = typename BasicVector<float, 2, Vec4fPipe>;
    using Vec1f = typename BasicVector<float, 1, Vec4fPipe>;
    using Vec4i = typename BasicVector<int, 4, Vec4iPipe>;
    using Vec3i = typename BasicVector<int, 3, Vec4iPipe>;
    using Vec2i = typename BasicVector<int, 2, Vec4iPipe>;
    using Vec1i = typename BasicVector<int, 1, Vec4fPipe>;


}