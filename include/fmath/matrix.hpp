#pragma once
#include "basic_matrix.hpp"
namespace force::math {
    using mat2x2f = typename basic_matrix<float32_t, 2, 2, pipe4f>;
    using mat3x3f = typename basic_matrix<float32_t, 3, 3, pipe4f>;
    using mat4x4f = typename basic_matrix<float32_t, 4, 4, pipe4f>;
    using mat2x2i = typename basic_matrix<int32_t, 2, 2, pipe4i>;
    using mat3x3i = typename basic_matrix<int32_t, 3, 3, pipe4i>;
    using mat4x4i = typename basic_matrix<int32_t, 4, 4, pipe4i>;
} //! namespace force::math