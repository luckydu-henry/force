#pragma once
#include "basic_vector.hpp"
#include "simd_decl.hpp"
#if FMA_ARCH & FMA_ARCH_SSE2
#include "simd_vector4.hpp"
#endif
namespace force::math {
    // Using for basic_vectors.
    // These usings can do conversions between.
#if SIMD_VECTOR4x32
    using vec4f = typename basic_vector<float32_t, 4, basic_pipe<float32_t, 4>>;
    using vec4i = typename basic_vector<int32_t, 4, basic_pipe<int32_t, 4>>;
#else
    using vec4f = typename basic_vector<float32_t, 4, pipe4f>;
    using vec4i = typename basic_vector
#endif
    using vec3f = typename basic_vector<float32_t, 3, pipe4f>;
    using vec3i = typename basic_vector<int32_t, 3, pipe4i>;
    using vec2f = typename basic_vector<float32_t, 2, pipe4f>;
    using vec2i = typename basic_vector<int32_t, 2, pipe4i>;
    using vec1f = typename basic_vector<float32_t, 1, pipe4f>;
    using vec1i = typename basic_vector<int32_t, 1, pipe4f>;
}