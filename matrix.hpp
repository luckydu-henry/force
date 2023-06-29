#pragma once
#include "basic_matrix.hpp"
namespace force {
    template <typename Ty>
    class matrix2x2;
    template <typename Ty>
    class matrix3x3;
    template <typename Ty>
    class matrix4x4;

    template <>
    class matrix2x2<float> : public basic_mat32x4x4<float> {
    public:
        static constexpr unsigned int col = 2;
        static constexpr unsigned int row = 2;
        static constexpr float identity[2 * 2] = {
            1.0f, 0.0f,
            0.0f, 1.0f
        };

        matrix2x2() :basic_mat32x4x4<float>() {}
        matrix2x2(const basic_mat32x4x4<float>& right) :basic_mat32x4x4<float>(right) {
            std::memset(m_data + 2, 0, 4 * sizeof(float));
            std::memset(m_data + 3, 0, 4 * sizeof(float));
            m_data[0][2] = m_data[0][3] = m_data[1][2] = m_data[1][3] = 0;
        }
        matrix2x2(basic_mat32x4x4<float>&& right) :basic_mat32x4x4<float>(right) {
            std::memset(m_data + 2, 0, 4 * sizeof(float));
            std::memset(m_data + 3, 0, 4 * sizeof(float));
            m_data[0][2] = m_data[0][3] = m_data[1][2] = m_data[1][3] = 0;
        }
        // Input is a float[4] or a float[2][2] array, it could get wrong if you type in something wrong.
        matrix2x2(const float* ptr)               :basic_mat32x4x4<float>() {
            std::memcpy(m_data + 0, ptr + 0, 2 * sizeof(float));
            std::memcpy(m_data + 1, ptr + 2, 2 * sizeof(float));
        }

        const float* operator[](unsigned int i) const { if (i > 1) throw "Not a valid sub vector!"; return m_data[i]; }
        float*       operator[](unsigned int i)       { if (i > 1) throw "Not a valid sub vector!"; return m_data[i]; }

        ~matrix2x2() override = default;
    };



    template <>
    class matrix3x3<float> : public basic_mat32x4x4<float> {
    public:
        static constexpr unsigned int col = 3;
        static constexpr unsigned int row = 3;
        static constexpr float identity[3*3] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        };

        matrix3x3()                                    :basic_mat32x4x4<float>() {}
        matrix3x3(const basic_mat32x4x4<float>& right) :basic_mat32x4x4<float>(right) {
            std::memset(m_data + 3, 0, 4 * sizeof(float));
            m_data[0][3] = m_data[1][3] = m_data[2][3] = 0;
        }
        matrix3x3(basic_mat32x4x4<float>&& right)      :basic_mat32x4x4<float>(right) {
            std::memset(m_data + 3, 0, 4 * sizeof(float));
            m_data[0][3] = m_data[1][3] = m_data[2][3] = 0;
        }
        // Input is a float[9] or a float[3][3] array, it could get wrong if you type in something wrong.
        matrix3x3(const float* ptr)                    :basic_mat32x4x4<float>() { 
            std::memcpy(m_data + 0, ptr + 0, 3 * sizeof(float));
            std::memcpy(m_data + 1, ptr + 3, 3 * sizeof(float));
            std::memcpy(m_data + 2, ptr + 6, 3 * sizeof(float));
        }

        const float* operator[](unsigned int i) const { if (i > 2) throw "Not a valid sub vector!"; return m_data[i]; }
        float*       operator[](unsigned int i)       { if (i > 2) throw "Not a valid sub vector!"; return m_data[i]; }

        ~matrix3x3() override = default;
    };

    template <>
    class matrix4x4<float> : public basic_mat32x4x4<float> {
    public:
        static constexpr unsigned int col = 4;
        static constexpr unsigned int row = 4;
        static constexpr float identity[4 * 4] = {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        matrix4x4()                                    :basic_mat32x4x4<float>() {}
        matrix4x4(const basic_mat32x4x4<float>& right) :basic_mat32x4x4<float>(right) {}
        matrix4x4(basic_mat32x4x4<float>&& right)      :basic_mat32x4x4<float>(right) {}
        matrix4x4(const float* ptr)                    :basic_mat32x4x4<float>() {
            std::memcpy(m_data, ptr, 16 * sizeof(float)); 
        }

        const float* operator[](unsigned int i) const { return m_data[i]; }
        float*       operator[](unsigned int i)       { return m_data[i]; }

        ~matrix4x4() override = default;
    };

    using mat4x4 = matrix4x4<float>;
    using mat3x3 = matrix3x3<float>;
    using mat2x2 = matrix2x2<float>;

    template <typename Ty>
    struct matrix_traits : std::false_type {};
    template <>
    struct matrix_traits<mat4x4> : std::true_type {};
    template <>
    struct matrix_traits<mat3x3> : std::true_type {};
    template <>
    struct matrix_traits<mat2x2> : std::true_type {};
    template <typename Ty>
    concept matrix = matrix_traits<Ty>::value;

} //! namespace force