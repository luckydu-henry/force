#pragma once
#include "matrix.hpp"
#include "vector.hpp"
// All transformation uses right hand coordinate system.
namespace force::matrices {
    // Basic transformation matrix.
    inline mat4x4 translate(const vec3& v) {
        const float d[4 * 4] = {
            1.0f, 0.0f, 0.0f, v[0],
            0.0f, 1.0f, 0.0f, v[1],
            0.0f, 0.0f, 1.0f, v[2],
            0.0f, 0.0f, 0.0f, 1.0f
        };
        return mat4x4(d);
    }
    inline mat3x3 translate(const vec2& v) {
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
    /////////////////////////////////////////////////
    // Viewport transformation matrices.
    /////////////////////////////////////////////////

    // Gaze matrix is same as glm's lookAt.
    // Parameter 1 is e(eye) position and P2 is look at vector and third is u(up) direction.
    // This gaze will set front to -z and up to y and x to right. (OpenGL default)
    inline mat4x4 gaze(const vec3& e, const vec3& a, const vec3& up) {
        vec3 N = normallize(a - e);
        vec3 U = normallize(cross(N, up));
        vec3 V = cross(U, N);
        mat4x4 M = mat4x4::identity;
        std::memcpy(M[0], U.data(), 3);
        std::memcpy(M[1], V.data(), 3);
        std::memcpy(M[2], (-N).data(), 3);
        M[0][3] = -dot(U, e);
        M[1][3] = -dot(V, e);
        M[2][3] =  dot(N, e);
        return M;
    }
    // Orthographic matrix.
    // info should be a float[6], the elem should be:
    // {left, right, bottom, top, near, far}
    inline mat4x4 ortho(float l, float r, float b, float t, float n, float f) {
        float d[4 * 4] = {
            2 / (r - l),0,0,(-l - r) / (r - l),
            0, 2 / (t - b),0,(-b - t) / (t - b),
            0,0,2 / (f - n),(-n - f) / (f - n),
            0,0,0,1
        };
        return mat4x4(d);
    }
    // Perspective matrix.
    // info should be a float[4], the elem should be:
    // {fov, width / height, z-near, z-far}
    inline mat4x4 persp(float fov, float aspect, float zn, float zf) {
        float d[4 * 4] = {
            (1 / aspect) * ::force::cot(0.5f * fov), 0, 0, 0,
            0, ::force::cot(0.5f * fov), 0, 0,
            0, 0, (zf + zn) / (zn - zf),-(2 * zn * zf) / (zn - zf),
            0,0,1,0
        };
        return mat4x4(d);
    }
}