#pragma once
#include "simd.hpp"         // for vectorlized initialization
#include "basic_vector.hpp" // for vector multiplication.

#if defined _WIN32
#    pragma warning(disable:4996) // no warning for memcpy
#endif

namespace force {

    template <typename Ty>
    class basic_mat4x4;

    template <>
    class alignas(64) basic_mat4x4<float> {
    protected:
        alignas(64) float m_data[4][4];
    public:
        constexpr explicit basic_mat4x4() : m_data() {}
        constexpr explicit basic_mat4x4(
            float a1, float a2, float a3, float a4,
            float b1, float b2, float b3, float b4,
            float c1, float c2, float c3, float c4,
            float d1, float d2, float d3, float d4) noexcept : m_data() {
            // Fuck you, so annoying!
            m_data[0][0] = a1; m_data[0][1] = a2; m_data[0][2] = a3; m_data[0][3] = a4;
            m_data[1][0] = b1; m_data[1][1] = b2; m_data[1][2] = b3; m_data[1][3] = b4;
            m_data[2][0] = c1; m_data[2][1] = c2; m_data[2][2] = c3; m_data[2][3] = c4;
            m_data[3][0] = d1; m_data[3][1] = d2; m_data[3][2] = d3; m_data[3][3] = d4;
        }
#if defined FORCE_USE_SIMD_MATRIX

#else
        explicit basic_mat4x4(float* a, float* b, float* c, float* d) : m_data() {
            memcpy(m_data[0], a, 4); 
            memcpy(m_data[1], b, 4);
            memcpy(m_data[2], c, 4);
            memcpy(m_data[3], d, 4);
        }
        explicit basic_mat4x4(const basic_mat4x4& right) noexcept : m_data() {
            memcpy(m_data[0], right.m_data[0], 4);
            memcpy(m_data[1], right.m_data[1], 4);
            memcpy(m_data[2], right.m_data[2], 4);
            memcpy(m_data[3], right.m_data[3], 4);
        }
        explicit basic_mat4x4(basic_mat4x4&& right) noexcept : m_data() {
            memcpy(m_data[0], right.m_data[0], 4);
            memcpy(m_data[1], right.m_data[1], 4);
            memcpy(m_data[2], right.m_data[2], 4);
            memcpy(m_data[3], right.m_data[3], 4);
        }
        basic_mat4x4& operator=(const basic_mat4x4& right) {
            memcpy(m_data[0], right.m_data[0], 4);
            memcpy(m_data[1], right.m_data[1], 4);
            memcpy(m_data[2], right.m_data[2], 4);
            memcpy(m_data[3], right.m_data[3], 4);
        }
        basic_mat4x4& operator+=(const basic_mat4x4& right) {
            const auto data = right.m_data;
            m_data[0][0] += data[0][0]; m_data[0][1] += data[0][1]; m_data[0][2] += data[0][2]; m_data[0][3] += data[0][3];
            m_data[1][0] += data[1][0]; m_data[1][1] += data[1][1]; m_data[1][2] += data[1][2]; m_data[1][3] += data[1][3];
            m_data[2][0] += data[2][0]; m_data[2][1] += data[2][1]; m_data[2][2] += data[2][2]; m_data[2][3] += data[2][3];
            m_data[3][0] += data[3][0]; m_data[3][1] += data[3][1]; m_data[3][2] += data[3][2]; m_data[3][3] += data[3][3];
            return *this;
        }
        basic_mat4x4& operator-=(const basic_mat4x4& right) {
            const auto data = right.m_data;
            m_data[0][0] -= data[0][0]; m_data[0][1] -= data[0][1]; m_data[0][2] -= data[0][2]; m_data[0][3] -= data[0][3];
            m_data[1][0] -= data[1][0]; m_data[1][1] -= data[1][1]; m_data[1][2] -= data[1][2]; m_data[1][3] -= data[1][3];
            m_data[2][0] -= data[2][0]; m_data[2][1] -= data[2][1]; m_data[2][2] -= data[2][2]; m_data[2][3] -= data[2][3];
            m_data[3][0] -= data[3][0]; m_data[3][1] -= data[3][1]; m_data[3][2] -= data[3][2]; m_data[3][3] -= data[3][3];
            return *this;
        }
        basic_mat4x4& operator*=(float k) {
            m_data[0][0] *= k; m_data[0][1] *= k; m_data[0][2] *= k; m_data[0][3] *= k;
            m_data[1][0] *= k; m_data[1][1] *= k; m_data[1][2] *= k; m_data[1][3] *= k;
            m_data[2][0] *= k; m_data[2][1] *= k; m_data[2][2] *= k; m_data[2][3] *= k;
            m_data[3][0] *= k; m_data[3][1] *= k; m_data[3][2] *= k; m_data[3][3] *= k;
            return *this;
        }
        basic_mat4x4& operator/=(float k) {
            m_data[0][0] /= k; m_data[0][1] /= k; m_data[0][2] /= k; m_data[0][3] /= k;
            m_data[1][0] /= k; m_data[1][1] /= k; m_data[1][2] /= k; m_data[1][3] /= k;
            m_data[2][0] /= k; m_data[2][1] /= k; m_data[2][2] /= k; m_data[2][3] /= k;
            m_data[3][0] /= k; m_data[3][1] /= k; m_data[3][2] /= k; m_data[3][3] /= k;
            return *this;
        }
#endif //! FORCE_USE_SIMD_MATRIX
        virtual ~basic_mat4x4() = default;
    };
}