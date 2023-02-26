#ifndef _FORCE_F32_VEC2_H_
#define _FORCE_F32_VEC2_H_

#include "../force_core.hpp"

namespace force::f32 {

    class vec2 : public basic_vector<vec2, float, 2> {
    public:

        vec2(float x, float y);
        vec2(const vec2&);
        vec2(vec2&&);
        vec2(const float* _arr);

        vec2&       operator=(const vec2&) noexcept;
        vec2&       operator=(vec2&&)      noexcept;

        vec2        operator-() noexcept;

        vec2        operator+(const vec2& v) noexcept;
        vec2        operator-(const vec2& v) noexcept;
        vec2        operator+(float s) noexcept;
        vec2        operator-(float s) noexcept;
        vec2        operator*(float s) noexcept;
        vec2        operator/(float s) noexcept;


        ~vec2() = default;
    };
    [[nodiscard]] float          dot(const vec2& v1, const vec2& v2);
    // Actually this cross product will returns the area
    // of the two vectors, so that is a scalar.
    [[nodiscard]] float          cross(const vec2& v1, const vec2& v2);

    [[nodiscard]] float          modulus(const vec2& v);
}

#endif //! _FORCE_F32_VECTOR_H_
