#pragma once
#include "matrix.hpp"
#include "vector.hpp"
// All transform matrices uses right hand coordinate system.
// And All transform functions starts with M.
namespace force::math {
    namespace matrices {
        // Basic transforMation Matrix.
        mat4x4f translate(const vec3f& v);
        mat3x3f translate(const vec2f& v);
        mat4x4f scale(const vec3f& v);
        mat3x3f scale(const vec2f& v);
        mat4x4f rotate(float32_t rad, const vec3f& k);
        mat3x3f rotate(float32_t rad, const vec2f& k);
        /////////////////////////////////////////////////
        // MVP Matrices.
        /////////////////////////////////////////////////
        // Gaze Matrix is same as glm's lookAt.
        // Parameter 1 is e(eye) position and P2 is look at(a) Vector and third is u(up) direction.
        // This gaze will set front to -z and up to y and x to right. (OpenGL default)
        mat4x4f gaze(const vec3f& e, const vec3f& a, const vec3f& u);
        // Orthographic Matrix.
        // info should be a float32_t[6], the elem should be:
        // {left, right, bottom, top, near, far}
        mat4x4f ortho(float32_t l, float32_t r, float32_t b, float32_t t, float32_t n, float32_t f);
        // Perspective Matrix.
        // Parameters are: fov(ield of view) how(height / width) zn(z-near) zf(z-far)
        mat4x4f persp(float32_t fov, float32_t how, float32_t zn, float32_t zf);
    }
}