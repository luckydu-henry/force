#include "vec2.h"
#include "fmath.hpp"

namespace force::__opm32 {
    vec2::vec2(float x, float y) {
        _M_vec[0] = x;
        _M_vec[1] = y;
    }
    vec2::vec2(const vec2& _right) {
        _M_vec[0] = _right[0];
        _M_vec[1] = _right[1];
    }
    vec2::vec2(vec2&& _right) {
        _M_vec[0] = _right[0];
        _M_vec[1] = _right[1];
    }
    vec2::vec2(const float* _arr) {
        at(0) = _arr[0];
        at(1) = _arr[1];
    }
    vec2& vec2::operator=(const vec2& v) noexcept {
        (*this)[0] = v[0];
        (*this)[1] = v[1];
        return *this;
    }
    vec2& vec2::operator=(vec2&& v) noexcept {
        _M_vec[0] = v[0];
        _M_vec[1] = v[1];
        return *this;
    }
    vec2 vec2::operator-() noexcept {
        return {
            0.f - _M_vec[0],
            0.f - _M_vec[1]
        };
    }
    vec2 vec2::operator+(const vec2& v) noexcept {
        return {
            _M_vec[0] + v[0],
            _M_vec[1] + v[1]
        };
    }
    vec2 vec2::operator-(const vec2& v) noexcept {
        return {
            _M_vec[0] - v[0],
            _M_vec[1] - v[1]
        };
    }
    vec2 vec2::operator+(float s) noexcept {
        return {
            _M_vec[0] + s,
            _M_vec[1] + s
        };
    }
    vec2 vec2::operator-(float s) noexcept {
        return {
           _M_vec[0] - s,
           _M_vec[1] - s
        };
    }
    vec2 vec2::operator*(float s) noexcept {
        return {
            _M_vec[0] * s,
            _M_vec[1] * s
        };
    }
    vec2 vec2::operator/(float s) noexcept {
        return {
            _M_vec[0] / s,
            _M_vec[1] / s
        };
    }
    float dot(const vec2& v1, const vec2& v2) {
        return v1[0] * v2[0] + v1[1] * v2[1];
    }
    float cross(const vec2& v1, const vec2& v2) {
        return v1[0] * v2[1] - v2[0] * v1[1];
    }
    float modulus(const vec2& v) {
        return sqrt(v[0] * v[0] + v[1] * v[1]);
    }
}
