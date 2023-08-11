#include <fmath/Matrices.hpp>

namespace Fma {
    Mat4x4f MTranslate(const Vec3f& v) {
        return {
            1.0f, 0.0f, 0.0f, v[0],
            0.0f, 1.0f, 0.0f, v[1],
            0.0f, 0.0f, 1.0f, v[2],
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }
    Mat3x3f MTranslate(const Vec2f& v) {
        return {
            1.0f, 0.0f, v[0],
            0.0f, 1.0f, v[1],
            0.0f, 0.0f, 1.0f,
        };
    }
    Mat4x4f MScale(const Vec3f& v) {
        return {
            v[0], 0.0f, 0.0f, 0.0f,
            0.0f, v[1], 0.0f, 0.0f,
            0.0f, 0.0f, v[2], 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }
    Mat3x3f MScale(const Vec2f& v) {
        return { v[0], 0.0f, 0.0f, 0.0f, v[1], 0.0f, 0.0f, 0.0f, 1.0f, };
    }
    Mat4x4f MRotate(float rad, const Vec3f& k) {
        Mat4x4f i = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
        Mat4x4f Rk = { 0.0f, -k[2], k[1], 0.0f, k[2], 0.0f, -k[0], 0.0f, -k[1], k[0], 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
        return Mat4x4f{ i } + (Rk * Rk) * (1.f - Fcos(rad)) + Rk * Fsin(rad);
    }
    Mat3x3f MRotate(float rad, const Vec2f& k) {
        return {
            Fcos(rad), -Fsin(rad), (-Fcos(rad) + 1) * k[0] + Fsin(rad) * k[1],
            Fsin(rad), Fcos(rad), -Fsin(rad) * k[0] + (-Fcos(rad) + 1) * k[1],
            0,0,1
        };
    }
    /////////////////////////////////////
    // Viewport transformation matrices.
    /////////////////////////////////////
    Mat4x4f MGaze(const Vec3f& e, const Vec3f& a, const Vec3f& up) {
        Vec3f N = Norm(a - e);
        Vec3f U = Norm(Cross(N, up));
        Vec3f V = Cross(U, N);
        Mat4x4f M = IdMat<Mat4x4f>();

        M[0] = *U;
        M[1] = *V;
        M[2] = *(-N);

        M[0][3] = -Dot(U, e); M[1][3] = -Dot(V, e); M[2][3] = Dot(N, e);

        return M;
    }
    Mat4x4f MOrtho(float l, float r, float b, float t, float n, float f) {
        return {
            2 / (r - l),0,0,(-l - r) / (r - l),
            0, 2 / (t - b),0,(-b - t) / (t - b),
            0,0,2 / (f - n),(-n - f) / (f - n),
            0,0,0,1
        };
    }
    Mat4x4f MPersp(float fov, float recpAspect, float zn, float zf) {
        return {
            recpAspect * Fcot(0.5f * fov), 0.f, 0.f, 0.f,
            0.f, Fcot(0.5f * fov), 0.f, 0.f,
            0.f, 0.f, (zf + zn) / (zn - zf),-(2.f * zn * zf) / (zn - zf),
            0.f, 0.f, 1.f, 0.f
        };
    }
}