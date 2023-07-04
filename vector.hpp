#pragma once
#include "basic_vector.hpp"
namespace force {
    // Using for basic_vectors.
    // These usings can do conversions between.
    using vec4f = typename basic_vector<float, 4, vec4f_view>;
    using vec3f = typename basic_vector<float, 3, vec4f_view>;
    using vec2f = typename basic_vector<float, 2, vec4f_view>;
    using vec4i = typename basic_vector<int, 4, vec4i_view>;
    using vec3i = typename basic_vector<int, 3, vec4i_view>;
    using vec2i = typename basic_vector<int, 2, vec4i_view>;
}