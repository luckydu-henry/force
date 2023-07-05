#pragma once
#include "basic_vector.hpp"
namespace force {
    // Using for basic_vectors.
    // These usings can do conversions between.
    using vec4f = typename basic_vector<float, 4, vec4f_pipe>;
    using vec3f = typename basic_vector<float, 3, vec4f_pipe>;
    using vec2f = typename basic_vector<float, 2, vec4f_pipe>;
    using vec1f = typename basic_vector<float, 1, vec4f_pipe>;
    using vec4i = typename basic_vector<int, 4, vec4i_pipe>;
    using vec3i = typename basic_vector<int, 3, vec4i_pipe>;
    using vec2i = typename basic_vector<int, 2, vec4i_pipe>;
    using vec1i = typename basic_vector<int, 1, vec4f_pipe>;


}