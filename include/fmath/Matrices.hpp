#pragma once
#include "Matrix.hpp"
#include "Vector.hpp"
// All transform matrices uses right hand coordinate system.
// And All transform functions starts with M.
namespace Fma {
    // Basic transforMation Matrix.
    Mat4x4f MTranslate(const Vec3f& v);
    Mat3x3f MTranslate(const Vec2f& v);
    Mat4x4f MScale(const Vec3f& v);
    Mat3x3f MScale(const Vec2f& v);
    Mat4x4f MRotate(float rad, const Vec3f& k);
    Mat3x3f MRotate(float rad, const Vec2f& k);
    /////////////////////////////////////////////////
    // MVP Matrices.
    /////////////////////////////////////////////////
    // Gaze Matrix is same as glm's lookAt.
    // Parameter 1 is e(eye) position and P2 is look at(a) Vector and third is u(up) direction.
    // This gaze will set front to -z and up to y and x to right. (OpenGL default)
    Mat4x4f MGaze(const Vec3f& e, const Vec3f& a, const Vec3f& u);
    // Orthographic Matrix.
    // info should be a float[6], the elem should be:
    // {left, right, bottom, top, near, far}
    Mat4x4f MOrtho(float l, float r, float b, float t, float n, float f);
    // Perspective Matrix.
    // Parameters are: fov(Field of view) how(height / width) zn(z-near) zf(z-far)
    Mat4x4f MPersp(float fov, float how, float zn, float zf);
}