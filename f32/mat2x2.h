#ifndef _FORCE_F32_MAT2X2_H_
#define _FORCE_F32_MAT2X2_H_
#include "../force_core.hpp"
namespace force::f32 {

    typedef class vec2 vec2;

    class mat2x2 : public basic_matrix<mat2x2, float, 2, 2>{
    public:
        // Two basic way to construct a mat2x2.
        mat2x2(const vec2& v1, const vec2& v2);
        mat2x2(float v11, float v21, float v12, float v22);
        mat2x2(const mat2x2&);
        mat2x2(mat2x2&&);


        mat2x2&        operator=(const mat2x2&);
        mat2x2&        operator=(mat2x2&&);

        mat2x2         operator+(const mat2x2&);
        mat2x2         operator-(const mat2x2&);
        mat2x2         operator+(float s);
        mat2x2         operator-(float s);
        mat2x2         operator*(float s);
        mat2x2         operator/(float s);

        // Matrix multiplication
        mat2x2         operator*(const mat2x2&);

        // Vector multiplication
        vec2           operator*(const vec2&);

        const float*   data() const;

        ~mat2x2() = default;
    };

    [[nodiscard]]    mat2x2 make_unit2dmat();
    [[nodiscard]]    mat2x2 make_rotate(float _Rad);
    [[nodiscard]]    mat2x2 make_scale(float  _Ratio);
}
#endif //! _FORCE_F32_MAT2X2_H_