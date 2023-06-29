#pragma once
#include "simd.hpp"         // for vectorlized initialization
#include "basic_vector.hpp" // for vector multiplication.

#if defined _WIN32
#    pragma warning(disable:4996) // no warning for memcpy
#endif

namespace force {

    template <typename Ty>
    // The base of mat2x2 and mat3x3 and mat4x4
    class basic_mat32x4x4 {
    protected:
        union {
            alignas(16 * 4) Ty m_data[4][4];
#if defined FORCE_USE_SIMD_MATRIX
            alignas(16 * 4) simd::vec128<Ty>::type m_vdata[4];
#endif
        };
    public:
        using value_type = Ty;
        static constexpr unsigned int memsize = 64;

        constexpr basic_mat32x4x4() :m_data()                              { std::memset(m_data, 0, memsize); }
        constexpr basic_mat32x4x4(const basic_mat32x4x4& right) : m_data() { std::memcpy(m_data, (right.m_data), memsize); }
        constexpr basic_mat32x4x4(basic_mat32x4x4&& right) : m_data()      { std::memcpy(m_data, (right.m_data), memsize); }
#if defined FORCE_USE_SIMD_MATRIX
#else
        basic_mat32x4x4& operator= (const basic_mat32x4x4& right) {
            std::memcpy(m_data, (right.m_data), memsize);
            return *this; 
        }
        basic_mat32x4x4& operator+=(const basic_mat32x4x4& right) {
            for (std::size_t i = 0; i < 4; ++i)
                for (std::size_t j = 0; j < 4; ++j)
                    m_data[i][j] += right.m_data[i][j];
            return *this;
        }
        basic_mat32x4x4& operator-=(const basic_mat32x4x4& right) {
            for (std::size_t i = 0; i < 4; ++i)
                for (std::size_t j = 0; j < 4; ++j)
                    m_data[i][j] -= right.m_data[i][j];
            return *this;
        }
        basic_mat32x4x4& operator*=(value_type k) { 
            for (std::size_t i = 0; i < 4; ++i)
                for (std::size_t j = 0; j < 4; ++j)
                    m_data[i][j] *= k;
            return *this;
        }
        basic_mat32x4x4& operator/=(value_type k) { 
            for (std::size_t i = 0; i < 4; ++i)
                for (std::size_t j = 0; j < 4; ++j)
                    m_data[i][j] /= k;
            return *this;
        }
        basic_mat32x4x4& operator*=(const basic_mat32x4x4& right) {
            basic_mat32x4x4 tmp;
            for (std::size_t i = 0; i < 4; ++i) {
                for (std::size_t j = 0; j < 4; ++j) {
                    Ty sum = 0;
                    for (std::size_t k = 0; k < 4; ++k)
                        sum += m_data[i][k] * right.m_data[k][j];
                    tmp.m_data[i][j] = sum;
                }
            }
            *this = tmp;
            return *this;
        }
        // basic_vec128 here can only use int or float.
        basic_vec128<Ty> operator*(const basic_vec128<Ty>& right) {
            auto* data = right.data();
            Ty d[4] = {
                data[0] * m_data[0][0] + data[1] * m_data[0][1] + data[2] * m_data[0][2] + data[3] * m_data[0][3],
                data[0] * m_data[1][0] + data[1] * m_data[1][1] + data[2] * m_data[1][2] + data[3] * m_data[1][3],
                data[0] * m_data[2][0] + data[1] * m_data[2][1] + data[2] * m_data[2][2] + data[3] * m_data[2][3],
                data[0] * m_data[3][0] + data[1] * m_data[3][1] + data[2] * m_data[3][2] + data[3] * m_data[3][3]
            };
            return basic_vec128<Ty>(d);
        }
#endif

        const Ty* data() const { return &m_data[0][0]; }
        virtual ~basic_mat32x4x4() = default;
    };

    template <typename Ty>
    [[nodiscard]] constexpr basic_mat32x4x4<Ty> operator+(const basic_mat32x4x4<Ty>& a, const basic_mat32x4x4<Ty>& b) {
        basic_mat32x4x4<Ty> tmp(a); tmp += b; return tmp;
    }
    template <typename Ty>
    [[nodiscard]] constexpr basic_mat32x4x4<Ty> operator-(const basic_mat32x4x4<Ty>& a, const basic_mat32x4x4<Ty>& b) {
        basic_mat32x4x4<Ty> tmp(a); tmp -= b; return tmp;
    }
    template <typename Ty>
    [[nodiscard]] constexpr basic_mat32x4x4<Ty> operator*(const basic_mat32x4x4<Ty>& a, Ty k) {
        basic_mat32x4x4<Ty> tmp(a); tmp *= k; return tmp;
    }
    template <typename Ty>
    [[nodiscard]] constexpr basic_mat32x4x4<Ty> operator/(const basic_mat32x4x4<Ty>& a, Ty k) {
        basic_mat32x4x4<Ty> tmp(a); tmp /= k; return tmp;
    }
    template <typename Ty>
    [[nodiscard]] constexpr basic_mat32x4x4<Ty> operator*(const basic_mat32x4x4<Ty>& a, const basic_mat32x4x4<Ty>& b) {
        basic_mat32x4x4<Ty> tmp(a); tmp *= b; return tmp;
    }
}