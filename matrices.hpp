#pragma once
#include "matrix.hpp"
#include "vector.hpp"
// All transformation uses right hand coordinate system.
namespace force {
    inline mat4x4 transform(const vec3& v) {
        const float d[4 * 4] = {
            1.0f, 0.0f, 0.0f, v[0],
            0.0f, 1.0f, 0.0f, v[1],
            0.0f, 0.0f, 1.0f, v[2],
            0.0f, 0.0f, 0.0f, 1.0f
        };
        return mat4x4(d);
    }
    inline mat3x3 transform(const vec2& v) {
        const float d[3 * 3] = {
            1.0f, 0.0f, v[0],
            0.0f, 1.0f, v[1],
            0.0f, 0.0f, 1.0f,
        };
        return mat3x3(d);
    }
    inline mat4x4 scale(const vec3& v) {
        const float d[4 * 4] = {
            v[0], 0.0f, 0.0f, 0.0f,
            0.0f, v[1], 0.0f, 0.0f,
            0.0f, 0.0f, v[2], 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
        return mat4x4(d);
    }
    inline mat3x3 scale(const vec2& v) {
        const float d[3 * 3] = {
            v[0], 0.0f, 0.0f,
            0.0f, v[1], 0.0f,
            0.0f, 0.0f, 1.0f,
        };
        return mat3x3(d);
    }
    inline mat4x4 rotate(float rad, const vec3& k) {
        float  i[4 * 4] = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
        float  r[4 * 4] = {
            0.0f, -k[2], k[1], 0.0f,
            k[2], 0.0f, -k[0], 0.0f,
            -k[1], k[0], 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f
        };
        mat4x4 Rk = r;
        return mat4x4{ i } + (Rk * Rk) * (1.f - ::force::cos(rad)) + Rk * ::force::sin(rad);
    }
    inline mat3x3 rotate(float rad, const vec2& k) {
        float d[3 * 3] = {
            ::force::cos(rad), -::force::sin(rad), (-::force::cos(rad) + 1) * k[0] + ::force::sin(rad) * k[1],
            ::force::sin(rad), ::force::cos(rad), -::force::sin(rad) * k[0] + (-::force::cos(rad) + 1) * k[1],
            0,0,1
        };
        return mat3x3(d);
    }
}