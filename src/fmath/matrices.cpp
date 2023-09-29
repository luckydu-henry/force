#include <fmath/matrices.hpp>

namespace force::math {
    namespace matrices {
        mat4x4f translate(const vec3f& v) {
            return {
                1.0f, 0.0f, 0.0f, v[0],
                0.0f, 1.0f, 0.0f, v[1],
                0.0f, 0.0f, 1.0f, v[2],
                0.0f, 0.0f, 0.0f, 1.0f
            };
        }
        mat3x3f translate(const vec2f& v) {
            return {
                1.0f, 0.0f, v[0],
                0.0f, 1.0f, v[1],
                0.0f, 0.0f, 1.0f,
            };
        }
        mat4x4f scale(const vec3f& v) {
            return {
                v[0], 0.0f, 0.0f, 0.0f,
                0.0f, v[1], 0.0f, 0.0f,
                0.0f, 0.0f, v[2], 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            };
        }
        mat3x3f scale(const vec2f& v) {
            return { v[0], 0.0f, 0.0f, 0.0f, v[1], 0.0f, 0.0f, 0.0f, 1.0f, };
        }
        mat4x4f rotate(float32_t rad, const vec3f& k) {
            mat4x4f i = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
            mat4x4f Rk = { 0.0f, -k[2], k[1], 0.0f, k[2], 0.0f, -k[0], 0.0f, -k[1], k[0], 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
            return mat4x4f{ i } + (Rk * Rk) * (1.f - cos(rad)) + Rk * sin(rad);
        }
        mat3x3f rotate(float32_t rad, const vec2f& k) {
            return {
                cos(rad), -sin(rad), (-cos(rad) + 1) * k[0] + sin(rad) * k[1],
                sin(rad), cos(rad), -sin(rad) * k[0] + (-cos(rad) + 1) * k[1],
                0,0,1
            };
        }
        /////////////////////////////////////
        // Viewport transformation matrices.
        /////////////////////////////////////
        mat4x4f gaze(const vec3f& e, const vec3f& a, const vec3f& up) {
            vec3f N = norm(a - e);
            vec3f U = norm(cross(N, up));
            vec3f V = cross(U, N);
            mat4x4f M = IdMat<mat4x4f>();

            M[0] = *U;
            M[1] = *V;
            M[2] = *(-N);

            M[0][3] = -dot(U, e); M[1][3] = -dot(V, e); M[2][3] = dot(N, e);

            return M;
        }
        mat4x4f ortho(float32_t l, float32_t r, float32_t b, float32_t t, float32_t n, float32_t f) {
            return {
                2 / (r - l),0,0,(-l - r) / (r - l),
                0, 2 / (t - b),0,(-b - t) / (t - b),
                0,0,2 / (f - n),(-n - f) / (f - n),
                0,0,0,1
            };
        }
        mat4x4f persp(float32_t fov, float32_t recpAspect, float32_t zn, float32_t zf) {
            return {
                recpAspect * cot(0.5f * fov), 0.f, 0.f, 0.f,
                0.f, cot(0.5f * fov), 0.f, 0.f,
                0.f, 0.f, (zf + zn) / (zn - zf),-(2.f * zn * zf) / (zn - zf),
                0.f, 0.f, 1.f, 0.f
            };
        }
    }
}