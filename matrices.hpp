#pragma once
#include "matrix.hpp"
#include "vector.hpp"
// All transformation uses right hand coordinate system.
namespace force::matrices {
    // Basic transformation matrix.
    inline mat4x4f translate(const vec3f& v) {
        return {
            1.0f, 0.0f, 0.0f, v[0],
            0.0f, 1.0f, 0.0f, v[1],
            0.0f, 0.0f, 1.0f, v[2],
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }
    inline mat3x3f translate(const vec2f& v) {
        return {
            1.0f, 0.0f, v[0],
            0.0f, 1.0f, v[1],
            0.0f, 0.0f, 1.0f,
        };
    }
    inline mat4x4f scale(const vec3f& v) {
        return {
            v[0], 0.0f, 0.0f, 0.0f,
            0.0f, v[1], 0.0f, 0.0f,
            0.0f, 0.0f, v[2], 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }
    inline mat3x3f scale(const vec2f& v) {
        return { v[0], 0.0f, 0.0f, 0.0f, v[1], 0.0f, 0.0f, 0.0f, 1.0f, };
    }
    inline mat4x4f rotate(float rad, const vec3f& k) {
        mat4x4f i = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
        mat4x4f Rk = { 0.0f, -k[2], k[1], 0.0f, k[2], 0.0f, -k[0], 0.0f, -k[1], k[0], 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
        return mat4x4f{ i } + (Rk * Rk) * (1.f - ::force::cos(rad)) + Rk * ::force::sin(rad);
    }
    inline mat3x3f rotate(float rad, const vec2f& k) {
        return {
            ::force::cos(rad), -::force::sin(rad), (-::force::cos(rad) + 1) * k[0] + ::force::sin(rad) * k[1],
            ::force::sin(rad), ::force::cos(rad), -::force::sin(rad) * k[0] + (-::force::cos(rad) + 1) * k[1],
            0,0,1
        };
    }
    /////////////////////////////////////////////////
    // Viewport transformation matrices.
    /////////////////////////////////////////////////

    // Gaze matrix is same as glm's lookAt.
    // Parameter 1 is e(eye) position and P2 is look at vector and third is u(up) direction.
    // This gaze will set front to -z and up to y and x to right. (OpenGL default)
    inline mat4x4f gaze(const vec3f& e, const vec3f& a, const vec3f& up) {
        vec3f N = normalize(a - e);
        vec3f U = normalize(cross(N, up));
        vec3f V = cross(U, N);
        mat4x4f M = identity<mat4x4f>();

        M[0]    = *U;         M[1]    = *V;         M[2]    = *(-N);
        M[0][3] = -dot(U, e); M[1][3] = -dot(V, e); M[2][3] = dot(N, e);

        return M;
    }
    // Orthographic matrix.
    // info should be a float[6], the elem should be:
    // {left, right, bottom, top, near, far}
    inline mat4x4f ortho(float l, float r, float b, float t, float n, float f) {
        return {
            2 / (r - l),0,0,(-l - r) / (r - l),
            0, 2 / (t - b),0,(-b - t) / (t - b),
            0,0,2 / (f - n),(-n - f) / (f - n),
            0,0,0,1
        };
    }
    // Perspective matrix.
    // info should be a float[4], the elem should be:
    // {fov, height / width, z-near, z-far}
    inline mat4x4f persp(float fov, float recp_aspect, float zn, float zf) {
        return {
            recp_aspect * ::force::cot(0.5f * fov), 0, 0, 0,
            0, ::force::cot(0.5f * fov), 0, 0,
            0, 0, (zf + zn) / (zn - zf),-(2 * zn * zf) / (zn - zf),
            0,0,1,0
        };
    }
}