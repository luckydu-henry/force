#pragma once
#include "BasicMatrix.hpp"
namespace Fma {
    using Mat2x2f = typename BasicMatrix<float, 2, 2, Vec4fPipe>;
    using Mat3x3f = typename BasicMatrix<float, 3, 3, Vec4fPipe>;
    using Mat4x4f = typename BasicMatrix<float, 4, 4, Vec4fPipe>;
    using Mat2x2i = typename BasicMatrix<int, 2, 2, Vec4iPipe>;
    using Mat3x3i = typename BasicMatrix<int, 3, 3, Vec4iPipe>;
    using Mat4x4i = typename BasicMatrix<int, 4, 4, Vec4iPipe>;
} //! namespace Fma