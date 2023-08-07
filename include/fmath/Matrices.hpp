#pragma once
#include "Matrix.hpp"
#include "Vector.hpp"
// All transforMation uses right hand coordinate system.
namespace Fma::Matrices {
    // Basic transforMation Matrix.
    inline Mat4x4f translate(const Vec3f& v) {
        return {
            1.0f, 0.0f, 0.0f, v[0],
            0.0f, 1.0f, 0.0f, v[1],
            0.0f, 0.0f, 1.0f, v[2],
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }
    inline Mat3x3f translate(const Vec2f& v) {
        return {
            1.0f, 0.0f, v[0],
            0.0f, 1.0f, v[1],
            0.0f, 0.0f, 1.0f,
        };
    }
    inline Mat4x4f scale(const Vec3f& v) {
        return {
            v[0], 0.0f, 0.0f, 0.0f,
            0.0f, v[1], 0.0f, 0.0f,
            0.0f, 0.0f, v[2], 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }
    inline Mat3x3f scale(const Vec2f& v) {
        return { v[0], 0.0f, 0.0f, 0.0f, v[1], 0.0f, 0.0f, 0.0f, 1.0f, };
    }
    inline Mat4x4f rotate(float rad, const Vec3f& k) {
        Mat4x4f i = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
        Mat4x4f Rk = { 0.0f, -k[2], k[1], 0.0f, k[2], 0.0f, -k[0], 0.0f, -k[1], k[0], 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
        return Mat4x4f{ i } + (Rk * Rk) * (1.f - ::Fma::cos(rad)) + Rk * ::Fma::sin(rad);
    }
    inline Mat3x3f rotate(float rad, const Vec2f& k) {
        return {
            ::Fma::cos(rad), -::Fma::sin(rad), (-::Fma::cos(rad) + 1) * k[0] + ::Fma::sin(rad) * k[1],
            ::Fma::sin(rad), ::Fma::cos(rad), -::Fma::sin(rad) * k[0] + (-::Fma::cos(rad) + 1) * k[1],
            0,0,1
        };
    }
    /////////////////////////////////////////////////
    // Pipeport transforMation Matrices.
    /////////////////////////////////////////////////

    // Gaze Matrix is same as glm's lookAt.
    // Parameter 1 is e(eye) position and P2 is look at Vector and third is u(up) direction.
    // This gaze will set front to -z and up to y and x to right. (OpenGL default)
    inline Mat4x4f gaze(const Vec3f& e, const Vec3f& a, const Vec3f& up) {
        Vec3f N = normalize(a - e);
        Vec3f U = normalize(cross(N, up));
        Vec3f V = cross(U, N);
        Mat4x4f M = identity<Mat4x4f>();

        M[0]    = *U;         M[1]    = *V;         M[2]    = *(-N);
        M[0][3] = -dot(U, e); M[1][3] = -dot(V, e); M[2][3] = dot(N, e);

        return M;
    }
    // Orthographic Matrix.
    // info should be a float[6], the elem should be:
    // {left, right, bottom, top, near, far}
    inline Mat4x4f ortho(float l, float r, float b, float t, float n, float f) {
        return {
            2 / (r - l),0,0,(-l - r) / (r - l),
            0, 2 / (t - b),0,(-b - t) / (t - b),
            0,0,2 / (f - n),(-n - f) / (f - n),
            0,0,0,1
        };
    }
    // Perspective Matrix.
    // info should be a float[4], the elem should be:
    // {fov, height / width, z-near, z-far}
    inline Mat4x4f persp(float fov, float recp_aspect, float zn, float zf) {
        return {
            recp_aspect * ::Fma::cot(0.5f * fov), 0, 0, 0,
            0, ::Fma::cot(0.5f * fov), 0, 0,
            0, 0, (zf + zn) / (zn - zf),-(2 * zn * zf) / (zn - zf),
            0,0,1,0
        };
    }
}