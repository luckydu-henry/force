#pragma once
#include "basic_matrix.hpp"
namespace force {
    using mat2x2f = typename basic_matrix<float, 2, 2, vec4f_pipe>;
    using mat3x3f = typename basic_matrix<float, 3, 3, vec4f_pipe>;
    using mat4x4f = typename basic_matrix<float, 4, 4, vec4f_pipe>;
    using mat2x2i = typename basic_matrix<int, 2, 2, vec4i_pipe>;
    using mat3x3i = typename basic_matrix<int, 3, 3, vec4i_pipe>;
    using mat4x4i = typename basic_matrix<int, 4, 4, vec4i_pipe>;
} //! namespace force