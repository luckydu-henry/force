#include "mat2x2.h"
#include "vec2.h"
#include <cmath>

namespace force::f32 {
    mat2x2::mat2x2(float v11, float v21, float v12, float v22) {
        _M_mat[0][0] = v11;
        _M_mat[1][0] = v21;
        _M_mat[0][1] = v12;
        _M_mat[1][1] = v22;
    }
    mat2x2::mat2x2(const vec2& v1, const vec2& v2) {
        _M_mat[0][0] = v1[0];
        _M_mat[1][0] = v1[1];
        _M_mat[0][1] = v2[0];
        _M_mat[1][1] = v2[1];
    }
    mat2x2::mat2x2(const mat2x2& _right) {
        _M_mat[0][0] = _right._M_mat[0][0];
        _M_mat[1][0] = _right._M_mat[1][0];
        _M_mat[0][1] = _right._M_mat[0][1];
        _M_mat[1][1] = _right._M_mat[1][1];
    }
    mat2x2::mat2x2(mat2x2&& _right) {
        _M_mat[0][0] = _right._M_mat[0][0];
        _M_mat[1][0] = _right._M_mat[1][0];
        _M_mat[0][1] = _right._M_mat[0][1];
        _M_mat[1][1] = _right._M_mat[1][1];

        _right._M_mat[0][0] = 0.f;
        _right._M_mat[1][0] = 0.f;
        _right._M_mat[0][1] = 0.f;
        _right._M_mat[1][1] = 0.f;
    }
    mat2x2& mat2x2::operator=(const mat2x2& _right) {
        _M_mat[0][0] = _right._M_mat[0][0];
        _M_mat[1][0] = _right._M_mat[1][0];
        _M_mat[0][1] = _right._M_mat[0][1];
        _M_mat[1][1] = _right._M_mat[1][1];
        return *this;
    }
    mat2x2& mat2x2::operator=(mat2x2&& _right) {
        _M_mat[0][0] = _right._M_mat[0][0];
        _M_mat[1][0] = _right._M_mat[1][0];
        _M_mat[0][1] = _right._M_mat[0][1];
        _M_mat[1][1] = _right._M_mat[1][1];

        _right._M_mat[0][0] = 0.f;
        _right._M_mat[1][0] = 0.f;
        _right._M_mat[0][1] = 0.f;
        _right._M_mat[1][1] = 0.f;
        return *this;
    }
    mat2x2 mat2x2::operator+(const mat2x2 & _right) {
        return {
            _M_mat[0][0] + _right._M_mat[0][0],
            _M_mat[1][0] + _right._M_mat[1][0],
            _M_mat[0][1] + _right._M_mat[0][1],
            _M_mat[1][1] + _right._M_mat[1][1]
        };
    }
    mat2x2 mat2x2::operator-(const mat2x2& _right) {
        return {
            _M_mat[0][0] - _right._M_mat[0][0],
            _M_mat[1][0] - _right._M_mat[1][0],
            _M_mat[0][1] - _right._M_mat[0][1],
            _M_mat[1][1] - _right._M_mat[1][1]
        };
    }
    mat2x2 mat2x2::operator+(float s) {
        return {
           _M_mat[0][0] + s,
           _M_mat[1][0] + s,
           _M_mat[0][1] + s,
           _M_mat[1][1] + s
        };
    }
    mat2x2 mat2x2::operator-(float s) {
        return {
           _M_mat[0][0] - s,
           _M_mat[1][0] - s,
           _M_mat[0][1] - s,
           _M_mat[1][1] - s
        };
    }
    mat2x2 mat2x2::operator*(float s) {
        return {
            _M_mat[0][0] * s,
            _M_mat[1][0] * s,
            _M_mat[0][1] * s,
            _M_mat[1][1] * s
        };
    }
    mat2x2 mat2x2::operator/(float s) {
        return {
            _M_mat[0][0] / s,
            _M_mat[1][0] / s,
            _M_mat[0][1] / s,
            _M_mat[1][1] / s
        };
    }
    mat2x2 mat2x2::operator*(const mat2x2& _right) {

        mat2x2 mat{ 0.f, 0.f, 
                    0.f, 0.f };
        mat[0][0] = _M_mat[0][0] * _right[0][0] + _M_mat[0][1] * _right[1][0];
        mat[1][0] = _M_mat[1][0] * _right[0][0] + _M_mat[1][1] * _right[1][0];
        mat[0][1] = _M_mat[0][0] * _right[0][1] + _M_mat[0][1] * _right[1][1];
        mat[1][1] = _M_mat[1][0] * _right[0][1] + _M_mat[1][1] * _right[1][1];
        return mat;
    }
    vec2    mat2x2::operator*(const vec2& _right) {
        vec2 x = vec2{ _M_mat[0][0], _M_mat[1][0] };
        vec2 y = vec2{ _M_mat[0][1], _M_mat[1][1] };
        return x * _right[0] + y * _right[1];
    }
    const float* mat2x2::data() const {
        static float v[4] = { _M_mat[0][0], _M_mat[1][0], _M_mat[0][1], _M_mat[1][1] };
        return v;
    }

    mat2x2 make_unit2dmat() {
        return mat2x2{1.f, 0.f, 0.f, 1.f};
    }
    mat2x2 make_rotate(float _Theta) {

        mat2x2 _Mat = { 1.f, 0.f, 0.f, 1.f };

        _Mat[0][0] =  cosf(_Theta);
        _Mat[1][0] =  sinf(_Theta);
        _Mat[0][1] = -sinf(_Theta);
        _Mat[1][1] =  cosf(_Theta);

        return _Mat;
    }
    mat2x2 make_scale(float _Ratio) {
        mat2x2 _Mat = { 1.f, 0.f, 0.f, 1.f };
        _Mat *= _Ratio;
        return _Mat;
    }
}