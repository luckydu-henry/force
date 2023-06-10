#include "vec3.h"
#include "fmath.hpp"

namespace force::__opm32 {
    vec3::vec3(float x, float y, float z) {
        _M_vec[0] = x;
        _M_vec[1] = y;
        _M_vec[2] = z;
    }
    vec3::vec3(const vec3& _right) {
        _M_vec[0] = _right[0];
        _M_vec[1] = _right[1];
        _M_vec[2] = _right[2];
    }
    vec3::vec3(vec3&& _right) {
        _M_vec[0] = _right[0];
        _M_vec[1] = _right[1];
        _M_vec[2] = _right[2];

        _right[0] = 0.f;
        _right[1] = 0.f;
        _right[2] = 0.f;
    }
    vec3::vec3(const float* _arr) {
        _M_vec[0] = _arr[0];
        _M_vec[1] = _arr[1];
        _M_vec[2] = _arr[2];
    }
    vec3& vec3::operator=(const vec3& _right) noexcept {
        _M_vec[0] = _right[0];
        _M_vec[1] = _right[1];
        _M_vec[2] = _right[2];
        return *this;
    }
    vec3& vec3::operator=(vec3&& _right) noexcept {
        _M_vec[0] = _right[0];
        _M_vec[1] = _right[1];
        _M_vec[2] = _right[2];

        _right[0] = 0.f;
        _right[1] = 0.f;
        _right[2] = 0.f;
        return *this;
    }
    vec3 vec3::operator-() noexcept {
        return {
            0.f - _M_vec[0],
            0.f - _M_vec[1],
            0.f - _M_vec[2]
        };
    }
    vec3 vec3::operator+(const vec3& v) noexcept {
        return {
            _M_vec[0] + v[0],
            _M_vec[1] + v[1],
            _M_vec[2] + v[2]
        };
    }
    vec3 vec3::operator-(const vec3& v) noexcept {
        return {
            _M_vec[0] - v[0],
            _M_vec[1] - v[1],
            _M_vec[2] - v[2]
        };
    }
    vec3 vec3::operator+(float s) noexcept {
        return {
            _M_vec[0] + s,
            _M_vec[1] + s,
            _M_vec[2] + s
        };
    }
    vec3 vec3::operator-(float s) noexcept {
        return {
           _M_vec[0] - s,
           _M_vec[1] - s,
           _M_vec[2] - s
        };
    }
    vec3 vec3::operator*(float s) noexcept {
        return {
            _M_vec[0] * s,
            _M_vec[1] * s,
            _M_vec[2] * s
        };
    }
    vec3 vec3::operator/(float s) noexcept {
        return {
            _M_vec[0] / s,
            _M_vec[1] / s,
            _M_vec[2] / s
        };
    }
    float dot(const vec3& v1, const vec3& v2) {
        return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
    }
    vec3 cross(const vec3& v1, const vec3& v2) {
        return {
            v1[1] * v2[2] - v2[1] * v1[2],
            v1[0] * v2[2] - v2[0] * v1[2],
            v1[0] * v2[1] - v2[0] * v1[1]
        };
    }
    float modulus(const vec3& v) {
        return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    }
}