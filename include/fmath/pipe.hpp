#pragma once
#include "basic_pipe.hpp"
namespace force::math {
    // pipe types for common Vectors.
    using pipe4f = typename basic_pipe<float32_t, 4>;
    using pipe4i = typename basic_pipe<int32_t, 4>;
    using pipe4u = typename basic_pipe<uint32_t, 4>;
}
