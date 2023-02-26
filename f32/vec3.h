#ifndef _FORCE_F32_VEC3_H_
#define _FORCE_F32_VEC3_H_
#include "../force_core.hpp"
namespace force::f32 {

    class vec3 : public basic_vector<vec3, float, 3> {
    public:

        vec3(float x, float y, float z);
        vec3(const vec3&);
        vec3(vec3&&);
        vec3(const float* _arr);

        vec3& operator=(const vec3&) noexcept;
        vec3& operator=(vec3&&)      noexcept;

        vec3        operator-() noexcept;

        vec3        operator+(const vec3& v) noexcept;
        vec3        operator-(const vec3& v) noexcept;
        vec3        operator+(float s) noexcept;
        vec3        operator-(float s) noexcept;
        vec3        operator*(float s) noexcept;
        vec3        operator/(float s) noexcept;


        ~vec3() = default;
    };

    [[nodiscard]] float          dot(const vec3& v1, const vec3& v2);
    [[nodiscard]] vec3           cross(const vec3& v1, const vec3& v2);
    [[nodiscard]] float          modulus(const vec3& v);
}
#endif //! _FORCE_F32_VEC3_H_

